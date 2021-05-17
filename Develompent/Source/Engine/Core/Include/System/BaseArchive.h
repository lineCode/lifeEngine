/**
 * @file
 * @addtogroup Core Core
 *
 * Copyright BSOD-Games, All Rights Reserved.
 * Authors: Yehor Pohuliaka (zombiHello)
 */

#ifndef BASEARCHIVE_H
#define BASEARCHIVE_H

#include "Core.h"
#include "Misc/Types.h"

/**
 * @ingroup Core
 * @brief The base class for work with file
 */
class FBaseArchive
{
public:
	/**
	 * @brief Destructor
	 */
	virtual					~FBaseArchive() {}

	/**
	 * @brief Serialize data
	 * 
	 * @param[in] InBuffer Pointer to buffer for serialize
	 * @param[in] InSize Size of buffer
	 */
	virtual void			Serialize( void* InBuffer, uint32 InSize ) {}

	/**
	 * @brief Get current position in archive
	 * @return Current position in archive
	 */
	virtual uint32			Tell() { return 0; };

	/**
	 * @brief Set current position in archive
	 * 
	 * @param[in] InPosition New position in archive
	 */
	virtual void			Seek( uint32 InPosition ) {}

	/**
	 * @brief Flush data
	 */
	virtual void			Flush() {}

	/**
	 * @brief Is saving archive
	 * @return True if archive saving, false if archive loading
	 */
	virtual bool			IsSaving() const { return false; }

	/**
	 * @breif Is loading archive
	 * @return True if archive loading, false if archive saving
	 */
	virtual bool			IsLoading() const { return false; }

	/**
	 * @brief Get size of archive
	 * @return Size of archive
	 */
	virtual uint32			GetSize() { return 0; }
};

//
// Overloaded operators for serialize in archive
//

/**
 * @brief Overload operator << for serialize TCHAR string
 */
FORCEINLINE FBaseArchive&		operator<<( FBaseArchive& InArchive, tchar* InStringC )
{
	InArchive.Serialize( InStringC, ( uint32 )wcslen( InStringC ) * 2 );
	return InArchive;
}

/**
 * @brief Overload operator << for serialize ANSI string
 */
FORCEINLINE FBaseArchive&		operator<<( FBaseArchive& InArchive, achar* InStringC )
{
	InArchive.Serialize( InStringC, ( uint32 )strlen( InStringC ) );
	return InArchive;
}

#endif // !BASEARCHIVE_H
