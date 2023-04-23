#pragma once

#include <cppnet/platform.hpp>

#if defined(CPPNET_PLATFORM_WINDOWS)
#include <basetsd.h>
#endif

namespace cppnet
{
////////////////////////////////////////////////////////////
// Define the low-level socket handle type, specific to
// each platform
////////////////////////////////////////////////////////////
#if defined(CPPNET_PLATFORM_WINDOWS)

using SocketHandle = UINT_PTR;

#else

using SocketHandle = int;

#endif

} // namespace cppnet
