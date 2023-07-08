#pragma once

#if defined _WIN32 || defined __CYGWIN__
#  define AdelDennaouiController_DLLIMPORT __declspec(dllimport)
#  define AdelDennaouiController_DLLEXPORT __declspec(dllexport)
#  define AdelDennaouiController_DLLLOCAL
#else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#    define AdelDennaouiController_DLLIMPORT __attribute__((visibility("default")))
#    define AdelDennaouiController_DLLEXPORT __attribute__((visibility("default")))
#    define AdelDennaouiController_DLLLOCAL __attribute__((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#    define AdelDennaouiController_DLLIMPORT
#    define AdelDennaouiController_DLLEXPORT
#    define AdelDennaouiController_DLLLOCAL
#  endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef AdelDennaouiController_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define AdelDennaouiController_DLLAPI
#  define AdelDennaouiController_LOCAL
#else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef AdelDennaouiController_EXPORTS
#    define AdelDennaouiController_DLLAPI AdelDennaouiController_DLLEXPORT
#  else
#    define AdelDennaouiController_DLLAPI AdelDennaouiController_DLLIMPORT
#  endif // AdelDennaouiController_EXPORTS
#  define AdelDennaouiController_LOCAL AdelDennaouiController_DLLLOCAL
#endif // AdelDennaouiController_STATIC