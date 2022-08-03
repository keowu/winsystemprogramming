#include <iostream>
#include <Windows.h>

auto main( ) -> int
{

    std::cout << "Hello World!\n";

    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
    HANDLE hCreateFile = CreateFile(
        _In_ L"\\\\.\\pipe\\KeowuPipe",  //[in]
        _In_ GENERIC_READ | GENERIC_WRITE, //[in]
        _In_ 0,  //[in]
        _In_opt_ NULL, //[in, optional]
        _In_ OPEN_EXISTING, //[in]
        _In_ FILE_ATTRIBUTE_NORMAL, //[in]
        _In_opt_ NULL //[in, optional]
    );

    if (hCreateFile == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Erro ao criar um handle: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao abrir um handle !").operator<<(std::endl);

    DWORD dwNumberBytesWrite = 0;
    char cBufferWrite[26]{ "Olá mundo, from Keowu !!" };
    DWORD dwSizeOfBuffer = sizeof(cBufferWrite);

    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile
    BOOL bWriteFile = WriteFile(
        _In_ hCreateFile,  //[in]
        _In_ cBufferWrite,  //[in]
        _In_ dwSizeOfBuffer,  //[in]
        _Out_opt_ &dwNumberBytesWrite, //[out, optional]
        _In_opt_z_ NULL //[in, out, optional]
    );

    if(!bWriteFile)
        std::operator<<(std::cout, "Erro ao escrever arquivo pipe: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao escrever no arquivo pipe !").operator<<(std::endl);

    DWORD dwNumberBytesRead = 0;
    char cBufferRead[1024]{ 0 };
    DWORD dwSizeOfBufferRead = sizeof(cBufferRead);

    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile
    BOOL bReadFile = ReadFile(
        _In_ hCreateFile, //[in]
        _Out_ cBufferRead, //[out]
        _In_ dwSizeOfBufferRead, //[in]
        _Out_opt_ &dwNumberBytesRead, //[out, optional]
        _In_opt_z_ NULL //[in, out, optional]
    );

    if (!bReadFile)
        std::operator<<(std::cout, "Erro ao ler o arquivo pipe: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao ler o arquivo pipe !").operator<<(std::endl);

    std::printf("Dados obtidos pelo cliente(este) do servidor(pipe server): %s", cBufferRead);

    std::cin.get();

    return 0;
}