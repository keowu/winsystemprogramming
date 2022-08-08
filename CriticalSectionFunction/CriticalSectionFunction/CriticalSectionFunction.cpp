#include <iostream>
#include <Windows.h>

int g_count = 1; // Brother, evite deixar global!

//https://docs.microsoft.com/pt-br/windows/win32/sync/critical-section-objects
CRITICAL_SECTION g_criticalSec;

auto WINAPI FunctEven(LPVOID params) -> DWORD {

    while (g_count < 10) {

        //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-entercriticalsection
        EnterCriticalSection(
            _Inout_ &g_criticalSec //[in, out]
        );

        if (g_count % 2 == 0)
            std::cout << "Par -> " << g_count++ << std::endl;

        //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-leavecriticalsection
        LeaveCriticalSection(
            _Inout_ &g_criticalSec //[in, out]
        );

    }

    return 0;
}

auto WINAPI FunctOdd(LPVOID params) -> DWORD {

    while (g_count < 10) {

        //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-entercriticalsection
        EnterCriticalSection(
            _Inout_ &g_criticalSec //[in, out]
        );

        if (g_count % 2 == 1)
            std::cout << "Impar -> " << g_count++ << std::endl;

        //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-leavecriticalsection
        LeaveCriticalSection(
           _Inout_ &g_criticalSec //[in, out]
        );

    }

    return 0;
}

auto main() -> int
{

    std::cout << "Hello World!\n";

    /*
        Critical Section no Windows

        Seção creitica é uma região de código que precisa ser executada atomicamente ou com operação indivisivel
        Seção critica usada para sincronização
        Isso provê um "lock" similar ao do mutex
        O Processo só é responsável por alocar memória usada pelo critical section.

        Exemplo:

        do {
            Entry_Section();
            //CRITICAL_SECTION
            Exit_Section();
        }while(TRUE);

        Diferenças entre o CRITICAL_SECTION e o MUTEX

        Critical section:
            1. Objeto C.S não é compartilhado pelo processo
            2. C.S é usado por somente uma thread de um processo
            3. Ele não consegue comunicar com o kernel
            4. É consideravelmente mais rápido que Event, Mutex e Semaphore
        
        Mutex:
            1. Objeto Mutex é compartilhado pelos processos
            2. É usado em mais de um processo
            3. Ele pode comunicar com o Kernel
            4. Ele é lento e pode ocasionar um risco de deadlock

        Critical Section API's:
            1. InitializeCriticalSection
            2. InitializeCriticalSectionAndSpinCount
            3. EnterCriticalSection
            4. TryEnterCriticalSection
            5. LeaveCriticalSection
            6. SetCriticalSectionSpinCount
            7. DeleteCriticalSection
    */
    
    //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-initializecriticalsection
    InitializeCriticalSection(
        _Out_ &g_criticalSec //[out]
    );

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread
    auto hThread = CreateThread(
        _In_opt_ NULL, //[in, optional]
        _In_ 0, //[in]
        _In_ FunctEven, //[in]
        _In_opt_ __drv_aliasesMem NULL, //[in, out]
        _In_ 0, //[in]
        _Out_opt_ 0 //[out, optional]
    );

    if (hThread == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Falhou ao criar a thread: ").operator<<(GetLastError());

    std::operator<<(std::cout, "Sucesso ao criar a thread !\n");

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread
    auto hThread2 = CreateThread(
        _In_opt_ NULL, //[in, optional]
        _In_ 0, //[in]
        _In_ FunctOdd, //[in]
        _In_opt_ __drv_aliasesMem NULL,  //[in, out]
        _In_ 0, //[in]
        _Out_opt_ 0 //[out, optional]
    );

    if (hThread2 == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Falhou ao criar a thread: ").operator<<(GetLastError());

    std::operator<<(std::cout, "Sucesso ao criar a thread !\n");

    //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject
    auto dwWaitForSingle = WaitForSingleObject(
        _In_ hThread, //[in]
        _In_ INFINITE //[in]
    );
    
    if (dwWaitForSingle == WAIT_FAILED)
        std::operator<<(std::cout, "Falhou ao esperar pelo objeto: ").operator<<(GetLastError());

    //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject
    dwWaitForSingle = WaitForSingleObject(
        _In_ hThread2, //[in]
        _In_ INFINITE //[in]
    );

    if(dwWaitForSingle == WAIT_FAILED)
        std::operator<<(std::cout, "Falhou ao esperar pelo objeto: ").operator<<(GetLastError());

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    if (!CloseHandle(
        _In_ _Post_ptr_invalid_ hThread //[in]
    ))
        std::operator<<(std::cout, "Falhou ao fechar o HANDLE !\n");

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    if(!CloseHandle(
        _In_ _Post_ptr_invalid_ hThread2 //[in]
    ))
        std::operator<<(std::cout, "Falhou ao fechar o HANDLE !\n");

    //https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-deletecriticalsection
    DeleteCriticalSection(
        _Inout_ &g_criticalSec //[in, out]
    );

    return 0;
}