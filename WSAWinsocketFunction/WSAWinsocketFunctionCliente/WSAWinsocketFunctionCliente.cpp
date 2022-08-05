#include <iostream>
#include <Windows.h>
#include <winsock.h>

auto main( ) -> int
{
    //Para compilar vá em Vinculador -> input -> Dependências adicionais -> editar -> coloque WS2_32.lib

    std::cout << "Hello World!\n";


    WSADATA wSocketData{ 0 };

    SOCKET uDPSocketServer{ 0 };
    struct sockaddr_in UDPServer { 0 };

    char buffer[512]{ "Ola mundo !! Do Keowu, HELLO WORLD FROM KEOWU !! "};
    int iBufferLen = sizeof(buffer) + 1;

    int iUDPServerLen = sizeof(UDPServer) + 1;

    //Iniciando winsock

    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
    int iWsaStartup = WSAStartup(
        _In_ MAKEWORD(2, 2), //[in]
        _Out_ & wSocketData //[out]
    );

    if (iWsaStartup != 0)
        std::operator<<(std::cout, "Falhou em iniciar o socket com WSAStartup !\n");

    std::operator<<(std::cout, "Sucesso ao criar socket com WSAStartup !\n");

    //Preencher detalhes da struct
    UDPServer.sin_family = AF_INET;
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
    UDPServer.sin_addr.S_un.S_addr = inet_addr(
        _In_ "127.0.0.1" //[in]
    );
    ////https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-htons
    UDPServer.sin_port = htons(
        _In_ 8001 //[in]
    );

    //Criar o socket

    //https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
    uDPSocketServer = socket(
        _In_ AF_INET,    //[in]
        _In_ SOCK_DGRAM, //[in]
        _In_ IPPROTO_UDP //[in]
    );

    if (uDPSocketServer == INVALID_SOCKET)
        std::operator<<(std::cout, "Falhou em iniciar o socket: !").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao criar socket !\n");

    //send dados

    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-sendto
    int iSendFrom = sendto(
        _In_ uDPSocketServer, //[in]
        _In_ buffer, //[in]
        _In_ iBufferLen, //[in]
        _In_ MSG_DONTROUTE, //[in]
        _In_ (SOCKADDR*)&UDPServer, //[in]
        _In_ iUDPServerLen //[in]
    );

    if (iSendFrom == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao enviar: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao enviar dados !\n");

    //fechando socket

    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-closesocket
    int iCloseSocket = closesocket(
        _In_ uDPSocketServer //[in]
    );

    if (iCloseSocket == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao fechar socket: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao fechar socket !\n");

    //limpando
    
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsacleanup
    int iWsaCleanup = WSACleanup(
    );

    if (iWsaCleanup == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao limpar socket: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao limpar o socket !\n");


    return 0;
}