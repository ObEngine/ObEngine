#include <cppnet/platform.hpp>

#if defined(CPPNET_PLATFORM_WINDOWS)

#include <win32/socket_impl.hpp>

#else

#include <unix/socket_impl.hpp>

#endif