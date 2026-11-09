void main();

void go(){
        main();
}

#include "loaderdefs.h"
#include "loader.h"
#include "resolve_eat.h"

#define WIN32_FUNC( x ) __typeof__( x ) * x

typedef struct {
        WIN32_FUNC(LoadLibraryA);
        WIN32_FUNC(GetProcAddress);
        WIN32_FUNC(VirtualAlloc);
} WIN32FUNCS;

#define KERNEL32DLL_HASH        0x6A4ABC5B
#define LOADLIBRARYA_HASH       0xEC0E4E8E
#define GETPROCADDRESS_HASH     0x7C0DFCAA
#define VIRTUALALLOC_HASH       0x91AFCA54

void findNeededFunctions(WIN32FUNCS * funcs) {
        char * hModule = (char *)findModuleByHash(KERNEL32DLL_HASH);

        funcs->LoadLibraryA   = (__typeof__(LoadLibraryA) *)   findFunctionByHash(hModule, LOADLIBRARYA_HASH);
        funcs->GetProcAddress = (__typeof__(GetProcAddress) *) findFunctionByHash(hModule, GETPROCADDRESS_HASH);
        funcs->VirtualAlloc   = (__typeof__(VirtualAlloc) *)   findFunctionByHash(hModule, VIRTUALALLOC_HASH);
}


void main(){
    WIN32FUNCS funcs;
    findNeededFunctions(&funcs);

    WIN32_FUNC(MessageBoxA);

    // char str_user32[] = {'U','s','e','r','3','2',0};
    // char str_messageboxa[] = {'M','e','s','s','a','g','e','B','o','x','A',0};
    // char str_main_message[] = {'w','e',' ','m','a','d','e',' ','P','I','C','!',0};
    // char str_heading[] = {'w','h','a','t',' ','w','e',' ','d','o','i','n','g','?',0};
   //
   //  HANDLE hUser32 = funcs.LoadLibraryA(str_user32);
   //  MessageBoxA = (__typeof__(MessageBoxA))funcs.GetProcAddress(hUser32,str_messageboxa);
   //
   //  dprintf((IMPORTFUNCS *)&funcs , str_debug_pointer, hUser32);
   //  dprintf((IMPORTFUNCS *)&funcs , str_debug_pointer, MessageBoxA);
   //
   //  MessageBoxA(NULL,str_main_message,str_heading,MB_OK);

    HANDLE hUser32 = funcs.LoadLibraryA("User32");
    MessageBoxA = (__typeof__(MessageBoxA))funcs.GetProcAddress(hUser32,"MessageBoxA");

    dprintf((IMPORTFUNCS *)&funcs, "hUser32 :%p", hUser32);
    dprintf((IMPORTFUNCS *)&funcs, "MessageBoxA :%p", MessageBoxA);

    MessageBoxA(NULL, "hello form PIC!" ,"PIC Test!",MB_OK);
}
