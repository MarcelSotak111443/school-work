#include <stdio.h>


char array[12]={0};

int main(int argc, char* argv[])
{

    #ifdef __GNUC__                      // Tato cast sa preklada len v Dev-C++ (gcc)

    asm(".intel_syntax noprefix \n"   // Prepneme z AT&T syntaxe na na Intel

        "mov EAX,0                           \n"   // iCislo -> EAX
        "cpuid                                 \n"
        "mov dword ptr [array],ebx             \n"   // ak je 10 vacsie ako eax
        "mov dword ptr [array+4],edx             \n"    // EAX  -> iVysledo
        "mov dword ptr [array+8],ecx             \n"
        ".att_syntax            \n"); // Dame vsetko do povodneho stavu

        #endif
    printf("nazov CPU je:  ");
    for (int i = 0; i < 12; i++) {
        printf("%c",array[i]);
        
    }
    printf("\n\nStlac ENTER a skoncime...");
    scanf("?");
    return(0);
}