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

void FullScreen();

void GoToXY(short x, short y);

CONSOLE_SCREEN_BUFFER_INFO GetWidthHeight(short *width = nullptr, short *height = nullptr);

string normalizeFloatString(string str);

//==========================================================

void DrawBorder(short padding, short margin);

void PutMidlle(vector<string> texts, int direction, CursorPlace cursorAfterPrint);

void PrintVecStr(vector<string> texts, DirectionType direction, char charForHorizontal = '\b');

// for product and profile
void PrintBoxesInCenter(string beginningMessage, string endMessage, vector<vector<string>> objects);

void PrintTransaction(vector<string> finalText);

//==========================================================

// for welcome page
vector<string> WelcomeText();

// for exit page
vector<string> FarewellText(int whichOne = 1);

// for profile
vector<string> ProfileText(int size);

// for products
vector<string> PetText(int size);

// Example: when you want combine button
vector<string> CombineVecStr(vector<vector<string>> texts, DirectionType direction);

vector<string> CreateButton(string text, int horizontalPadding, int horizontalMargin, int verticalMargin = 0);

vector<string> CreateTitle(string text);

//==========================================================

int SetIds(ObjectType type);

int DeleteLastIds(ObjectType type);

string createTransactionId(int userId);

string getTime();

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
    std::cout << message;
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

            std::cout << "\r";
            tempMembers = members;
            std::cout << message;
            createSelectedOption<vector<string>, SelectorType::OptionSelector>(tempMembers, i);
            PrintVecStr(tempMembers, DirectionType::Horizontal, '|');
        }
    } while (key != ENTER_KEY);

    std::cout << std::endl; // Enter Key pressed

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

            std::cout << "\r";
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
                 int horizontalPaddingButton, int horizontalMarginButton, int verticalMarginButton);

int SelectMenu(string message, vector<string> optionsMenu);

// for product and profile
int SelectBoxes(vector<vector<string>> boxes, string endMessage, string beginningMessage = "");

// for product and profile
void ShowSomeBoxes(vector<vector<string>> boxes);

void ShowSomeTransaction(vector<TransactionInfo> data);

int SelectTransaction(vector<TransactionInfo> data);

//==========================================================

void LoadingAnimation(string loadingText = "Checking Data");

// whichType == 1 : Rotary
// whichType == 2 : Sweep
void FarewellAnimation(int whichType);