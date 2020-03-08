import fileinput

excluded = ['_init', '_fini']

print('#include <stdio.h>')
print('#include <stdlib.h>')
print('#include "func_open.hpp"')

for line in fileinput.input():
    line = line.rstrip()
    if (line in excluded):
        continue

    print(f'extern "C" void {line}(...) {{')
    print(f'\tprintf("{line}(): reached stub function\\n");')
    print(f'\tvoid *func = func_open("{line}", "{line}");')
    print('\tif (!func) {')
    print(f'\t\tprintf("{line}(): failed to load desired function in either hl.so or hl.dll\\n");')
    print('\t\tabort();')
    print('\t}')
    print('}\n')
