#include <iostream>
#include <Windows.h>

auto main( ) -> int
{

    std::cout << "Hello World!\n";

    /*
        Semaphore:
            1 - Semaphore é uma variável inteira (Mutex é um objeto)
            2 - Semaphore é um mecanismo de signals (Mutex é um mecanismo de locking)
            3 - No Semaphore o valor pode ser modificado usando operações WAIT & SIGNAL (Mutex - Somente Locked e Unlocked)
            4 - Semaphore tem dois tipos (Mutex não tem categoria)
                i. Semaphore Binário(Binary Semaphore)
                ii. Semaphor de contagem(Counting Semaphore)
            5 - O valor de um Semaphore pode ser modiciado por um processo adquirindo ou liberando o Semaphore
                (Mutex - Somente quem adquiriu o lock pode fazer unlocking por exemplo um Mutual Ownership)
    */

    //https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createsemaphorea
    HANDLE hSemaphore = CreateSemaphore(
        _In_opt_ NULL, //[In, Optional]
        _In_ 1, //[In]
        _In_ 1, //[In]
        _In_opt_ NULL //[In, Optional] -> Unamed Semaphore
    );

    if (!hSemaphore)
        std::operator<<(std::cout, "Erro ao criar o unamed semaphore: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar o unamed semaphore").operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    BOOL bClosed = CloseHandle(
        _In_ hSemaphore //[In]
    );

    if(!bClosed)
        std::operator<<(std::cout, "Erro ao fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

    std::cin.get();

    hSemaphore = CreateSemaphore(
        _In_opt_    NULL, //[In, Optional]
        _In_    1, //[In]
        _In_    1, //[In]
        _In_opt_    L"ONomeDoSemaphoreVaiAqui" //[In, Optional] -> Named Semaphore
    );

    if (!hSemaphore)
        std::operator<<(std::cout, "Erro ao criar o semaphore named: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar o semaphore named").operator<<(std::endl);

    bClosed = CloseHandle(
        _In_ hSemaphore //[In]
    );

    if (!bClosed)
        std::operator<<(std::cout, "Erro ao fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

    return 0;
}