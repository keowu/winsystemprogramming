#include <iostream>
#include <Windows.h>

//Use DWORD WINAPI assinatura e LPVOID para parametros
DWORD WINAPI MinhaThread(LPVOID lpParams) {


    while (TRUE)
        std::operator<<(std::cout, "Poxa Brother tou preso no loop, vou ficar ruim da cabeca assim !").operator<<(std::endl);


    return 0;
}


auto main( ) -> int
{

    std::cout << "Hello World!\n";


    /*
        Definição:
            Thread é uma entidade independente que roda com um processo.
            Notas:
                1 - Thread compartilha alguns recursos com o processo exceto STACK e Registradores
                2 - Por padrão o máximo que um thread pode ter de tamanho no Windows é 1 MB de stack
                3 - Podem ser criados no máximo 2048 threads no Window em um processo em execução(De acordo com a documentação da Microsoft)
                4 - Terminar uma thread não necessáriamente removera o objeto dela do sistema operacional isso só acontecera se o último handle dela for fechado
                5 - Para mais informações o GOOGLE é seu amigo!
    */

    DWORD hTID = 0;

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread
    HANDLE hThread = CreateThread(
        NULL, //[in, optional]
        100, //[in]
        MinhaThread, //[in]
        NULL, //[in, optional]
        NULL, //[in] -> NULL é uma macro que expande para zero, zero inicia a thread automáticamente, CREATE_SUSPENDED suspende a thread e STACK_SIZE_PARAM_IS_A_RESERVATION reserva a stack para a thread
        &hTID //[out, optional]
    );

    if (hThread == INVALID_HANDLE_VALUE) 
        std::operator<<(std::cout, "Não foi possivel criar a thread: ").operator<<(GetLastError()).operator<<(std::endl);
    
    std::operator<<(std::cout, "Sucesso ao criar a thread para matar ela aperte qualquer tecla").operator<<(std::endl);

    std::cin.get();

    std::operator<<(std::cout, "Matei a thread: ").operator<<(std::hex).operator<<(hTID).operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-terminatethread
    BOOL bThread = TerminateThread(
        hThread, //[in, out]
        0x00 //[in]
    );

    if (!bThread)
        std::operator<<(std::cout, "A thread não pode ser encerrada: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "A Thread foi encerrada com sucesso !").operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    BOOL bClosed = CloseHandle(
        hThread //[in]
    );

    if (!bClosed)
        std::operator<<(std::cout, "Não foi possível fechar o Handle !").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "o Handle foi fechado com sucesso !").operator<<(std::endl);

    //CRIANDO UMA THREAD SUSPENSA

    hThread = CreateThread(
        NULL, //[in, optional]
        100, //[in]
        MinhaThread, //[in]
        NULL, //[in, optional]
        CREATE_SUSPENDED, //[in] -> NULL é uma macro que expande para zero, zero inicia a thread automáticamente, CREATE_SUSPENDED suspende a thread e STACK_SIZE_PARAM_IS_A_RESERVATION reserva a stack para a thread
        &hTID //[out, optional]
    );

    if(hThread == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Não foi possivel criar a thread: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar a thread!").operator<<(std::endl);

    std::operator<<(std::cout, "Apete uma tecla para iniciar a thread que estava em espera ").operator<<(std::endl);

    std::cin.get();

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-resumethread
    if (!ResumeThread(
        hThread //[in]
    ) == -1)
        std::operator<<(std::cout, "A Thread não pode ser retomada um erro aconteceu: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao resumar a thread !").operator<<(std::endl);

    return 0;
}