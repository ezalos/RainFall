#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void sym.imp.operator_new_unsigned_int(void)
{
    // WARNING: Could not recover jumptable at 0x08048530. Too many branches
    // WARNING: Treating indirect jump as call
    // operator new(unsigned int)
    (*_reloc.operator_new_unsigned_int)();
    return;
}


// WARNING: Variable defined which should be unmapped: var_bp_4h
// WARNING: [r2ghidra] Failed to match type size_t for variable n to Decompiler type: Unknown type identifier size_t

int main(char **argv, char **envp)
{
    void *s1;
    code **arg_8h;
    int32_t var_bp_4h;

    if ((int32_t)argv < 2) {
        sym.imp._exit(1);
    }
    s1 = (void *)sym.imp.operator_new_unsigned_int(0x6c);
    method.N.N_int((int32_t)s1, 5);
    arg_8h = (code **)sym.imp.operator_new_unsigned_int(0x6c);
    method.N.N_int((int32_t)arg_8h, 6);
    method.N.setAnnotation_char(s1, envp[1]);
    (**(code **)*arg_8h)(arg_8h, s1);
    return;
}
