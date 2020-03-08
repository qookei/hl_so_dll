import fileinput, requests, subprocess

from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection

import pefile

excluded = ['_init', '_fini']

def demangle_msvc(names):
    params = (
            ('input', names),
            )
    resp = requests.post('http://demangler.com/raw', data={'input': names})#params=params)
    return resp.content.decode('utf-8').split('\n')

def demangle_gcc(names):
    args = ['c++filt']
    args.extend(names)
    pipe = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    stdout, _ = pipe.communicate()
    demangled = stdout.decode('utf-8').split('\n')

    return demangled[:-1]


def comma_separate(l):
    return ', '.join(l)

def emit_stdcall_stub(so_name, dll_name, return_type, args_types, args_with_types, args_names):
    print(f'extern "C" {return_type} {so_name}({comma_separate(args_with_types)}) {{')
    print('\tabort();')
    print(f'\tprintf("{so_name}(): reached stdcall stub function\\n");')
    print(f'\tvoid *func = func_open("{so_name}", "{dll_name}");')
    print('\tif (!func) {')
    print(f'\t\tprintf("{so_name}(): failed to load desired function in either hl.so or hl.dll\\n");')
    print('\t\tabort();')
    print('\t}')
    print(f'\treturn (({return_type}(STDCALL*)({comma_separate(args_types)}))func)({comma_separate(args_names)});')
    print('}\n')

def emit_cdecl_stub(so_name, dll_name, return_type, args_types, args_with_types, args_names):
    print(f'extern "C" {return_type} {so_name}({comma_separate(args_with_types)}) {{')
    print('\tabort();')
    print(f'\tprintf("{so_name}(): reached cdecl stub function\\n");')
    print(f'\tvoid *func = func_open("{so_name}", "{dll_name}");')
    print('\tif (!func) {')
    print(f'\t\tprintf("{so_name}(): failed to load desired function in either hl.so or hl.dll\\n");')
    print('\t\tabort();')
    print('\t}')
    print(f'\treturn (({return_type}(*)({comma_separate(args_types)}))func)({comma_separate(args_names)});')
    print('}\n')

def emit_thiscall_stub(so_name, dll_name, return_type, args_types, args_with_types, args_names):
    print(f'extern "C" {return_type} {so_name}({comma_separate(["void *this__"] + args_with_types)}) {{')
    print('\tabort();')
    print(f'\tprintf("{so_name}(): reached thiscall stub function\\n");')
    print(f'\tvoid *func = func_open("{so_name}", "{dll_name}");')
    print('\tif (!func) {')
    print(f'\t\tprintf("{so_name}(): failed to load desired function in either hl.so or hl.dll\\n");')
    print('\t\tabort();')
    print('\t}')
    print(f'\treturn invoke_on_thiscall<{return_type}>({comma_separate(["this__", "func"] + args_names)});')
    print('}\n')

def emit_cdecl_class_stub(so_name, return_type, args_types, args_with_types, args_names):
    print(f'extern "C" {return_type} {so_name}({comma_separate(["void *this__"] + args_with_types)}) {{')
    print('\tabort();')
    print(f'\tprintf("{so_name}(): reached cdecl class stub function\\n");')
    print(f'\tvoid *func = func_open("{so_name}", nullptr);')
    print('\tif (!func) {')
    print(f'\t\tprintf("{so_name}(): failed to load desired function in either hl.so or hl.dll\\n");')
    print('\t\tabort();')
    print('\t}')
    print(f'\treturn invoke_on_cdecl<{return_type}>({comma_separate(["this__", "func"] + args_names)});')
    #print(f'\treturn invoke_on_cdecl<{comma_separate([return_type] + args_types)}>({comma_separate(["this__", "func"] + args_names)});')
    print('}\n')

def load_elf_symbols(path):
    base_syms = []

    with open(path, 'rb') as f:
        elf = ELFFile(f)
        symtabs = [s for s in elf.iter_sections() if type(s) is SymbolTableSection]
        for s in symtabs:
            if s['sh_type'] != 'SHT_DYNSYM':
                continue
            for sym in s.iter_symbols():
                if (sym['st_info']['type'] != 'STT_FUNC'):
                    continue
                if(sym['st_info']['bind'] != 'STB_GLOBAL'):
                    continue
                if(sym['st_shndx'] == 'SHN_UNDEF'):
                    continue
                base_syms.append(sym.name)

    demangled = demangle_gcc(base_syms)
    return zip(base_syms, demangled)

def load_pe_symbols(path):
    base_syms = []

    pe = pefile.PE(path)
    for export in pe.DIRECTORY_ENTRY_EXPORT.symbols:
        base_syms.append(export.name.decode('utf-8'))

    demangled = demangle_msvc('\n'.join(base_syms))
    return zip(base_syms, demangled)

so_syms = load_elf_symbols('hl.so')
dll_syms = list(load_pe_symbols('hl.dll'))

print('#include <stdio.h>')
print('#include <stdlib.h>')
print('#include <stdarg.h>')
print('#include <utility>')
print('#include "func_open.hpp"')
print('#include "../loader/util.hpp"\n')

print('template <typename R, typename ...Args>')
print('inline __attribute__((always_inline)) R invoke_on_thiscall(void *this__, void *func, Args &&...args) {')
print('\tstruct A {} *a = (A *)this__;\n')
print('\tunion {')
print('\t\tvoid *ptr;')
print('\t\tR (__attribute__((thiscall)) A::*func)(Args...);')
print('\t} ptr;\n')
print('\tptr.ptr = func;')
print('\treturn (a->*(ptr.func))(std::forward<Args>(args)...);')
print('}\n')

print('template <typename R, typename ...Args>')
print('inline __attribute__((always_inline)) R invoke_on_cdecl(void *this__, void *func, Args &&...args) {')
print('\tunion {')
print('\t\tvoid *ptr;')
print('\t\tR (*func)(void *, Args...);')
print('\t} ptr;\n')
print('\tptr.ptr = func;')
print('\tprintf("this__ = %p\\n", this__);')
print('\treturn (ptr.func)(this__, std::forward<Args>(args)...);')
print('}\n')

print('struct Vector{float x,y,z;};\n')
print('typedef int Activity;\n')
print('typedef int Materials;\n')

def normalize_type(type):
    if type[-1:] == '*' or type[-1:] == '&':
        return 'void *' # pointers and references
    elif type.split('::')[-1].isupper():
        return 'int' # enums
    elif 'int' in type or 'float' == type or 'Vector' == type:
        return type # known types
    else:
        return type # unknown, yikes

def generate_args_and_types(demangled_name):
    types = []
    names = []
    types_names = []

    parts = demangled_name.split('(')
    parts = parts[1].split(',')
    parts[-1] = parts[-1][:-1]
    parts = list([part.strip() for part in parts])
    parts = filter(None, parts)

    i = 0

    for part in parts:
        type = normalize_type(part)
        types.append(type)
        names.append(f'a{i}')
        types_names.append(f'{type} a{i}')

        i += 1

    #print(types_names)
    #print(types)
    #print(names)

    return (types, types_names, names)

for mangled, unmangled in so_syms:
    if (mangled in excluded):
        continue

    so_name = mangled
    dll_name = 'nullptr'

    dll_counterpart = ('bad', 'bad')
    for dll_sym in dll_syms:
        dll_mangled, dll_unmangled = dll_sym
        if mangled == unmangled:
            if mangled == dll_mangled:
                dll_counterpart = dll_sym
        else:
            parts = unmangled.split('(')
            base_name = parts[0]

            dll_parts = dll_unmangled.split('(')
            dll_parts = dll_parts[0].split(' ')
            if len(dll_parts) < 3:
                continue
            dll_base_name = dll_parts[3]

            if base_name == dll_base_name:
                dll_counterpart = dll_sym


    if dll_counterpart[0] == 'bad':
        continue

    if mangled == unmangled:
        print(f'#warning ADD PROPER PROTOTYPE FOR {mangled}');
        dll_counterpart = ('bad', 'bad')
        for dll_sym in dll_syms:
            dll_mangled, dll_unmangled = dll_sym
            if mangled == dll_mangled:
                dll_counterpart = dll_sym

        # dll name and so name match for unmangled symbols (or so we hope)
        if dll_counterpart[0] != 'bad':
            emit_stdcall_stub(so_name, so_name, 'void', ['void *'], ['void *t'], ['t'])
        else:
            emit_cdecl_stub(so_name, so_name, 'void', ['void *'], ['void *t'], ['t'])
    else:
        parts = unmangled.split('(')
        base_name = parts[0]
        dll_counterpart = ('bad', 'bad')
        for dll_sym in dll_syms:
            dll_mangled, dll_unmangled = dll_sym
            dll_parts = dll_unmangled.split('(')
            dll_parts = dll_parts[0].split(' ')
            if len(dll_parts) < 3:
                continue
            dll_base_name = dll_parts[3]

            if base_name == dll_base_name:
                dll_counterpart = dll_sym

        if mangled == '_Z12UTIL_VarArgsPcz':
            print('extern "C" char *_Z12UTIL_VarArgsPcz(char *format, ...) {')
            print('\tva_list argptr;')
            print('\tstatic char string[1024];\n')
            print('\tva_start(argptr, format);')
            print('\tvsprintf(string, format, argptr);')
            print('\tva_end(argptr);\n')
            print('\treturn string;')
            print('}\n')
        elif mangled == '_Z14UTIL_LogPrintfPcz':
            print('extern "C" void _Z14UTIL_LogPrintfPcz(char *format, ...) {')
            print('\tva_list argptr;\n')
            print('\tva_start(argptr, format);')
            print('\tvprintf(format, argptr);')
            print('\tva_end(argptr);')
            print('}\n')
        elif base_name[:1] != 'C':
            print(f'#warning ADD PROPER RETURN TYPES FOR {unmangled}');
            # not a class
            types, types_names, names = generate_args_and_types(unmangled)
            emit_cdecl_stub(so_name, so_name, 'void', types, types_names, names)
        elif dll_counterpart[0] == 'bad':
            print(f'#warning ADD PROPER RETURN TYPES FOR {unmangled}');
            #print(f'failed to find DLL counterpart for "{unmangled}"')
            types, types_names, names = generate_args_and_types(unmangled)
            emit_cdecl_class_stub(so_name, 'void', types, types_names, names)
        else:
            types, types_names, names = generate_args_and_types(unmangled)
            emit_thiscall_stub(so_name, dll_counterpart[0], 'void', types, types_names, names)
            #print(f'found DLL counterpart for "{unmangled}", that is "{dll_counterpart[1]}"')
            
    #emit_stdcall_stub(so_name, dll_name, 'void', ['void *'], ['void *t'], ['t'])
