/**
 * @file
 * @addtogroup Engine Engine
 *
 * Copyright BSOD-Games, All Rights Reserved.
 * Authors: Yehor Pohuliaka (zombiHello)
 */

#ifndef BASERHI_H
#define BASERHI_H

#include "Misc/Types.h"
#include "Render/Shaders/ShaderCompiler.h"
#include "TypesRHI.h"

/**
 * @ingroup Engine
 * @brief Enumeration of primitive types
 */
enum EPrimitiveType
{
	PT_PointList,			/**< Points */
	PT_TriangleList,		/**< Triangles */
	PT_TriangleStrip,		/**< Triangles strip */
	PT_LineList,			/**< Lines */
	PT_Num					/**< Count primitives */
};

/**
 * @ingroup Engine
 * @brief Enumeration of types fill mode
 */
enum ERasterizerFillMode
{
	FM_Point,			/**< Point */
	FM_Wireframe,		/**< Wireframe */
	FM_Solid			/**< Solid */
};

/**
 * @ingroup Engine
 * @brief Enumeration of types cull mode
 */
enum ERasterizerCullMode
{
	CM_None,				/**< Cull mode is disabled */
	CM_NoneReversed,		/**< In this mode enabled front counter clockwise */
	CM_CW,					/**< Cull back */
	CM_CCW					/**< Cull front */
};

/**
 * @ingroup Engine
 * @brief Structc for create resterize state in RHI
 */
struct FRasterizerStateInitializerRHI
{
	ERasterizerFillMode			fillMode;				/**< Fill mode */
	ERasterizerCullMode			cullMode;				/**< Cull mode */
	float						depthBias;				/**< Depth bias */
	float						slopeScaleDepthBias;	/**< Slope scale depth bias */
	bool						isAllowMSAA;			/**< Is allow MSAA */
};

/**
 * @ingroup Engine
 * @brief Base class of resterize state
 */
class FBaseRasterizerStateRHI : public FRefCounted
{
public:
	/**
	 * @brief Destructor
	 */
	virtual ~FBaseRasterizerStateRHI()
	{}
};

/**
 * @ingroup Engine
 * @brief Base class of RHI
 */
class FBaseRHI
{
public:
	/**
	 * @brief Destructor
	 */
	virtual										~FBaseRHI() {}

	/**
	 * @brief Initialize RHI
	 * 
	 * @param[in] InIsEditor Is current application editor
	 */
	virtual void								Init( bool InIsEditor )	{}

	/**
	 * @brief Destroy RHI
	 */
	virtual void								Destroy() {}

	/**
	 * @brief Acquire thread ownership
	 */
	virtual void								AcquireThreadOwnership() {}

	/**
	 * @brief Release thread ownership
	 */
	virtual void								ReleaseThreadOwnership() {}

	/**
	 * @brief Create viewport
	 * 
	 * @param[in] InWindowHandle OS handle on window
	 * @param[in] InWidth Width of viewport
	 * @param[in] InHeight Height of viewport
	 * @return Pointer on viewport
	 */
	virtual class FBaseViewportRHI*				CreateViewport( void* InWindowHandle, uint32 InWidth, uint32 InHeight )								{ return nullptr; }

	/**
	 * @brief Create vertex shader
	 * 
	 * @param[in] InShaderName Shader name
	 * @param[in] InData Data to shader code
	 * @param[in] InSize Size of data
	 * @return Pointer to vertex shader
	 */
	virtual FVertexShaderRHIRef					CreateVertexShader( const tchar* InShaderName, const byte* InData, uint32 InSize )					{ return nullptr; }

	/**
	 * @brief Create hull shader
	 *
	 * @param[in] InShaderName Shader name
	 * @param[in] InData Data to shader code
	 * @param[in] InSize Size of data
	 * @return Pointer to hull shader
	 */
	virtual FHullShaderRHIRef					CreateHullShader( const tchar* InShaderName, const byte* InData, uint32 InSize )					{ return nullptr; }

	/**
	 * @brief Create domain shader
	 *
	 * @param[in] InShaderName Shader name
	 * @param[in] InData Data to shader code
	 * @param[in] InSize Size of data
	 * @return Pointer to domain shader
	 */
	virtual FDomainShaderRHIRef					CreateDomainShader( const tchar* InShaderName, const byte* InData, uint32 InSize )					{ return nullptr; }

	/**
	 * @brief Create pixel shader
	 *
	 * @param[in] InShaderName Shader name
	 * @param[in] InData Data to shader code
	 * @param[in] InSize Size of data
	 * @return Pointer to pixel shader
	 */
	virtual FPixelShaderRHIRef					CreatePixelShader( const tchar* InShaderName, const byte* InData, uint32 InSize )					{ return nullptr; }

	/**
	 * @brief Create geometry shader
	 *
	 * @param[in] InShaderName Shader name
	 * @param[in] InData Data to shader code
	 * @param[in] InSize Size of data
	 * @return Pointer to geometry shader
	 */
	virtual FGeometryShaderRHIRef				CreateGeometryShader( const tchar* InShaderName, const byte* InData, uint32 InSize )				{ return nullptr; }

	/**
	 * @brief Create vertex buffer
	 * 
	 * @param[in] InBufferName Buffer name
	 * @param[in] InSize Size buffer
	 * @param[in] InData Pointer to data
	 * @param[in] InUsage Usage flags
	 * @return Pointer to vertex buffer
	 */
	virtual FVertexBufferRHIRef					CreateVertexBuffer( const tchar* InBufferName, uint32 InSize, const byte* InData, uint32 InUsage )	{ return nullptr; }

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
	virtual FIndexBufferRHIRef					CreateIndexBuffer( const tchar* InBufferName, uint32 InStride, uint32 InSize, const byte* InData, uint32 InUsage )	{ return nullptr; }

	/**
	 * @brief Create vertex declaration
	 * 
	 * @param[in] InElementList Array of vertex elements
	 * @return Pointer to vertex declaration
	 */
	virtual FVertexDeclarationRHIRef			CreateVertexDeclaration( const FVertexDeclarationElementList& InElementList ) { return nullptr; }

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
	virtual FBoundShaderStateRHIRef				CreateBoundShaderState( const tchar* InBoundShaderStateName, FVertexDeclarationRHIRef InVertexDeclaration, FVertexShaderRHIRef InVertexShader, FPixelShaderRHIRef InPixelShader, FHullShaderRHIRef InHullShader = nullptr, FDomainShaderRHIRef InDomainShader = nullptr, FGeometryShaderRHIRef InGeometryShader = nullptr ) { return nullptr; }

	/**
	 * @brief Create rasterizer state
	 * 
	 * @param[in] InInitializer Initializer of rasterizer state
	 * @return Pointer to rasterizer state
	 */
	virtual FRasterizerStateRHIRef				CreateRasterizerState( const FRasterizerStateInitializerRHI& InInitializer ) { return nullptr; }

	/**
	 * @brief Begin drawing viewport
	 * 
	 * @param[in] InDeviceContext Device context
	 * @param[in] InViewport Viewport
	 */
	virtual void								BeginDrawingViewport( class FBaseDeviceContextRHI* InDeviceContext, class FBaseViewportRHI* InViewport ) {}

	/**
	 * @brief End drawing viewport
	 * 
	 * @param[in] InDeviceContext Device context
	 * @param[in] InViewport Viewport
	 * @param[in] InIsPresent Whether to display the frame on the screen
	 * @param[in] InLockToVsync Is it necessary to block for Vsync
	 */
	virtual void								EndDrawingViewport( class FBaseDeviceContextRHI* InDeviceContext, class FBaseViewportRHI* InViewport, bool InIsPresent, bool InLockToVsync ) {}

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
	virtual bool								CompileShader( const tchar* InSourceFileName, const tchar* InFunctionName, EShaderFrequency InFrequency, const FShaderCompilerEnvironment& InEnvironment, FShaderCompilerOutput& InOutput, bool InDebugDump = false, const tchar* InShaderSubDir = TEXT( "" ) )			{ return false; }

	/**
	 * @brief Initialize render of ImGUI
	 * 
	 * @param[in] InDeviceContext Device context
	 */
	virtual void								InitImGUI( class FBaseDeviceContextRHI* InDeviceContext ){}

	/**
	 * @brief Shutdown render of ImGUI
	 * 
	 * @param[in] InDeviceContext Device context
	 */
	virtual void								ShutdownImGUI( class FBaseDeviceContextRHI* InDeviceContext ){}

	/**
	 * @brief Draw ImGUI
	 * 
	 * @param[in] InDeviceContext Device context
	 * @param[in] InImGUIDrawData Pointer to draw data of ImGUI
	 */
	virtual void								DrawImGUI( class FBaseDeviceContextRHI* InDeviceContext, struct ImDrawData* InImGUIDrawData ){}
#endif // WITH_EDITOR

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
	virtual void								SetViewport( class FBaseDeviceContextRHI* InDeviceContext, uint32 InMinX, uint32 InMinY, float InMinZ, uint32 InMaxX, uint32 InMaxY, float InMaxZ ) {}

	/**
	 * @brief Set bound shader state
	 * 
	 * @param[in] InDeviceContext Device context
	 * @param[in] InBoundShaderState Bound shader state
	 */
	virtual void								SetBoundShaderState( class FBaseDeviceContextRHI* InDeviceContext, FBoundShaderStateRHIParamRef InBoundShaderState ) {}

	/**
	 * @brief Set stream source
	 * 
	 * @param[in] InDeviceContext Device context
	 * @param[in] InStreamIndex Stream index
	 * @param[in] InVertexBuffer Vertex buffer
	 * @param[in] InStride Stride
	 * @param[in] InOffset Offset
	 */
	virtual void								SetStreamSource( class FBaseDeviceContextRHI* InDeviceContext, uint32 InStreamIndex, FVertexBufferRHIParamRef InVertexBuffer, uint32 InStride, uint32 InOffset ) {}

	/**
	 * @brief Set rasterizer state
	 * 
	 * @param[in] InDeviceContext Device context
	 * @param[in] InNewState New rasterizer state
	 */
	virtual void								SetRasterizerState( class FBaseDeviceContextRHI* InDeviceContext, FRasterizerStateRHIParamRef InNewState ) {}

	/**
	 * @brief Lock vertex buffer
	 * 
	 * @param[in] InDeviceContext Device context
	 * @param[in] InVertexBuffer Pointer to vertex buffer
	 * @param[in] InSize Size
	 * @param[in] InOffset Offset in buffer
	 * @param[out] OutLockedData Locked data in buffer	 
	 */
	virtual void								LockVertexBuffer( class FBaseDeviceContextRHI* InDeviceContext, const FVertexBufferRHIRef InVertexBuffer, uint32 InSize, uint32 InOffset, FLockedData& OutLockedData ) {}

	/**
	 * @brief Unlock vertex buffer
	 * 
	 * @param[in] InDeviceContext Device context
	 * @param[in] InVertexBuffer Pointer to vertex buffer
	 * @param[in] InLockedData Locked data in buffer
	 */
	virtual void								UnlockVertexBuffer( class FBaseDeviceContextRHI* InDeviceContext, const FVertexBufferRHIRef InVertexBuffer, FLockedData& InLockedData ) {}

	/**
	 * @brief Lock index buffer
	 * 
	 * @param[in] InDeviceContext Device context
	 * @param[in] InIndexBuffer Pointer to index buffer
	 * @param[in] InSize Size
	 * @param[in] InOffset Offset in buffer
	 * @param[out] OutLockedData Locked data in buffer
	 */
	virtual void								LockIndexBuffer( class FBaseDeviceContextRHI* InDeviceContext, const FIndexBufferRHIRef InIndexBuffer, uint32 InSize, uint32 InOffset, FLockedData& OutLockedData ) {}

	/**
	 * @brief Unlock index buffer
	 *
	 * @param[in] InDeviceContext Device context
	 * @param[in] InIndexBuffer Pointer to index buffer
	 * @param[in] InLockedData Locked data in buffer
	 */
	virtual void								UnlockIndexBuffer( class FBaseDeviceContextRHI* InDeviceContext, const FIndexBufferRHIRef InIndexBuffer, FLockedData& InLockedData ) {}

	/**
	 * @brief Draw primitive
	 * 
	 * @param[in] InDeviceContext Device context
	 * @param[in] InPrimitiveType Primitive type
	 * @param[in] InBaseVertexIndex Base vertex index
	 * @param[in] InNumPrimitives Number primitives for render
	 */
	virtual void								DrawPrimitive( class FBaseDeviceContextRHI* InDeviceContext, EPrimitiveType InPrimitiveType, uint32 InBaseVertexIndex, uint32 InNumPrimitives ) {}

	/**
	 * @brief Is initialized RHI
	 * @return Return true if RHI is initialized, else false
	 */
	virtual bool								IsInitialize() const			{ return false; }

	/**
	 * @brief Get RHI name
	 * @return Return RHI name
	 */
	virtual const tchar*						GetRHIName() const				{ return TEXT( "NullRHI" ); }

	/**
	 * @brief Get device context
	 * @return Pointer to device context
	 */
	virtual class FBaseDeviceContextRHI*		GetImmediateContext() const		{ return nullptr; }
};

#endif // !BASERHI_H
