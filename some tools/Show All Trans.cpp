#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
using namespace std;

#define PathTransaction "../file/Transaction.dat"
#define TitleBorder '='
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

enum class TransactionType
{
    Deposit,
    Withdrawal,
    Transfer,
    Purchase,
    Sell
};

enum class TransactionStatus
{
    Pending,
    Success,
    Canceled,
    Failed
};

struct TransactionInfo
{
    string transactionId;
    int userId;
    TransactionType type;
    float amount;
    float newBalance;
    TransactionStatus status;
    string transactionTime;
    int petId;
    int sellerId;
};

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

template <typename X>
string enum_to_string(X enumValue)
{
    if constexpr (is_same_v<X, TransactionType>)
    {
        switch (enumValue)
        {
        case TransactionType::Deposit:
            return "Deposit";
        case TransactionType::Withdrawal:
            return "Withdrawal";
        case TransactionType::Transfer:
            return "Transfer";
        case TransactionType::Purchase:
            return "Purchase";
        case TransactionType::Sell:
            return "Sell";
        }

        return "\nUnknown UserType...\n";
    }
    else if constexpr (is_same_v<X, TransactionStatus>)
    {
        switch (enumValue)
        {
        case TransactionStatus::Pending:
            return "Pending";
        case TransactionStatus::Success:
            return "Success";
        case TransactionStatus::Canceled:
            return "Canceled";
        case TransactionStatus::Failed:
            return "Failed";
        }

        return "\nUnknown UserType...\n";
    }
}

template <typename X>
vector<string> enumMember()
{
    vector<string> members;

    if constexpr (is_same_v<X, TransactionType>)
    {
        members.push_back("Deposit");
        members.push_back("Withdrawal");
        members.push_back("Transfer");
        members.push_back("Purchase");
    }
    else if constexpr (is_same_v<X, TransactionStatus>)
    {
        members.push_back("Pending");
        members.push_back("Success");
        members.push_back("Canceled");
        members.push_back("Failed");
        members.push_back("Sell");
    }

    return members;
}

void PrintTransaction(vector<string> finalText)
{
    cout << endl;
    for (auto x : finalText)
    {
        cout << x;
        cout << endl;
    }
}

vector<TransactionInfo> loadAllTransaction()
{
    vector<TransactionInfo> data;

    int sizeStr_transactionId;
    string _transactionId;
    int _userId;
    TransactionType _type;
    float _amount;
    float _newBalance;
    TransactionStatus _status;
    int sizeStr_transactionTime;
    string _transactionTime;
    int _petId;
    int _sellerId;

    fstream file(PathTransaction, ios::in | ios::binary);

    if (file)
    {
        while (file.read(reinterpret_cast<char *>(&sizeStr_transactionId), sizeof(sizeStr_transactionId)))
        {

            _transactionId.resize(sizeStr_transactionId, '\0');
            file.read(_transactionId.data(), sizeStr_transactionId);

            file.read(reinterpret_cast<char *>(&_userId), sizeof(_userId));
            file.read(reinterpret_cast<char *>(&_type), sizeof(_type));
            file.read(reinterpret_cast<char *>(&_amount), sizeof(_amount));
            file.read(reinterpret_cast<char *>(&_newBalance), sizeof(_newBalance));
            file.read(reinterpret_cast<char *>(&_status), sizeof(_status));

            file.read(reinterpret_cast<char *>(&sizeStr_transactionTime), sizeof(sizeStr_transactionTime));
            _transactionTime.resize(sizeStr_transactionTime, '\0');
            file.read(_transactionTime.data(), sizeStr_transactionTime);

            file.read(reinterpret_cast<char *>(&_petId), sizeof(_petId));
            file.read(reinterpret_cast<char *>(&_sellerId), sizeof(_sellerId));

            TransactionInfo temp{_transactionId, _userId, _type, _amount, _newBalance, _status, _transactionTime, _petId, _sellerId};
            data.push_back(temp);
        }
    }

    file.close();

    return data;
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

void transactionHistory(vector<TransactionInfo> data)
{
    ShowSomeTransaction(data);
}

int main()
{
    vector<TransactionInfo> allTransactions = loadAllTransaction();

    if (allTransactions.size() != 0)
    {
        transactionHistory(allTransactions);
    }
    else
    {
        cout << endl;
        cout << endl;
        PutMidlle(vector<string>{"-- There is no transaction --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
        cin.get();
    }
}