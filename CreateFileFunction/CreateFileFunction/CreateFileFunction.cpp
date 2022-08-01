#include <iostream>
#include <Windows.h>

auto main() -> int
{

    std::cout << "Hello World!\n";

    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
    HANDLE hFile = CreateFile(
        L"C:\\Users\\oimeuchapavm\\Downloads\\Nova pasta (2)\\Teste.teste", //[in]
        GENERIC_READ | GENERIC_WRITE, //[in]
        FILE_SHARE_READ | FILE_SHARE_WRITE, //[in]
        NULL, //[optional]
        CREATE_NEW, //[in]
        FILE_ATTRIBUTE_NORMAL, //[in]
        NULL  //[optional]
    );

    if (hFile == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "O Handle para o arquivo não foi aberto ").operator<<(GetLastError()).operator<<(std::endl);
    
    std::operator<<(std::cout, "O arquivo foi criado com sucesso !").operator<<(std::endl);



    /// <summary>
    ///     WRITE FILE
    /// </summary>
    char buffer[]{ "Olá mundo real !" };
    DWORD dwNumbBytesBuffer = strlen(buffer);
    DWORD dwNumbBytesWrite = 0;

    
    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile
    BOOL bFile = WriteFile(
        hFile, //[in]
        buffer, //[in]
        dwNumbBytesBuffer, //[in]
        &dwNumbBytesWrite,//[out, optional]
        NULL //[out, optional]
    );

    if (!bFile)
        std::operator<<(std::cout, "O Arquivo não foi escrito ").operator<<(GetLastError()).operator<<(std::endl);
    

    std::operator<<(std::cout, "Sucesso ao escrever no arquivo ").operator<<(std::endl);


    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile
    bFile = ReadFile(
        hFile, //[in]
        buffer, //[out]
        dwNumbBytesBuffer,//[in]
        &dwNumbBytesWrite,//[out, optional]
        NULL//[in, out, optional]
    );

    if (!bFile)
        std::operator<<(std::cout, "Erro ao ler o arquivo ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao ler o arquivo !").operator<<(std::endl);    
    std::cout << buffer << std::endl;

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    BOOL bClosed = CloseHandle(
        hFile //[in]
    );

    if (!bClosed)
        std::operator<<(std::cout, "O Handle não foi fechado ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "O Handle foi fechado com sucesso !").operator<<(std::endl);

    return 0;
}