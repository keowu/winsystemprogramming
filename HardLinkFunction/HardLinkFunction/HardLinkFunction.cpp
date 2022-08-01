#include <iostream>
#include <Windows.h>

auto main() -> int
{

    std::cout << "Hello World!\n";

    /*
    * Hardlink
        1 - Um arquivo pode ter dois diferentes nomes
        2 - Hardlink somente pode ser criado para arquivos e não para diretórios
        3 - Se você excluir o arquivo original, então ele podera ser acessivel via um hardlink do arquivo
        4 - Isso é criado na memória(Memória Física)
    */

    //https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createhardlinka
    BOOL hFile = CreateHardLink(
        L"C:\\Users\\oimeuchapavm\\Downloads\\Nova pasta (2)\\a.txt",
        L"C:\\Users\\oimeuchapavm\\Downloads\\Nova pasta (2)\\testeardlink.txt",
        NULL
    );

    if (!hFile)
        std::operator<<(std::cout, "Erro ao criar um hardlink").operator<<(std::endl);
    
    std::operator<<(std::cout, "Sucesso ao criar hardlink").operator<<(std::endl);

    return 0;
}