/*
    NÃO COPIE E COLE ESSE MEU EXEMPLO EM UM SOFTWARE DE RELEASE, A NÃO SER QUE VOCÊ SEJA RETARDADO !
*/
#include <iostream>
#include <Windows.h>


DWORD WINAPI MinhaThread(LPVOID params) {

    for (;;)
        std::operator<<(std::cout, "AEEEE BROTHER ESTOU EM OUTRO ENDERECO VIRTUAL LMAO").operator<<(std::endl);

    return 0;
}


auto main( ) -> int
{
    std::cout << "Hello World!\n";

    /*
    *   CreateRemoteThread:
            Permite criar uma thread que é executada no espaço de endereço virtual de outro processo.
    */

    //https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-findwindowa
    HWND hwProc = FindWindowA(
        NULL, //[in, optional]
        "Cheat Engine 7.4" //[in, optional]
    );

    if (!hwProc) {
        std::operator<<(std::cout, "Não foi encontrado esse processo, erro: ").operator<<(GetLastError()).operator<<(std::endl);
        exit(-1);
    }
    
    DWORD PID = 0;

    //https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowthreadprocessid
    GetWindowThreadProcessId(
        hwProc, //[in]
        &PID //[out, optional]
    );

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-openprocess
    HANDLE hProc = OpenProcess(
        PROCESS_ALL_ACCESS, //[in]
        TRUE, //[in]
        PID //[in]
    );

    if (!hProc) {
        std::operator<<(std::cout, "Não foi possível abrir o processo, erro: ").operator<<(GetLastError()).operator<<(std::endl);
        exit(-1);
    }
        
    DWORD dTID = 0;

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createremotethread
    HANDLE hTidProcMem = CreateRemoteThread(
        hProc, //[in]
        NULL, //[in]
        0, //[in]
        MinhaThread, //[in]
        NULL, //[in]
        NULL, //[in]
        &dTID //[out]
    );

    if (hTidProcMem == INVALID_HANDLE_VALUE) {
        std::operator<<(std::cout, "Não foi possível iniciar a thread remota: ").operator<<(GetLastError()).operator<<(std::endl);
        exit(-1);
    }

    std::cin.get();

    return 0;
}