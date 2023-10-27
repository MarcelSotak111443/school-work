#include <stdio.h>

static int iCislo, iVysledok,iCislo2;         // Niektore verzie potrebuju globalne premenne

int main(int argc, char* argv[])
{
    iCislo = 27;
    iCislo2 = 5;
    iVysledok = 0;
    printf("\nCislo: %d  Vysledok: %d",iCislo,iVysledok);

#ifdef __GNUC__                      // Tato cast sa preklada len v Dev-C++ (gcc)

    asm(".intel_syntax noprefix \n"   // Prepneme z AT&T syntaxe na na Intel

        "mov eax,iCislo        \n"   // iCislo -> EAX
        "add eax,iCislo2                \n"   // EAX ++
        "mov iVysledok,eax     \n"   // EAX  -> iVysledok

        ".att_syntax            \n"); // Dame vsetko do povodneho stavu


#endif

    printf("\nCislo: %d  Vysledok: %d",iCislo,iVysledok);

    printf("\n\nStlac ENTER a skoncime...");
    scanf("?");
    return(0);
}