#include <iostream>
#include <Windows.h>
#include <winsock.h>

auto main( ) -> int
{

    //Para compilar vá em Vinculador -> input -> Dependências adicionais -> editar -> coloque WS2_32.lib
    std::cout << "Hello World!\n";

    WSADATA WinsockData{ 0 };

    struct sockaddr_in TCPServerAdd { 0 };
    struct sockaddr_in TCPClientAdd { 0 };
    int iTCPClientAdd = sizeof(TCPClientAdd);

    char SenderBuff[512] = "Hello Servidor chegou sim !";
    int iSenderBuffer = strlen(SenderBuff) + 1;

    char RecvBuffer[512]{ 0 };
    int iRecvBuffer = sizeof(RecvBuffer) + 1;

    //1º WSAStartUp
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
    int iWsaStartup = WSAStartup(
        _In_ MAKEWORD(2, 2), //[in]
        _Out_ &WinsockData //[out]
    );

    if (iWsaStartup != NULL)
        std::operator<<(std::cout, "Erro ao inicializar WSA !\n");

    std::operator<<(std::cout, "Sucesso ao inicializar WSAStartUp !\n");

    //2º Preencher a struct
    TCPServerAdd.sin_family = AF_INET;
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-inet_addr
    TCPServerAdd.sin_addr.S_un.S_addr = inet_addr(
        _In_ "127.0.0.1" //[in]
    );
    
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-htons
    TCPServerAdd.sin_port = htons(
        _In_ 8000 //[in]
    );

    //3º Criar o socket
    
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
    SOCKET TCPClientSocket = socket(
        _In_ AF_INET, //[in]
        _In_ SOCK_STREAM, //[in]
        _In_ IPPROTO_TCP //[in]
    );

    if (TCPClientSocket == INVALID_SOCKET)
        std::operator<<(std::cout, "Erro ao inicializar socket TCP: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao inicializar o socket TCP !\n");

    //4º Conectar
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-connect
    int iConnect = connect(
        _In_ TCPClientSocket, //[in]
        _In_reads_bytes_(TCPServerAdd) (SOCKADDR*)&TCPServerAdd, //[in]
        _In_ sizeof(TCPServerAdd) //[in]
    );

    if(iConnect == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao conectar socket TCP: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao conectar o socket TCP !\n");

    //5º Receber dados do Cliente
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-recv
    int iRecv = recv(
        _In_ TCPClientSocket, //[in]
        _Out_ RecvBuffer, //[out]
        _In_ iRecvBuffer, //[in]
        _In_ 0   //[in]
    );

    if (iRecv == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro receber informações do cliente: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao receber informações para o cliente !\n");

    std::printf("Recebido: %s \n", RecvBuffer);

    //6º Enviar dados para o servidor
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-send
    int iSend = send(
        _In_ TCPClientSocket, //[in]
        _In_reads_bytes_(iSenderBuffer) SenderBuff, //[in]
        _In_ iSenderBuffer, //[in]
        _In_ 0 //[in]
    );

    if(iSend == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao enviar buffer: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao enviar buffer !\n");

    //7º Fechar socket
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-closesocket
    int iSocketClose = closesocket(
        _In_ TCPClientSocket //[in]
    );

    if (iSocketClose == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao fechar o socket: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao fechar o socket !\n");

    //8º cleanup
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsacleanup
    int iWSACleanUp = WSACleanup(
    );

    if (iWSACleanUp == INVALID_SOCKET)
        std::operator<<(std::cout, "Erro ao fazer o WSACleanUp: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao fazer o WSACleanUp !\n");

    return 0;
}