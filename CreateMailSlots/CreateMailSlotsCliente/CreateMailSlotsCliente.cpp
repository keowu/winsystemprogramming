#include <iostream>
#include <Windows.h>

auto main( ) -> int
{

    std::cout << "Hello World!\n";

    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
    HANDLE hFileMailSlots = CreateFile(
        _In_ L"\\\\.\\mailslot\\KEOWUMAILSLOTS", //[in]
        _In_ GENERIC_READ | GENERIC_WRITE, //[in]
        _In_ 0, //[in]
        _In_opt_ NULL, //[in, optional]
        _In_ OPEN_EXISTING, //[in]
        _In_ FILE_ATTRIBUTE_NORMAL, //[in]
        _In_opt_ NULL //[in, optional]
    );

    if (hFileMailSlots == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Falhou em criar arquivo para obter handle para mailslots: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao obter handle para mailslots !").operator<<(std::endl);

    char cBufferToWrite[44]{ "Ola mundo do Keowu através de Mailslots !!" };
    DWORD dwBufferSizeWrite = sizeof(cBufferToWrite);
    DWORD dwNumberOfBytesWrittern = 0;

    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile
    BOOL bWriteFile = WriteFile(
        _In_ hFileMailSlots, //[in]
        _In_ cBufferToWrite, //[in]
        _In_ dwBufferSizeWrite, //[in]
        _Out_opt_ &dwNumberOfBytesWrittern, //[out, optional]
        _In_opt_z_ NULL //[in, out, optional]
    );

    if (!bWriteFile)
        std::operator<<(std::cout, "Falhou em escreve no mailslots !!").operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao escrever no mailslots !!").operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
    BOOL bClosed = CloseHandle(
        _In_ hFileMailSlots //[in]
    );

    if(!bClosed)
        std::operator<<(std::cout, "Falha em fechar o handle: ").operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao fechar o handle !").operator<<(std::endl);

    return 0;
}