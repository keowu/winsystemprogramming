#include <iostream>
#include <Windows.h>

auto main( ) -> int
{

    std::cout << "Hello World!\n";

    /*
        Definição de processos:
            - Um programa em execução é chamado de processo
                        ou
            - Processo é uma estrutura de dados que armazena informações sobre seu estado na memória

        1º CreateProcess - Cria um novo processo
        2º GetProcessID - obtem o PID do processo
        3º GetThreadID - obtem o TID do processo
        4º WaitForSingleObject - Espera um signal
        6º CloseHandle - fecha um processoe sua thread primária
    */

    HANDLE hProc;
    HANDLE hThread;

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-startupinfoa
    STARTUPINFO sInfo{ 0 }; //ou ZeroMemory
    
    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-process_information
    PROCESS_INFORMATION pInfo{ 0 }; //ou ZeroMemory

    //https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/aa366920(v=vs.85)
    ZeroMemory(
        &sInfo, //[in]
        sizeof(sInfo) //[in]
    );

    ZeroMemory(
        &pInfo, //[in]
        sizeof(pInfo) //[in]
    );

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createprocessa
    BOOL bProc = CreateProcess(
        L"C:\\Program Files\\VMProtect Ultimate Partner Edition\\VMProtect.exe", //[in, optional]
        NULL, //[in, out, optional]
        NULL, //[in, optional]
        NULL, //[in, optional]
        FALSE, //[in]
        NORMAL_PRIORITY_CLASS, //[in] NORMAL_PRIORITY_CLASS ou outras flags ou NULL para não usar flag
        NULL, //[in]
        NULL, //[in, optional] 
        &sInfo, //[in]
        &pInfo //[out]
    );

    if (!bProc)
        std::operator<<(std::cout, "Não foi possível criar o processo, erro obtido: ").operator<<(GetLastError()).operator<<(std::endl);


    std::operator<<(std::cout, "O Processo foi criado com sucesso !").operator<<(std::endl);

    std::operator<<(std::cout, "PID(PROCESS ID): ").operator<<(std::hex).operator<<(pInfo.dwProcessId).operator<<(std::endl);
    
    std::operator<<(std::cout, "TID(Thread ID): ").operator<<(std::hex).operator<<(pInfo.dwThreadId).operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getprocessid
    std::operator<<(std::cout, "PID(WINAPI): ").operator<<(std::hex).operator<<(GetProcessId(pInfo.hProcess)).operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getthreadid
    std::operator<<(std::cout, "TID(WINAPI): ").operator<<(std::hex).operator<<(GetThreadId(pInfo.hThread)).operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject
    WaitForSingleObject(
        pInfo.hProcess, //[in]
        10 //[in]
    );

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    CloseHandle(
        pInfo.hProcess //[in]
    );

    CloseHandle(
        pInfo.hThread //[in]
    );

    std::cin.get();

    return 0;
}