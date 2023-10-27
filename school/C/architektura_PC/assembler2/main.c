#include <stdio.h>

static int iCislo, iVysledok;         // Niektore verzie potrebuju globalne premenne

int main(int argc, char* argv[])
{
    iCislo = 27;
    printf("\nCislo: %d \n",iCislo);

#ifdef __GNUC__                      // Tato cast sa preklada len v Dev-C++ (gcc)

    asm(".intel_syntax noprefix \n"   // Prepneme z AT&T syntaxe na na Intel

        "mov eax,iCislo        \n"   // iCislo -> EAX
        "SHL eax                \n"   // EAX ++
        "mov iVysledok,eax     \n"   // EAX  -> iVysledok

        ".att_syntax            \n"); // Dame vsetko do povodneho stavu


#endif

    printf("\nCislo: %d  Cislo krat dva je: %d",iCislo,iVysledok);

    printf("\n\nStlac ENTER a skoncime...");
    scanf("?");
    return(0);
}