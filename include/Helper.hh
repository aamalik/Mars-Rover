#ifndef _HELPER_HH
#define _HELPER_HH

#include <stdio.h>

/**
 * DEBUG HANDLER
 */

#ifdef DEBUG
  #define _debug_(args, ...) printf(args, ##__VA_ARGS__)
#else
  #define _debug_(args, ...)
#endif

#ifdef DEEPDEBUG
  #define _deep_debug_(args, ...) printf(args, ##__VA_ARGS__)
#else
  #define _deep_debug_(args, ...)
#endif

#endif