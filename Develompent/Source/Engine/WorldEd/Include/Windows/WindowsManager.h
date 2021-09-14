/**
 * @file
 * @addtogroup WorldEd World editor
 *
 * Copyright BSOD-Games, All Rights Reserved.
 * Authors: Yehor Pohuliaka (zombiHello)
 */

#ifndef WORLDED_WINDOWSMANAGER_H
#define WORLDED_WINDOWSMANAGER_H

#include <vector>

#include "Misc/WorldEdTypes.h"
#include "Windows/BaseWindow.h"

/**
 * @ingroup WorldEd
 * Class for control of windows in world editor
 */
class FWindowsManager
{
public:
	/**
	 * Add window
	 * 
	 * @param[in] InWindow Window
	 */
	FORCEINLINE void Add( FWBaseWindowParamRef InWindow )
	{
		windows.push_back( InWindow );
	}

	/**
	 * Remove window
	 * 
	 * @param[in] InWindow Window
	 */
	void Remove( FWBaseWindowParamRef InWindow );

	/**
	 * Remove all windows
	 */
	FORCEINLINE void RemoveAll()
	{
		windows.clear();
	}

	/**
	 * Update all windows
	 */
	void Tick();

private:
	std::vector< FWBaseWindowRef >			windows;	/**< Array of opened windows */
};

#endif // !WORLDED_WINDOWSMANAGER_H