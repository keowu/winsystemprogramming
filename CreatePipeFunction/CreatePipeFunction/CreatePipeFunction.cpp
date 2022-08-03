#include <iostream>
#include <Windows.h>

auto main( ) -> int
{

    std::cout << "Hello World!\n";

    /*
        IPC - é um mecanismo que é usado para comunicação entre diferentes processos.
        PIPE - é um mecanismo IPC. que é usado para comunicação com o processo local ou processos diferentes
            1. Ele tem dois tipos
                i. Pipe Anonimo(Anonymous Pipe) ou Pipe não nomeado(Unamed Pipe)
                ii. Pipe Nomeado(Named Pipe)
    
        Unamed ou Pipe Anonimo:
            1. Usado para um caminho de comunicação ou unidirecional
            2. Pipe anonimo é local do sistema
            3. Pipe anonimo pode ser usado para sobrepor rede
            4. Ao final será possivel ler/escrever do outro processo
                Por exemplo: Pipe/Read/Write file
    */
    HANDLE hReadFile, hWriteFile;
    char cBuff[13]{ "Olá Mundo !!" };
    DWORD dwBuffSize = strlen(cBuff), dwWritten;

    //https://docs.microsoft.com/en-us/windows/win32/api/namedpipeapi/nf-namedpipeapi-createpipe
    BOOL bPipe = CreatePipe(
        _Out_ &hReadFile, //[out]
        _Out_ &hWriteFile, //[out]
        _In_opt_ NULL, //[in, optional]
        _In_ dwBuffSize //[in]
    );

    if (!bPipe)
        std::operator<<(std::cout, "Falhou ao criar o PIPE: ").operator<<(GetLastError()).operator<<(std::endl);
    
    std::operator<<(std::cout, "Sucesso ao criar o PIPE !").operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile
    bPipe = WriteFile(
        _In_ hWriteFile, //[in]
        _In_ cBuff,  //[in]
        _In_ dwBuffSize, //[in]
        _Out_opt_ &dwWritten, //[out, optional] 
        _In_opt_z_ NULL //[in, out, optional]
    );

    if(!bPipe)
        std::operator<<(std::cout, "Falhou ao escrever o arquivo: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao escrever o arquivo !").operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    bPipe = CloseHandle(
        _In_ hWriteFile //[In]
    );

    if (!bPipe)
        std::operator<<(std::cout, "Falhou ao fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile
    bPipe = ReadFile(
       _In_ hReadFile, //[in]
       _Out_ cBuff,  //[out]
       _In_ dwBuffSize, //[in]
       _Out_opt_ &dwWritten, //[out, optional]
       _In_opt_z_ NULL //[in, out, optional]
    );

    if (!bPipe)
        std::operator<<(std::cout, "Falhou ao ler o arquivo: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao ler o arquivo !").operator<<(std::endl);

    bPipe = CloseHandle(
        _In_ hReadFile //[In]
    );

    if (!bPipe)
        std::operator<<(std::cout, "Falhou ao fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

    std::printf("Valor lido pelo PIPE -> %s", cBuff);

    return 0;
}