#pragma once
#define COMMA ,
#ifdef OBE_IS_NOT_PLUGIN
#define GLOBE(INDEX, NAME, TYPE, ...) inline TYPE NAME{__VA_ARGS__}; inline Types::Global<INDEX, TYPE> NAME ## _GLOB(&NAME);
#define GLOBE_GET(NAME) &NAME
#else
#define GLOBE(INDEX, NAME, TYPE, ...) inline TYPE* NAME ## _PTR = nullptr; inline TYPE& NAME = *NAME ## _PTR; inline Types::Global<INDEX, TYPE> NAME ## _GLOB(NAME ## _PTR);
#define GLOBE_GET(NAME) &NAME ## _PTR
#endif