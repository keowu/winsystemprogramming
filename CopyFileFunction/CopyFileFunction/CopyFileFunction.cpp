#include <iostream>
#include <Windows.h>

auto main() -> int
{
    std::cout << "Hello World!\n";


    //https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-copyfile

    BOOL bCpy = CopyFile(
        L"C:\\Users\\oimeuchapavm\\Downloads\\Nova pasta (2)\\muhahah.txt", //In
        L"C:\\Users\\oimeuchapavm\\Downloads\\Nova pasta (2)\\dir2\\muhahhaha.txt", //In
        TRUE //In
    );

    if (!bCpy) {
        std::operator<<(std::cout, "Erro ao copiar arquivo: ").operator<<(GetLastError()).operator<<(std::endl);
    }

    std::operator<<(std::cout, "Sucesso ao copiar arquivo !").operator<<(std::endl);

    std::cin.get();

    return 0;
}