#pragma once

#ifdef DX_PLATFORM_WINDOWS
	#ifdef DX_BUILD_DLL
		#define DUNIX_API __declspec(dllexport)
	#else
		#define DUNIX_API __declspec(dllimport)
	#endif
#else 
	#error Dunix only supports Windows!
#endif