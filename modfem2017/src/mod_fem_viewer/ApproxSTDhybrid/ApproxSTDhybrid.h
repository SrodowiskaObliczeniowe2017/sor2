#ifndef _APPROX_STDH_H_
#define _APPROX_STDH_H_

#include "../ApproxModule/ApproxManager.h"
#include "../include/fv_config.h"

#ifdef _WIN32
#  ifdef ApproxSTDhybrid_EXPORTS
#    define DLL_MAPPING  __declspec(dllexport)
#  else
#    define DLL_MAPPING  __declspec(dllimport)
#  endif
#else 
#  define DLL_MAPPING 
#endif

#ifdef _WIN32
    #define APR_API __stdcall
#else
    #define APR_API
#endif







#endif /* _APPROX_DG_H_
*/
