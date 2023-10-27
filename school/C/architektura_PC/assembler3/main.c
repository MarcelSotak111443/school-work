#include <stdio.h>

int i, vysledok;      // Niektore verzie potrebuju globalne premenne

int main(int argc, char* argv[])
{
    for (i = 0; i < 16; i++) {

#ifdef __GNUC__                      // Tato cast sa preklada len v Dev-C++ (gcc)

    asm(".intel_syntax noprefix \n"   // Prepneme z AT&T syntaxe na na Intel

        "mov eax,9                \n"   // iCislo -> EAX
        "mov ecx,i            \n"
        "cmp ecx,eax               \n"   // ak je 10 vacsie ako eax
        "jg gg                     \n"    // EAX  -> iVysledo
        "add ecx,'0'               \n"
        "mov vysledok,ecx          \n"
        "jmp bb                    \n"
        "gg:                       \n"
        "add ecx,55                \n"
        "mov vysledok,ecx          \n"
        "bb:                       \n"
        ".att_syntax            \n"); // Dame vsetko do povodneho stavu

        #endif

    printf("%c \n",vysledok);
    }
    printf("\n\nStlac ENTER a skoncime...");
    scanf("?");
    return(0);
}