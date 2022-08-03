#include <iostream>
#include <Windows.h>

auto main( ) -> int
{

    std::cout << "Hello World!\n";

    /*
        Named Pipe

            1. Named Pipe é bidirecional ou unidirecional ou Full Duplex
            2. Pode-se fazer simultaneamente operações leitura e escrita
            3. Named Pipe é usado pra sobrepor a rede
            4. é uma extenção do Pipe Tradicional

            Passos para programar:
                
                Servidor:                                                         Cliente:
                1. Criar um pipe nomeado (CreateNamedPipe)                        1. CreateFile ou CallNamedPipe
                2. ConnectNamedPipe                                               2. WriteFile/ReadFile/TransactNamedPipe
                3. WriteFile ou ReadFile                                          3. CloseHandle
                4. FlushFileBuffers
                5. DisconnectNamedPipe
                6. CloseHandle
    */

    BOOL bWriteFile;
    char cWriteFileBuffer[27]{"Hello World from Keowu !!!"};
    DWORD dwWriteBufferSize = sizeof(cWriteFileBuffer);
    DWORD dwBytesWritten = 0;

    BOOL bReadFile;
    char cReadFileBuffer[1024]{ 0 };
    DWORD dwReadBufferSize = sizeof(cReadFileBuffer);
    DWORD dwReadBytes = 0;

    //1º Criar o pipe
    char cInputBuffer[1024]{ 0 };
    char cOutputBuffer[1024]{ 0 };
    DWORD dwSizeInputOfBuffer = sizeof(cInputBuffer);
    DWORD dwSizeOutputOfBuffer = sizeof(cOutputBuffer);

    //https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createnamedpipea
    HANDLE hCreateNamedPipe = CreateNamedPipe(
        _In_ L"\\\\.\\pipe\\KeowuPipe", //[in]
        _In_ PIPE_ACCESS_DUPLEX, //[in]
        _In_ PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, //[in]
        _In_ PIPE_UNLIMITED_INSTANCES, //[in]
        _In_ dwSizeOutputOfBuffer, //[in]
        _In_ dwSizeInputOfBuffer, //[in]
        _In_ 0, //[in]
        _In_opt_ NULL //[in, optional
    );

    if (hCreateNamedPipe == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Falhou ao criar o PIPE: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar o pipe\n");

    //2º Conectar o pipe
    
    //https://docs.microsoft.com/en-us/windows/win32/api/namedpipeapi/nf-namedpipeapi-connectnamedpipe
    BOOL bConnectedNamedPipe = ConnectNamedPipe(
        _In_ hCreateNamedPipe, //[in]
        _In_opt_z_ NULL //[in, out, optional]
    );

    if(!bConnectedNamedPipe)
        std::operator<<(std::cout, "Falhou ao conectar no PIPE: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao connectar ao pipe\n");

    //Escrevendo arquivo

    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile
    bWriteFile = WriteFile(
        _In_ hCreateNamedPipe, //[in]
        _In_ cWriteFileBuffer, //[in]
        _In_ dwWriteBufferSize, //[in]
        _Out_opt_ &dwBytesWritten, //[out, optional]
        _In_opt_z_ NULL //[in, out, optional]
    );

    if (!bWriteFile)
        std::operator<<(std::cout, "Não foi possível escrever: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao escrever !").operator<<(std::endl);

    //Flush buffer
    
    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-flushfilebuffers
    BOOL bFlush = FlushFileBuffers(
        _In_ hCreateNamedPipe //[in]
    );

    if (!bFlush)
        std::operator<<(std::cout, "Não foi possível fazer o flush do buffer: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao fazer o flush do buffer !").operator<<(std::endl);

    //Lendo arquivo

    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile
    bReadFile = ReadFile(
        _In_ hCreateNamedPipe,  //[in]
        _Out_ cReadFileBuffer,  //[out]
        _In_ dwReadBufferSize,  //[in]
        _Out_opt_ &dwReadBytes, //[out, optional]
        _In_opt_z_ NULL         //[in, out, optional]
    );

    if (!bReadFile)
        std::operator<<(std::cout, "Não foi possível ler: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao ler !").operator<<(std::endl);

    std::printf("Dados do cliente: %s\n", cReadFileBuffer);

    //Disconecta o Pipe

    //https://docs.microsoft.com/en-us/windows/win32/api/namedpipeapi/nf-namedpipeapi-disconnectnamedpipe
    BOOL bDisconnect = DisconnectNamedPipe(
        _In_ hCreateNamedPipe //[in]
    );

    if (!bDisconnect)
        std::operator<<(std::cout, "Não foi possível desconectar do pipe: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao desconectar !").operator<<(std::endl);

    //Fechar o handle

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    BOOL bClosed = CloseHandle(
       _In_ hCreateNamedPipe //[in]
    );

    if (!bClosed)
        std::operator<<(std::cout, "Não foi possível fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao fechar o handle !").operator<<(std::endl);

    return 0;
}