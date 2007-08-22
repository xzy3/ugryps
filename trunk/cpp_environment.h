#ifndef CPP_ENVIRONMENT_H
#define CPP_ENVIRONMENT_H

void* __dso_handle = & __dso_handle;

extern "C" void __cxa_atexit(void (*arg1)(void*), void* arg2, void* arg3) { }

extern "C" void __cxa_pure_virtual(void) { }
#endif
