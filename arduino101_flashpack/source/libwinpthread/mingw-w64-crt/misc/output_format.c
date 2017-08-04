#include <windows.h>
#include <stdio.h>
#include <msvcrt.h>

static unsigned int last_value = 0;
typedef unsigned int (*f_get_output_format)(void);
typedef unsigned int (*f_set_output_format)(unsigned int);

static unsigned int init_set_output_format(unsigned int);
f_set_output_format __MINGW_IMP_SYMBOL(_set_output_format) = init_set_output_format;

static unsigned int fake_set_output_format(unsigned int value)
{
    return InterlockedExchange((LONG*)&last_value, value);
}

static unsigned int init_set_output_format(unsigned int format)
{
  f_set_output_format sof;

  sof = (f_set_output_format) GetProcAddress (__mingw_get_msvcrt_handle(), "_set_output_format");
  if(!sof)
      sof = fake_set_output_format;

  return (__MINGW_IMP_SYMBOL(_set_output_format) = sof)(format);
}


static unsigned int init_get_output_format(void);
f_get_output_format __MINGW_IMP_SYMBOL(_get_output_format) = init_get_output_format;

static unsigned int fake_get_output_format(void)
{
    return last_value;
}

static unsigned int init_get_output_format(void)
{
  f_get_output_format gof;

  gof = (f_get_output_format) GetProcAddress (__mingw_get_msvcrt_handle(), "_get_output_format");
  if(!gof)
      gof = fake_get_output_format;

  return (__MINGW_IMP_SYMBOL(_get_output_format) = gof)();
}
