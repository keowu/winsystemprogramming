#include <iostream>
#include <Windows.h>

auto main( ) -> int
{

    std::cout << "Hello World!\n";

    //https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-openfilemappinga
    HANDLE hFileMap = OpenFileMapping(
        _In_ FILE_MAP_ALL_ACCESS, //[in]
        _In_ FALSE, //[in]
        _In_ L"Local\\KeowuFileMapp" //[in]
    );

    //https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-mapviewoffile
    PCHAR buffer = (PCHAR)MapViewOfFile(
        _In_ hFileMap, //[in]
        _In_ FILE_MAP_ALL_ACCESS, //[in]
        _In_ 0, //[in]
        _In_ 0, //[in]
        _In_ 256 //[in]
    );

    if (!buffer)
        std::operator<<(std::cout, "Não foi possível mapear arquivo: ").operator<<(GetLastError()).operator<<(std::endl);
    
    std::operator<<(std::cout, "Sucesso em mapear arquivo !").operator<<(std::endl);

    std::printf("Enviado do servidor -> %s", buffer);

    //https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-unmapviewoffile
    BOOL bUnmapFile = UnmapViewOfFile(
        _In_ buffer //[in]
    );

    if(!bUnmapFile)
        std::operator<<(std::cout, "Não foi possível fazer unmap do arquivo: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso em unmapear arquivo !").operator<<(std::endl);

    if(!CloseHandle(
        hFileMap
    ))
        std::operator<<(std::cout, "O Handle não pode ser fechado: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao fechar o handle !").operator<<(std::endl);

    return 0;
}