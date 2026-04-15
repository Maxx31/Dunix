#pragma once

#include "ProfileScope.h"

#define DX_PROFILE(name) Dunix::ProfileScope profileScope##__LINE__(name)
#define PROFILE_FUNCTION() DX_PROFILE(__FUNCTION__)