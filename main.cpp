#include "headers/myClass.hpp"
#include "headers/graphic_utilities.hpp"
#include "headers/myException.hpp"
#include "headers/printEnum.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define HorizontalPaddingButton 2
#define HorizontalMarginButton 2
#define VerticalMarginButton 3

int main()
{
    srand(time(nullptr));
    FullScreen();
    Sleep(100);

    while (1)
    {
        fstream file(PathSavedAccount, ios::in | ios::binary);
        User *tempUser = nullptr;
        if (file)
        {
            int sizeStr_username;
            string _username;
            int sizeStr_password;
            string _password;

            file.read(reinterpret_cast<char *>(&sizeStr_username), sizeof(sizeStr_username));
            _username.resize(sizeStr_username, '\0');
            file.read(_username.data(), sizeStr_username);

            file.read(reinterpret_cast<char *>(&sizeStr_password), sizeof(sizeStr_password));
            _password.resize(sizeStr_password, '\0');
            file.read(_password.data(), sizeStr_password);

            int i;
            User *temp;
            if (IsThereThisInfo<string, UserInfo>(_username, UserInfo::Username, &i))
            {
                temp = User::loadInfoOneUser(i, 1);

                if (temp->getPassword() == _password)
                {
                    switch (temp->getType())
                    {
                    case UserType::Admin:
                        tempUser = dynamic_cast<Admin *>(temp);
                        break;
                    case UserType::Seller:
                        tempUser = dynamic_cast<Seller *>(temp);
                        break;
                    case UserType::Buyer:
                        tempUser = dynamic_cast<Buyer *>(temp);
                        break;

                    default:
                        break;
                    }
                }
            }
        }
        file.close();

        if (tempUser == nullptr)
        {
            // welcome screen and signup-login menu
            AccountAction action;
            bool isTheChoiceChanged = false;
            string guidText1 = "Change your choice with [<-] , [->] keys";
            string guidText2 = "Select your choice with [Enter] key";
            string guidText3 = "* If your window isn't full screen it's best to make it full screen *";

            vector<string> options = {"Signup", "Login", "Exit"};
            vector<string> tempOptions;
            vector<vector<string>> buttons;

            tempOptions = options;
            for (auto x : tempOptions)
            {
                buttons.push_back(CreateButton(x, HorizontalPaddingButton, HorizontalMarginButton, VerticalMarginButton));
            }

            DrawBorder(Padding, Margin);
            PutMidlle(WelcomeText(), Horizontal, CursorPlace::BeginningNextLine);
            PutMidlle(CombineVecStr(buttons, Horizontal), Horizontal, CursorPlace::BeginningNextLine);

            buttons.clear();

            PutMidlle(vector<string>{guidText1, guidText2, guidText3, "", "Developed by Morteza Mahboobi"}, Horizontal, CursorPlace::BeginningNextLine);

            int i;
            int key;
            do
            {
                key = getch();

                if (key == 0 || key == 224)
                {
                    key = getch();

                    if (key == RIGHT_KEY)
                    {
                        if (!isTheChoiceChanged)
                        {
                            isTheChoiceChanged = true;
                            i = 0;
                        }
                        else
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
                    }
                    else if (key == LEFT_KEY)
                    {
                        if (!isTheChoiceChanged)
                        {
                            isTheChoiceChanged = true;
                            i = 0;
                        }
                        else
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

                    system("cls");
                    tempOptions = options;
                    createSelectedOption<vector<string>, SelectorType::OptionSelector>(tempOptions, i);
                    for (auto x : tempOptions)
                    {
                        buttons.push_back(CreateButton(x, HorizontalPaddingButton, HorizontalMarginButton, VerticalMarginButton));
                    }

                    DrawBorder(Padding, Margin);
                    PutMidlle(WelcomeText(), Horizontal, CursorPlace::BeginningNextLine);
                    PutMidlle(CombineVecStr(buttons, Horizontal), Horizontal, CursorPlace::BeginningNextLine);

                    buttons.clear();

                    PutMidlle(vector<string>{guidText1, guidText2, guidText3, "", "Developed by Morteza Mahboobi"}, Horizontal, CursorPlace::BeginningNextLine);
                }
            } while (!(key == ENTER_KEY && isTheChoiceChanged));

            if (i == 0)
            {
                action = AccountAction::Signup;
            }
            else if (i == 1)
            {
                action = AccountAction::Login;
            }
            else if (i == 2)
            {
                FarewellAnimation(1);
                return 0;
            }

            system("cls");

            // login and signup menu
            switch (action)
            {
            case AccountAction::Signup:
                try
                {
                    tempUser = User::signup();

                    fstream file(PathSavedAccount, ios::out | ios::binary);

                    int sizeStr_username = tempUser->getUsername().size();
                    string _username = tempUser->getUsername();
                    int sizeStr_password = tempUser->getPassword().size();
                    string _password = tempUser->getPassword();

                    file.write(reinterpret_cast<char *>(&sizeStr_username), sizeof(sizeStr_username));
                    file.write(_username.data(), sizeStr_username);

                    file.write(reinterpret_cast<char *>(&sizeStr_password), sizeof(sizeStr_password));
                    file.write(_password.data(), sizeStr_password);

                    file.close();

                    cout << "\nAccount created successfully.\n";
                }
                catch (const runtime_error &e)
                {
                    cout << endl;
                    cerr << e.what() << endl;
                    tempUser = nullptr;
                }
                Sleep(700);
                system("cls");
                break;
            case AccountAction::Login:
                try
                {
                    tempUser = User::login();

                    fstream file(PathSavedAccount, ios::out | ios::binary);

                    int sizeStr_username = tempUser->getUsername().size();
                    string _username = tempUser->getUsername();
                    int sizeStr_password = tempUser->getPassword().size();
                    string _password = tempUser->getPassword();

                    file.write(reinterpret_cast<char *>(&sizeStr_username), sizeof(sizeStr_username));
                    file.write(_username.data(), sizeStr_username);

                    file.write(reinterpret_cast<char *>(&sizeStr_password), sizeof(sizeStr_password));
                    file.write(_password.data(), sizeStr_password);

                    file.close();

                    cout << "\nLogged in successfully.\n";
                }
                catch (const runtime_error &e)
                {
                    cout << endl;
                    cerr << e.what() << endl;
                    tempUser = nullptr;
                }
                Sleep(700);
                system("cls");
                break;
            }
        }

        if (tempUser != nullptr)
        {
            if (tempUser->getType() == UserType::Admin)
            {
                Admin &admin = dynamic_cast<Admin &>(*tempUser);

                int choice;
                do
                {
                    system("cls");
                    PrintVecStr(CreateTitle("Welcome To Admin Panel"), Vertical);

                    vector<string> options = {
                        "Show All Product",
                        "Accept Product",
                        "Delete Product",
                        "Discount On Products",
                        "History Of All Sales",
                        "Manage Users\n",
                        "Show Profile",
                        "Change Info",
                        "Manage Wallet",
                        "Delete Account",
                        "Logout\n",
                        "Exit"};

                    choice = SelectMenu("Choose The Option: \n", options);

                    system("cls");

                    switch (choice)
                    {
                    case 0:
                    {
                        admin.showProducts();
                        break;
                    }
                    case 1:
                    {
                        admin.acceptProduct();
                        break;
                    }
                    case 2:
                    {
                        admin.deleteProduct();
                        break;
                    }
                    case 3:
                    {
                        while (1)
                        {
                            system("cls");

                            float discountAmount;

                            PrintVecStr(CreateTitle("Discount Page"), Vertical);
                            cout << "How many percent: ";
                            cin >> discountAmount;
                            cin.get();
                            cout << endl;

                            if (discountAmount < 0 || discountAmount > 100)
                            {
                                cout << "Discount must be between 0 and 100...";
                                cout << endl;
                            }
                            else
                            {
                                int whichOne = SelectMenu("Choose one option: ", vector<string>{"All product", "Special pet", "Special info\n", "Exit"});

                                if (whichOne == 3)
                                {
                                    break;
                                }
                                else
                                {
                                    switch (whichOne)
                                    {
                                    case 0:
                                    {
                                        admin.discountOnProducts(Pet::loadInfoAllPet(), discountAmount);

                                        LoadingAnimation();

                                        cout << "\nDiscount applied to products...";
                                        Sleep(700);

                                        break;
                                    }
                                    case 1:
                                    {
                                        int selectedProduct;
                                        vector<Pet *> pets = Pet::loadInfoAllPet();
                                        vector<Pet *> tempPets;
                                        vector<vector<string>> products;

                                        for (auto x : pets)
                                        {
                                            products.push_back(x->createProductStyleForManaging());
                                        }

                                        while (1)
                                        {
                                            system("cls");

                                            if (products.size() != 0)
                                            {
                                                selectedProduct = SelectBoxes(products, "Use [->] , [<-] key to navigate between items | Press [Enter] to choose pet | Press [Esc] for end choosing");

                                                if (selectedProduct != -1)
                                                {
                                                    tempPets.push_back(pets[selectedProduct]);

                                                    products.erase(products.begin() + selectedProduct);
                                                    pets.erase(pets.begin() + selectedProduct);
                                                }
                                                else
                                                {
                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                cout << endl;
                                                cout << endl;
                                                PutMidlle(vector<string>{"-- There is no product --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
                                                cin.get();
                                                system("cls");
                                                break;
                                            }
                                        }

                                        if (tempPets.size() != 0)
                                        {
                                            admin.discountOnProducts(tempPets, discountAmount);

                                            LoadingAnimation();

                                            cout << "\nDiscount applied to products...";
                                            Sleep(700);
                                        }
                                        break;
                                    }
                                    case 2:
                                    {
                                        vector<Pet *> pets = Pet::loadInfoAllPet();
                                        vector<Pet *> tempPets;

                                        system("cls");

                                        PrintVecStr(CreateTitle("Discount Page"), Vertical);
                                        cout << "How many percent: " << discountAmount;
                                        cout << "\n\n";

                                        int whichInfo = SelectMenu("Choose one info: ", vector<string>{"Species",
                                                                                                       "Color",
                                                                                                       "Breed",
                                                                                                       "Seller Id",
                                                                                                       "Rating\n",
                                                                                                       "Exit"});

                                        switch (whichInfo)
                                        {
                                        case 0:
                                        {
                                            cout << endl;
                                            PetSpecies _species;
                                            _species = SelectOption<PetSpecies>("Pet's Species: ");

                                            for (auto x : pets)
                                            {
                                                if (x->getSpecies() == _species)
                                                {
                                                    tempPets.push_back(x);
                                                }
                                            }

                                            break;
                                        }
                                        case 1:
                                        {
                                            cout << endl;
                                            Colors _color;
                                            _color = SelectOption<Colors>("Pet's Color: ");

                                            for (auto x : pets)
                                            {
                                                if (x->getColor() == _color)
                                                {
                                                    tempPets.push_back(x);
                                                }
                                            }

                                            break;
                                        }
                                        case 2:
                                        {
                                            cout << endl;
                                            string _breed;
                                            cout << "Pet's Breed: ";
                                            getline(cin, _breed);

                                            for (auto x : pets)
                                            {
                                                if (x->getBreed() == _breed)
                                                {
                                                    tempPets.push_back(x);
                                                }
                                            }

                                            break;
                                        }
                                        case 3:
                                        {
                                            cout << endl;
                                            int _sellerId;
                                            cout << "Seller Id: ";
                                            cin >> _sellerId;
                                            cin.get();

                                            for (auto x : pets)
                                            {
                                                if (x->getSellerId() == _sellerId)
                                                {
                                                    tempPets.push_back(x);
                                                }
                                            }

                                            break;
                                        }
                                        case 4:
                                        {
                                            cout << endl;
                                            int _minRating;
                                            int _maxRating;
                                            cout << "Minimum Pet's Rating: ";
                                            cin >> _minRating;
                                            cout << "Maximum Pet's Rating: ";
                                            cin >> _maxRating;
                                            cin.get();

                                            for (auto x : pets)
                                            {
                                                if (x->getRating() >= _minRating && x->getRating() <= _maxRating)
                                                {
                                                    tempPets.push_back(x);
                                                }
                                            }

                                            break;
                                        }
                                        case 5:
                                        {
                                            break;
                                        }
                                        }

                                        admin.discountOnProducts(tempPets, discountAmount);

                                        LoadingAnimation();

                                        cout << "\nDiscount applied to products...";
                                        Sleep(700);

                                        break;
                                    }
                                    }
                                }
                            }
                        }

                        break;
                    }
                    case 4:
                    {
                        admin.allSalesHistory();
                        break;
                    }
                    case 5:
                    {
                        while (1)
                        {
                            system("cls");

                            PrintVecStr(CreateTitle("User Management Page"), Vertical);
                            vector<string> options = enumMember<ManagingOption>();
                            options.insert(options.begin(), "View All User Profiles");
                            options[3].push_back('\n');
                            options.push_back("Exit");
                            int _option = SelectMenu("What do you want to do? ", options);
                            system("cls");

                            int selectedUser = -1;

                            vector<User *> users = User::loadInfoAllUser();
                            vector<vector<string>> profiles;

                            for (auto it = users.begin(); it != users.end();)
                            {
                                if ((*it)->getId() != admin.getId())
                                {
                                    profiles.push_back((*it)->createProfileStyle());
                                    it++;
                                }
                                else
                                {
                                    it = users.erase(it);
                                }
                            }

                            if (_option == 4)
                            {
                                break;
                            }
                            else if (_option != 0)
                            {
                                if (profiles.size() != 0)
                                {
                                    selectedUser = SelectBoxes(profiles, "Use [->] , [<-] key to navigate between items | Press [Enter] to choose the user | Press [Esc] to exit");
                                }
                                else
                                {
                                    cout << endl;
                                    cout << endl;
                                    PutMidlle(vector<string>{"-- There is no user --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
                                    cin.get();
                                }

                                if (selectedUser != -1)
                                {
                                    system("cls");
                                    _option--;
                                    admin.manageUser(users[selectedUser], static_cast<ManagingOption>(_option));
                                }
                            }
                            else
                            {
                                if (profiles.size() != 0)
                                {
                                    ShowSomeBoxes(profiles);
                                }
                                else
                                {
                                    cout << endl;
                                    cout << endl;
                                    PutMidlle(vector<string>{"-- There is no user --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
                                    cin.get();
                                }
                            }
                        }
                        break;
                    }
                    case 6:
                    {
                        admin.showProfile();
                        break;
                    }
                    case 7:
                    {
                        admin.changeInfo();
                        break;
                    }
                    case 8:
                    {
                        admin.manageWallet();
                        break;
                    }
                    case 9:
                    {
                        admin.deleteAccount();
                        fstream file(PathSavedAccount, ios::out | ios::binary);
                        file.close();
                        break;
                    }
                    case 10:
                    {
                        fstream file(PathSavedAccount, ios::out | ios::binary);
                        file.close();
                        break;
                    }
                    case 11:
                    {
                        FarewellAnimation(2);
                        return 0;
                        break;
                    }
                    default:
                        break;
                    }
                } while (!(choice == 9 || choice == 10 || choice == 11));
            }
            else if (tempUser->getType() == UserType::Seller)
            {
                Seller &seller = dynamic_cast<Seller &>(*tempUser);

                int choice;
                do
                {
                    system("cls");
                    PrintVecStr(CreateTitle("Welcome To Seller Panel"), Vertical);

                    vector<string> options = {
                        "Show My Products",
                        "Add Product",
                        "Edit Product",
                        "Delete Product",
                        "Sales History\n",
                        "Show Profile",
                        "Change Info",
                        "Manage Wallet",
                        "Delete Account",
                        "Logout\n",
                        "Exit"};

                    choice = SelectMenu("Choose The Option: \n", options);

                    system("cls");

                    switch (choice)
                    {
                    case 0:
                    {
                        seller.showProducts();
                        break;
                    }
                    case 1:
                    {
                        seller.addProduct();
                        break;
                    }
                    case 2:
                    {
                        seller.editProduct();
                        break;
                    }
                    case 3:
                    {
                        seller.deleteProduct();
                        break;
                    }
                    case 4:
                    {
                        seller.salesHistory();
                        break;
                    }
                    case 5:
                    {
                        seller.showProfile();
                        break;
                    }
                    case 6:
                    {
                        seller.changeInfo();
                        break;
                    }
                    case 7:
                    {
                        seller.manageWallet();
                        break;
                    }
                    case 8:
                    {
                        seller.deleteAccount();
                        fstream file(PathSavedAccount, ios::out | ios::binary);
                        file.close();
                        break;
                    }
                    case 9:
                    {
                        fstream file(PathSavedAccount, ios::out | ios::binary);
                        file.close();
                        break;
                    }
                    case 10:
                    {
                        FarewellAnimation(2);
                        return 0;
                        break;
                    }
                    default:
                        break;
                    }
                } while (!(choice == 8 || choice == 9 || choice == 10));
            }
            else if (tempUser->getType() == UserType::Buyer)
            {
                Buyer &buyer = dynamic_cast<Buyer &>(*tempUser);

                int choice;
                do
                {

                    system("cls");
                    PrintVecStr(CreateTitle("Welcome To Pet Shop Menu"), Vertical);

                    vector<string> options = {
                        "Show The Products",
                        "Buying + Rating (After Buying)",
                        "Search Product",
                        "Show Shopping History\n",
                        "Show Profile",
                        "Change Info",
                        "Manage Wallet",
                        "Delete Account",
                        "Logout\n",
                        "Exit"};

                    choice = SelectMenu("Choose The Option: \n", options);

                    system("cls");

                    switch (choice)
                    {
                    case 0:
                    {
                        buyer.showProducts();
                        break;
                    }
                    case 1:
                    {
                        int selectedProduct;

                        vector<Pet *> pets = Pet::loadInfoAllPet();
                        vector<Pet *> tempPets;
                        vector<vector<string>> products;

                        for (auto x : pets)
                        {
                            if (x->getStatus() == true)
                            {
                                products.push_back(x->createProductStyleForManaging());
                                tempPets.push_back(x);
                            }
                        }

                        if (products.size() != 0)
                        {
                            selectedProduct = SelectBoxes(products, "Use [->] , [<-] key to navigate between items | Press [Enter] to select the product for buying | Press [Esc] to exit");

                            system("cls");

                            if (selectedProduct != -1)
                            {
                                if (buyer.buying(tempPets, selectedProduct))
                                {
                                    float score;
                                    system("cls");
                                    cout << endl;
                                    cout << "Thank you for your purchase!\n";
                                    cout << "Please rate this pet. Your feedback helps us improve.\n";

                                    cout << endl;
                                    cout << "Rate [0-5]: ";
                                    cin >> score;
                                    cin.get();

                                    buyer.ratingPet(tempPets[selectedProduct], score);

                                    cout << endl;
                                    cout << "Thanks for rating";
                                    Sleep(700);
                                }
                                else
                                {
                                    cout << endl;
                                    cout << "You can't rate this pet. You need to buy it first to rate it.\n";
                                    cout << endl;
                                    cout << "Press [Enter] to continue";
                                    cin.get();
                                }
                            }
                        }
                        else
                        {
                            cout << endl;
                            cout << endl;
                            PutMidlle(vector<string>{"-- There is no product --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
                            cin.get();
                        }

                        break;
                    }
                    case 2:
                    {
                        PrintVecStr(CreateTitle("Searche Page"), Vertical);
                        SearchingItems _category;
                        _category = SelectOption<SearchingItems>("Select the animal category: ");

                        system("cls");

                        vector<Pet *> targetPets = buyer.searchProduct(_category);

                        system("cls");

                        vector<vector<string>> products;

                        int selectedProduct;

                        for (auto x : targetPets)
                        {
                            if (x->getStatus() == true)
                            {
                                products.push_back(x->createProductStyleForManaging());
                            }
                        }

                        if (products.size() != 0)
                        {
                            selectedProduct = SelectBoxes(products, "Use [->] , [<-] key to navigate between items | Press [Enter] to select the product for buying | Press [Esc] to exit");

                            system("cls");

                            if (selectedProduct != -1)
                            {
                                if (buyer.buying(targetPets, selectedProduct))
                                {
                                    float score;
                                    system("cls");
                                    cout << endl;
                                    cout << "Thank you for your purchase!\n";
                                    cout << "Please rate this pet. Your feedback helps us improve.\n";

                                    cout << endl;
                                    cout << "Rate [0-5]: ";
                                    cin >> score;
                                    cin.get();

                                    buyer.ratingPet(targetPets[selectedProduct], score);

                                    cout << endl;
                                    cout << "Thanks for rating";
                                    Sleep(700);
                                }
                                else
                                {
                                    cout << endl;
                                    cout << "You can't rate this pet. You need to buy it first to rate it.\n";
                                    cout << endl;
                                    cout << "Press [Enter] to continue";
                                    cin.get();
                                }
                            }
                        }
                        else
                        {
                            cout << endl;
                            cout << endl;
                            PutMidlle(vector<string>{"-- There is no product --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
                            cin.get();
                        }

                        break;
                    }
                    case 3:
                    {
                        buyer.purchaseHistory();
                        break;
                    }
                    case 4:
                    {
                        buyer.showProfile();
                        break;
                    }
                    case 5:
                    {
                        buyer.changeInfo();
                        break;
                    }
                    case 6:
                    {
                        buyer.manageWallet();
                        break;
                    }
                    case 7:
                    {
                        buyer.deleteAccount();
                        fstream file(PathSavedAccount, ios::out | ios::binary);
                        file.close();
                        break;
                    }
                    case 8:
                    {
                        fstream file(PathSavedAccount, ios::out | ios::binary);
                        file.close();
                        break;
                    }
                    case 9:
                    {
                        FarewellAnimation(2);
                        return 0;
                        break;
                    }
                    default:
                        break;
                    }
                } while (!(choice == 7 || choice == 8 || choice == 9));
            }
            system("cls");
            delete tempUser;
        }
    }
}