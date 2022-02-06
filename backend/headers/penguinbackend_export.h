#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__) // Windows anything
#if defined(_WIN64) // Windows 64-bit

#ifndef PENGUINBACKEND_EXPORT_H
#define PENGUINBACKEND_EXPORT_H

#ifdef PENGUINBACKEND_STATIC_DEFINE
#  define PENGUINBACKEND_EXPORT
#  define PENGUINBACKEND_NO_EXPORT
#else
#  ifndef PENGUINBACKEND_EXPORT
#    ifdef penguinbackend_EXPORTS
        /* We are building this library */
#      define PENGUINBACKEND_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define PENGUINBACKEND_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef PENGUINBACKEND_NO_EXPORT
#    define PENGUINBACKEND_NO_EXPORT 
#  endif
#endif

#ifndef PENGUINBACKEND_DEPRECATED
#  define PENGUINBACKEND_DEPRECATED __declspec(deprecated)
#endif

#ifndef PENGUINBACKEND_DEPRECATED_EXPORT
#  define PENGUINBACKEND_DEPRECATED_EXPORT PENGUINBACKEND_EXPORT PENGUINBACKEND_DEPRECATED
#endif

#ifndef PENGUINBACKEND_DEPRECATED_NO_EXPORT
#  define PENGUINBACKEND_DEPRECATED_NO_EXPORT PENGUINBACKEND_NO_EXPORT PENGUINBACKEND_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PENGUINBACKEND_NO_DEPRECATED
#    define PENGUINBACKEND_NO_DEPRECATED
#  endif
#endif

#endif /* PENGUINBACKEND_EXPORT_H */
#else // Windows 32-bit

#ifndef PENGUINBACKEND_EXPORT_H
#define PENGUINBACKEND_EXPORT_H

#ifdef PENGUINBACKEND_STATIC_DEFINE
#  define PENGUINBACKEND_EXPORT
#  define PENGUINBACKEND_NO_EXPORT
#else
#  ifndef PENGUINBACKEND_EXPORT
#    ifdef penguinbackend_EXPORTS
        /* We are building this library */
#      define PENGUINBACKEND_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define PENGUINBACKEND_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef PENGUINBACKEND_NO_EXPORT
#    define PENGUINBACKEND_NO_EXPORT 
#  endif
#endif

#ifndef PENGUINBACKEND_DEPRECATED
#  define PENGUINBACKEND_DEPRECATED __declspec(deprecated)
#endif

#ifndef PENGUINBACKEND_DEPRECATED_EXPORT
#  define PENGUINBACKEND_DEPRECATED_EXPORT PENGUINBACKEND_EXPORT PENGUINBACKEND_DEPRECATED
#endif

#ifndef PENGUINBACKEND_DEPRECATED_NO_EXPORT
#  define PENGUINBACKEND_DEPRECATED_NO_EXPORT PENGUINBACKEND_NO_EXPORT PENGUINBACKEND_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PENGUINBACKEND_NO_DEPRECATED
#    define PENGUINBACKEND_NO_DEPRECATED
#  endif
#endif

#endif /* PENGUINBACKEND_EXPORT_H */
#endif // End of windows
#elif defined(__APPLE__) // Mac OS

#ifndef PENGUINBACKEND_EXPORT_H
#define PENGUINBACKEND_EXPORT_H

#ifdef PENGUINBACKEND_STATIC_DEFINE
#  define PENGUINBACKEND_EXPORT
#  define PENGUINBACKEND_NO_EXPORT
#else
#  ifndef PENGUINBACKEND_EXPORT
#    ifdef penguinbackend_EXPORTS
        /* We are building this library */
#      define PENGUINBACKEND_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define PENGUINBACKEND_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef PENGUINBACKEND_NO_EXPORT
#    define PENGUINBACKEND_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef PENGUINBACKEND_DEPRECATED
#  define PENGUINBACKEND_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef PENGUINBACKEND_DEPRECATED_EXPORT
#  define PENGUINBACKEND_DEPRECATED_EXPORT PENGUINBACKEND_EXPORT PENGUINBACKEND_DEPRECATED
#endif

#ifndef PENGUINBACKEND_DEPRECATED_NO_EXPORT
#  define PENGUINBACKEND_DEPRECATED_NO_EXPORT PENGUINBACKEND_NO_EXPORT PENGUINBACKEND_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PENGUINBACKEND_NO_DEPRECATED
#    define PENGUINBACKEND_NO_DEPRECATED
#  endif
#endif

#endif /* PENGUINBACKEND_EXPORT_H */
#else // Linux

#ifndef PENGUINBACKEND_EXPORT_H
#define PENGUINBACKEND_EXPORT_H

#ifdef PENGUINBACKEND_STATIC_DEFINE
#  define PENGUINBACKEND_EXPORT
#  define PENGUINBACKEND_NO_EXPORT
#else
#  ifndef PENGUINBACKEND_EXPORT
#    ifdef penguinbackend_EXPORTS
        /* We are building this library */
#      define PENGUINBACKEND_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define PENGUINBACKEND_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef PENGUINBACKEND_NO_EXPORT
#    define PENGUINBACKEND_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef PENGUINBACKEND_DEPRECATED
#  define PENGUINBACKEND_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef PENGUINBACKEND_DEPRECATED_EXPORT
#  define PENGUINBACKEND_DEPRECATED_EXPORT PENGUINBACKEND_EXPORT PENGUINBACKEND_DEPRECATED
#endif

#ifndef PENGUINBACKEND_DEPRECATED_NO_EXPORT
#  define PENGUINBACKEND_DEPRECATED_NO_EXPORT PENGUINBACKEND_NO_EXPORT PENGUINBACKEND_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PENGUINBACKEND_NO_DEPRECATED
#    define PENGUINBACKEND_NO_DEPRECATED
#  endif
#endif

#endif /* PENGUINBACKEND_EXPORT_H */
#endif // End
