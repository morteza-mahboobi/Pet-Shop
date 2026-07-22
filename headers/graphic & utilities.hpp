#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <conio.h>
#include <cmath>
#include <type_traits>
#include "printEnum.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ios;
using std::is_same_v;
using std::string;
using std::to_string;
using std::vector;

#define PathIds "file/ids.dat"

#define Padding 2
#define Margin 1
#define BorderShape '#'
#define ButtonBorderH '-'
#define ButtonBorderV '|'
#define TitleBorder '='
#define TimeSleepLoading 80
#define ENTER_KEY 13
#define ESC_KEY 27
#define UP_KEY 72
#define DOWN_KEY 80
#define RIGHT_KEY 77
#define LEFT_KEY 75

enum DirectionType
{
    Horizontal = 1 << 0,
    Vertical = 1 << 1
};

enum class CursorPlace
{
    ZeroZero,
    LastLocation,
    RightWhereYouAre,
    BeginningNextLine
};

enum class ObjectType
{
    User,
    Pet
};

enum class UserInfo
{
    Id,
    Name,
    Username,
    Password,
    PhoneNumber,
    Type,
    Balance
};

enum class PetInfo
{
    PetId,
    Name,
    Age,
    Price,
    Breed,
    Color,
    Status,
    SellerName,
    Species,
    Rating,
    Ratings,
    FlightHeight,
    Sound,
    Iq,
    Water,
    AquariumSize,
    SwimmingSpeed,
    SpeedUnit,
    RunningSpeed,
    ManeColor,
    EnergyLevel
};

enum class SelectorType
{
    MenuSelector,
    OptionSelector,
    BoxesSelector,
    TransactionSelector
};

//==========================================================

void FullScreen()
{
    // Down Keys Alt + Enter
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_RETURN, 0, 0, 0);

    // Up Keys Alt + Enter
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
}

void GoToXY(short x, short y)
{
    static HANDLE h = NULL;
    if (!h)
    {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

CONSOLE_SCREEN_BUFFER_INFO GetWidthHeight(short *width = nullptr, short *height = nullptr)
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

    if (width != nullptr && height != nullptr)
    {
        *width = Right - Left + 1;
        *height = Bottom - Top + 1;
    }

    return csbi;
}

string normalizeFloatString(string str)
{
    int indexOfFirstZero = str.find('0', str.find('.', 0));

    for (int i = indexOfFirstZero; i < str.size(); i++)
    {
        if (str[i] != '0')
        {
            indexOfFirstZero = i + 1;
        }
    }

    if (indexOfFirstZero == str.find('.', 0) + 1)
    {
        indexOfFirstZero = str.find('.', 0);
    }

    if (indexOfFirstZero != string::npos)
    {
        str = str.erase(indexOfFirstZero);
    }

    return str;
}

//==========================================================

void DrawBorder(short padding, short margin)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi = GetWidthHeight();

    short Top = csbi.srWindow.Top;
    short Bottom = csbi.srWindow.Bottom;
    short Left = csbi.srWindow.Left;
    short Right = csbi.srWindow.Right;

    for (int i = Top + margin; i <= Bottom - margin; i++)
    {
        for (int j = Left + margin; j <= Right - margin; j++)
        {
            if (i == Top + margin || j == Left + margin || i == Bottom - margin || j == Right - margin)
            {
                GoToXY(j, i);
                cout << BorderShape;
            }
        }
    }

    GoToXY(Top + padding + 1 + margin, Left + padding + 1 + margin);
}

void PutMidlle(vector<string> texts, int direction, CursorPlace cursorAfterPrint)
{
    short width, height;
    static HANDLE h = NULL;
    if (!h)
    {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    CONSOLE_SCREEN_BUFFER_INFO csbi = GetWidthHeight(&width, &height);

    short CurPosX = csbi.dwCursorPosition.X;
    short CurPosY = csbi.dwCursorPosition.Y;

    int i = 0;
    if (direction == Horizontal)
    {
        short middle;
        for (auto x : texts)
        {
            middle = (width - x.size()) / 2;
            GoToXY(middle, CurPosY + i);
            cout << x;
            i++;
        }
    }
    else if (direction == Vertical)
    {
        short middle;
        for (auto x : texts)
        {
            middle = (height - texts.size()) / 2;
            GoToXY(CurPosX, middle + i);
            cout << x;
            i++;
        }
    }
    else if (direction == Vertical | Horizontal)
    {
        short middle1;
        short middle2;
        for (auto x : texts)
        {
            middle1 = (width - x.size()) / 2;
            middle2 = (height - texts.size()) / 2;
            GoToXY(middle1, middle2 + i);
            cout << x;
            i++;
        }
    }

    if (cursorAfterPrint == CursorPlace::ZeroZero)
    {
        GoToXY(0, 0);
    }
    else if (cursorAfterPrint == CursorPlace::LastLocation)
    {
        GoToXY(CurPosX, CurPosY);
    }
    else if (cursorAfterPrint == CursorPlace::BeginningNextLine)
    {
        GetConsoleScreenBufferInfo(h, &csbi);

        CurPosY = csbi.dwCursorPosition.Y;

        GoToXY(CurPosX, CurPosY + 1);
    }
    else if (cursorAfterPrint == CursorPlace::RightWhereYouAre)
    {
    }
}

void PrintVecStr(vector<string> texts, DirectionType direction, char charForHorizontal = '\b')
{
    if (direction == DirectionType::Horizontal)
    {
        for (auto x : texts)
        {
            cout << x;
            if (x != texts[texts.size() - 1])
                cout << " " << charForHorizontal << " ";
        }
    }
    else if (direction == DirectionType::Vertical)
    {
        for (auto x : texts)
        {
            cout << x;
            cout << endl;
        }
    }
}

// for product and profile
void PrintBoxesInCenter(string beginningMessage, string endMessage, vector<vector<string>> objects)
{
    bool isThereBeginningMessage = !(beginningMessage == "");
    bool isThereEndMessage = !(endMessage == "");

    short width, height;
    GetWidthHeight(&width, &height);

    int horizontalBoxCount = objects.size();
    int totalBoxesWidth = 0;
    for (auto x : objects)
    {
        totalBoxesWidth += x[0].size();
    }
    int availableSpaceHorizontally = width - totalBoxesWidth;
    int horizontalGapBetweenBoxes = availableSpaceHorizontally / (horizontalBoxCount + 1);
    int spaceOfLeftSide = horizontalGapBetweenBoxes + (availableSpaceHorizontally % (horizontalBoxCount + 1)) / 2 + (availableSpaceHorizontally % (horizontalBoxCount + 1)) % 2;
    int spaceOfRightSide = horizontalGapBetweenBoxes + (availableSpaceHorizontally % (horizontalBoxCount + 1)) / 2;

    int verticalBoxCount = 0;
    int totalBoxesHeight = 0;
    // beginningMessage
    if (isThereBeginningMessage)
    {
        totalBoxesHeight += 1;
        verticalBoxCount += 1;
    }
    // objects
    totalBoxesHeight += objects[0].size();
    verticalBoxCount += 1;
    // endMessage
    if (isThereEndMessage)
    {
        totalBoxesHeight += 1;
        verticalBoxCount += 1;
    }
    int availableSpaceVertically = height - totalBoxesHeight;
    int verticalGapBetweenBoxes = availableSpaceVertically / (verticalBoxCount + 1);                                                                                  // number of box : 3
    int spaceOfTopSide = verticalGapBetweenBoxes + (availableSpaceVertically % (verticalBoxCount + 1)) / 2 + (availableSpaceVertically % (verticalBoxCount + 1)) % 2; // number of box : 3
    int spaceOfBottomSide = verticalGapBetweenBoxes + (availableSpaceVertically % (verticalBoxCount + 1)) / 2;                                                        // number of box : 3

    // top padding
    for (int i = 0; i < spaceOfTopSide; i++)
    {
        cout << endl;
    }

    // beginningMessage
    if (isThereBeginningMessage)
    {
        PutMidlle(vector{beginningMessage}, DirectionType::Horizontal, CursorPlace::BeginningNextLine);

        // gap
        for (int i = 0; i < verticalGapBetweenBoxes; i++)
        {
            cout << endl;
        }
    }

    // print boxes
    for (int i = 0; i < objects[0].size(); i++)
    {
        // left padding
        for (int j = 0; j < spaceOfLeftSide; j++)
        {
            cout << " ";
        }

        // print rows of each bowes
        for (int j = 0; j < objects.size() - 1; j++)
        {
            // print column
            cout << objects[j][i];

            // print gap
            for (int k = 0; k < horizontalGapBetweenBoxes; k++)
            {
                cout << " ";
            }
        }

        // print last column
        cout << objects[objects.size() - 1][i];
        cout << endl;
    }

    // endMessage
    if (isThereEndMessage)
    {
        // gap
        for (int i = 0; i < verticalGapBetweenBoxes; i++)
        {
            cout << endl;
        }

        PutMidlle(vector{endMessage}, DirectionType::Horizontal, CursorPlace::BeginningNextLine);
    }
}

void PrintTransaction(vector<string> finalText)
{
    cout << endl;
    for (auto x : finalText)
    {
        cout << x;
        cout << endl;
    }
    cout << endl;
}

//==========================================================

// for welcome page
vector<string> WelcomeText()
{
    short width, height;
    CONSOLE_SCREEN_BUFFER_INFO csbi = GetWidthHeight(&width, &height);

    vector<string> texts;

    if (height > 27)
    {
        if (width > 150)
        {
            texts = {
                "##     ## ####### ##       ######  ######  ###    ### #######     ########   ###### ",
                "##     ## ##      ##      ##      ##    ## ####  #### ##             ##     ##    ##",
                "##  #  ## #####   ##      ##      ##    ## ## #### ## #####          ##     ##    ##",
                "## ### ## ##      ##      ##      ##    ## ##  ##  ## ##             ##     ##    ##",
                " ### ###  ####### #######  ######  ######  ##      ## #######        ##      ###### ",
                " ",
                "######  ####### ########     ####### ##   ##  ######  ###### ",
                "##   ## ##         ##        ##      ##   ## ##    ## ##   ##",
                "######  #####      ##        ####### ####### ##    ## ###### ",
                "##      ##         ##             ## ##   ## ##    ## ##     ",
                "##      #######    ##        ####### ##   ##  ######  ##     "};
        }
        else if (width > 80)
        {
            texts = {
                "#   # ##### #      ####  ###  #   # #####      #####  ### ",
                "#   # #     #     #     #   # ## ## #            #   #   #",
                "# # # ####  #     #     #   # # # # ####         #   #   #",
                "## ## #     #     #     #   # #   # #            #   #   #",
                "#   # ##### #####  ####  ###  #   # #####        #    ### ",
                " ",
                "####  ##### #####    ##### #   #  ###  #### ",
                "#   # #       #      #     #   # #   # #   #",
                "####  ####    #       ###  ##### #   # #### ",
                "#     #       #          # #   # #   # #    ",
                "#     #####   #      ##### #   #  ###  #    "};
        }
        else
        {
            texts = {"WELCOME TO PET SHOP"};
        }
    }
    else
    {
        texts = {"WELCOME TO PET SHOP"};
    }

    return texts;
}

// for exit page
vector<string> FarewellText(int whichOne = 1)
{
    short width, height;
    CONSOLE_SCREEN_BUFFER_INFO csbi = GetWidthHeight(&width, &height);

    vector<string> texts;

    if (height > 28)
    {
        if (width > 170)
        {
            switch (whichOne)
            {
            case 1:
                texts = {
                    R"(                                                                                                                                                                    )",
                    R"($$$$$$$$\ $$\                           $$\                        $$$$$$\                                      $$\           $$\   $$\     $$\                     )",
                    R"(\__$$  __|$$ |                          $$ |                      $$  __$$\                                     \__|          \__|  $$ |    \__|                    )",
                    R"(   $$ |   $$$$$$$\   $$$$$$\  $$$$$$$\  $$ |  $$\  $$$$$$$\       $$ /  \__|$$$$$$\   $$$$$$\        $$\    $$\ $$\  $$$$$$$\ $$\ $$$$$$\   $$\ $$$$$$$\   $$$$$$\  )",
                    R"(   $$ |   $$  __$$\  \____$$\ $$  __$$\ $$ | $$  |$$  _____|      $$$$\    $$  __$$\ $$  __$$\       \$$\  $$  |$$ |$$  _____|$$ |\_$$  _|  $$ |$$  __$$\ $$  __$$\ )",
                    R"(   $$ |   $$ |  $$ | $$$$$$$ |$$ |  $$ |$$$$$$  / \$$$$$$\        $$  _|   $$ /  $$ |$$ |  \__|       \$$\$$  / $$ |\$$$$$$\  $$ |  $$ |    $$ |$$ |  $$ |$$ /  $$ |)",
                    R"(   $$ |   $$ |  $$ |$$  __$$ |$$ |  $$ |$$  _$$<   \____$$\       $$ |     $$ |  $$ |$$ |              \$$$  /  $$ | \____$$\ $$ |  $$ |$$\ $$ |$$ |  $$ |$$ |  $$ |)",
                    R"(   $$ |   $$ |  $$ |\$$$$$$$ |$$ |  $$ |$$ | \$$\ $$$$$$$  |      $$ |     \$$$$$$  |$$ |               \$  /   $$ |$$$$$$$  |$$ |  \$$$$  |$$ |$$ |  $$ |\$$$$$$$ |)",
                    R"(   \__|   \__|  \__| \_______|\__|  \__|\__|  \__|\_______/       \__|      \______/ \__|                \_/    \__|\_______/ \__|   \____/ \__|\__|  \__| \____$$ |)",
                    R"(                                                                                                                                                          $$\   $$ |)",
                    R"(                                                                                                                                                          \$$$$$$  |)",
                    R"(                                                                                                                                                           \______/ )",
                    R"( )",
                    R"( $$$$$$\                                                                                                        )",
                    R"($$  __$$\                                                                                                       )",
                    R"($$ /  \__| $$$$$$\   $$$$$$\        $$\   $$\  $$$$$$\  $$\   $$\        $$$$$$$\  $$$$$$\   $$$$$$\  $$$$$$$\  )",
                    R"(\$$$$$$\  $$  __$$\ $$  __$$\       $$ |  $$ |$$  __$$\ $$ |  $$ |      $$  _____|$$  __$$\ $$  __$$\ $$  __$$\ )",
                    R"( \____$$\ $$$$$$$$ |$$$$$$$$ |      $$ |  $$ |$$ /  $$ |$$ |  $$ |      \$$$$$$\  $$ /  $$ |$$ /  $$ |$$ |  $$ |)",
                    R"($$\   $$ |$$   ____|$$   ____|      $$ |  $$ |$$ |  $$ |$$ |  $$ |       \____$$\ $$ |  $$ |$$ |  $$ |$$ |  $$ |)",
                    R"(\$$$$$$  |\$$$$$$$\ \$$$$$$$\       \$$$$$$$ |\$$$$$$  |\$$$$$$  |      $$$$$$$  |\$$$$$$  |\$$$$$$  |$$ |  $$ |)",
                    R"( \______/  \_______| \_______|       \____$$ | \______/  \______/       \_______/  \______/  \______/ \__|  \__|)",
                    R"(                                    $$\   $$ |                                                                  )",
                    R"(                                    \$$$$$$  |                                                                  )",
                    R"(                                     \______/                                                                   )",
                    R"(                                                                                                                )"};
                break;
            case 2:
                texts = {
                    R"(                                                                                                                                                                    )",
                    R"( /$$$$$$$$ /$$                           /$$                        /$$$$$$                                     /$$           /$$   /$$     /$$                     )",
                    R"(|__  $$__/| $$                          | $$                       /$$__  $$                                   |__/          |__/  | $$    |__/                     )",
                    R"(   | $$   | $$$$$$$   /$$$$$$  /$$$$$$$ | $$   /$$  /$$$$$$$      | $$  \__//$$$$$$   /$$$$$$        /$$    /$$ /$$  /$$$$$$$ /$$ /$$$$$$   /$$ /$$$$$$$   /$$$$$$  )",
                    R"(   | $$   | $$__  $$ |____  $$| $$__  $$| $$  /$$/ /$$_____/      | $$$$   /$$__  $$ /$$__  $$      |  $$  /$$/| $$ /$$_____/| $$|_  $$_/  | $$| $$__  $$ /$$__  $$ )",
                    R"(   | $$   | $$  \ $$  /$$$$$$$| $$  \ $$| $$$$$$/ |  $$$$$$       | $$_/  | $$  \ $$| $$  \__/       \  $$/$$/ | $$|  $$$$$$ | $$  | $$    | $$| $$  \ $$| $$  \ $$ )",
                    R"(   | $$   | $$  | $$ /$$__  $$| $$  | $$| $$_  $$  \____  $$      | $$    | $$  | $$| $$              \  $$$/  | $$ \____  $$| $$  | $$ /$$| $$| $$  | $$| $$  | $$ )",
                    R"(   | $$   | $$  | $$|  $$$$$$$| $$  | $$| $$ \  $$ /$$$$$$$/      | $$    |  $$$$$$/| $$               \  $/   | $$ /$$$$$$$/| $$  |  $$$$/| $$| $$  | $$|  $$$$$$$ )",
                    R"(   |__/   |__/  |__/ \_______/|__/  |__/|__/  \__/|_______/       |__/     \______/ |__/                \_/    |__/|_______/ |__/   \___/  |__/|__/  |__/ \____  $$ )",
                    R"(                                                                                                                                                          /$$  \ $$ )",
                    R"(                                                                                                                                                         |  $$$$$$/ )",
                    R"(                                                                                                                                                          \______/  )",
                    R"( )",
                    R"(  /$$$$$$                                                                                                       )",
                    R"( /$$__  $$                                                                                                      )",
                    R"(| $$  \__/  /$$$$$$   /$$$$$$        /$$   /$$  /$$$$$$  /$$   /$$        /$$$$$$$  /$$$$$$   /$$$$$$  /$$$$$$$ )",
                    R"(|  $$$$$$  /$$__  $$ /$$__  $$      | $$  | $$ /$$__  $$| $$  | $$       /$$_____/ /$$__  $$ /$$__  $$| $$__  $$)",
                    R"( \____  $$| $$$$$$$$| $$$$$$$$      | $$  | $$| $$  \ $$| $$  | $$      |  $$$$$$ | $$  \ $$| $$  \ $$| $$  \ $$)",
                    R"( /$$  \ $$| $$_____/| $$_____/      | $$  | $$| $$  | $$| $$  | $$       \____  $$| $$  | $$| $$  | $$| $$  | $$)",
                    R"(|  $$$$$$/|  $$$$$$$|  $$$$$$$      |  $$$$$$$|  $$$$$$/|  $$$$$$/       /$$$$$$$/|  $$$$$$/|  $$$$$$/| $$  | $$)",
                    R"( \______/  \_______/ \_______/       \____  $$ \______/  \______/       |_______/  \______/  \______/ |__/  |__/)",
                    R"(                                     /$$  | $$                                                                  )",
                    R"(                                    |  $$$$$$/                                                                  )",
                    R"(                                     \______/                                                                   )",
                    R"(                                                                                                                )"};
                break;
            case 3:
                texts = {
                    R"( ________  __                            __                         ______                                       __            __    __      __                     )",
                    R"(|        \|  \                          |  \                       /      \                                     |  \          |  \  |  \    |  \                    )",
                    R"( \$$$$$$$$| $$____    ______   _______  | $$   __   _______       |  $$$$$$\ ______    ______         __     __  \$$  _______  \$$ _| $$_    \$$ _______    ______  )",
                    R"(   | $$   | $$    \  |      \ |       \ | $$  /  \ /       \      | $$_  \$$/      \  /      \       |  \   /  \|  \ /       \|  \|   $$ \  |  \|       \  /      \ )",
                    R"(   | $$   | $$$$$$$\  \$$$$$$\| $$$$$$$\| $$_/  $$|  $$$$$$$      | $$ \   |  $$$$$$\|  $$$$$$\       \$$\ /  $$| $$|  $$$$$$$| $$ \$$$$$$  | $$| $$$$$$$\|  $$$$$$\)",
                    R"(   | $$   | $$  | $$ /      $$| $$  | $$| $$   $$  \$$    \       | $$$$   | $$  | $$| $$   \$$        \$$\  $$ | $$ \$$    \ | $$  | $$ __ | $$| $$  | $$| $$  | $$)",
                    R"(   | $$   | $$  | $$|  $$$$$$$| $$  | $$| $$$$$$\  _\$$$$$$\      | $$     | $$__/ $$| $$               \$$ $$  | $$ _\$$$$$$\| $$  | $$|  \| $$| $$  | $$| $$__| $$)",
                    R"(   | $$   | $$  | $$ \$$    $$| $$  | $$| $$  \$$\|       $$      | $$      \$$    $$| $$                \$$$   | $$|       $$| $$   \$$  $$| $$| $$  | $$ \$$    $$)",
                    R"(    \$$    \$$   \$$  \$$$$$$$ \$$   \$$ \$$   \$$ \$$$$$$$        \$$       \$$$$$$  \$$                 \$     \$$ \$$$$$$$  \$$    \$$$$  \$$ \$$   \$$ _\$$$$$$$)",
                    R"(                                                                                                                                                          |  \__| $$)",
                    R"(                                                                                                                                                           \$$    $$)",
                    R"(                                                                                                                                                            \$$$$$$ )",
                    R"( )",
                    R"(  ______                                                                                                        )",
                    R"( /      \                                                                                                       )",
                    R"(|  $$$$$$\  ______    ______         __    __   ______   __    __         _______   ______    ______   _______  )",
                    R"(| $$___\$$ /      \  /      \       |  \  |  \ /      \ |  \  |  \       /       \ /      \  /      \ |       \ )",
                    R"( \$$    \ |  $$$$$$\|  $$$$$$\      | $$  | $$|  $$$$$$\| $$  | $$      |  $$$$$$$|  $$$$$$\|  $$$$$$\| $$$$$$$\)",
                    R"( _\$$$$$$\| $$    $$| $$    $$      | $$  | $$| $$  | $$| $$  | $$       \$$    \ | $$  | $$| $$  | $$| $$  | $$)",
                    R"(|  \__| $$| $$$$$$$$| $$$$$$$$      | $$__/ $$| $$__/ $$| $$__/ $$       _\$$$$$$\| $$__/ $$| $$__/ $$| $$  | $$)",
                    R"( \$$    $$ \$$     \ \$$     \       \$$    $$ \$$    $$ \$$    $$      |       $$ \$$    $$ \$$    $$| $$  | $$)",
                    R"(  \$$$$$$   \$$$$$$$  \$$$$$$$       _\$$$$$$$  \$$$$$$   \$$$$$$        \$$$$$$$   \$$$$$$   \$$$$$$  \$$   \$$)",
                    R"(                                    |  \__| $$                                                                  )",
                    R"(                                     \$$    $$                                                                  )",
                    R"(                                      \$$$$$$                                                                   )"};
                break;
            case 4:
                texts = {
                    R"( ________  __                            __                         ______                                      __            __    __      __                      )",
                    R"(/        |/  |                          /  |                       /      \                                    /  |          /  |  /  |    /  |                     )",
                    R"($$$$$$$$/ $$ |____    ______   _______  $$ |   __   _______       /$$$$$$  |______    ______         __     __ $$/   _______ $$/  _$$ |_   $$/  _______    ______   )",
                    R"(   $$ |   $$      \  /      \ /       \ $$ |  /  | /       |      $$ |_ $$//      \  /      \       /  \   /  |/  | /       |/  |/ $$   |  /  |/       \  /      \  )",
                    R"(   $$ |   $$$$$$$  | $$$$$$  |$$$$$$$  |$$ |_/$$/ /$$$$$$$/       $$   |  /$$$$$$  |/$$$$$$  |      $$  \ /$$/ $$ |/$$$$$$$/ $$ |$$$$$$/   $$ |$$$$$$$  |/$$$$$$  | )",
                    R"(   $$ |   $$ |  $$ | /    $$ |$$ |  $$ |$$   $$<  $$      \       $$$$/   $$ |  $$ |$$ |  $$/        $$  /$$/  $$ |$$      \ $$ |  $$ | __ $$ |$$ |  $$ |$$ |  $$ | )",
                    R"(   $$ |   $$ |  $$ |/$$$$$$$ |$$ |  $$ |$$$$$$  \  $$$$$$  |      $$ |    $$ \__$$ |$$ |              $$ $$/   $$ | $$$$$$  |$$ |  $$ |/  |$$ |$$ |  $$ |$$ \__$$ | )",
                    R"(   $$ |   $$ |  $$ |$$    $$ |$$ |  $$ |$$ | $$  |/     $$/       $$ |    $$    $$/ $$ |               $$$/    $$ |/     $$/ $$ |  $$  $$/ $$ |$$ |  $$ |$$    $$ | )",
                    R"(   $$/    $$/   $$/  $$$$$$$/ $$/   $$/ $$/   $$/ $$$$$$$/        $$/      $$$$$$/  $$/                 $/     $$/ $$$$$$$/  $$/    $$$$/  $$/ $$/   $$/  $$$$$$$ | )",
                    R"(                                                                                                                                                         /  \__$$ | )",
                    R"(                                                                                                                                                         $$    $$/  )",
                    R"(                                                                                                                                                          $$$$$$/   )",
                    R"( )",
                    R"(  ______                                                                                                        )",
                    R"( /      \                                                                                                       )",
                    R"(/$$$$$$  |  ______    ______         __    __   ______   __    __         _______   ______    ______   _______  )",
                    R"($$ \__$$/  /      \  /      \       /  |  /  | /      \ /  |  /  |       /       | /      \  /      \ /       \ )",
                    R"($$      \ /$$$$$$  |/$$$$$$  |      $$ |  $$ |/$$$$$$  |$$ |  $$ |      /$$$$$$$/ /$$$$$$  |/$$$$$$  |$$$$$$$  |)",
                    R"( $$$$$$  |$$    $$ |$$    $$ |      $$ |  $$ |$$ |  $$ |$$ |  $$ |      $$      \ $$ |  $$ |$$ |  $$ |$$ |  $$ |)",
                    R"(/  \__$$ |$$$$$$$$/ $$$$$$$$/       $$ \__$$ |$$ \__$$ |$$ \__$$ |       $$$$$$  |$$ \__$$ |$$ \__$$ |$$ |  $$ |)",
                    R"($$    $$/ $$       |$$       |      $$    $$ |$$    $$/ $$    $$/       /     $$/ $$    $$/ $$    $$/ $$ |  $$ |)",
                    R"( $$$$$$/   $$$$$$$/  $$$$$$$/        $$$$$$$ | $$$$$$/   $$$$$$/        $$$$$$$/   $$$$$$/   $$$$$$/  $$/   $$/ )",
                    R"(                                    /  \__$$ |                                                                  )",
                    R"(                                    $$    $$/                                                                   )",
                    R"(                                     $$$$$$/                                                                    )"};
                break;
            }
        }
        else if (width > 90)
        {
            texts = {
                R"( _____ _                 _           __                   _     _ _   _             )",
                R"(|_   _| |               | |         / _|                 (_)   (_) | (_)            )",
                R"(  | | | |__   __ _ _ __ | | _____  | |_ ___  _ __  __   ___ ___ _| |_ _ _ __   __ _ )",
                R"(  | | | '_ \ / _` | '_ \| |/ / __| |  _/ _ \| '__| \ \ / / / __| | __| | '_ \ / _` |)",
                R"(  | | | | | | (_| | | | |   <\__ \ | || (_) | |     \ V /| \__ \ | |_| | | | | (_| |)",
                R"(  \_/ |_| |_|\__,_|_| |_|_|\_\___/ |_| \___/|_|      \_/ |_|___/_|\__|_|_| |_|\__, |)",
                R"(                                                                               __/ |)",
                R"(                                                                              |___/ )",
                R"()",
                R"( _____                                                       )",
                R"(/  ___|                                                      )",
                R"(\ `--.  ___  ___   _   _  ___  _   _   ___  ___   ___  _ __  )",
                R"( `--. \/ _ \/ _ \ | | | |/ _ \| | | | / __|/ _ \ / _ \| '_ \ )",
                R"(/\__/ /  __/  __/ | |_| | (_) | |_| | \__ \ (_) | (_) | | | |)",
                R"(\____/ \___|\___|  \__, |\___/ \__,_| |___/\___/ \___/|_| |_|)",
                R"(                    __/ |                                    )",
                R"(                   |___/                                     )"};
        }
        else
        {
            texts = {"Thanks for visiting", "See you soon"};
        }
    }
    else
    {
        texts = {"Thanks for visiting", "See you soon"};
    }

    return texts;
}

// for profile
vector<string> ProfileText(int size)
{
    vector<string> texts;

    if (size == 1)
    {
        texts = {"* Info *"};
    }
    else if (size == 2)
    {
        texts = {
            "### #   # #####  ### ",
            " #  ##  # #     #   #",
            " #  # # # ####  #   #",
            " #  #  ## #     #   #",
            "### #   # #      ### "};
    }

    return texts;
}

// for products
vector<string> PetText(int size)
{
    vector<string> texts;

    if (size == 1)
    {
        texts = {"* PET *"};
    }
    else if (size == 2)
    {
        texts = {
            "######  ####### ########",
            "##   ## ##         ##   ",
            "######  #####      ##   ",
            "##      ##         ##   ",
            "##      #######    ##   "};
    }

    return texts;
}

// Example: when you want combine button
vector<string> CombineVecStr(vector<vector<string>> texts, DirectionType direction)
{
    vector<string> result;
    string temp;

    if (direction == Horizontal)
    {
        for (int i = 0; i < texts[0].size(); i++)
        {
            temp.clear();
            for (auto x : texts)
            {
                temp += x[i];
            }
            result.push_back(temp);
        }
    }
    else if (direction == Vertical)
    {
        for (auto x : texts)
        {
            for (auto y : x)
            {
                result.push_back(y);
            }
        }
    }

    return result;
}

vector<string> CreateButton(string text, int horizontalPadding, int horizontalMargin, int verticalMargin = 0)
{
    vector<string> texts;
    string temp;

    // margin
    for (int i = 0; i < verticalMargin; i++)
    {
        for (int i = 0; i < text.size() + (2 * horizontalPadding + 2) + horizontalMargin + 2; i++)
        {
            temp += ' ';
        }
        texts.push_back(temp);
        temp.clear();
    }

    // line ( ----- )
    for (int i = 0; i < horizontalMargin; i++)
    {
        temp += ' ';
    }
    for (int i = 0; i < text.size() + (2 * horizontalPadding + 2) + 2; i++)
    {
        temp += ButtonBorderH;
    }
    for (int i = 0; i < horizontalMargin; i++)
    {
        temp += ' ';
    }
    texts.push_back(temp);
    temp.clear();

    // margin + pading + txet
    for (int i = 0; i < horizontalMargin; i++)
    {
        temp += ' ';
    }
    temp += ButtonBorderV;
    for (int i = 0; i < horizontalPadding + 1; i++)
    {
        temp += ' ';
    }
    temp += text;
    for (int i = 0; i < horizontalPadding + 1; i++)
    {
        temp += ' ';
    }
    temp += ButtonBorderV;
    for (int i = 0; i < horizontalMargin; i++)
    {
        temp += ' ';
    }
    texts.push_back(temp);
    temp.clear();

    // line ( ----- )
    for (int i = 0; i < horizontalMargin; i++)
    {
        temp += ' ';
    }
    for (int i = 0; i < text.size() + (2 * horizontalPadding + 2) + 2; i++)
    {
        temp += ButtonBorderH;
    }
    for (int i = 0; i < horizontalMargin; i++)
    {
        temp += ' ';
    }
    texts.push_back(temp);
    temp.clear();

    // margin
    for (int i = 0; i < verticalMargin; i++)
    {
        for (int i = 0; i < text.size() + (2 * horizontalPadding + 2) + horizontalMargin + 2; i++)
        {
            temp += ' ';
        }
        texts.push_back(temp);
        temp.clear();
    }

    return texts;
}

vector<string> CreateTitle(string text)
{
    vector<string> texts;
    string temp;

    texts.push_back(" ");

    // line ( ===== )
    for (int i = 0; i < text.size() + 6; i++)
    {
        temp += TitleBorder;
    }
    texts.push_back(temp);
    temp.clear();

    // txet
    for (int i = 0; i < 3; i++)
    {
        temp += ' ';
    }
    temp += text;
    for (int i = 0; i < 3; i++)
    {
        temp += ' ';
    }
    texts.push_back(temp);
    temp.clear();

    // line ( ===== )
    for (int i = 0; i < text.size() + 6; i++)
    {
        temp += TitleBorder;
    }
    texts.push_back(temp);
    temp.clear();

    texts.push_back(" ");
    texts.push_back(" ");

    return texts;
}

//==========================================================

int SetIds(ObjectType type)
{
    int user;
    int pet;
    fstream file;
    file.open(PathIds, ios::in | ios::binary);

    if (!file)
    {
        pet = 0;
        user = 0;

        file.close();
        file.open(PathIds, ios::out | ios::binary);
    }
    else
    {
        file.read(reinterpret_cast<char *>(&user), sizeof(int));
        file.read(reinterpret_cast<char *>(&pet), sizeof(int));

        file.close();
        file.open(PathIds, ios::out | ios::binary);
    }

    if (type == ObjectType::User)
    {
        user++;
        file.write(reinterpret_cast<char *>(&user), sizeof(int));
        file.write(reinterpret_cast<char *>(&pet), sizeof(int));
        file.close();
        return user;
    }
    else
    {
        pet++;
        file.write(reinterpret_cast<char *>(&user), sizeof(int));
        file.write(reinterpret_cast<char *>(&pet), sizeof(int));
        file.close();
        return pet;
    }
}

int DeleteLastIds(ObjectType type)
{
    int user;
    int pet;
    fstream file;
    file.open(PathIds, ios::in | ios::binary);

    file.read(reinterpret_cast<char *>(&user), sizeof(int));
    file.read(reinterpret_cast<char *>(&pet), sizeof(int));

    file.close();
    file.open(PathIds, ios::out | ios::binary);

    if (type == ObjectType::User)
    {
        user--;
        file.write(reinterpret_cast<char *>(&user), sizeof(int));
        file.write(reinterpret_cast<char *>(&pet), sizeof(int));
        file.close();
        return user;
    }
    else
    {
        pet--;
        file.write(reinterpret_cast<char *>(&user), sizeof(int));
        file.write(reinterpret_cast<char *>(&pet), sizeof(int));
        file.close();
        return pet;
    }
}

string createTransactionId(int userId)
{
    time_t now = time(nullptr);
    tm *timeNow = localtime(&now);

    char dateBuffer[100];
    char clockBuffer[100];

    strftime(dateBuffer, sizeof(dateBuffer), "%Y%m%d", timeNow);
    strftime(clockBuffer, sizeof(clockBuffer), "%H%M%S", timeNow);

    string date = dateBuffer;
    string clock = clockBuffer;

    string id;
    id = to_string(userId);
    id += "-";
    id += date;
    id += "-";
    id += clock;

    return id;
}

string getTime()
{
    time_t now = time(nullptr);
    tm *timeNow = localtime(&now);
    char buffer[100];

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", timeNow);

    string result = buffer;

    return result;
}

// searching info
template <typename KeyType, typename ObjectTypeInfo>
bool IsThereThisInfo(KeyType key, ObjectTypeInfo whichInfo, int *indexOfVector = nullptr)
{
    int i = 0;

    if constexpr (is_same_v<ObjectTypeInfo, UserInfo>)
    {
        vector<User *> users = User::loadInfoAllUser();

        if (whichInfo == UserInfo::Id)
        {
            if constexpr (is_same_v<KeyType, int>)
                for (auto x : users)
                {
                    if (x->getId() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == UserInfo::Name)
        {
            if constexpr (is_same_v<KeyType, string>)
                for (auto x : users)
                {
                    if (x->getName() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == UserInfo::Username)
        {
            if constexpr (is_same_v<KeyType, string>)
                for (auto x : users)
                {
                    if (x->getUsername() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == UserInfo::Password)
        {
            if constexpr (is_same_v<KeyType, string>)
                for (auto x : users)
                {
                    if (x->getPassword() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == UserInfo::PhoneNumber)
        {
            if constexpr (is_same_v<KeyType, string>)
                for (auto x : users)
                {
                    if (x->getPhoneNumber() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == UserInfo::Type)
        {
            if constexpr (is_same_v<KeyType, UserType>)
                for (auto x : users)
                {
                    if (x->getType() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == UserInfo::Balance)
        {
            if constexpr (is_same_v<KeyType, float>)
                for (auto x : users)
                {
                    if (x->getBalance() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
    }
    else if constexpr (is_same_v<ObjectTypeInfo, PetInfo>)
    {
        vector<Pet *> pets = Pet::loadInfoAllPet();

        if (whichInfo == PetInfo::PetId)
        {
            if constexpr (is_same_v<KeyType, int>)
                for (auto x : pets)
                {
                    if (x->getId() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::Name)
        {
            if constexpr (is_same_v<KeyType, string>)
                for (auto x : pets)
                {
                    if (x->getName() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::Age)
        {
            if constexpr (is_same_v<KeyType, int>)
                for (auto x : pets)
                {
                    if (x->getAge() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::Price)
        {
            if constexpr (is_same_v<KeyType, float>)
                for (auto x : pets)
                {
                    if (x->getPrice() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::Breed)
        {
            if constexpr (is_same_v<KeyType, string>)
                for (auto x : pets)
                {
                    if (x->getBreed() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::Color)
        {
            if constexpr (is_same_v<KeyType, Colors>)
                for (auto x : pets)
                {
                    if (x->getColor() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::Status)
        {
            if constexpr (is_same_v<KeyType, bool>)
                for (auto x : pets)
                {
                    if (x->getStatus() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::SellerName)
        {
            if constexpr (is_same_v<KeyType, string>)
                for (auto x : pets)
                {
                    if (x->getSellerName() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::Species)
        {
            if constexpr (is_same_v<KeyType, PetSpecies>)
                for (auto x : pets)
                {
                    if (x->getSpecies() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::Rating)
        {
            if constexpr (is_same_v<KeyType, float>)
                for (auto x : pets)
                {
                    if (x->getRating() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::Ratings)
        {
            if constexpr (is_same_v<KeyType, int>)
                for (auto x : pets)
                {
                    if (x->getRatings() == key)
                    {
                        if (indexOfVector != nullptr)
                            *indexOfVector = i;
                        return true;
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::FlightHeight)
        {
            if constexpr (is_same_v<KeyType, float>)
                for (auto x : pets)
                {
                    if (dynamic_cast<Bird *>(x))
                    {
                        if (dynamic_cast<Bird *>(x)->getFlightHeight() == key)
                        {
                            if (indexOfVector != nullptr)
                                *indexOfVector = i;
                            return true;
                        }
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::Sound)
        {
            if constexpr (is_same_v<KeyType, VoiceType>)
                for (auto x : pets)
                {
                    if (dynamic_cast<Bird *>(x))
                    {
                        if (dynamic_cast<Bird *>(x)->getSound() == key)
                        {
                            if (indexOfVector != nullptr)
                                *indexOfVector = i;
                            return true;
                        }
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::Iq)
        {
            if constexpr (is_same_v<KeyType, float>)
                for (auto x : pets)
                {
                    if (dynamic_cast<Bird *>(x))
                    {
                        if (dynamic_cast<Bird *>(x)->getIq() == key)
                        {
                            if (indexOfVector != nullptr)
                                *indexOfVector = i;
                            return true;
                        }
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::Water)
        {
            if constexpr (is_same_v<KeyType, WaterType>)
                for (auto x : pets)
                {
                    if (dynamic_cast<Fish *>(x))
                    {
                        if (dynamic_cast<Fish *>(x)->getWater() == key)
                        {
                            if (indexOfVector != nullptr)
                                *indexOfVector = i;
                            return true;
                        }
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::AquariumSize)
        {
            if constexpr (is_same_v<KeyType, float>)
                for (auto x : pets)
                {
                    if (dynamic_cast<Fish *>(x))
                    {
                        if (dynamic_cast<Fish *>(x)->getAquariumSize() == key)
                        {
                            if (indexOfVector != nullptr)
                                *indexOfVector = i;
                            return true;
                        }
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::SwimmingSpeed)
        {
            if constexpr (is_same_v<KeyType, float>)
                for (auto x : pets)
                {
                    if (dynamic_cast<Fish *>(x))
                    {
                        if (dynamic_cast<Fish *>(x)->getSwimmingSpeed() == key)
                        {
                            if (indexOfVector != nullptr)
                                *indexOfVector = i;
                            return true;
                        }
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::RunningSpeed)
        {
            if constexpr (is_same_v<KeyType, float>)
                for (auto x : pets)
                {
                    if (dynamic_cast<Pony *>(x))
                    {
                        if (dynamic_cast<Pony *>(x)->getRunningSpeed() == key)
                        {
                            if (indexOfVector != nullptr)
                                *indexOfVector = i;
                            return true;
                        }
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::ManeColor)
        {
            if constexpr (is_same_v<KeyType, Colors>)
                for (auto x : pets)
                {
                    if (dynamic_cast<Pony *>(x))
                    {
                        if (dynamic_cast<Pony *>(x)->getManeColor() == key)
                        {
                            if (indexOfVector != nullptr)
                                *indexOfVector = i;
                            return true;
                        }
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::EnergyLevel)
        {
            if constexpr (is_same_v<KeyType, float>)
                for (auto x : pets)
                {
                    if (dynamic_cast<Pony *>(x))
                    {
                        if (dynamic_cast<Pony *>(x)->getEnergyLevel() == key)
                        {
                            if (indexOfVector != nullptr)
                                *indexOfVector = i;
                            return true;
                        }
                    }
                    i++;
                }
        }
        else if (whichInfo == PetInfo::SpeedUnit)
        {
            if constexpr (is_same_v<KeyType, SpeedUnitType>)
                for (auto x : pets)
                {
                    if (dynamic_cast<Fish *>(x) || dynamic_cast<Pony *>(x))
                    {
                        if (dynamic_cast<Fish *>(x)->getUnitOfSpeed() == key || dynamic_cast<Pony *>(x)->getUnitOfSpeed == key)
                        {
                            if (indexOfVector != nullptr)
                                *indexOfVector = i;
                            return true;
                        }
                    }
                    i++;
                }
        }
    }

    if (indexOfVector != nullptr)
        *indexOfVector = -1;
    return false;
}

//==========================================================

template <typename typeOfMember, SelectorType type>
void createSelectedOption(typeOfMember &members, int whichMember)
{
    string temp;

    if constexpr (is_same_v<typeOfMember, vector<string>>)
    {
        if constexpr (type == SelectorType::MenuSelector)
        {
            temp += "-> ";
            temp += members[whichMember];
        }
        else if constexpr (type == SelectorType::OptionSelector)
        {
            temp += "[";
            temp += members[whichMember];
            temp += "]";
        }
        else if constexpr (type == SelectorType::TransactionSelector)
        {
            string text = members[whichMember];

            for (int i = 0; i < members[1].size(); i++)
            {
                if (members[1][i] == ' ')
                {
                    temp += ' ';
                    text.erase(0, 1);
                }
                else
                {
                    break;
                }
            }

            if (temp.size() >= 2)
            {
                temp[temp.size() - 2] = '-';
                temp[temp.size() - 1] = '>';
            }
            else
            {
                temp += '-';
                temp += '>';
            }

            temp += text;
            temp += "<-";
        }
        members[whichMember] = temp;
    }
    else if constexpr (is_same_v<typeOfMember, vector<vector<string>>>)
    {
        if constexpr (type == SelectorType::BoxesSelector)
        {
            vector<string> selectedBox = members[whichMember];

            for (int i = 0; i < selectedBox[0].size(); i++)
            {
                temp += "#";
            }

            selectedBox[0] = temp;
            selectedBox[selectedBox.size() - 1] = temp;

            for (auto &x : selectedBox)
            {
                x[0] = '#';
                x[x.size() - 1] = '#';
            }

            members[whichMember] = selectedBox;
        }
    }
}

template <typename X>
X SelectOption(string message)
{
    const vector<string> members = enumMember<X>();
    vector<string> tempMembers = members;

    int i = 0;
    cout << message;
    createSelectedOption<vector<string>, SelectorType::OptionSelector>(tempMembers, i);
    PrintVecStr(tempMembers, DirectionType::Horizontal, '|');

    int key;
    do
    {
        key = getch();

        if (key == 0 || key == 224)
        {
            key = getch();

            if (key == RIGHT_KEY)
            {
                if (i == members.size() - 1)
                {
                    i = 0;
                }
                else
                {
                    i++;
                }
            }
            else if (key == LEFT_KEY)
            {
                if (i == 0)
                {
                    i = members.size() - 1;
                }
                else
                {
                    i--;
                }
            }

            cout << "\r";
            tempMembers = members;
            cout << message;
            createSelectedOption<vector<string>, SelectorType::OptionSelector>(tempMembers, i);
            PrintVecStr(tempMembers, DirectionType::Horizontal, '|');
        }
    } while (key != ENTER_KEY);

    cout << endl; // Enter Key pressed

    return static_cast<X>(i);
}

template <typename X>
int SelectOptionForSearching(string message, int CurrentSelectedItem, int &lastKey)
{
    const vector<string> members = enumMember<X>();
    vector<string> tempMembers = members;
    string tempText;

    int i = CurrentSelectedItem;

    tempText.clear();
    tempText += message;
    if (i != -1)
    {
        createSelectedOption<vector<string>, SelectorType::OptionSelector>(tempMembers, i);
    }
    for (auto x : tempMembers)
    {
        tempText += x;
        if (x != tempMembers[tempMembers.size() - 1])
            tempText += " | ";
    }
    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

    int key;
    do
    {
        key = getch();

        if (key == 0 || key == 224)
        {
            key = getch();

            if (key == RIGHT_KEY)
            {
                if (i == members.size() - 1)
                {
                    i = 0;
                }
                else
                {
                    i++;
                }
            }
            else if (key == LEFT_KEY)
            {
                if (i == 0 || i == -1)
                {
                    i = members.size() - 1;
                }
                else
                {
                    i--;
                }
            }

            cout << "\r";
            tempMembers = members;
            tempText.clear();
            createSelectedOption<vector<string>, SelectorType::OptionSelector>(tempMembers, i);
            tempText += message;
            for (auto x : tempMembers)
            {
                tempText += x;
                if (x != tempMembers[tempMembers.size() - 1])
                    tempText += " | ";
            }
            PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);
        }
    } while (key != ENTER_KEY && key != '\t');

    lastKey = key;

    return i;
}

int SelectButton(vector<string> beforeMessage, vector<string> options, DirectionType direction,
                 int horizontalPaddingButton, int horizontalMarginButton, int verticalMarginButton)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    vector<string> tempOptions;
    vector<vector<string>> buttons;

    int i = 0;
    PutMidlle(beforeMessage, Horizontal, CursorPlace::BeginningNextLine);

    csbi = GetWidthHeight();
    const short BeginningCurPosX = csbi.dwCursorPosition.X;
    const short BeginningCurPosY = csbi.dwCursorPosition.Y;
    short TempBeginningCurPosX = BeginningCurPosX;
    short TempBeginningCurPosY = BeginningCurPosY;
    short NowCurPosX;
    short NowCurPosY;

    tempOptions = options;
    createSelectedOption<vector<string>, SelectorType::OptionSelector>(tempOptions, i);
    for (auto x : tempOptions)
    {
        buttons.push_back(CreateButton(x, horizontalPaddingButton, horizontalMarginButton, verticalMarginButton));
    }
    PutMidlle(CombineVecStr(buttons, direction), Horizontal, CursorPlace::BeginningNextLine);
    buttons.clear();

    int key;
    do
    {
        key = getch();

        if (key == 0 || key == 224)
        {
            key = getch();
            if (direction == Horizontal)
            {
                if (key == RIGHT_KEY)
                {
                    if (i == options.size() - 1)
                    {
                        i = 0;
                    }
                    else
                    {
                        i++;
                    }
                }
                else if (key == LEFT_KEY)
                {
                    if (i == 0)
                    {
                        i = options.size() - 1;
                    }
                    else
                    {
                        i--;
                    }
                }
            }
            else if (direction == Vertical)
            {
                if (key == DOWN_KEY)
                {
                    if (i == options.size() - 1)
                    {
                        i = 0;
                    }
                    else
                    {
                        i++;
                    }
                }
                else if (key == UP_KEY)
                {
                    if (i == 0)
                    {
                        i = options.size() - 1;
                    }
                    else
                    {
                        i--;
                    }
                }
            }
            TempBeginningCurPosX = BeginningCurPosX;
            TempBeginningCurPosY = BeginningCurPosY;
            csbi = GetWidthHeight();
            NowCurPosX = csbi.dwCursorPosition.X;
            NowCurPosY = csbi.dwCursorPosition.Y;

            GoToXY(BeginningCurPosX, BeginningCurPosY);

            while (TempBeginningCurPosY != NowCurPosY)
            {
                while (TempBeginningCurPosX != csbi.srWindow.Right)
                {
                    cout << " ";
                    TempBeginningCurPosX++;
                }
                TempBeginningCurPosX = 0;
                TempBeginningCurPosY++;
            }

            GoToXY(BeginningCurPosX, BeginningCurPosY);

            tempOptions = options;
            createSelectedOption<vector<string>, SelectorType::OptionSelector>(tempOptions, i);
            for (auto x : tempOptions)
            {
                buttons.push_back(CreateButton(x, horizontalPaddingButton, horizontalMarginButton, verticalMarginButton));
            }
            PutMidlle(CombineVecStr(buttons, direction), Horizontal, CursorPlace::BeginningNextLine);
            buttons.clear();
        }
    } while (key != ENTER_KEY);

    return i;
}

int SelectMenu(string message, vector<string> optionsMenu)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    vector<string> tempOptionsMenu;

    int i = 0;
    cout << message << endl;

    csbi = GetWidthHeight();
    const short BeginningCurPosX = csbi.dwCursorPosition.X;
    const short BeginningCurPosY = csbi.dwCursorPosition.Y;
    short TempBeginningCurPosX = BeginningCurPosX;
    short TempBeginningCurPosY = BeginningCurPosY;
    short NowCurPosX;
    short NowCurPosY;

    tempOptionsMenu = optionsMenu;
    createSelectedOption<vector<string>, SelectorType::MenuSelector>(tempOptionsMenu, i);
    PrintVecStr(tempOptionsMenu, DirectionType::Vertical);

    int key;
    do
    {
        key = getch();

        if (key == 0 || key == 224)
        {
            key = getch();

            if (key == DOWN_KEY)
            {
                if (i == optionsMenu.size() - 1)
                {
                    i = 0;
                }
                else
                {
                    i++;
                }
            }
            else if (key == UP_KEY)
            {
                if (i == 0)
                {
                    i = optionsMenu.size() - 1;
                }
                else
                {
                    i--;
                }
            }

            TempBeginningCurPosX = BeginningCurPosX;
            TempBeginningCurPosY = BeginningCurPosY;
            csbi = GetWidthHeight();
            NowCurPosX = csbi.dwCursorPosition.X;
            NowCurPosY = csbi.dwCursorPosition.Y;

            GoToXY(BeginningCurPosX, BeginningCurPosY);

            while (TempBeginningCurPosY != NowCurPosY)
            {
                while (TempBeginningCurPosX != csbi.srWindow.Right)
                {
                    cout << " ";
                    TempBeginningCurPosX++;
                }
                TempBeginningCurPosX = 0;
                TempBeginningCurPosY++;
            }

            GoToXY(BeginningCurPosX, BeginningCurPosY);

            tempOptionsMenu = optionsMenu;
            createSelectedOption<vector<string>, SelectorType::MenuSelector>(tempOptionsMenu, i);
            PrintVecStr(tempOptionsMenu, DirectionType::Vertical);
        }
    } while (key != ENTER_KEY);

    cout << endl; // Enter Key pressed

    return i;
}

// for product and profile
int SelectBoxes(vector<vector<string>> boxes, string endMessage, string beginningMessage = "")
{
    bool doesHaveBeginningMessage = beginningMessage == "";
    short width, height;
    GetWidthHeight(&width, &height);

    float fitRatio;
    int sumOfSize;
    int numberOfBoxThisPage;
    int minRequiredSpace = 2;
    vector<int> numberOfBoxEachPage;
    for (int i = 0; i < boxes.size();)
    {
        fitRatio = 0;
        sumOfSize = minRequiredSpace;
        numberOfBoxThisPage = 0;
        while (i < boxes.size())
        {
            sumOfSize += boxes[i][0].size();
            if (numberOfBoxThisPage > 1)
            {
                sumOfSize++; // amnout of space we need after add one more box
            }
            fitRatio = (float)width / sumOfSize;
            if (fitRatio > 1)
            {
                numberOfBoxThisPage++;
                i++;
            }
            else
            {
                break;
            }
        }
        numberOfBoxEachPage.push_back(numberOfBoxThisPage);
    }

    vector<vector<vector<string>>> groupedBoxes;
    int indexOfBox;
    int NumberOfPage = numberOfBoxEachPage.size();

    vector<vector<string>> tempBoxes;
    int indexOfSelectedBox = 0;
    int indexOfSelectedPage = 0;

    if (doesHaveBeginningMessage)
        beginningMessage = "items : " + to_string(indexOfSelectedBox + 1) + "/" + to_string(boxes.size()) + " | page : " + to_string(indexOfSelectedPage + 1) + "/" + to_string(numberOfBoxEachPage.size());
    tempBoxes = boxes;
    createSelectedOption<vector<vector<string>>, SelectorType::BoxesSelector>(tempBoxes, indexOfSelectedBox);
    indexOfBox = 0;
    for (int i = 0; i < NumberOfPage; i++)
    {
        groupedBoxes.push_back(vector<vector<string>>());
        for (int j = 0; j < numberOfBoxEachPage[i]; j++)
        {
            groupedBoxes[i].push_back(tempBoxes[indexOfBox]);
            indexOfBox++;
        }
    }
    PrintBoxesInCenter(beginningMessage, endMessage, groupedBoxes[indexOfSelectedPage]);

    int key;
    do
    {
        key = getch();

        if (key == 0 || key == 224)
        {
            key = getch();

            if (key == RIGHT_KEY)
            {
                if (indexOfSelectedBox == boxes.size() - 1)
                {
                    indexOfSelectedBox = 0;
                    indexOfSelectedPage = 0;
                }
                else
                {
                    indexOfSelectedBox++;
                    if (groupedBoxes[indexOfSelectedPage][numberOfBoxEachPage[indexOfSelectedPage] - 1] == tempBoxes[indexOfSelectedBox - 1])
                    {
                        indexOfSelectedPage++;
                    }
                }
            }
            else if (key == LEFT_KEY)
            {
                if (indexOfSelectedBox == 0)
                {
                    indexOfSelectedBox = boxes.size() - 1;
                    indexOfSelectedPage = numberOfBoxEachPage.size() - 1;
                }
                else
                {
                    indexOfSelectedBox--;
                    if (groupedBoxes[indexOfSelectedPage][0] == tempBoxes[indexOfSelectedBox + 1])
                    {
                        indexOfSelectedPage--;
                    }
                }
            }

            system("cls");
            if (doesHaveBeginningMessage)
                beginningMessage = "items : " + to_string(indexOfSelectedBox + 1) + "/" + to_string(boxes.size()) + " | page : " + to_string(indexOfSelectedPage + 1) + "/" + to_string(numberOfBoxEachPage.size());
            groupedBoxes.clear();
            tempBoxes = boxes;
            createSelectedOption<vector<vector<string>>, SelectorType::BoxesSelector>(tempBoxes, indexOfSelectedBox);
            indexOfBox = 0;
            for (int i = 0; i < NumberOfPage; i++)
            {
                groupedBoxes.push_back(vector<vector<string>>());
                for (int j = 0; j < numberOfBoxEachPage[i]; j++)
                {
                    groupedBoxes[i].push_back(tempBoxes[indexOfBox]);
                    indexOfBox++;
                }
            }
            PrintBoxesInCenter(beginningMessage, endMessage, groupedBoxes[indexOfSelectedPage]);
        }
    } while (!(key == ENTER_KEY || key == ESC_KEY));

    if (key == ESC_KEY)
    {
        return -1;
    }
    else
    {
        return indexOfSelectedBox;
    }
}

// for product and profile
void ShowSomeBoxes(vector<vector<string>> boxes)
{
    string beginningMessage;
    short width, height;
    GetWidthHeight(&width, &height);

    float fitRatio;
    int sumOfSize;
    int numberOfBoxThisPage;
    int minRequiredSpace = 2;
    vector<int> numberOfBoxEachPage;
    for (int i = 0; i < boxes.size();)
    {
        fitRatio = 0;
        sumOfSize = minRequiredSpace;
        numberOfBoxThisPage = 0;
        while (i < boxes.size())
        {
            sumOfSize += boxes[i][0].size();
            if (numberOfBoxThisPage > 1)
            {
                sumOfSize++; // amnout of space we need after add one more box
            }
            fitRatio = (float)width / sumOfSize;
            if (fitRatio > 1)
            {
                numberOfBoxThisPage++;
                i++;
            }
            else
            {
                break;
            }
        }
        numberOfBoxEachPage.push_back(numberOfBoxThisPage);
    }

    vector<vector<vector<string>>> groupedBoxes;
    int indexOfBox = 0;
    int indexOfSelectedPage = 0;
    int NumberOfPage = numberOfBoxEachPage.size();
    for (int i = 0; i < NumberOfPage; i++)
    {
        groupedBoxes.push_back(vector<vector<string>>());
        for (int j = 0; j < numberOfBoxEachPage[i]; j++)
        {
            groupedBoxes[i].push_back(boxes[indexOfBox]);
            indexOfBox++;
        }
    }

    beginningMessage = "page : " + to_string(indexOfSelectedPage + 1) + "/" + to_string(numberOfBoxEachPage.size());
    PrintBoxesInCenter(beginningMessage, "Use [->] , [<-] key to navigate between pages | Press [Esc] to exit", groupedBoxes[indexOfSelectedPage]);

    int key;
    do
    {
        key = getch();

        if (key == 0 || key == 224)
        {
            key = getch();

            if (key == RIGHT_KEY)
            {
                if (indexOfSelectedPage == groupedBoxes.size() - 1)
                {
                    indexOfSelectedPage = 0;
                }
                else
                {
                    indexOfSelectedPage++;
                }
            }
            else if (key == LEFT_KEY)
            {
                if (indexOfSelectedPage == 0)
                {
                    indexOfSelectedPage = groupedBoxes.size() - 1;
                }
                else
                {
                    indexOfSelectedPage--;
                }
            }
        }

        system("cls");
        beginningMessage = "page : " + to_string(indexOfSelectedPage + 1) + "/" + to_string(numberOfBoxEachPage.size());
        PrintBoxesInCenter(beginningMessage, "Use [->] , [<-] key to navigate between items | Press [Esc] to exit", groupedBoxes[indexOfSelectedPage]);
    } while (!(key == ESC_KEY));
}

void ShowSomeTransaction(vector<TransactionInfo> data)
{
    PutMidlle(CreateTitle("             Transaction Instructions             "), Horizontal, CursorPlace::RightWhereYouAre);
    PutMidlle(vector<string>{"You can scroll Transaction with [UP Arrow] , [Down Arrow] keys",
                             "Press [Esc] for Exit",
                             "",
                             "Now press [Enter] to continue"},
              Horizontal, CursorPlace::BeginningNextLine);
    cin.get();
    system("cls");

    short width, height;
    GetWidthHeight(&width, &height);

    vector<vector<string>> rowMembers;

    // add title members
    vector<string> titles = {
        "Transaction ID",
        "User ID",
        "Type",
        "Amount",
        "New Balance",
        "Status",
        "Transaction Time"};

    rowMembers.push_back(titles);

    // add info members
    for (auto x : data)
    {
        string _transactionId = x.transactionId;
        string _userId = to_string(x.userId);
        string _type = enum_to_string<TransactionType>(x.type);
        string _amount;
        if (x.type == TransactionType::Deposit || x.type == TransactionType::Sell)
        {
            _amount = "+" + normalizeFloatString(to_string(x.amount)) + " $";
        }
        else
        {
            _amount = "-" + normalizeFloatString(to_string(x.amount)) + " $";
        }
        string _newBalance = normalizeFloatString(to_string(x.newBalance)) + " $";
        string _status = enum_to_string<TransactionStatus>(x.status);
        string _transactionTime = x.transactionTime;

        vector<string> temprowMembers = {_transactionId,
                                         _userId,
                                         _type,
                                         _amount,
                                         _newBalance,
                                         _status,
                                         _transactionTime};

        rowMembers.push_back(temprowMembers);
    }

    // find max size of each column
    vector<int> maxSizes(rowMembers[0].size(), 0);

    for (int i = 0; i < rowMembers[0].size(); i++)
    {
        for (int j = 0; j < rowMembers.size(); j++)
        {
            if (rowMembers[j][i].size() > maxSizes[i])
            {
                maxSizes[i] = rowMembers[j][i].size();
            }
        }
        maxSizes[i] += 2; // Padding of text ( X )
    }

    // total column size
    int totalColumnSize = 0;
    for (auto x : maxSizes)
    {
        totalColumnSize += x;
    }
    totalColumnSize += rowMembers[0].size() - 1; // the | sign between texts

    // make a vector of information with style
    vector<string> finalInfo;
    string temp;

    int paddingOfBox = (width - totalColumnSize) / 2;
    int leftPaddingOfText;
    int rightPaddingOfText;
    int indexOfMaxSizes;
    for (auto x : rowMembers)
    {
        // info
        for (int i = 0; i < paddingOfBox; i++)
        {
            temp += " ";
        }

        indexOfMaxSizes = 0;
        for (auto y : x)
        {
            leftPaddingOfText = (maxSizes[indexOfMaxSizes] - y.size()) / 2 + (maxSizes[indexOfMaxSizes] - y.size()) % 2;
            rightPaddingOfText = (maxSizes[indexOfMaxSizes] - y.size()) / 2;
            for (int i = 0; i < leftPaddingOfText; i++)
            {
                temp += " ";
            }
            temp += y;
            for (int i = 0; i < rightPaddingOfText; i++)
            {
                temp += " ";
            }
            if (y != x[x.size() - 1])
            {
                temp += "|";
            }

            indexOfMaxSizes++;
        }
        finalInfo.push_back(temp);
        temp.clear();

        // ----------
        if (x != rowMembers[rowMembers.size() - 1])
        {
            for (int i = 0; i < paddingOfBox; i++)
            {
                temp += " ";
            }
            for (int i = 0; i < totalColumnSize; i++)
            {
                temp += "-";
            }
            finalInfo.push_back(temp);
            temp.clear();
        }
    }

    // create group of information
    bool doesItNeedScrolling = true;
    int numberOfRows = finalInfo.size();

    int availableSpace = height - 2; // 2 == min padding for top and bottom
    if (availableSpace % 2 == 0)     // we need the amount of available space to be non-even
    {
        availableSpace -= 1;
    }

    int lastSelectedRow;
    vector<string> partOfFinalInfo;
    for (lastSelectedRow = 0; lastSelectedRow < availableSpace; lastSelectedRow++)
    {
        if (lastSelectedRow < numberOfRows)
        {
            partOfFinalInfo.push_back(finalInfo[lastSelectedRow]);
        }
        else
        {
            break;
        }
    }
    lastSelectedRow--;

    if (lastSelectedRow == numberOfRows - 1)
    {
        doesItNeedScrolling = false;
    }

    PrintTransaction(partOfFinalInfo);
    int key;
    do
    {
        key = getch();
        if (doesItNeedScrolling)
        {
            if (key == 0 || key == 224)
            {
                key = getch();

                if (key == DOWN_KEY)
                {
                    if (lastSelectedRow != numberOfRows - 1)
                    {
                        lastSelectedRow++;
                        partOfFinalInfo.erase(partOfFinalInfo.begin() + 1);
                        partOfFinalInfo.push_back(finalInfo[lastSelectedRow]);
                        lastSelectedRow++;
                        partOfFinalInfo.erase(partOfFinalInfo.begin() + 1);
                        partOfFinalInfo.push_back(finalInfo[lastSelectedRow]);
                        system("cls");
                        PrintTransaction(partOfFinalInfo);
                    }
                }
                else if (key == UP_KEY)
                {
                    if (lastSelectedRow != availableSpace - 1)
                    {
                        partOfFinalInfo.pop_back();
                        partOfFinalInfo.insert(partOfFinalInfo.begin() + 1, finalInfo[lastSelectedRow - (availableSpace - 1)]);
                        lastSelectedRow--;
                        partOfFinalInfo.pop_back();
                        partOfFinalInfo.insert(partOfFinalInfo.begin() + 1, finalInfo[lastSelectedRow - (availableSpace - 1)]);
                        lastSelectedRow--;
                        system("cls");
                        PrintTransaction(partOfFinalInfo);
                    }
                }
            }
        }
    } while (!(key == ESC_KEY));
}

int SelectTransaction(vector<TransactionInfo> data)
{
    PutMidlle(CreateTitle("             Transaction Instructions             "), Horizontal, CursorPlace::RightWhereYouAre);
    PutMidlle(vector<string>{"You can navigate between Transaction with [UP Arrow] , [Down Arrow] keys",
                             "You can choose transaction for view product with [Enter] key",
                             "Press [Esc] for Exit",
                             "",
                             "Now press [Enter] to continue"},
              Horizontal, CursorPlace::BeginningNextLine);
    cin.get();
    system("cls");

    short width, height;
    GetWidthHeight(&width, &height);

    vector<vector<string>> rowMembers;

    // add title members
    vector<string> titles = {
        "Transaction ID",
        "User ID",
        "Type",
        "Amount",
        "New Balance",
        "Status",
        "Transaction Time"};

    rowMembers.push_back(titles);

    // add info members
    for (auto x : data)
    {
        string _transactionId = x.transactionId;
        string _userId = to_string(x.userId);
        string _type = enum_to_string<TransactionType>(x.type);
        string _amount;
        if (x.type == TransactionType::Deposit || x.type == TransactionType::Sell)
        {
            _amount = "+" + normalizeFloatString(to_string(x.amount)) + " $";
        }
        else
        {
            _amount = "-" + normalizeFloatString(to_string(x.amount)) + " $";
        }
        string _newBalance = normalizeFloatString(to_string(x.newBalance)) + " $";
        string _status = enum_to_string<TransactionStatus>(x.status);
        string _transactionTime = x.transactionTime;

        vector<string> temprowMembers = {_transactionId,
                                         _userId,
                                         _type,
                                         _amount,
                                         _newBalance,
                                         _status,
                                         _transactionTime};

        rowMembers.push_back(temprowMembers);
    }

    // find max size of each column
    vector<int> maxSizes(rowMembers[0].size(), 0);

    for (int i = 0; i < rowMembers[0].size(); i++)
    {
        for (int j = 0; j < rowMembers.size(); j++)
        {
            if (rowMembers[j][i].size() > maxSizes[i])
            {
                maxSizes[i] = rowMembers[j][i].size();
            }
        }
        maxSizes[i] += 2; // Padding of text ( X )
    }

    // total column size
    int totalColumnSize = 0;
    for (auto x : maxSizes)
    {
        totalColumnSize += x;
    }
    totalColumnSize += rowMembers[0].size() - 1; // the | sign between texts

    // make a vector of information with style
    vector<string> finalInfo;
    string temp;

    int paddingOfBox = (width - totalColumnSize) / 2;
    int leftPaddingOfText;
    int rightPaddingOfText;
    int indexOfMaxSizes;
    for (auto x : rowMembers)
    {
        // info
        for (int i = 0; i < paddingOfBox; i++)
        {
            temp += " ";
        }

        indexOfMaxSizes = 0;
        for (auto y : x)
        {
            leftPaddingOfText = (maxSizes[indexOfMaxSizes] - y.size()) / 2 + (maxSizes[indexOfMaxSizes] - y.size()) % 2;
            rightPaddingOfText = (maxSizes[indexOfMaxSizes] - y.size()) / 2;
            for (int i = 0; i < leftPaddingOfText; i++)
            {
                temp += " ";
            }
            temp += y;
            for (int i = 0; i < rightPaddingOfText; i++)
            {
                temp += " ";
            }
            if (y != x[x.size() - 1])
            {
                temp += "|";
            }

            indexOfMaxSizes++;
        }
        finalInfo.push_back(temp);
        temp.clear();

        // ----------
        if (x != rowMembers[rowMembers.size() - 1])
        {
            for (int i = 0; i < paddingOfBox; i++)
            {
                temp += " ";
            }
            for (int i = 0; i < totalColumnSize; i++)
            {
                temp += "-";
            }
            finalInfo.push_back(temp);
            temp.clear();
        }
    }

    // create group of information
    bool doesItNeedScrolling = true;
    int numberOfRows = finalInfo.size();

    int availableSpace = height - 2; // 2 == min padding for top and bottom
    if (availableSpace % 2 == 0)     // we need the amount of available space to be non-even
    {
        availableSpace -= 1;
    }

    int lastSelectedRow;
    vector<string> partOfFinalInfo;
    for (lastSelectedRow = 0; lastSelectedRow < availableSpace; lastSelectedRow++)
    {
        if (lastSelectedRow < numberOfRows)
        {
            partOfFinalInfo.push_back(finalInfo[lastSelectedRow]);
        }
        else
        {
            break;
        }
    }
    lastSelectedRow--;

    if (lastSelectedRow == numberOfRows - 1)
    {
        doesItNeedScrolling = false;
    }

    int selectedTransaction = 0;
    int selectedRow = 2; // selected row of tempPartOfFinalInfo
    vector<string> tempPartOfFinalInfo;
    tempPartOfFinalInfo = partOfFinalInfo;
    createSelectedOption<vector<string>, SelectorType::TransactionSelector>(tempPartOfFinalInfo, selectedRow);
    PrintTransaction(tempPartOfFinalInfo);

    int key;
    do
    {
        key = getch();

        if (key == 0 || key == 224)
        {
            key = getch();

            if (key == DOWN_KEY)
            {
                if (doesItNeedScrolling && (lastSelectedRow != numberOfRows - 1) && selectedRow == partOfFinalInfo.size() - 1) // for scrolling
                {
                    lastSelectedRow++;
                    partOfFinalInfo.erase(partOfFinalInfo.begin() + 1);
                    partOfFinalInfo.push_back(finalInfo[lastSelectedRow]);
                    lastSelectedRow++;
                    partOfFinalInfo.erase(partOfFinalInfo.begin() + 1);
                    partOfFinalInfo.push_back(finalInfo[lastSelectedRow]);
                }

                if (selectedTransaction != (numberOfRows - 1) / 2 - 1)
                {
                    selectedTransaction++;
                    if (selectedRow != partOfFinalInfo.size() - 1)
                    {
                        selectedRow += 2;
                    }
                    system("cls");
                    tempPartOfFinalInfo = partOfFinalInfo;
                    createSelectedOption<vector<string>, SelectorType::TransactionSelector>(tempPartOfFinalInfo, selectedRow);
                    PrintTransaction(tempPartOfFinalInfo);
                }
            }
            else if (key == UP_KEY)
            {
                if (doesItNeedScrolling && (lastSelectedRow != availableSpace - 1) && selectedRow == 2) // for scrolling
                {
                    partOfFinalInfo.pop_back();
                    partOfFinalInfo.insert(partOfFinalInfo.begin() + 1, finalInfo[lastSelectedRow - (availableSpace - 1)]);
                    lastSelectedRow--;
                    partOfFinalInfo.pop_back();
                    partOfFinalInfo.insert(partOfFinalInfo.begin() + 1, finalInfo[lastSelectedRow - (availableSpace - 1)]);
                    lastSelectedRow--;
                }

                if (selectedTransaction != 0)
                {
                    selectedTransaction--;
                    if (selectedRow != 2)
                    {
                        selectedRow -= 2;
                    }
                    system("cls");
                    tempPartOfFinalInfo = partOfFinalInfo;
                    createSelectedOption<vector<string>, SelectorType::TransactionSelector>(tempPartOfFinalInfo, selectedRow);
                    PrintTransaction(tempPartOfFinalInfo);
                }
            }
        }
    } while (!(key == ENTER_KEY || key == ESC_KEY));

    if (key == ESC_KEY)
    {
        return -1;
    }
    else
    {
        return selectedTransaction;
    }
}

//==========================================================

void LoadingAnimation(string loadingText = "Checking Data")
{
    cout << endl;
    cout << loadingText;
    Sleep(TimeSleepLoading);
    cout << ".";
    Sleep(TimeSleepLoading);
    cout << ".";
    Sleep(TimeSleepLoading);
    cout << ".";

    int x = rand() % (3 - 1 + 1) + 1; // 1 to 3

    for (int i = 0; i < x; i++)
    {
        Sleep(TimeSleepLoading);
        cout << "\b \b";
        Sleep(TimeSleepLoading);
        cout << "\b \b";
        Sleep(TimeSleepLoading);
        cout << "\b \b";
        Sleep(TimeSleepLoading);
        cout << ".";
        Sleep(TimeSleepLoading);
        cout << ".";
        Sleep(TimeSleepLoading);
        cout << ".";
    }

    cout << endl;
}

// whichType == 1 : Rotary
// whichType == 2 : Sweep
void FarewellAnimation(int whichType)
{

    short width, height;
    CONSOLE_SCREEN_BUFFER_INFO csbi = GetWidthHeight(&width, &height);

    vector<string> texts;

    system("cls");
    if (height > 28 && width > 170)
    {
        DrawBorder(Padding, Margin);
        switch (whichType)
        {
        case 1:
            texts = FarewellText(1);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(2);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(3);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(4);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(1);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(2);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(3);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(4);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(1);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);
            break;
        case 2:
            texts = FarewellText(1);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(2);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(1);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(2);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(1);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(2);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(1);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(2);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);

            texts = FarewellText(1);
            PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
            Sleep(500);
            break;
        }
    }
    else
    {
        DrawBorder(Padding, Margin);
        texts = FarewellText();
        PutMidlle(texts, Vertical | Horizontal, CursorPlace::ZeroZero);
        Sleep(1500);
    }
}
