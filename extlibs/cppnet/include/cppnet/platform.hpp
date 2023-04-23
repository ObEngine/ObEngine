#pragma once

////////////////////////////////////////////////////////////
// Identify the operating system
// see https://sourceforge.net/p/predef/wiki/Home/
////////////////////////////////////////////////////////////
#if defined(_WIN32)

// Windows
#define CPPNET_PLATFORM_WINDOWS
#ifndef NOMINMAX
#define NOMINMAX
#endif

#elif defined(__APPLE__) && defined(__MACH__)

// Apple platform, see which one it is
#include "TargetConditionals.h"

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

// iOS
#define CPPNET_PLATFORM_IOS

#elif TARGET_OS_MAC

// MacOS
#define CPPNET_PLATFORM_MACOS

#else

// Unsupported Apple system
#error This Apple operating system is not supported by CppNet library

#endif

#elif defined(__unix__)

// UNIX system, see which one it is
#if defined(__ANDROID__)

// Android
#define CPPNET_PLATFORM_ANDROID

#elif defined(__linux__)

// Linux
#define CPPNET_PLATFORM_LINUX

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

// FreeBSD
#define CPPNET_PLATFORM_FREEBSD

#elif defined(__OpenBSD__)

// OpenBSD
#define CPPNET_PLATFORM_OPENBSD

#elif defined(__NetBSD__)

// NetBSD
#define CPPNET_PLATFORM_NETBSD

#else

// Unsupported UNIX system
#error This UNIX operating system is not supported by CppNet library

#endif

#else

// Unsupported system
#error This operating system is not supported by CppNet library

#endif
