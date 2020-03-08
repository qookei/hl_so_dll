#include "fake_kernel32.hpp"
#include "util.hpp"
#include <iostream>

static symbol_map _fake_kernel32_symbols;

#define STR_(x) #x
#define STR(x) STR_(x)

#define ADD_FAKE(name) _fake_kernel32_symbols[STR(name)] = (uint32_t)&FAKE_##name;

void register_fake_symbols() {
	ADD_FAKE(TlsAlloc);
	ADD_FAKE(HeapFree);
	ADD_FAKE(HeapAlloc);
	ADD_FAKE(InterlockedDecrement);
	ADD_FAKE(InterlockedIncrement);
	ADD_FAKE(GetCommandLineA);
	ADD_FAKE(GetVersion);
	ADD_FAKE(GetProcAddress);
	ADD_FAKE(GetModuleHandleA);
	ADD_FAKE(GetModuleFileNameA);
	ADD_FAKE(GetEnvironmentVariableA);
	ADD_FAKE(GetVersionExA);
	ADD_FAKE(HeapDestroy);
	ADD_FAKE(HeapCreate);
	ADD_FAKE(VirtualFree);
	ADD_FAKE(VirtualAlloc);
	ADD_FAKE(HeapReAlloc);
	ADD_FAKE(IsBadWritePtr);
	ADD_FAKE(InitializeCriticalSection);
	ADD_FAKE(DeleteCriticalSection);
	ADD_FAKE(EnterCriticalSection);
	ADD_FAKE(LeaveCriticalSection);
	ADD_FAKE(ExitProcess);
	ADD_FAKE(FatalAppExitA);
	ADD_FAKE(RtlUnwind);
	ADD_FAKE(GetLastError);
	ADD_FAKE(CloseHandle);
	ADD_FAKE(WriteFile);
	ADD_FAKE(Sleep);
	ADD_FAKE(WideCharToMultiByte);
	ADD_FAKE(MultiByteToWideChar);
	ADD_FAKE(LCMapStringA);
	ADD_FAKE(LCMapStringW);
	ADD_FAKE(GetStringTypeA);
	ADD_FAKE(GetStringTypeW);
	ADD_FAKE(GetCurrentThreadId);
	ADD_FAKE(TlsSetValue);
	ADD_FAKE(CreateDirectoryA);
	ADD_FAKE(TlsFree);
	ADD_FAKE(SetLastError);
	ADD_FAKE(TlsGetValue);
	ADD_FAKE(GetCurrentThread);
	ADD_FAKE(TerminateProcess);
	ADD_FAKE(GetCurrentProcess);
	ADD_FAKE(SetHandleCount);
	ADD_FAKE(GetStdHandle);
	ADD_FAKE(GetFileType);
	ADD_FAKE(GetStartupInfoA);
	ADD_FAKE(FreeEnvironmentStringsA);
	ADD_FAKE(FreeEnvironmentStringsW);
	ADD_FAKE(GetEnvironmentStrings);
	ADD_FAKE(GetEnvironmentStringsW);
	ADD_FAKE(SetFilePointer);
	ADD_FAKE(SetStdHandle);
	ADD_FAKE(FlushFileBuffers);
	ADD_FAKE(CreateFileA);
	ADD_FAKE(GetCPInfo);
	ADD_FAKE(IsValidLocale);
	ADD_FAKE(IsValidCodePage);
	ADD_FAKE(GetLocaleInfoA);
	ADD_FAKE(EnumSystemLocalesA);
	ADD_FAKE(GetUserDefaultLCID);
	ADD_FAKE(UnhandledExceptionFilter);
	ADD_FAKE(GetACP);
	ADD_FAKE(GetOEMCP);
	ADD_FAKE(LoadLibraryA);
	ADD_FAKE(SetConsoleCtrlHandler);
	ADD_FAKE(RaiseException);
	ADD_FAKE(ReadFile);
	ADD_FAKE(SetEndOfFile);
	ADD_FAKE(GetTimeZoneInformation);
	ADD_FAKE(GetLocaleInfoW);
	ADD_FAKE(CompareStringA);
	ADD_FAKE(CompareStringW);
	ADD_FAKE(SetEnvironmentVariableA);
}

uint32_t lookup_fake_symbol(const char *name) {
	if (!_fake_kernel32_symbols.size())
		register_fake_symbols();

	auto ptr = _fake_kernel32_symbols[name];
	if (!ptr) {
#ifdef FAKE_KERNEL32_NO_ABORT
		return 0;
#endif
		fprintf(stderr, "lookup_fake_symbol(): '%s' is not implemented\n", name);
		abort();
	}

	return ptr;
}

// --------------------------------------------------------------------

DLL_FAKE void FAKE_TlsAlloc(){fprintf(stderr, "FAKE_TlsAlloc(): called\n");}
DLL_FAKE void FAKE_HeapFree(){fprintf(stderr, "FAKE_HeapFree(): called\n");}
DLL_FAKE void FAKE_HeapAlloc(){fprintf(stderr, "FAKE_HeapAlloc(): called\n");}
DLL_FAKE void FAKE_InterlockedDecrement(){fprintf(stderr, "FAKE_InterlockedDecrement(): called\n");}
DLL_FAKE void FAKE_InterlockedIncrement(){fprintf(stderr, "FAKE_InterlockedIncrement(): called\n");}
DLL_FAKE void FAKE_GetCommandLineA(){fprintf(stderr, "FAKE_GetCommandLineA(): called\n");}
DLL_FAKE void FAKE_GetVersion(){fprintf(stderr, "FAKE_GetVersion(): called\n");}
DLL_FAKE void FAKE_GetProcAddress(){fprintf(stderr, "FAKE_GetProcAddress(): called\n");}
DLL_FAKE void FAKE_GetModuleHandleA(){fprintf(stderr, "FAKE_GetModuleHandleA(): called\n");}
DLL_FAKE void FAKE_GetModuleFileNameA(){fprintf(stderr, "FAKE_GetModuleFileNameA(): called\n");}
DLL_FAKE void FAKE_GetEnvironmentVariableA(){fprintf(stderr, "FAKE_GetEnvironmentVariableA(): called\n");}
DLL_FAKE void FAKE_GetVersionExA(){fprintf(stderr, "FAKE_GetVersionExA(): called\n");}
DLL_FAKE void FAKE_HeapDestroy(){fprintf(stderr, "FAKE_HeapDestroy(): called\n");}
DLL_FAKE void FAKE_HeapCreate(){fprintf(stderr, "FAKE_HeapCreate(): called\n");}
DLL_FAKE void FAKE_VirtualFree(){fprintf(stderr, "FAKE_VirtualFree(): called\n");}
DLL_FAKE void FAKE_VirtualAlloc(){fprintf(stderr, "FAKE_VirtualAlloc(): called\n");}
DLL_FAKE void FAKE_HeapReAlloc(){fprintf(stderr, "FAKE_HeapReAlloc(): called\n");}
DLL_FAKE void FAKE_IsBadWritePtr(){fprintf(stderr, "FAKE_IsBadWritePtr(): called\n");}
DLL_FAKE void FAKE_InitializeCriticalSection(){fprintf(stderr, "FAKE_InitializeCriticalSection(): called\n");}
DLL_FAKE void FAKE_DeleteCriticalSection(){fprintf(stderr, "FAKE_DeleteCriticalSection(): called\n");}
DLL_FAKE void FAKE_EnterCriticalSection(){fprintf(stderr, "FAKE_EnterCriticalSection(): called\n");}
DLL_FAKE void FAKE_LeaveCriticalSection(){fprintf(stderr, "FAKE_LeaveCriticalSection(): called\n");}
DLL_FAKE void FAKE_ExitProcess(){fprintf(stderr, "FAKE_ExitProcess(): called\n");}
DLL_FAKE void FAKE_FatalAppExitA(){fprintf(stderr, "FAKE_FatalAppExitA(): called\n");}
DLL_FAKE void FAKE_RtlUnwind(){fprintf(stderr, "FAKE_RtlUnwind(): called\n");}
DLL_FAKE void FAKE_GetLastError(){fprintf(stderr, "FAKE_GetLastError(): called\n");}
DLL_FAKE void FAKE_CloseHandle(){fprintf(stderr, "FAKE_CloseHandle(): called\n");}
DLL_FAKE void FAKE_WriteFile(){fprintf(stderr, "FAKE_WriteFile(): called\n");}
DLL_FAKE void FAKE_Sleep(){fprintf(stderr, "FAKE_Sleep(): called\n");}
DLL_FAKE void FAKE_WideCharToMultiByte(){fprintf(stderr, "FAKE_WideCharToMultiByte(): called\n");}
DLL_FAKE void FAKE_MultiByteToWideChar(){fprintf(stderr, "FAKE_MultiByteToWideChar(): called\n");}
DLL_FAKE void FAKE_LCMapStringA(){fprintf(stderr, "FAKE_LCMapStringA(): called\n");}
DLL_FAKE void FAKE_LCMapStringW(){fprintf(stderr, "FAKE_LCMapStringW(): called\n");}
DLL_FAKE void FAKE_GetStringTypeA(){fprintf(stderr, "FAKE_GetStringTypeA(): called\n");}
DLL_FAKE void FAKE_GetStringTypeW(){fprintf(stderr, "FAKE_GetStringTypeW(): called\n");}
DLL_FAKE void FAKE_GetCurrentThreadId(){fprintf(stderr, "FAKE_GetCurrentThreadId(): called\n");}
DLL_FAKE void FAKE_TlsSetValue(){fprintf(stderr, "FAKE_TlsSetValue(): called\n");}
DLL_FAKE void FAKE_CreateDirectoryA(){fprintf(stderr, "FAKE_CreateDirectoryA(): called\n");}
DLL_FAKE void FAKE_TlsFree(){fprintf(stderr, "FAKE_TlsFree(): called\n");}
DLL_FAKE void FAKE_SetLastError(){fprintf(stderr, "FAKE_SetLastError(): called\n");}
DLL_FAKE void FAKE_TlsGetValue(){fprintf(stderr, "FAKE_TlsGetValue(): called\n");}
DLL_FAKE void FAKE_GetCurrentThread(){fprintf(stderr, "FAKE_GetCurrentThread(): called\n");}
DLL_FAKE void FAKE_TerminateProcess(){fprintf(stderr, "FAKE_TerminateProcess(): called\n");}
DLL_FAKE void FAKE_GetCurrentProcess(){fprintf(stderr, "FAKE_GetCurrentProcess(): called\n");}
DLL_FAKE void FAKE_SetHandleCount(){fprintf(stderr, "FAKE_SetHandleCount(): called\n");}
DLL_FAKE void FAKE_GetStdHandle(){fprintf(stderr, "FAKE_GetStdHandle(): called\n");}
DLL_FAKE void FAKE_GetFileType(){fprintf(stderr, "FAKE_GetFileType(): called\n");}
DLL_FAKE void FAKE_GetStartupInfoA(){fprintf(stderr, "FAKE_GetStartupInfoA(): called\n");}
DLL_FAKE void FAKE_FreeEnvironmentStringsA(){fprintf(stderr, "FAKE_FreeEnvironmentStringsA(): called\n");}
DLL_FAKE void FAKE_FreeEnvironmentStringsW(){fprintf(stderr, "FAKE_FreeEnvironmentStringsW(): called\n");}
DLL_FAKE void FAKE_GetEnvironmentStrings(){fprintf(stderr, "FAKE_GetEnvironmentStrings(): called\n");}
DLL_FAKE void FAKE_GetEnvironmentStringsW(){fprintf(stderr, "FAKE_GetEnvironmentStringsW(): called\n");}
DLL_FAKE void FAKE_SetFilePointer(){fprintf(stderr, "FAKE_SetFilePointer(): called\n");}
DLL_FAKE void FAKE_SetStdHandle(){fprintf(stderr, "FAKE_SetStdHandle(): called\n");}
DLL_FAKE void FAKE_FlushFileBuffers(){fprintf(stderr, "FAKE_FlushFileBuffers(): called\n");}
DLL_FAKE void FAKE_CreateFileA(){fprintf(stderr, "FAKE_CreateFileA(): called\n");}
DLL_FAKE void FAKE_GetCPInfo(){fprintf(stderr, "FAKE_GetCPInfo(): called\n");}
DLL_FAKE void FAKE_IsValidLocale(){fprintf(stderr, "FAKE_IsValidLocale(): called\n");}
DLL_FAKE void FAKE_IsValidCodePage(){fprintf(stderr, "FAKE_IsValidCodePage(): called\n");}
DLL_FAKE void FAKE_GetLocaleInfoA(){fprintf(stderr, "FAKE_GetLocaleInfoA(): called\n");}
DLL_FAKE void FAKE_EnumSystemLocalesA(){fprintf(stderr, "FAKE_EnumSystemLocalesA(): called\n");}
DLL_FAKE void FAKE_GetUserDefaultLCID(){fprintf(stderr, "FAKE_GetUserDefaultLCID(): called\n");}
DLL_FAKE void FAKE_UnhandledExceptionFilter(){fprintf(stderr, "FAKE_UnhandledExceptionFilter(): called\n");}
DLL_FAKE void FAKE_GetACP(){fprintf(stderr, "FAKE_GetACP(): called\n");}
DLL_FAKE void FAKE_GetOEMCP(){fprintf(stderr, "FAKE_GetOEMCP(): called\n");}
DLL_FAKE void FAKE_LoadLibraryA(){fprintf(stderr, "FAKE_LoadLibraryA(): called\n");}
DLL_FAKE void FAKE_SetConsoleCtrlHandler(){fprintf(stderr, "FAKE_SetConsoleCtrlHandler(): called\n");}
DLL_FAKE void FAKE_RaiseException(){fprintf(stderr, "FAKE_RaiseException(): called\n");}
DLL_FAKE void FAKE_ReadFile(){fprintf(stderr, "FAKE_ReadFile(): called\n");}
DLL_FAKE void FAKE_SetEndOfFile(){fprintf(stderr, "FAKE_SetEndOfFile(): called\n");}
DLL_FAKE void FAKE_GetTimeZoneInformation(){fprintf(stderr, "FAKE_GetTimeZoneInformation(): called\n");}
DLL_FAKE void FAKE_GetLocaleInfoW(){fprintf(stderr, "FAKE_GetLocaleInfoW(): called\n");}
DLL_FAKE void FAKE_CompareStringA(){fprintf(stderr, "FAKE_CompareStringA(): called\n");}
DLL_FAKE void FAKE_CompareStringW(){fprintf(stderr, "FAKE_CompareStringW(): called\n");}
DLL_FAKE void FAKE_SetEnvironmentVariableA(){fprintf(stderr, "FAKE_SetEnvironmentVariableA(): called\n");}


//DLL_FAKE bool FAKE_TlsFree(uint32_t tls_index) {
//	fprintf(stderr, "FAKE_TlsFree(): called with %u\n", tls_index);

//	return true;
//}
