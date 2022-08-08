#include <iostream>
#include <Windows.h>

auto main( ) -> int
{

    std::cout << "Hello World!\n";

    std::basic_string< char, std::char_traits< char >, std::allocator< char > > path( "C:\\Users\\oimeuchapavm\\Downloads\\imags\\ElonMuskTorso.png" );

    //https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-systemparametersinfow
    if (!SystemParametersInfoW(
        _In_ SPI_SETDESKWALLPAPER, //[in]
        _In_ 0, //[in]
        _Inout_ _Pre_maybenull_ _Post_valid_(void*)path.c_str(), //[in, out]
        _In_ SPIF_SENDCHANGE //[in]
    ))
        std::operator<<(std::cout, "Erro ao definir wallpaper !\n");

    std::operator<<(std::cout, "Sucesso ao definir wallpaper !");

    return 0;
}