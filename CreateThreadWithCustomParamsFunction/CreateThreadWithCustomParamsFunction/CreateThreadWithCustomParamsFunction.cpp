#include <iostream>
#include <Windows.h>


typedef struct blastruct{
    std::int32_t idade;
    bool isInfeliz;
};


DWORD WINAPI MinhaThread(LPVOID params) {

    auto bla = *reinterpret_cast<blastruct *>(params);
    
    std::printf("\nIDADE: %d, FELIZ: %d", bla.idade, bla.isInfeliz);

    return 0;
}


auto main() -> int
{

    std::cout << "Hello World!\n";

    DWORD dTID;

    blastruct* bla = reinterpret_cast<blastruct*>(malloc(sizeof(blastruct)));

    ZeroMemory(bla, sizeof(bla));

    bla->idade = 400;

    bla->isInfeliz = false;

    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread
    HANDLE hThread = CreateThread(
        NULL, //[in, optional]
        0, //[in]
        MinhaThread, //[in]
        (void*)bla, //[in, optional]
        NULL, //[in]
        &dTID //[out, optional]
    );

    if (hThread == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Ocorreu um erro ao abrir um handle para a thread: ").operator<<(GetLastError()).operator<<(std::endl);
    
    std::operator<<(std::cout, "Sucesso ao criar um handle para a thread, ela comecou a executar !");

    return 0;
}