#include <Windows.h>
#include <iostream>
using namespace std;

void PauseScreen()
{
    cin.get();
}

void getinfo()
{
    static HANDLE h = NULL;
    if (!h)
    {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h, &csbi);

    short Top = csbi.srWindow.Top;
    short Bottom = csbi.srWindow.Bottom;
    short Left = csbi.srWindow.Left;
    short Right = csbi.srWindow.Right;

    short width = Right - Left + 1;
    short height = Bottom - Top + 1;

    cout << "width : " << width << endl;
    cout << "height : " << height << endl;
}

int main()
{
    while (1)
    {
        getinfo();
        cin.get();
        system("cls");
    }

    PauseScreen();
}
