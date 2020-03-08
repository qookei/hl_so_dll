#pragma once

#include <stdint.h>
#include <stddef.h>

#include "util.hpp"

void register_fake_symbols();
uint32_t lookup_fake_symbol(const char *name);

//DLL_FAKE bool FAKE_TlsFree(uint32_t);
DLL_FAKE void FAKE_TlsAlloc();
DLL_FAKE void FAKE_HeapFree();
DLL_FAKE void FAKE_HeapAlloc();
DLL_FAKE void FAKE_InterlockedDecrement();
DLL_FAKE void FAKE_InterlockedIncrement();
DLL_FAKE void FAKE_GetCommandLineA();
DLL_FAKE void FAKE_GetVersion();
DLL_FAKE void FAKE_GetProcAddress();
DLL_FAKE void FAKE_GetModuleHandleA();
DLL_FAKE void FAKE_GetModuleFileNameA();
DLL_FAKE void FAKE_GetEnvironmentVariableA();
DLL_FAKE void FAKE_GetVersionExA();
DLL_FAKE void FAKE_HeapDestroy();
DLL_FAKE void FAKE_HeapCreate();
DLL_FAKE void FAKE_VirtualFree();
DLL_FAKE void FAKE_VirtualAlloc();
DLL_FAKE void FAKE_HeapReAlloc();
DLL_FAKE void FAKE_IsBadWritePtr();
DLL_FAKE void FAKE_InitializeCriticalSection();
DLL_FAKE void FAKE_DeleteCriticalSection();
DLL_FAKE void FAKE_EnterCriticalSection();
DLL_FAKE void FAKE_LeaveCriticalSection();
DLL_FAKE void FAKE_ExitProcess();
DLL_FAKE void FAKE_FatalAppExitA();
DLL_FAKE void FAKE_RtlUnwind();
DLL_FAKE void FAKE_GetLastError();
DLL_FAKE void FAKE_CloseHandle();
DLL_FAKE void FAKE_WriteFile();
DLL_FAKE void FAKE_Sleep();
DLL_FAKE void FAKE_WideCharToMultiByte();
DLL_FAKE void FAKE_MultiByteToWideChar();
DLL_FAKE void FAKE_LCMapStringA();
DLL_FAKE void FAKE_LCMapStringW();
DLL_FAKE void FAKE_GetStringTypeA();
DLL_FAKE void FAKE_GetStringTypeW();
DLL_FAKE void FAKE_GetCurrentThreadId();
DLL_FAKE void FAKE_TlsSetValue();
DLL_FAKE void FAKE_CreateDirectoryA();
DLL_FAKE void FAKE_TlsFree();
DLL_FAKE void FAKE_SetLastError();
DLL_FAKE void FAKE_TlsGetValue();
DLL_FAKE void FAKE_GetCurrentThread();
DLL_FAKE void FAKE_TerminateProcess();
DLL_FAKE void FAKE_GetCurrentProcess();
DLL_FAKE void FAKE_SetHandleCount();
DLL_FAKE void FAKE_GetStdHandle();
DLL_FAKE void FAKE_GetFileType();
DLL_FAKE void FAKE_GetStartupInfoA();
DLL_FAKE void FAKE_FreeEnvironmentStringsA();
DLL_FAKE void FAKE_FreeEnvironmentStringsW();
DLL_FAKE void FAKE_GetEnvironmentStrings();
DLL_FAKE void FAKE_GetEnvironmentStringsW();
DLL_FAKE void FAKE_SetFilePointer();
DLL_FAKE void FAKE_SetStdHandle();
DLL_FAKE void FAKE_FlushFileBuffers();
DLL_FAKE void FAKE_CreateFileA();
DLL_FAKE void FAKE_GetCPInfo();
DLL_FAKE void FAKE_IsValidLocale();
DLL_FAKE void FAKE_IsValidCodePage();
DLL_FAKE void FAKE_GetLocaleInfoA();
DLL_FAKE void FAKE_EnumSystemLocalesA();
DLL_FAKE void FAKE_GetUserDefaultLCID();
DLL_FAKE void FAKE_UnhandledExceptionFilter();
DLL_FAKE void FAKE_GetACP();
DLL_FAKE void FAKE_GetOEMCP();
DLL_FAKE void FAKE_LoadLibraryA();
DLL_FAKE void FAKE_SetConsoleCtrlHandler();
DLL_FAKE void FAKE_RaiseException();
DLL_FAKE void FAKE_ReadFile();
DLL_FAKE void FAKE_SetEndOfFile();
DLL_FAKE void FAKE_GetTimeZoneInformation();
DLL_FAKE void FAKE_GetLocaleInfoW();
DLL_FAKE void FAKE_CompareStringA();
DLL_FAKE void FAKE_CompareStringW();
DLL_FAKE void FAKE_SetEnvironmentVariableA();

