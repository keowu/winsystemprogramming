#include <iostream>
#include <Windows.h>

auto main() -> int
{

    std::cout << "Hello World!\n";

    /*
        1 - Um arquivo pode ter diferentes nomes
        2 - Soft link pode ser criado para arquivos e diretórios
        3 - Se o arquivo original for excluído, então vou não pode acessar o arquivo soft link
        4 - Soft link é um atalho para o arquivo original
    */

    //https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createsymboliclinka
    BOOL bSym = CreateSymbolicLink(
        L"C:\\Users\\oimeuchapavm\\Downloads\\Nova pasta (2)\\testeardlink.txt",
        L"C:\\Users\\oimeuchapavm\\Downloads\\Nova pasta (2)\\testeardlink2.txt",
        NULL // 0(NULL) para arquivos, SYMBOLIC_LINK_FLAG_DIRECTORY(Para diretórios)
    );

    if (!bSym)
        std::operator<<(std::cout, "Falhou ao criar o symboliclink ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar o symboliclink !").operator<<(std::endl);    

    return 0;
}