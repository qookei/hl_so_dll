__declspec(dllimport) __stdcall void TlsFree(unsigned int);

__declspec(dllexport) int foo(unsigned int d) {
	TlsFree(d);
	return 42;
}
