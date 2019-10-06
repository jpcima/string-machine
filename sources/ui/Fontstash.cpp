#ifdef _WIN32
#include <windows.h>
#endif

// disable an avalanche of "unused function" warnings
#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

#define FONTSTASH_IMPLEMENTATION
#include <fontstash.h>
