#include <iostream>
#include <Windows.h>


auto main() -> int
{

    std::cout << "Hello World!\n";

    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createdirectorya
    BOOL bDir = CreateDirectory(
        L"C:\\Users\\oimeuchapavm\\Downloads\\Nova pasta (2)\\dirnovo", //in
        NULL //in opt
    );

    if (!bDir) {
        DWORD err = GetLastError();
        std::operator<<(std::cout, "Erro ao criar diretorio ").operator<<(err).operator<<(std::endl);
    }

    std::operator<<(std::cout, "SUCESSO ao criar diretorio !").operator<<(std::endl);

    std::cin.get();

    bDir = RemoveDirectory(
        L"C:\\Users\\oimeuchapavm\\Downloads\\Nova pasta (2)\\dirnovo"
    );

    if (!bDir) {
        DWORD err = GetLastError();
        std::operator<<(std::cout, "Erro ao excluir diretorio ").operator<<(err).operator<<(std::endl);
    }

    std::operator<<(std::cout, "SUCESSO ao excluir diretorio !").operator<<(std::endl);

    return 0;
}
