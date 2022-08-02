#include <iostream>
#include <Windows.h>

HANDLE g_hMutex, g_hTid1, g_hTid2; // não faça isso em aplicação release, ou você pode deixar que terceiros brinquem com seus handles
int g_count = 1;

auto WINAPI FunctEven(LPVOID params) -> DWORD{

    while ( g_count < 10 ) {

        //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject
        WaitForSingleObject(
            _In_ g_hMutex, //[in]
            _In_ INFINITE  //[in]
        );

        if (g_count % 2 == 0)
            std::cout << "Par -> " << g_count++ << std::endl;

        //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-releasemutex
        ReleaseMutex(
           _In_ g_hMutex //[in]
        );
    }

    return 0;
}

auto WINAPI FunctOdd(LPVOID params) -> DWORD {

    while (g_count < 10) {

        WaitForSingleObject(
            _In_ g_hMutex, //[in]
            _In_ INFINITE  //[in]
        );

        if (g_count % 2 == 1)
            std::cout << "Impar -> " << g_count++ << std::endl;

        ReleaseMutex(
            _In_ g_hMutex //[in]
        );

    }

    return 0;
}

auto main( ) -> int
{

    std::cout << "Hello World!\n";

    /*
        Sincronização de Thread:
            1 - Escrever o número par e ímpar usando Thread e Mutex
            2 - CreateMutex
            3 - Criar duas threads
            4 - Criar thread chamada de muha, Thread muha usa as API's WaitForSingleObject e ReleaseMutex
            5 - No método main, usar a API CloseHandle
    */
    std::operator<<(std::cout, "Sincronizacao entre threads !!").operator<<(std::endl);

    DWORD dTID = 0;

    //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexa
    g_hMutex = CreateMutex(
        _In_ NULL, //[in, optional]
        _In_ FALSE, //[in]
        _In_ NULL //[in, optional]
    );

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread
    g_hTid1 = CreateThread(
        _In_ NULL, //[in, optional]
        _In_ NULL, //[in]
        _In_ FunctEven, //[in]
        _In_ NULL, //[in, optional]
        _In_ NULL, //[in]
        _Out_ &dTID //[out, optional]
    );

    g_hTid2 = CreateThread(
      _In_  NULL,  //[in, optional]
      _In_  NULL,  //[in]
      _In_  FunctOdd, //[in]
      _In_  NULL, //[in, optional]
      _In_  NULL, //[in]
      _Out_ NULL //[out, optional]
    );

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    BOOL bClosed = CloseHandle(
        _In_ g_hTid1 //[in]
    );

    if (!bClosed)
        std::operator<<(std::cout, "Erro ao fechar o HANDLE: ").operator<<(GetLastError()).operator<<(std::endl);

    bClosed = CloseHandle(
        _In_ g_hTid2 //[in]
    );

    if (!bClosed)
        std::operator<<(std::cout, "Erro ao fechar o HANDLE: ").operator<<(GetLastError()).operator<<(std::endl);

    return 0;
}