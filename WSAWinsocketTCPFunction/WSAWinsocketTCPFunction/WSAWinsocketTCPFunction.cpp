#include <iostream>
#include <Windows.h>
#include <winsock.h>

auto main( ) -> int
{

    //Para compilar vá em Vinculador -> input -> Dependências adicionais -> editar -> coloque WS2_32.lib
    std::cout << "Hello World!\n";

    /*
        Programando o socket TCP do Windows
         
         O que é o socket:
            Socket é um endpoint no qual é usado para comunicação entre dois nós de rede.
            Socket é uma interface que segue a arquitetura cliente-servidor
                            Socket
            [ Server ]    ---------------  [Cliente]
        Tipos de socket:
            - Sockets de internet
            - Unix sockets
            - x.25 sockets entre outros.
        Internet sockets:
            Internet socket é caracterizado por um endereço ip(4 Bytes) e uma porta(2 bytes)
            é um protocolo de transporte

        Tipos:
            1. Sockets de stream(Stream Sock)
                i. Orientado a conexão
                ii. Confiar no TCP que provê dois caminhos de conexão
            2. Sockets de datagram(Dgram Sock)
                i. A conexão não é confiável
                ii. Confiar no UDP

        Transmission Control Protocol(TCP):
            1. Baseado em stream
            2. Orientado a conexão
            3. Tamanho grande porque só o cabeçalho do TCP tem 20 Bytes
            4. Provê correção de erros(AÍ ENTRA NEQUELE CONCEITO DE PARIDADE DE BIT)
            5. Re-transmissão de dados se os dados forem corrompidos
            6. Prove transmissão de dados em ordem
            Exemplo - Telefone:
                [ABCDE] -----------------------------------> [AB(C)DE] ---------------------------->[ABCDE]
                    |_____________________________________________|
                           Retransmissão de dados corrompidos
       

       Protocolo orientado a conexão:

        Servidor:                                  Cliente:
            SOCKET                                      SOCKET
            BIND
            LISTEN  <-------------------------------    CONNECT
            ACCEPT
            SEND    ------------------------------->    RECV
            RECV    <-------------------------------    SEND
            CLOSE                                       CLOSE


        Passo para programar TCP:
            Servidor:                                                                Cliente:
            1. WSAStartUp                                                            1. WSAStartUp
            2. Preencher as structs do Cliente ou Servidor                           2. Preencher a struct do cliente
            3. Socket                                                                3. Socket
            4. Bind                                                                  4. Connect
            5. Listen                                                                5. sendto ou recvfrm
            6. Accept                                                                6. closesocket
            7. recvfrm ou sendto                                                     7.WSACleanUp
            8. closesocket
            9. WSACleanUp

    */
    WSADATA WinsockData{ 0 };

    struct sockaddr_in TCPServerAdd{ 0 };
    struct sockaddr_in TCPClientAdd{ 0 };
    int iTCPClientAdd = sizeof(TCPClientAdd);

    char SenderBuff[512] = "Hello World from Keowu, Ola Mundo do Keowu, usando TCP(Transmission control Protocol)";
    int iSenderBuffer = strlen(SenderBuff)+1;

    char RecvBuffer[512]{ 0 };
    int iRecvBuffer = sizeof(RecvBuffer)+1;

    //1º WSAStartUp
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
    int iWsaStartup = WSAStartup(
        _In_ MAKEWORD(2, 2), //[in]
        _Out_ &WinsockData //[out]
    );

    if(iWsaStartup != NULL)
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
    SOCKET TCPServerSocket = socket(
        _In_ AF_INET, //[in]
        _In_ SOCK_STREAM, //[in]
        _In_ IPPROTO_TCP //[in]
    );

    if (TCPServerSocket == INVALID_SOCKET)
        std::operator<<(std::cout, "Erro ao inicializar socket TCP: ").operator<<(WSAGetLastError()).operator<<("\n");
    
    std::operator<<(std::cout, "Sucesso ao inicializar o socket TCP !\n");

    //3º Função Bind
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-bind
    int iBind = bind(
        _In_ TCPServerSocket, //[in]
        _In_reads_bytes_(TCPServerAdd) (SOCKADDR*)&TCPServerAdd, //[out]
        _In_ sizeof(TCPServerAdd) //[in]
    );

    if(iBind == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao fazer o bind: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao fazer o bind !\n");

    //5º Função de escuta
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen
    int iListen = listen(
        _In_ TCPServerSocket, //[in]
        _In_ 2   //[in]
    );

    if(iListen == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao listen: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao listen do servidor !\n");

    //6º Aceitar
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept
    SOCKET sAcceptSocket = accept(
        _In_ TCPServerSocket, //[in]
        _Out_writes_bytes_opt_(*iTCPClientAdd) (SOCKADDR*)&TCPClientAdd, //[out]
        _Inout_ &iTCPClientAdd //[in, out]
    );

    if(sAcceptSocket == INVALID_SOCKET)
        std::operator<<(std::cout, "Erro ao aceitar: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao aceitar !\n");

    //7º Enviar Dados para o Cliente

    //https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-send
    int iSend = send(
        _In_ sAcceptSocket, //[in]
        _In_reads_bytes_(iSenderBuffer) SenderBuff, //[in]
        _In_ iSenderBuffer, //[in]
        _In_ 0 //[in]
    );

    if(iSend == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro enviar para o cliente: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao enviar para o cliente !\n");

    //8º Receber dados do Cliente
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-recv
    int iRecv = recv(
        _In_ sAcceptSocket, //[in]
        _Out_writes_bytes_to_(iRecvBuffer, return) RecvBuffer, //[out] 
        _In_ iRecvBuffer,  //[in]
        _In_ 0  //[in]
    );

    if(iRecv == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro receber informações do cliente: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao receber informações para o cliente !\n");

    //Escrevendo dados
    std::printf("Recebido: %s \n", RecvBuffer);

    //9º Fechar socket
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-closesocket
    int iSocketClose = closesocket(
        _In_ TCPServerSocket //[in]
    );

    if(iSocketClose == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao fechar o socket: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao fechar o socket !\n");

    //10º cleanup
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsacleanup
    int iWSACleanUp = WSACleanup(
    );

    if(iWSACleanUp == INVALID_SOCKET)
        std::operator<<(std::cout, "Erro ao fazer o WSACleanUp: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao fazer o WSACleanUp !\n");

    return 0;
}