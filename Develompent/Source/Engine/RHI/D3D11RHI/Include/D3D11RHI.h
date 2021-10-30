/**
 * @file
 * @addtogroup D3D11RHI D3D11RHI
 *
 * Copyright BSOD-Games, All Rights Reserved.
 * Authors: Yehor Pohuliaka (zombiHello)
 */

#ifndef D3D11RHI_H
#define D3D11RHI_H

#include <d3d11.h>

#include "Misc/EngineGlobals.h"
#include "Render/BoundShaderStateCache.h"
#include "RHI/BaseRHI.h"

/**
 * @ingroup D3D11RHI
 * @brief Main class of DirectX 11
 */
class FD3D11RHI : public FBaseRHI
{
public:
	/**
	 * @brief Constructor
	 */
													FD3D11RHI();

	/**
	 * @brief Destructor
	 */
													~FD3D11RHI();

	/**
	 * @brief Initialize RHI
	 *
	 * @param[in] InIsEditor Is current application editor
	 */
	virtual void									Init( bool InIsEditor ) override;

	/**
	 * @brief Destroy RHI
	 */
	virtual void									Destroy() override;

	/**
	 * @brief Acquire thread ownership
	 */
	virtual void									AcquireThreadOwnership() override;

	/**
	 * @brief Release thread ownership
	 */
	virtual void									ReleaseThreadOwnership() override;

	/**
	 * @brief Create viewport
	 *
	 * @param[in] InWindowHandle OS handle on window
	 * @param[in] InWidth Width of viewport
	 * @param[in] InHeight Height of viewport
	 * @return Pointer on viewport
	 */
	virtual FViewportRHIRef							CreateViewport( void* InWindowHandle, uint32 InWidth, uint32 InHeight ) override;

	/**
	 * @brief Create vertex shader
	 *
	 * @param[in] InShaderName Shader name
	 * @param[in] InData Data to shader code
	 * @param[in] InSize Size of data
	 * @return Pointer to vertex shader
	 */
	virtual FVertexShaderRHIRef						CreateVertexShader( const tchar* InShaderName, const byte* InData, uint32 InSize ) override;

	/**
	 * @brief Create hull shader
	 *
	 * @param[in] InShaderName Shader name
	 * @param[in] InData Data to shader code
	 * @param[in] InSize Size of data
	 * @return Pointer to hull shader
	 */
	virtual FHullShaderRHIRef						CreateHullShader( const tchar* InShaderName, const byte* InData, uint32 InSize ) override;

	/**
	 * @brief Create domain shader
	 *
	 * @param[in] InShaderName Shader name
	 * @param[in] InData Data to shader code
	 * @param[in] InSize Size of data
	 * @return Pointer to domain shader
	 */
	virtual FDomainShaderRHIRef						CreateDomainShader( const tchar* InShaderName, const byte* InData, uint32 InSize ) override;

	/**
	 * @brief Create pixel shader
	 *
	 * @param[in] InShaderName Shader name
	 * @param[in] InData Data to shader code
	 * @param[in] InSize Size of data
	 * @return Pointer to pixel shader
	 */
	virtual FPixelShaderRHIRef						CreatePixelShader( const tchar* InShaderName, const byte* InData, uint32 InSize ) override;

	/**
	 * @brief Create geometry shader
	 *
	 * @param[in] InShaderName Shader name
	 * @param[in] InData Data to shader code
	 * @param[in] InSize Size of data
	 * @return Pointer to geometry shader
	 */
	virtual FGeometryShaderRHIRef					CreateGeometryShader( const tchar* InShaderName, const byte* InData, uint32 InSize ) override;

	/**
	 * @brief Create vertex buffer
	 *
	 * @param[in] InBufferName Buffer name
	 * @param[in] InSize Size buffer
	 * @param[in] InData Pointer to data
	 * @param[in] InUsage Usage flags
	 * @return Pointer to vertex buffer
	 */
	virtual FVertexBufferRHIRef						CreateVertexBuffer( const tchar* InBufferName, uint32 InSize, const byte* InData, uint32 InUsage ) override;

	/**
	 * @brief Create index buffer
	 *
	 * @param[in] InBufferName Buffer name
	 * @param[in] InStride Stride of struct
	 * @param[in] InSize Size buffer
	 * @param[in] InData Pointer to data
	 * @param[in] InUsage Usage flags
	 * @return Pointer to index buffer
	 */
	virtual FIndexBufferRHIRef						CreateIndexBuffer( const tchar* InBufferName, uint32 InStride, uint32 InSize, const byte* InData, uint32 InUsage ) override;

	/**
	 * @brief Create vertex declaration
	 *
	 * @param[in] InElementList Array of vertex elements
	 * @return Pointer to vertex declaration
	 */
	virtual FVertexDeclarationRHIRef				CreateVertexDeclaration( const FVertexDeclarationElementList& InElementList ) override;

	/**
	 * @brief Create bound shader state
	 *
	 * @param[in] InBoundShaderStateName Bound shader state name for debug
	 * @param[in] InVertexDeclaration Vertex declaration
	 * @param[in] InVertexShader Vertex shader
	 * @param[in] InPixelShader Pixel shader
	 * @param[in] InHullShader Hull shader
	 * @param[in] InDomainShader Domain shader
	 * @param[in] InGeometryShader Geometry shader
	 * @return Pointer to bound shader state
	 */
	virtual FBoundShaderStateRHIRef					CreateBoundShaderState( const tchar* InBoundShaderStateName, FVertexDeclarationRHIRef InVertexDeclaration, FVertexShaderRHIRef InVertexShader, FPixelShaderRHIRef InPixelShader, FHullShaderRHIRef InHullShader = nullptr, FDomainShaderRHIRef InDomainShader = nullptr, FGeometryShaderRHIRef InGeometryShader = nullptr ) override;

	/**
	 * @brief Create rasterizer state
	 *
	 * @param[in] InInitializer Initializer of rasterizer state
	 * @return Pointer to rasterizer state
	 */
	virtual FRasterizerStateRHIRef					CreateRasterizerState( const FRasterizerStateInitializerRHI& InInitializer ) override;

	/**
	 * @brief Create sampler state
	 *
	 * @param[in] InInitializer Initializer of sampler state
	 * @return Pointer to sampler state
	 */
	virtual FSamplerStateRHIRef						CreateSamplerState( const FSamplerStateInitializerRHI& InInitializer ) override;

	/**
	 * @brief Create texture 2D
	 *
	 * @param[in] InDebugName Debug name
	 * @param[in] InSizeX Width
	 * @param[in] InSizeY Height
	 * @param[in] InFormat Pixel format
	 * @param[in] InNumMips Count mips
	 * @param[in] InFlags Texture create flags (use ETextureCreateFlags)
	 * @param[in] InData Pointer to data texture
	 */
	virtual FTexture2DRHIRef						CreateTexture2D( const tchar* InDebugName, uint32 InSizeX, uint32 InSizeY, EPixelFormat InFormat, uint32 InNumMips, uint32 InFlags, void* InData = nullptr ) override;

	/**
	 * @brief Begin drawing viewport
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InViewport Viewport
	 */
	virtual void									BeginDrawingViewport( class FBaseDeviceContextRHI* InDeviceContext, class FBaseViewportRHI* InViewport ) override;

	/**
	 * @brief End drawing viewport
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InViewport Viewport
	 * @param[in] InIsPresent Whether to display the frame on the screen
	 * @param[in] InLockToVsync Is it necessary to block for Vsync
	 */
	virtual void									EndDrawingViewport( class FBaseDeviceContextRHI* InDeviceContext, class FBaseViewportRHI* InViewport, bool InIsPresent, bool InLockToVsync ) override;

#if WITH_EDITOR
	/**
	 * @brief Compile shader
	 *
	 * @param[in] InSourceFileName Path to source file of shader
	 * @param[in] InFunctionName Main function in shader
	 * @param[in] InFrequency Frequency of shader (Vertex, pixel, etc)
	 * @param[in] InEnvironment Environment of shader
	 * @param[out] InOutput Output data after compiling
	 * @param[in] InDebugDump Is need create debug dump of shader?
	 * @param[in] InShaderSubDir SubDir for debug dump
	 * @return Return true if compilation is succeed, else returning false
	 */
	virtual bool									CompileShader( const tchar* InSourceFileName, const tchar* InFunctionName, EShaderFrequency InFrequency, const FShaderCompilerEnvironment& InEnvironment, FShaderCompilerOutput& InOutput, bool InDebugDump = false, const tchar* InShaderSubDir = TEXT( "" ) ) override;
#endif // WITH_EDITOR

#if WITH_IMGUI
	/**
	 * @brief Initialize render of ImGUI
	 *
	 * @param[in] InDeviceContext Device context
	 */
	virtual void								InitImGUI( class FBaseDeviceContextRHI* InDeviceContext ) override;

	/**
	 * @brief Shutdown render of ImGUI
	 *
	 * @param[in] InDeviceContext Device context
	 */
	virtual void								ShutdownImGUI( class FBaseDeviceContextRHI* InDeviceContext ) override;

	/**
	 * @brief Draw ImGUI
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InImGUIDrawData Pointer to draw data of ImGUI
	 */
	virtual void								DrawImGUI( class FBaseDeviceContextRHI* InDeviceContext, struct ImDrawData* InImGUIDrawData ) override;
#endif // WITH_IMGUI

	/**
	 * @brief Set viewport
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InMinX Min x
	 * @param[in] InMinY Min y
	 * @param[in] InMinZ Min z
	 * @param[in] InMaxX Max x
	 * @param[in] InMaxY Max y
	 * @param[in] InMaxZ Max z
	 */
	virtual void									SetViewport( class FBaseDeviceContextRHI* InDeviceContext, uint32 InMinX, uint32 InMinY, float InMinZ, uint32 InMaxX, uint32 InMaxY, float InMaxZ ) override;

	/**
	 * @brief Set bound shader state
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InBoundShaderState Bound shader state
	 */
	virtual void									SetBoundShaderState( class FBaseDeviceContextRHI* InDeviceContext, FBoundShaderStateRHIParamRef InBoundShaderState ) override;

	/**
	 * @brief Set stream source
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InStreamIndex Stream index
	 * @param[in] InVertexBuffer Vertex buffer
	 * @param[in] InStride Stride
	 * @param[in] InOffset Offset
	 */
	virtual void									SetStreamSource( class FBaseDeviceContextRHI* InDeviceContext, uint32 InStreamIndex, FVertexBufferRHIParamRef InVertexBuffer, uint32 InStride, uint32 InOffset ) override;

	/**
	 * @brief Set rasterizer state
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InNewState New rasterizer state
	 */
	virtual void									SetRasterizerState( class FBaseDeviceContextRHI* InDeviceContext, FRasterizerStateRHIParamRef InNewState ) override;

	/**
	 * @brief Set sampler state
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InPixelShader Pointer to pixel shader
	 * @param[in] InNewState New sampler state
	 * @param[in] InStateIndex Slot for bind sampler
	 */
	virtual void									SetSamplerState( class FBaseDeviceContextRHI* InDeviceContext, FPixelShaderRHIParamRef InPixelShader, FSamplerStateRHIParamRef InNewState, uint32 InStateIndex ) override;

	/**
	 * Set texture parameter in pixel shader
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InPixelShader Pointer to pixel shader
	 * @param[in] InTexture Pointer to texture
	 * @param[in] InTextureIndex Slot for bind texture
	 */
	virtual void									SetTextureParameter( class FBaseDeviceContextRHI* InDeviceContext, FPixelShaderRHIParamRef InPixelShader, FTextureRHIParamRef InTexture, uint32 InTextureIndex ) override;

	/**
	 * Set shader parameter in vertex shader
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InVertexShader Pointer to vertex shader
	 * @param[in] InBufferIndex Buffer index
	 * @param[in] InBaseIndex Offset value in buffer
	 * @param[in] InNumBytes Size value in bytes
	 * @param[in] InNewValue Pointer to value
	 */
	//virtual void									SetShaderParameter( class FBaseDeviceContextRHI* InDeviceContext, FVertexShaderRHIParamRef InVertexShader, uint32 InBufferIndex, uint32 InBaseIndex, uint32 InNumBytes, const void* InNewValue ) override;

	/**
	 * Set shader parameter in pixel shader
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InPixelShader Pointer to pixel shader
	 * @param[in] InBufferIndex Buffer index
	 * @param[in] InBaseIndex Offset value in buffer
	 * @param[in] InNumBytes Size value in bytes
	 * @param[in] InNewValue Pointer to value
	 */
	virtual void									SetShaderParameter( class FBaseDeviceContextRHI* InDeviceContext, FPixelShaderRHIParamRef InPixelShader, uint32 InBufferIndex, uint32 InBaseIndex, uint32 InNumBytes, const void* InNewValue ) override;

	/**
	 * Set view parameters
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InSceneView Scene view
	 */
	virtual void									SetViewParameters( class FBaseDeviceContextRHI* InDeviceContext, class FSceneView& InSceneView ) override;

	/**
	 * @brief Lock vertex buffer
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InVertexBuffer Pointer to vertex buffer
	 * @param[in] InSize Size
	 * @param[in] InOffset Offset in buffer
	 * @param[out] OutLockedData Locked data in buffer
	 */
	virtual void									LockVertexBuffer( class FBaseDeviceContextRHI* InDeviceContext, const FVertexBufferRHIRef InVertexBuffer, uint32 InSize, uint32 InOffset, FLockedData& OutLockedData ) override;

	/**
	 * @brief Unlock vertex buffer
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InVertexBuffer Pointer to vertex buffer
	 * @param[in] InLockedData Locked data in buffer
	 */
	virtual void									UnlockVertexBuffer( class FBaseDeviceContextRHI* InDeviceContext, const FVertexBufferRHIRef InVertexBuffer, FLockedData& InLockedData ) override;

	/**
	 * @brief Lock index buffer
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InIndexBuffer Pointer to index buffer
	 * @param[in] InSize Size
	 * @param[in] InOffset Offset in buffer
	 * @param[out] OutLockedData Locked data in buffer
	 */
	virtual void									LockIndexBuffer( class FBaseDeviceContextRHI* InDeviceContext, const FIndexBufferRHIRef InIndexBuffer, uint32 InSize, uint32 InOffset, FLockedData& OutLockedData ) override;

	/**
	 * @brief Unlock index buffer
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InIndexBuffer Pointer to index buffer
	 * @param[in] InLockedData Locked data in buffer
	 */
	virtual void									UnlockIndexBuffer( class FBaseDeviceContextRHI* InDeviceContext, const FIndexBufferRHIRef InIndexBuffer, FLockedData& InLockedData ) override;

	/**
	 * @brief Lock texture 2D
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InTexture Pointer to texture 2D
	 * @param[in] InMipIndex Mip index
	 * @param[in] InIsDataWrite Is begin written to texture
	 * @param[out] OutLockedData Locked data in texture
	 * @param[in] InIsUseCPUShadow Is use CPU shadow
	 */
	virtual void									LockTexture2D( class FBaseDeviceContextRHI* InDeviceContext, FTexture2DRHIParamRef InTexture, uint32 InMipIndex, bool InIsDataWrite, FLockedData& OutLockedData, bool InIsUseCPUShadow = false ) override;

	/**
	 * @brief Unlock texture 2D
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InTexture Pointer to texture 2D
	 * @param[in] InMipIndex Mip index
	 * @param[in] InLockedData Locked data in texture
	 */
	virtual void									UnlockTexture2D( class FBaseDeviceContextRHI* InDeviceContext, FTexture2DRHIParamRef InTexture, uint32 InMipIndex, FLockedData& InLockedData ) override;

	/**
	 * @brief Draw primitive
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InPrimitiveType Primitive type
	 * @param[in] InBaseVertexIndex Base vertex index
	 * @param[in] InNumPrimitives Number primitives for render
	 */
	virtual void									DrawPrimitive( class FBaseDeviceContextRHI* InDeviceContext, EPrimitiveType InPrimitiveType, uint32 InBaseVertexIndex, uint32 InNumPrimitives ) override;

	/**
	 * @brief Is initialized RHI
	 * @return Return true if RHI is initialized, else false
	 */
	virtual bool									IsInitialize() const override;

	/**
	 * @brief Get RHI name
	 * @return Return RHI name
	 */
	virtual const tchar*							GetRHIName() const override;

	/**
	 * @brief Get device context
	 * @return Pointer to device context
	 */
	virtual class FBaseDeviceContextRHI*			GetImmediateContext() const override;

	/**
	 * @brief Get D3D11 device
	 * @return Pointer to D3D11 device
	 */
	FORCEINLINE ID3D11Device*						GetD3D11Device() const
	{
		return d3d11Device;
	}

	/**
	 * @brief Get DXGI factory
	 * @return Pointer to DXGI factory
	 */
	FORCEINLINE IDXGIFactory*						GetDXGIFactory() const
	{
		return dxgiFactory;
	}

	/**
	 * @brief Get DXGI adapter
	 * @return Pointer to DXGI adapter
	 */
	FORCEINLINE IDXGIAdapter*						GetDXGIAdapter() const
	{
		return dxgiAdapter;
	}

	/**
	 * @brief Get bound shader state history
	 * @return Reference to bound shader state history
	 */
	FORCEINLINE FBoundShaderStateHistory&			GetBoundShaderStateHistory()
	{
		return boundShaderStateHistory;
	}

private:
	bool							isInitialize;				/**< Is RHI is initialized */
	class FD3D11ConstantBuffer*		globalConstantBuffer;		/**< Global constant buffer */
	class FD3D11DeviceContext*		immediateContext;			/**< Immediate context */
	FBoundShaderStateHistory		boundShaderStateHistory;	/**< History of using bound shader states */

	ID3D11Device*					d3d11Device;				/**< D3D11 Device */
	IDXGIFactory*					dxgiFactory;				/**< DXGI factory */
	IDXGIAdapter*					dxgiAdapter;				/**< DXGI adapter */
};

/**
 * @brief Set debug name fore DirectX 11 resource
 * 
 * @param[in] InObject Object of D3D11
 * @param[in] InName Debug name of resource
 */
void				D3D11SetDebugName( ID3D11DeviceChild* InObject, const achar* InName );

/**
 * @brief Set debug name fore DirectX 11 resource
 *
 * @param[in] InObject Object of D3D11
 * @param[in] InName Debug name of resource
 */
void				D3D11SetDebugName( IDXGIObject* InObject, const achar* InName );

#endif // !D3D11RHI_H
