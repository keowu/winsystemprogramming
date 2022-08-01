#include <iostream>
#include <Windows.h>

auto main() -> int
{

    std::cout << "Hello World!\n";

    //https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-movefile
    BOOL bMove = MoveFile(
        L"C:\\Users\\oimeuchapavm\\Downloads\\Nova pasta (2)\\muhahah.txt", //In
        L"C:\\Users\\oimeuchapavm\\Downloads\\Nova pasta (2)\\dir2\\muhahahNew.txt" //In
    );


    if (!bMove)
        std::operator<<(std::cout, "Erro ao mover arquivo ").operator<<(GetLastError()).operator<<(std::endl);
    
    std::operator<<(std::cout, "Sucesso ao mover o arquivo !").operator<<(std::endl);

    return 0;
}