#include <iostream>
#include <Windows.h>

auto main() -> int
{

    std::cout << "Hello World!\n";

    /*
        1º Mutex é um mecanismo de bloqueio
        2º Mutex tem somente um estado entre locked e unlocked
        3º Mutex tem dois "proprietarios" o que adiquire o lock e o que libera o lock
        4º Se o mutex é locked com NON-RECURSIVE um deadlock vai ocorrer
        5º Mutex só é usado para sincronização de thread
        6º No Windows:
               i. Mutex nomeada
               ii. Mutex não nomeada
    */

    //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexa
    HANDLE hMutex = CreateMutex(
        NULL, //[in, optional]
        FALSE, //[in]
        NULL //[in, optional] -> Mutex não nomeado
    );

    if (hMutex == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Não foi possível criar o mutex: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar o mutex !").operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    if (!CloseHandle(
        hMutex //[in]
    ))
        std::operator<<(std::cout, "O Handle para o mutex não pode ser fechado: ").operator<<(GetLastError()).operator<<(std::endl);


    /*
        Exemplo com mutex nomeado
    */

    hMutex = CreateMutex(
        NULL,//[in, optional]
        FALSE,//[in]
        L"MeuMutex"//[in, optional] -> Nome do mutex
    );

    if (hMutex == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Não foi possível criar o mutex: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar o mutex !").operator<<(std::endl);

    std::cin.get();

    if(!CloseHandle(
        hMutex
    ))
        std::operator<<(std::cout, "O Handle para o mutex não pode ser fechado: ").operator<<(GetLastError()).operator<<(std::endl);

    return 0;
}
