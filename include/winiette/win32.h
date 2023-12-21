#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_WIN32_H_
#define WINIETTE_INCLUDE_WINIETTE_WIN32_H_

#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>

#define STDCXX_17_OR_HIGHER (__cplusplus >= 201703L || _MSVC_LANG >= 201703L)

#endif  // WINIETTE_INCLUDE_WINIETTE_WIN32_H_
