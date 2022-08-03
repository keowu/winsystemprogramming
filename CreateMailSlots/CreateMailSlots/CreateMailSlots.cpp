#include <iostream>
#include <Windows.h>

auto main( ) -> int
{

    std::cout << "Hello World!\n";

    /*
        Mailslots:
            1 - Mailslots é um outro mecanismo de IPC
            2 - Usado como um meio de comunicação
            3 - Mailslots geralmente são usados para tramitir pequenas mensagens, por exemplo: diagramas
            4 - Mailslots podem ser usados localmente ou via rede
            5 - Mailslots é uma interface cliente-servidor
            6 - No Mailslots somente o cliente escreve as mensagens que serão armazenadas no mailslot e depois o cleinte que pode obter ou seja ler a mensagem
            7 - Geralmente mailslots é uma troca de comunicação
            8 - Mailslots não fornecem nenhuma confirmação que a mensagem foi recebida
            9 - Pode-se enviar apenas 424 bytes de mensagem


            Servidor                                                     Cliente
            1 - CreateMailSlots                                         1 - CreateFile
            2 - ReadFile                                                2 - WriteFile
            3 - CloseHandle                                             3 - CloseHandle
    */

    //https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createmailslota
    HANDLE hSlots = CreateMailslot(
        _In_ L"\\\\.\\mailslot\\KEOWUMAILSLOTS", //[in]
        _In_ NULL, //[in]
        _In_ MAILSLOT_WAIT_FOREVER, //[in]
        _In_opt_ NULL //[in, optional]
    );

    if (hSlots == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Erro ao tentar criar um mailslots: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar mailslots").operator<<(std::endl);

    char cBufferRead[1024]{ 0 };
    DWORD dwBufferSizeRead = sizeof(cBufferRead);
    DWORD dwBufferSizeReaded = 0;

    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile
    BOOL bReadFile = ReadFile(
        _In_ hSlots, //[in]
        _Out_ cBufferRead, //[out]
        _In_ dwBufferSizeRead, //[in]
        _Out_opt_ &dwBufferSizeReaded, //[out, optional]
        _In_opt_z_ NULL //[in, out, optional]
    );

    if (!bReadFile)
        std::operator<<(std::cout, "Falha ao ler o arquivo: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao ler o arquivo !").operator<<(std::endl);

    std::printf("Cliente devolveu: %s \n", cBufferRead);

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    BOOL bClosed = CloseHandle(
        _In_ hSlots //[in]
    );

    if(!bClosed)
        std::operator<<(std::cout, "Falha ao fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao fechar o handle !").operator<<(std::endl);

    return 0;
}