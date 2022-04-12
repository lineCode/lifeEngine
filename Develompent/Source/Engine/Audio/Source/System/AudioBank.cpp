#include <vorbis/vorbisfile.h>
#include <vorbis/vorbisenc.h>
#include <ogg/ogg.h>

#include "Misc/AudioGlobals.h"
#include "Misc/CoreGlobals.h"
#include "System/BaseFileSystem.h"
#include "System/AudioBufferManager.h"
#include "Logger/LoggerMacros.h"
#include "System/AudioBank.h"

/**
 * Struct of info about OGG file in archive
 */
struct FArchiveOGGRawData
{
	FArchive*	archive;		/**< Archive */
	uint64		beginOffset;	/**< Begin of raw data in archive */	
	uint64		endOffset;		/**< Offset to end of raw data in archive */
};

/**
 * Struct of OGG parser from archive
 */
struct FAudioBankOGG
{
	/**
	 * Constructor
	 */
	FAudioBankOGG()
		: vorbisInfo( nullptr )
		, sampleOffset( 0 )
	{}

	OggVorbis_File		oggVorbisFile;		/**< Ogg/Vorbis file parser */
	vorbis_info*		vorbisInfo;			/**< Vorbis info */
	FAudioBankInfo		info;				/**< Info about bank */
	uint64				sampleOffset;		/**< Sample offset */
};

/**
 * Read bytes in OGG file from archive
 */
size_t Archive_ReadOgg( void* InDst, size_t InSize1, size_t InSize2, void* InUser )
{
	FArchiveOGGRawData*		rawDataInfo		= ( FArchiveOGGRawData* )InUser;
	size_t					size			= InSize1 * InSize2;
	uint64					currentOffset	= rawDataInfo->archive->Tell();

	// Trim the number of bytes to read if we've reached the end of the file
	if ( currentOffset + size > rawDataInfo->endOffset )
	{
		size = rawDataInfo->endOffset - currentOffset;
	}

	if ( size > 0 )
	{
		rawDataInfo->archive->Serialize( InDst, size );
	}
	return size;
}

/**
 * Seek bytes in OGG file in archive
 */
int Archive_SeekOgg( void* InUser, ogg_int64_t InTo, int InType )
{
	FArchiveOGGRawData*		rawDataInfo		= ( FArchiveOGGRawData* )InUser;
	uint64					currentOffset	= rawDataInfo->archive->Tell();
	
	switch ( InType )
	{
	case SEEK_CUR:		currentOffset += InTo;								break;
	case SEEK_END:		currentOffset = rawDataInfo->endOffset - InTo;		break;
	case SEEK_SET:		currentOffset = rawDataInfo->beginOffset + InTo;	break;
	default:			return -1;
	}

	int		result = 0;
	if ( currentOffset < rawDataInfo->beginOffset )
	{
		currentOffset = rawDataInfo->beginOffset;
		result = -1;
	}

	if ( currentOffset > rawDataInfo->endOffset )
	{
		currentOffset = rawDataInfo->endOffset;
		result = -1;
	}

	rawDataInfo->archive->Seek( currentOffset );
	return result;
}

/**
 * Close OGG file in archive
 */
int Archive_CloseOgg( void* InUser )
{
	FArchiveOGGRawData*		rawDataInfo = ( FArchiveOGGRawData* )InUser;
	delete rawDataInfo->archive;
	delete rawDataInfo;
	return 0;
}

/**
 * Tell OGG file in archive
 */
long Archive_TellOgg( void* InUser )
{
	FArchiveOGGRawData*		rawDataInfo = ( FArchiveOGGRawData* )InUser;
	uint64					currentOffset = rawDataInfo->archive->Tell();
	return currentOffset - rawDataInfo->beginOffset;
}

FAudioBank::FAudioBank()
	: FAsset( AT_AudioBank )
	, offsetToRawData( -1 )
	, rawDataSize( 0 )
{}

FAudioBank::~FAudioBank()
{
	if ( audioBuffer )
	{
		GAudioBufferManager.Remove( this );
	}
}

void FAudioBank::Serialize( class FArchive& InArchive )
{
	FAsset::Serialize( InArchive );
	InArchive << rawDataSize;

	if ( InArchive.IsLoading() && rawDataSize > 0 )
	{	
		offsetToRawData		= InArchive.Tell();
		pathToArchive		= InArchive.GetPath();
		InArchive.Seek( offsetToRawData + rawDataSize );
	}
#if WITH_EDITOR
	else if ( rawDataSize > 0 )
	{
		InArchive.Serialize( rawData.data(), rawDataSize );
	}
#endif // WITH_EDITOR
}

FAudioBankHandle FAudioBank::OpenBank( FAudioBankInfo& OutBankInfo )
{
	// If bank is empty - we exit from method
	if ( IsEmpty() )
	{
		return nullptr;
	}
	check( offsetToRawData != -1 );

	// Init callback for read OGG/Vorbis from raw data
	ov_callbacks				ovCallbacks;
	ovCallbacks.read_func		= Archive_ReadOgg;
	ovCallbacks.seek_func		= Archive_SeekOgg;
	ovCallbacks.close_func		= Archive_CloseOgg;
	ovCallbacks.tell_func		= Archive_TellOgg;

	// Init descriptor for read OGG/Vorbis from memory
	FArchiveOGGRawData*			oggRawDataDesc = new FArchiveOGGRawData();
	oggRawDataDesc->archive		= GFileSystem->CreateFileReader( pathToArchive );
	oggRawDataDesc->beginOffset	= offsetToRawData;
	oggRawDataDesc->endOffset	= offsetToRawData + rawDataSize;

	// If failed open archive - we set 'error' to OV_FALSE
	FAudioBankOGG*		audioBankOgg = nullptr;
	int32				error = 0;
	if ( !oggRawDataDesc->archive )
	{
		error = OV_FALSE;
	}
	else
	{
		audioBankOgg = new FAudioBankOGG();
		oggRawDataDesc->archive->Seek( offsetToRawData );
		error = ov_open_callbacks( oggRawDataDesc, &audioBankOgg->oggVorbisFile, nullptr, -1, ovCallbacks );
	}
			
	if ( error < 0 )
	{
		std::wstring				strError = TEXT( "unknow error" );
		switch ( error )
		{
		case OV_FALSE:				strError = TEXT( "not found" );															break;
		case OV_EREAD:				strError = TEXT( "a read from media returned an error" );								break;
		case OV_ENOTVORBIS:			strError = TEXT( "bitstream does not contain any Vorbis data" );						break;
		case OV_EVERSION:			strError = TEXT( "vorbis version mismatch" );											break;
		case OV_EBADHEADER:			strError = TEXT( "invalid Vorbis bitstream header" );									break;
		case OV_EFAULT:				strError = TEXT( "internal logic fault; indicates a bug or heap/stack corruption" );	break;
		}

		delete oggRawDataDesc;
		if ( audioBankOgg )
		{
			delete audioBankOgg;
		}
		
		LE_LOG( LT_Warning, LC_Audio, TEXT( "Failed loading bank: %s" ), strError.c_str() );
		return nullptr;
	}

	// Getting info about bank
	audioBankOgg->vorbisInfo = ov_info( &audioBankOgg->oggVorbisFile, -1 );
	check( audioBankOgg->vorbisInfo );

	OutBankInfo.numChannels = audioBankOgg->vorbisInfo->channels;
	OutBankInfo.format		= audioBankOgg->vorbisInfo->channels == 1 ? SF_Mono16 : SF_Stereo16;
	OutBankInfo.rate		= audioBankOgg->vorbisInfo->rate;
	OutBankInfo.numSamples	= ov_pcm_total( &audioBankOgg->oggVorbisFile, -1 ) * audioBankOgg->vorbisInfo->channels * 2;
	audioBankOgg->info		= OutBankInfo;
	return audioBankOgg;
}

void FAudioBank::CloseBank( FAudioBankHandle InBankHandle )
{
	if ( !InBankHandle )
	{
		return;
	}

	FAudioBankOGG*		audioBankOgg = ( FAudioBankOGG* )InBankHandle;
	vorbis_info_clear( audioBankOgg->vorbisInfo );
	ov_clear( &audioBankOgg->oggVorbisFile );
	delete audioBankOgg;
}

uint64 FAudioBank::ReadBankPCM( FAudioBankHandle InBankHandle, byte* InSamples, uint64 InMaxSize )
{
	check( InBankHandle && InSamples );
	FAudioBankOGG*		audioBankOgg = ( FAudioBankOGG* )InBankHandle;

	// Try to read the requested number of samples, stop only on error or end of file
	uint64			size = 0;
	while ( size < InMaxSize )
	{
		uint64			bytesToRead = ( InMaxSize - size ) * sizeof( byte );
		long			bytesRead = ov_read( &audioBankOgg->oggVorbisFile, ( char* )InSamples, bytesToRead, 0, 2, 1, nullptr );
		
		if ( bytesRead > 0 )
		{
			long		samplesRead		= bytesRead / sizeof( byte );
			size						+= samplesRead;
			InSamples					+= samplesRead;
			audioBankOgg->sampleOffset	+= samplesRead;
		}

		// Error or end of file
		else
		{		
			size = 0;

			// If less 0 - this is error
			if ( bytesToRead < 0 )
			{
				appErrorf( TEXT( "Failed read from bank. Vorbisfile error code: 0x%X" ), bytesToRead );
			}
			break;
		}
	}

	return size;
}

void FAudioBank::SeekBankPCM( FAudioBankHandle InBankHandle, uint64 InSampleOffset )
{
	check( InBankHandle );
	FAudioBankOGG*		audioBankOgg = ( FAudioBankOGG* )InBankHandle;
	ov_pcm_seek( &audioBankOgg->oggVorbisFile, InSampleOffset / audioBankOgg->info.numChannels );
	audioBankOgg->sampleOffset = InSampleOffset;
}

uint64 FAudioBank::GetOffsetBankPCM( FAudioBankHandle InBankHandle ) const
{
	check( InBankHandle );
	FAudioBankOGG*		audioBankOgg = ( FAudioBankOGG* )InBankHandle;
	return audioBankOgg->sampleOffset;
}

#if WITH_EDITOR
void FAudioBank::SetSourceOGGFile( const std::wstring& InPath )
{
	// Read raw data of Ogg/Vorbis file
	FArchive*		archive = GFileSystem->CreateFileReader( InPath.c_str() );
	if ( !archive )
	{
		LE_LOG( LT_Warning, LC_Audio, TEXT( "Failed open archive '%s'" ), InPath.c_str() );
		return;
	}

	// Serialize audio bank to memory
	offsetToRawData		= 0;
	pathToArchive		= InPath;
	rawDataSize			= archive->GetSize();

	rawData.resize( rawDataSize );
	if ( rawDataSize > 0 )
	{
		archive->Serialize( rawData.data(), rawDataSize );
	}
	else
	{
		LE_LOG( LT_Warning, LC_Audio, TEXT( "Archive '%s' is empty" ), InPath.c_str() );
	}

	delete archive;
}
#endif // WITH_EDITOR

FAudioBufferRef FAudioBank::GetAudioBuffer()
{
	if ( audioBuffer )
	{
		return audioBuffer;
	}

	audioBuffer = GAudioBufferManager.Find( this );
	return audioBuffer;
}