#pragma once

#ifdef DX_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include <iostream>
#include <algorithm>
#include <memory>
#include <utility>
#include <functional>
#include <cstdint>

#include <string>
#include <sstream>

#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Dunix/Core/Log.h"

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T>
using WeakPtr = std::weak_ptr<T>;

template<typename T>
using UniquePtr = std::unique_ptr<T>;