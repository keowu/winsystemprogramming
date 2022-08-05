#include <iostream>
#include <Windows.h>
#include <winsock.h>

auto main( ) -> int
{
    //Para compilar vá em Vinculador -> input -> Dependências adicionais -> editar -> coloque WS2_32.lib
    std::cout << "Hello World!\n";

    /*
        Programando o socket do Windows
         
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

        User Datagram Protocol:
            1. Orientado a mensagem
            2. perdas de conexão por exemplo: sem conexão ou manutenções
            3. Tamanho pequeno(Cabeçalho do UDP é 60% menor que o cabeçalho do TCP)
            4. Pequeno tamanho do pacote, cabeçalho do UDP tem 8 Bytes.
            5. Não possui detecção de erros
            6. Se perder data então não é possivel recuperar
            7. Dados corrompidos podem ser descartados conforme a ordem
            8. Exemplo é um e-mail

            [ABCDE] ----------------------> [ABDE]
                                             [C]

       Protocolo de conexão:
        Servidor                  Cliente
           [Socket]                 [Socket]
           [Bind]                   [Bind]
           [Recv]                   [Send]
           [Send]                   [Recv]
           [Close]                  [Close]

        Passos para programar o UDP:

            Servidor:                                                                               Cliente:
                [WSAStartUp]                                                                             [WSAStartUp]
                [Preencher a struct do cliente Cliente ou Servidor]                                      [Preencher a struct do cliente ou servidor]
                [Socket]                                                                                 [Socket]
                [Bind]                                                                                   [Send e Recv]
                [Recv e send]                                                                            [CloseSocket]
                [closesocket]                                                                            [WSACleanUp]
                [WSACleanUp] 

    */

    WSADATA wSocketData{ 0 };

    SOCKET uDPSocketServer{ 0 };
    struct sockaddr_in UDPCliente { 0 };

    char buffer[512]{ 0 };
    int iBufferLen = sizeof(buffer) + 1;

    int iUDPClienteLen = sizeof(UDPCliente) + 1;

    //Iniciando winsock
    
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
    int iWsaStartup = WSAStartup(
        _In_ MAKEWORD(2, 2), //[in]
        _Out_ &wSocketData //[out]
    );

    if (iWsaStartup != 0)
        std::operator<<(std::cout, "Falhou em iniciar o socket com WSAStartup !\n");

    std::operator<<(std::cout, "Sucesso ao criar socket com WSAStartup !\n");

    //Preencher detalhes da struct
    UDPCliente.sin_family = AF_INET;
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-inet_addr
    UDPCliente.sin_addr.S_un.S_addr = inet_addr(
        _In_ "127.0.0.1" //[in]
    );
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-htons
    UDPCliente.sin_port = htons(
        _In_ 8001 //[in]
    );

    //Criar o socket

    //https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
    uDPSocketServer = socket(
        _In_ AF_INET,    //[in]
        _In_ SOCK_DGRAM, //[in]
        _In_ IPPROTO_UDP //[in]
    );

    if(uDPSocketServer == INVALID_SOCKET)
        std::operator<<(std::cout, "Falhou em iniciar o socket: !").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao criar socket !\n");

    //Bind

    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-bind
    int iBind = bind(
       _In_ uDPSocketServer,    //[in]
        _In_reads_bytes_(UDPCliente) (SOCKADDR *)&UDPCliente, //[in]
        sizeof(UDPCliente)  //[in]
    );

    if(iBind == SOCKET_ERROR)
        std::operator<<(std::cout, "O Bind falhou ao ser efetuado: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao fazer o bind !\n");

    //recv dados

    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-recvfrom
    int iReceiveFrom = recvfrom(
        _In_ uDPSocketServer, //[in]
        _Out_ buffer, //[out]
        _In_ iBufferLen,  //[in]
        _In_ MSG_PEEK,  //[in]
        _Out_writes_bytes_to_opt_(*iUDPClienteLen, *iUDPClienteLen) (SOCKADDR*)&UDPCliente, //[out]
        _In_opt_z_ &iUDPClienteLen //[in, out, optional]
    );

    if(iReceiveFrom == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao receber: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao receber dados !\n");

    std::printf("Recebido: %s\n", buffer);

    //fechando socket
    
    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-closesocket
    int iCloseSocket = closesocket(
        _In_ uDPSocketServer //[in]
    );

    if(iCloseSocket == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao fechar socket: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao fechar socket !\n");

    //limpando

    //https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsacleanup
    int iWsaCleanup = WSACleanup(
    );

    if(iWsaCleanup == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao limpar socket: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao limpar o socket !\n");

    return 0;
}