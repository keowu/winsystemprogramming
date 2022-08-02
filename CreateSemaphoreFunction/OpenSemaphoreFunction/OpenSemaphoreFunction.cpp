#include <iostream>
#include <Windows.h>

auto main( ) -> int
{

    std::cout << "Hello World!\n";

    //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-opensemaphorew
    HANDLE hSem = OpenSemaphore(
        _In_ SEMAPHORE_ALL_ACCESS, //[in]
        _In_ FALSE,  //[in]
        _In_ L"ONomeDoSemaphoreVaiAqui" //[in]
    );

    if (!hSem)
        std::operator<<(std::cout, "Erro ao abrir o semaphore nomeado: ").operator<<(GetLastError()).operator<<(std::endl);
    
    std::operator<<(std::cout, "Sucesso ao abrir o semaphore nomeado").operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    BOOL bClosed = CloseHandle(
        _In_ hSem //[in]
    );

    if (!bClosed)
        std::operator<<(std::cout, "Erro ao fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

    return 0;
}