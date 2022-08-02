#include <iostream>
#include <Windows.h>

auto main( ) -> int
{

    std::cout << "Hello World!\n";

    //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-openmutexw
    HANDLE hMutex = OpenMutex(
        MUTEX_ALL_ACCESS, //[in]
        FALSE, //[in]
        L"MeuMutex" //[in]
    );

    if (hMutex == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Não foi possível abrir o mutex: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao abrir o mutex !").operator<<(std::endl);

    std::cin.get();

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    if(!CloseHandle(
        hMutex
    ))
        std::operator<<(std::cout, "O Handle para o mutex não pode ser fechado: ").operator<<(GetLastError()).operator<<(std::endl);

    return 0;
}