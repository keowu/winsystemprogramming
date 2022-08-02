#include <iostream>
#include <Windows.h>


auto main( ) -> int
{

    std::cout << "Hello World!\n";


    /*
        Os Registros:

        Os registros podem ser definidos como uma "database" hierarquica e centralizada para aplicações
        e para configurações do sistema operacional

        Informação: Registros no Windows são armazenados seguindo o padrão chave/valor

        Os registros podem conter informações como por exemplo:

            1 - Número da versão, número da build, e dados do usuário.
            2 - Informações sobre o computador como por exemplo tipo do processador
            3 - Informações especificas do usuário
            4 - Segurança da informação
            5 - Serviços instalados, isso incluí drivers/anticheats etc
            6 - Nome do arquivo e extensões

        Chaves de registro:
            1 - HKEY_LOCAL_MACHINE: É armazenado informações fisicas sobre a maquna com os softwares instalados.
            2 - HKEY_USERS: É definido informaões de configurações para o usuário
            3 - HKEY_CURRENT_CONFIG: Contem configurações para o usuário como fontes e resoluções
            4 - HKEY_CLASSES_ROOT: Contem entradas para mapeamento de arquivos e extenções
            5 - HKEY_CURRENT_USER: Contem informações especificas do usuário

        Para Windows internals você pode acessar os registros através do regedit.exe


    */

    //https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regcreatekeyexa

    HKEY hKey;

    LONG lReg = RegCreateKeyEx(
            HKEY_LOCAL_MACHINE, //[in] -> HKEY_CLASSES_ROOT, HKEY_CURRENT_CONFIG, HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE e HKEY_USERS
            L"Software\\VmpSoftware\\VmProtect\\License\\licenseID", //[in] -> https://docs.microsoft.com/en-us/windows/desktop/SysInfo/structure-of-the-registry
            NULL, //[optional]
            NULL, //[in]
            REG_OPTION_NON_VOLATILE, //[in] -> REG_OPTION_BACKUP_RESTORE, REG_OPTION_CREATE_LINK, REG_OPTION_VOLATILE e a MAIS COMUM QUE É A REG_OPTION_NON_VOLATILE
            KEY_ALL_ACCESS | KEY_WOW64_64KEY, //[in] -> https://docs.microsoft.com/en-us/windows/win32/sysinfo/registry-key-security-and-access-rights
            NULL, //[optional]
            &hKey, //[out]
            NULL  //[optional]
    );


    if (lReg == ERROR_SUCCESS)
        std::operator<<(std::cout, "Erro ao criar a chave de registro ").operator<<(GetLastError()).operator<<(std::endl);
    

    std::operator<<(std::cout, "Sucesso ao criar chave de registro !").operator<<(std::endl);

    std::cin.get();

    DWORD dwData = 777;

    //https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regsetvalueexa
    lReg = RegSetValueEx(
        hKey,  //[in]
        L"LICENSEID_OLAMUNDO", //[in, optional]
        NULL, //Brisas da Microsoft [Reserved]
        REG_DWORD, //[in] REG_DWORD - Um número de 32-bit -> https://docs.microsoft.com/en-us/windows/win32/sysinfo/registry-value-types
        reinterpret_cast<LPBYTE>(& dwData), //[in] 
        sizeof(dwData) //[in] 
    );

    if (lReg != ERROR_SUCCESS) 
        std::operator<<(std::cout, "Erro ao definir valor para a chave de registro ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao definir um valor para a chave de registro !").operator<<(std::endl);

    //https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regclosekey
    RegCloseKey(
        hKey //[in]
    );


    return 0;
}