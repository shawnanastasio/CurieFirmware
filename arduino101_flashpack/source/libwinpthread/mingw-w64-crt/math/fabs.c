/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#define __CRT__NO_INLINE
#include <math.h>

double
fabs (double x)
{
#ifdef __x86_64__
  return __builtin_fabs (x);
#else
  double res = 0.0;

  asm ("fabs;" : "=t" (res) : "0" (x));
  return res;
#endif
}
