#pragma once

#include <memory>

#ifdef DX_PLATFORM_WINDOWS


#if DX_DYNAMIC_LINK
	#ifdef DX_BUILD_DLL
		#define DUNIX_API __declspec(dllexport)
	#else
		#define DUNIX_API __declspec(dllimport)
	#endif
#else
	#define DUNIX_API
#endif

#else 
	#error Dunix only supports Windows!
#endif

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T>
using WeakPtr = std::weak_ptr<T>;

template<typename T>
using UniquePtr = std::unique_ptr<T>;
