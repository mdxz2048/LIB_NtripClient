#ifndef __LIB_MDXZ_NTRIPCLIENT_TEST__H_
#define __LIB_MDXZ_NTRIPCLIENT_TEST__H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "mdxz_types.h"

#define ARG_SHORT_OPTS "dhvM:s:r:u:p:m:n:"


typedef enum {
    NO_ARGUMENT       = 0,
    REQUIRED_ARGUMENT = 1,
    OPTIONAL_ARGUMENT = 2,
}OPTION_FLAG_e;

typedef struct 
{
  const CHAR *name;
  /* has_arg can't be an enum because some compilers complain about
     type mismatches in all the code that assumes it is an int.  */
  OPTION_FLAG_e has_arg;
  INT32 *flag;
  INT32 val;
}OPTION_t;


typedef struct 
{
  MDXZ_DEV_STATUS_e print_version_flag;
  MDXZ_DEV_STATUS_e print_help_flag;
  MDXZ_DEV_STATUS_e cfg_rtk_flag;
  MDXZ_DEV_STATUS_e debug_flag;
  rtkServer_c srv_info;
  char * cfg_gga;
}ARGS_t;


#ifdef __cplusplus
}

#endif

#endif