#include "headers/myClass.hpp"
#include "headers/graphic & utilities.hpp"
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
#define PathUser "file/User.dat"
#define PathPet "file/Pet.dat"
#define PathTransaction "file/Transaction.dat"
#define PathSavedAccount "file/SavedAccount.dat"

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

            PutMidlle(vector<string>{guidText1, guidText2, guidText3,"","Developed by Morteza Mahboobi"}, Horizontal, CursorPlace::BeginningNextLine);

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

                    PutMidlle(vector<string>{guidText1, guidText2, guidText3,"","Developed by Morteza Mahboobi"}, Horizontal, CursorPlace::BeginningNextLine);
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
                } while (!(choice == 10 || choice == 11));
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
                } while (!(choice == 9 || choice == 10));
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
                } while (!(choice == 8 || choice == 9));
            }
            system("cls");
            delete tempUser;
        }
    }
}

//========================= Account Class Functions

Account::Account()
{
    setBalance(0);
}

Account::Account(float _balance)
{
    bool areAllValuesOk = false;

    while (!areAllValuesOk)
    {
        try
        {
            setBalance(_balance);

            areAllValuesOk = true;
        }
        catch (const setValuesException &e)
        {
            cout << endl;
            cerr << e.what() << endl;
            cout << "Plese enter your " << enum_to_string<VariablesToValidate>(e.getVariableName()) << " again: ";
            if (e.checkVariableName(VariablesToValidate::Balance))
            {
                cin >> _balance;
                cin.get();
            }
        }
    }
}

void Account::setBalance(float _balance)
{
    if (_balance < 0)
        throw setValuesException("The balance amount isn't valid... ", VariablesToValidate::Balance);

    balance = _balance;
}

float Account::getBalance() const { return balance; }

string Account::showBalance()
{
    string text = "Your Balance is: " + normalizeFloatString(to_string(balance)) + " $";
    return text;
}

void Account::deposit(int userId)
{
    float amount;

    PrintVecStr(CreateTitle("Money Deposit Page"), Vertical);
    cout << "How much do you want to deposit: ";
    cin >> amount;
    cin.get();

    TransactionInfo info;
    info.transactionId = createTransactionId(userId);
    info.userId = userId;
    info.type = TransactionType::Deposit;
    info.amount = amount;
    info.newBalance = balance;
    info.status = TransactionStatus::Success;
    info.transactionTime = getTime();
    info.petId = -1;
    info.sellerId = -1;

    User *tmpUser = User::loadInfoOneUser(userId, 2);

    tmpUser->setBalance(balance + amount);
    setBalance(balance + amount);
    info.newBalance = balance;
    saveTransaction(info);

    tmpUser->updateInfoThisUserInBinaryFile();

    LoadingAnimation();

    cout << "\nDeposit completed successfully...";
    Sleep(700);
}

void Account::withdraw(int userId)
{
    float amount;

    PrintVecStr(CreateTitle("Money Withdrawal Page"), Vertical);
    cout << "How much do you want to withdraw: ";
    cin >> amount;
    cin.get();

    TransactionInfo info;
    info.transactionId = createTransactionId(userId);
    info.userId = userId;
    info.type = TransactionType::Withdrawal;
    info.amount = amount;
    info.newBalance = balance;
    info.status = TransactionStatus::Pending;
    info.transactionTime = getTime();
    info.petId = -1;
    info.sellerId = -1;
    saveTransaction(info);

    while (1)
    {
        try
        {
            User *tmpUser = User::loadInfoOneUser(userId, 2);
            tmpUser->setBalance(balance - amount);
            setBalance(balance - amount);
            info.newBalance = balance;
            info.status = TransactionStatus::Success;
            updateThisTransaction(info);

            tmpUser->updateInfoThisUserInBinaryFile();

            LoadingAnimation();

            cout << "\nWithdrawal completed successfully...";
            Sleep(700);

            break;
        }
        catch (const setValuesException &e)
        {
            info.status = TransactionStatus::Failed;
            updateThisTransaction(info);

            cout << endl;

            cout << "The amount you want to withdraw is more than your balance...\n";
            cout << "Your balance: " << balance << endl;
            cout << "If you want to cancel it, enter 0 ";
            cout << "or enter an amount less than or equal to your available balance: ";
            cin >> amount;
            cin.get();

            if (amount == 0)
            {
                info.status = TransactionStatus::Canceled;
                updateThisTransaction(info);
                break;
            }
        }
    }
}

void Account::transfer(int senderId, int recipientId = -1)
{
    float amount;

    try
    {
        PrintVecStr(CreateTitle("Money Transfer Page"), Vertical);
        if (recipientId == -1)
        {
            cout << "Please enter the ID of the person you want to transfer money to: ";
            cin >> recipientId;
            cin.get();
        }

        if (senderId == recipientId)
        {
            cout << endl;
            cout << "You can't transfer money to yourself\n";
            cout << endl;
            cout << "Press [Enter] to continue";
            cin.get();
            return;
        }

        User *recipient = User::loadInfoOneUser(recipientId, 2);
        cout << "How much do you want to transfer to \"" << recipient->getName() << "\": ";
        cin >> amount;
        cin.get();

        TransactionInfo senderInfo;
        senderInfo.transactionId = createTransactionId(senderId);
        senderInfo.userId = senderId;
        senderInfo.type = TransactionType::Transfer;
        senderInfo.amount = amount;
        senderInfo.newBalance = getBalance();
        senderInfo.status = TransactionStatus::Pending;
        senderInfo.transactionTime = getTime();
        senderInfo.petId = -1;
        senderInfo.sellerId = -1;
        saveTransaction(senderInfo);

        TransactionInfo recipientInfo;
        recipientInfo.transactionId = createTransactionId(recipientId);
        recipientInfo.userId = recipientId;
        recipientInfo.type = TransactionType::Deposit;
        recipientInfo.amount = amount;
        recipientInfo.newBalance = recipient->getBalance();
        recipientInfo.status = TransactionStatus::Pending;
        recipientInfo.transactionTime = getTime();
        recipientInfo.petId = -1;
        recipientInfo.sellerId = -1;
        saveTransaction(recipientInfo);

        while (1)
        {
            try
            {
                User *tmpUser = User::loadInfoOneUser(senderId, 2);
                tmpUser->setBalance(balance - amount);
                setBalance(balance - amount);
                senderInfo.newBalance = getBalance();
                senderInfo.status = TransactionStatus::Success;
                updateThisTransaction(senderInfo);

                tmpUser->updateInfoThisUserInBinaryFile();

                recipient->setBalance(recipient->getBalance() + amount);
                recipientInfo.newBalance = recipient->getBalance();
                recipientInfo.status = TransactionStatus::Success;
                updateThisTransaction(recipientInfo);

                recipient->updateInfoThisUserInBinaryFile();

                LoadingAnimation();

                cout << "\nTransfer completed successfully...";
                Sleep(700);

                break;
            }
            catch (const setValuesException &e)
            {
                senderInfo.status = TransactionStatus::Failed;
                updateThisTransaction(senderInfo);
                recipientInfo.status = TransactionStatus::Failed;
                updateThisTransaction(recipientInfo);

                cout << endl;

                cout << "The amount you want to recipientInfo is more than your balance...\n";
                cout << "Your balance: " << getBalance() << endl;
                cout << "If you want to cancel it, enter 0 ";
                cout << "or enter an amount less than or equal to your available balance: ";
                cin >> amount;
                cin.get();

                if (amount == 0)
                {
                    senderInfo.status = TransactionStatus::Canceled;
                    updateThisTransaction(senderInfo);
                    recipientInfo.status = TransactionStatus::Canceled;
                    updateThisTransaction(recipientInfo);
                    break;
                }
            }
        }
    }
    catch (const runtime_error &e)
    {
        cout << endl;
        cerr << e.what() << endl;
        cout << endl;
        cout << "Press [Enter] to continue";
        cin.get();
    }
}

bool Account::purchase(Pet *pet, int buyerId)
{
    TransactionInfo buyerInfo;
    buyerInfo.transactionId = createTransactionId(buyerId);
    buyerInfo.userId = buyerId;
    buyerInfo.type = TransactionType::Purchase;
    buyerInfo.amount = pet->getPrice();
    buyerInfo.newBalance = balance;
    buyerInfo.status = TransactionStatus::Pending;
    buyerInfo.transactionTime = getTime();
    buyerInfo.petId = pet->getId();
    buyerInfo.sellerId = User::loadInfoOneUser(pet->getSellerId(), 2)->getId();
    saveTransaction(buyerInfo);

    User *seller = User::loadInfoOneUser(pet->getSellerId(), 2);
    TransactionInfo sellerInfo;
    sellerInfo.transactionId = createTransactionId(seller->getId());
    sellerInfo.userId = seller->getId();
    sellerInfo.type = TransactionType::Sell;
    sellerInfo.amount = pet->getPrice();
    sellerInfo.newBalance = seller->getBalance();
    sellerInfo.status = TransactionStatus::Pending;
    sellerInfo.transactionTime = getTime();
    sellerInfo.petId = pet->getId();
    sellerInfo.sellerId = seller->getId();
    saveTransaction(sellerInfo);

    try
    {
        User *tmpUser = User::loadInfoOneUser(buyerId, 2);
        tmpUser->setBalance(balance - pet->getPrice());
        setBalance(balance - pet->getPrice());
        buyerInfo.newBalance = balance;
        buyerInfo.status = TransactionStatus::Success;
        updateThisTransaction(buyerInfo);

        tmpUser->updateInfoThisUserInBinaryFile();

        seller->setBalance(seller->getBalance() + pet->getPrice());
        sellerInfo.newBalance = seller->getBalance();
        sellerInfo.status = TransactionStatus::Success;
        updateThisTransaction(sellerInfo);

        seller->updateInfoThisUserInBinaryFile();

        LoadingAnimation();

        cout << "\nPurchase completed successfully...";
        Sleep(700);

        return true;
    }
    catch (const setValuesException &e)
    {
        buyerInfo.status = TransactionStatus::Failed;
        updateThisTransaction(buyerInfo);
        sellerInfo.status = TransactionStatus::Failed;
        updateThisTransaction(sellerInfo);

        cout << endl;

        cout << "The price of the pet you chosen is more than your balance...\n";
        cout << "Your balance: " << balance << endl;
        cout << "Please choose another one or Increase your balance.\n";

        return false;
    }
}

void Account::saveTransaction(const TransactionInfo &info)
{
    int sizeStr_transactionId = info.transactionId.size();
    string _transactionId = info.transactionId;
    int _userId = info.userId;
    TransactionType _type = info.type;
    float _amount = info.amount;
    float _newBalance = info.newBalance;
    TransactionStatus _status = info.status;
    int sizeStr_transactionTime = info.transactionTime.size();
    string _transactionTime = info.transactionTime;
    int _petId = info.petId;
    int _sellerId = info.sellerId;

    fstream file(PathTransaction, ios::binary | ios::app);

    file.write(reinterpret_cast<char *>(&sizeStr_transactionId), sizeof(sizeStr_transactionId));
    file.write(_transactionId.data(), sizeStr_transactionId);

    file.write(reinterpret_cast<char *>(&_userId), sizeof(_userId));
    file.write(reinterpret_cast<char *>(&_type), sizeof(_type));
    file.write(reinterpret_cast<char *>(&_amount), sizeof(_amount));
    file.write(reinterpret_cast<char *>(&_newBalance), sizeof(_newBalance));
    file.write(reinterpret_cast<char *>(&_status), sizeof(_status));

    file.write(reinterpret_cast<char *>(&sizeStr_transactionTime), sizeof(sizeStr_transactionTime));
    file.write(_transactionTime.data(), sizeStr_transactionTime);

    file.write(reinterpret_cast<char *>(&_petId), sizeof(_petId));
    file.write(reinterpret_cast<char *>(&_sellerId), sizeof(_sellerId));

    file.close();
}

vector<TransactionInfo> Account::loadAllTransaction()
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

void Account::updateThisTransaction(const TransactionInfo &info)
{
    vector<TransactionInfo> data = Account::loadAllTransaction();

    int index = 0;

    if (data.size() != 0)
    {
        for (auto x : data)
        {
            if (x.transactionId == info.transactionId)
            {
                break;
            }
            index++;
        }
        data[index] = info;

        fstream file(PathTransaction, ios::out | ios::binary);

        for (auto x : data)
        {
            Account::saveTransaction(x);
        }

        file.close();
    }
    else
    {
        cout << endl;
        cout << endl;
        PutMidlle(vector<string>{"-- There is no transaction --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
        cin.get();
    }
}

void Account::updateAllTransactionInBinaryFile(const vector<TransactionInfo> &transactions)
{
    fstream file(PathTransaction, ios::out | ios::binary);

    for (auto x : transactions)
    {
        saveTransaction(x);
    }

    file.close();
}

void Account::transactionHistory(vector<TransactionInfo> data)
{
    ShowSomeTransaction(data);
}

//========================= User Class Functions

User::User(string _name, string _username, string _password, string _phoneNumber, UserType _type)
    : id(SetIds(ObjectType::User))
{
    bool areAllValuesOk = false;

    while (!areAllValuesOk)
    {
        try
        {
            setName(_name);
            setUsername(_username);
            setPassword(_password);
            setPhoneNumber(_phoneNumber);
            setType(_type);

            areAllValuesOk = true;
        }
        catch (const setValuesException &e)
        {
            cout << endl;
            cerr << e.what() << endl;
            cout << "-> If you want to exit, enter 0, otherwise ";
            cout << "Enter your " << enum_to_string<VariablesToValidate>(e.getVariableName()) << " again: ";
            if (e.checkVariableName(VariablesToValidate::Username))
            {
                cin >> _username;
                cin.get();
                if (_username == "0")
                {
                    DeleteLastIds(ObjectType::User);
                    throw runtime_error("Exit...");
                }
            }
            else if (e.checkVariableName(VariablesToValidate::Password))
            {
                cin >> _password;
                cin.get();
                if (_password == "0")
                {
                    DeleteLastIds(ObjectType::User);
                    throw runtime_error("Exit...");
                }
            }
            else if (e.checkVariableName(VariablesToValidate::PhoneNumber))
            {
                cin >> _phoneNumber;
                cin.get();
                if (_phoneNumber == "0")
                {
                    DeleteLastIds(ObjectType::User);
                    throw runtime_error("Exit...");
                }
            }
        }
    }

    saveInBinaryFile();
}

// for load info
User::User(int _id, string _name, string _username, string _password, string _phoneNumber, UserType _type, float _balance)
    : id(_id), name(_name), username(_username), password(_password), phoneNumber(_phoneNumber), type(_type), userAccount(_balance) {}

void User::setType(UserType _type)
{
    type = _type;
}

void User::setName(string _name)
{
    name = _name;
}

void User::setUsername(string _username)
{
    if (isDuplicateUsername(_username))
        throw setValuesException("This username is already taken... ", VariablesToValidate::Username);

    if (!((_username[0] >= 'a' && _username[0] <= 'z') || (_username[0] >= 'A' && _username[0] <= 'Z')))
        throw setValuesException("Username must start with an English letter... ", VariablesToValidate::Username);

    username = _username;
}

void User::setPassword(string _password)
{
    if (_password.size() < 4)
        throw setValuesException("Password must be at least 4 characters long.... ", VariablesToValidate::Password);

    password = _password;
}

void User::setPhoneNumber(string _phoneNumber)
{
    bool isItNumber = true;
    for (auto x : _phoneNumber)
    {
        if (!(x >= '0' && x <= '9'))
        {
            isItNumber = false;
            break;
        }
    }

    bool rightLength = true;
    if (_phoneNumber.size() != 11)
        rightLength = false;

    if (!isItNumber)
        throw setValuesException("Your phone number must only contain numbers... ", VariablesToValidate::PhoneNumber);

    if (!rightLength)
        throw setValuesException("Phone number must be exactly 11 digits... ", VariablesToValidate::PhoneNumber);

    phoneNumber = _phoneNumber;
}

void User::setBalance(float _balance)
{
    userAccount.setBalance(_balance);
}

int User::getId() const { return id; }

string User::getName() const { return name; }

string User::getUsername() const { return username; }

string User::getPassword() const { return password; }

string User::getPhoneNumber() const { return phoneNumber; }

UserType User::getType() const { return type; }

float User::getBalance() const { return userAccount.getBalance(); }

User *User::signup()
{
    PrintVecStr(CreateTitle("Signup Page"), Vertical);
    cout << "Enter the requested information:\n";
    cout << "       * Case sensitive *       \n\n";

    string _name;
    cout << "Name: ";
    getline(cin, _name);

    string _username;
    cout << "Username: ";
    cin >> _username;
    cin.get();

    string _password;
    cout << "Password: ";
    cin >> _password;
    cin.get();

    string _phoneNumber;
    cout << "Phone Number: ";
    cin >> _phoneNumber;
    cin.get();

    UserType _type;
    _type = SelectOption<UserType>("Type: ");

    LoadingAnimation();

    User *temp;

    switch (_type)
    {
    case UserType::Admin:
        temp = new Admin(_name, _username, _password, _phoneNumber, _type);
        break;
    case UserType::Seller:
        temp = new Seller(_name, _username, _password, _phoneNumber, _type);
        break;
    case UserType::Buyer:
        temp = new Buyer(_name, _username, _password, _phoneNumber, _type);
        break;

    default:
        break;
    }

    return temp;
}

User *User::login()
{
    PrintVecStr(CreateTitle("Login Page"), Vertical);
    cout << "Enter the requested information:\n";
    cout << "       * Case sensitive *       \n\n";

    string _username;
    cout << "Username: ";
    cin >> _username;
    cin.get();

    string _password;
    cout << "Password: ";
    cin >> _password;
    cin.get();

    LoadingAnimation();

    int i;
    User *temp;

    if (IsThereThisInfo<string, UserInfo>(_username, UserInfo::Username, &i))
    {
        temp = loadInfoOneUser(i, 1);

        while (!(temp->password == _password))
        {
            cout << "\nThe password you entered is incorrect....\n";
            cout << "Please enter the password again or enter 0 to exit: ";
            cin >> _password;
            cin.get();

            if (_password == "0")
            {
                DeleteLastIds(ObjectType::User);
                throw runtime_error("Exit...");
            }
        }
    }
    else
    {
        throw runtime_error("User not found...");
    }

    switch (temp->type)
    {
    case UserType::Admin:
        temp = dynamic_cast<Admin *>(temp);
        break;
    case UserType::Seller:
        temp = dynamic_cast<Seller *>(temp);
        break;
    case UserType::Buyer:
        temp = dynamic_cast<Buyer *>(temp);
        break;

    default:
        break;
    }

    return temp;
}

void User::deleteAccount()
{
    vector<string> warnings{
        "",
        "** Warning **",
        "if you delete this account, this action cannot be undone",
        "by deleting this account, all information, transactions and balance will be lost",
        ""};

    PutMidlle(warnings, Horizontal, CursorPlace::BeginningNextLine);

    bool isAccepted = (SelectButton(vector<string>{"are you sure about that ?"}, vector<string>{"Accept", "Reject"}, Vertical, 2, 0, 1) == 0) ? true : false;

    if (isAccepted)
    {
        vector<User *> users = User::loadInfoAllUser();
        auto it = users.begin();
        for (; it != users.end(); it++)
        {
            if ((*it)->getId() == getId())
            {
                users.erase(it);
                break;
            }
        }
        User::updateAllUserInBinaryFile(users);

        vector<TransactionInfo> transactions = Account::loadAllTransaction();
        for (auto itTrans = transactions.begin(); itTrans != transactions.end(); itTrans++)
        {
            if ((*itTrans).userId == getId())
            {
                transactions.erase(itTrans);
                break;
            }
        }
        Account::updateAllTransactionInBinaryFile(transactions);
    }
}

void User::changeInfo()
{
    while (1)
    {
        system("cls");

        PrintVecStr(CreateTitle("User Info Edit Page"), Vertical);
        cout << "Which information do you want to edit:\n\n";

        cout << "User ID: " << getId();
        cout << endl;
        cout << "Type: " << enum_to_string<UserType>(getType());
        cout << endl;

        string _name = name;
        string _username = username;
        string _password = password;
        string _phoneNumber = phoneNumber;

        vector<string> optionsMenu{
            "Name: " + _name,
            "Username: " + _username,
            "Password: " + _password,
            "Phone Number: " + _phoneNumber + '\n',
            "Exit"};

        int selected = SelectMenu("", optionsMenu);

        bool areAllValuesOk = false;

        if (selected == 4)
        {
            break;
        }
        else
        {
            system("cls");

            PrintVecStr(CreateTitle("User Info Edit Page"), Vertical);
            cout << "Which information do you want to edit:\n\n";

            cout << "User ID: " << getId();
            cout << endl;
            cout << "Type: " << enum_to_string<UserType>(getType());
            cout << endl;

            switch (selected)
            {
            case 0:
                cout << "Name: ";
                getline(cin, _name);
                break;
            case 1:
                cout << "Username: ";
                cin >> _username;
                cin.get();
                break;
            case 2:
                cout << "Password: ";
                cin >> _password;
                cin.get();
                break;
            case 3:
                cout << "Phone Number: ";
                cin >> _phoneNumber;
                cin.get();
                break;

            default:
                break;
            }

            while (!areAllValuesOk)
            {
                try
                {
                    switch (selected)
                    {
                    case 0:
                        setName(_name);
                        break;
                    case 1:
                        setUsername(_username);
                        break;
                    case 2:
                        setPassword(_password);
                        break;
                    case 3:
                        setPhoneNumber(_phoneNumber);
                        break;

                    default:
                        break;
                    }

                    LoadingAnimation();

                    cout << "\nChanges saved successfully...";
                    Sleep(700);

                    areAllValuesOk = true;
                }
                catch (const setValuesException &e)
                {
                    LoadingAnimation();

                    cout << endl;
                    cerr << e.what() << endl;
                    cout << "-> If you want to exit, enter 0, otherwise ";
                    cout << "Enter your " << enum_to_string<VariablesToValidate>(e.getVariableName()) << " again: ";
                    if (e.checkVariableName(VariablesToValidate::Username))
                    {
                        cin >> _username;
                        cin.get();
                        if (_username == "0")
                        {
                            DeleteLastIds(ObjectType::User);
                            throw runtime_error("Exit...");
                        }
                    }
                    else if (e.checkVariableName(VariablesToValidate::Password))
                    {
                        cin >> _password;
                        cin.get();
                        if (_password == "0")
                        {
                            DeleteLastIds(ObjectType::User);
                            throw runtime_error("Exit...");
                        }
                    }
                    else if (e.checkVariableName(VariablesToValidate::PhoneNumber))
                    {
                        cin >> _phoneNumber;
                        cin.get();
                        if (_phoneNumber == "0")
                        {
                            DeleteLastIds(ObjectType::User);
                            throw runtime_error("Exit...");
                        }
                    }
                }
            }

            updateInfoThisUserInBinaryFile();
        }
    }
}

void User::manageWallet()
{
    while (1)
    {
        system("cls");

        PrintVecStr(CreateTitle("Wallet Management Page"), Vertical);
        cout << "Hello Dear \"" << name << "\"" << endl;
        cout << userAccount.showBalance();
        cout << "\n\n";

        int option = SelectMenu("What do you want to do?", vector<string>{"Deposit", "Withdraw", "Transfer", "All Transaction History\n", "Exit"});
        system("cls");

        if (option == 4)
        {
            break;
        }
        else
        {
            switch (option)
            {
            case 0:
            {
                userAccount.deposit(getId());
                break;
            }
            case 1:
            {
                userAccount.withdraw(getId());
                break;
            }
            case 2:
            {
                userAccount.transfer(getId());
                break;
            }
            case 3:
            {
                vector<TransactionInfo> allTransactions = Account::loadAllTransaction();
                vector<TransactionInfo> tempTransactions;

                for (auto x : allTransactions)
                {
                    if (x.userId == getId())
                    {
                        tempTransactions.push_back(x);
                    }
                }

                if (tempTransactions.size() != 0)
                {
                    userAccount.transactionHistory(tempTransactions);
                }
                else
                {
                    cout << endl;
                    cout << endl;
                    PutMidlle(vector<string>{"-- There is no transaction --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
                    cin.get();
                }

                break;
            }
            }
        }
    }
}

void User::saveInBinaryFile()
{
    int _id = id;
    int sizeStr_name = name.size();
    string _name = name;
    int sizeStr_username = username.size();
    string _username = username;
    int sizeStr_password = password.size();
    string _password = password;
    int sizeStr_phoneNumber = phoneNumber.size();
    string _phoneNumber = phoneNumber;
    UserType _type = type;
    float _balance = userAccount.getBalance();

    fstream file(PathUser, ios::app | ios::binary);

    file.write(reinterpret_cast<char *>(&_id), sizeof(_id));

    file.write(reinterpret_cast<char *>(&sizeStr_name), sizeof(sizeStr_name));
    file.write(_name.data(), sizeStr_name);

    file.write(reinterpret_cast<char *>(&sizeStr_username), sizeof(sizeStr_username));
    file.write(_username.data(), sizeStr_username);

    file.write(reinterpret_cast<char *>(&sizeStr_password), sizeof(sizeStr_password));
    file.write(_password.data(), sizeStr_password);

    file.write(reinterpret_cast<char *>(&sizeStr_phoneNumber), sizeof(sizeStr_phoneNumber));
    file.write(_phoneNumber.data(), sizeStr_phoneNumber);

    file.write(reinterpret_cast<char *>(&_type), sizeof(_type));
    file.write(reinterpret_cast<char *>(&_balance), sizeof(_balance));

    file.close();
}

vector<User *> User::loadInfoAllUser()
{
    vector<User *> users;

    int _id;
    int sizeStr_name;
    string _name;
    int sizeStr_username;
    string _username;
    int sizeStr_password;
    string _password;
    int sizeStr_phoneNumber;
    string _phoneNumber;
    UserType _type;
    float _balance;

    fstream file(PathUser, ios::in | ios::binary);

    if (file)
    {
        while (file.read(reinterpret_cast<char *>(&_id), sizeof(_id)))
        {

            file.read(reinterpret_cast<char *>(&sizeStr_name), sizeof(sizeStr_name));
            _name.resize(sizeStr_name, '\0');
            file.read(_name.data(), sizeStr_name);

            file.read(reinterpret_cast<char *>(&sizeStr_username), sizeof(sizeStr_username));
            _username.resize(sizeStr_username, '\0');
            file.read(_username.data(), sizeStr_username);

            file.read(reinterpret_cast<char *>(&sizeStr_password), sizeof(sizeStr_password));
            _password.resize(sizeStr_password, '\0');
            file.read(_password.data(), sizeStr_password);

            file.read(reinterpret_cast<char *>(&sizeStr_phoneNumber), sizeof(sizeStr_phoneNumber));
            _phoneNumber.resize(sizeStr_phoneNumber, '\0');
            file.read(_phoneNumber.data(), sizeStr_phoneNumber);

            file.read(reinterpret_cast<char *>(&_type), sizeof(_type));
            file.read(reinterpret_cast<char *>(&_balance), sizeof(_balance));

            User *temp;
            switch (_type)
            {
            case UserType::Admin:
                temp = new Admin(_id, _name, _username, _password, _phoneNumber, _type, _balance);
                break;
            case UserType::Seller:
                temp = new Seller(_id, _name, _username, _password, _phoneNumber, _type, _balance);
                break;
            case UserType::Buyer:
                temp = new Buyer(_id, _name, _username, _password, _phoneNumber, _type, _balance);
                break;

            default:
                break;
            }
            users.push_back(temp);
        }
    }

    file.close();

    return users;
}

// whichInfo == 1 -> index of vector of all user
// whichInfo == 2 -> user id
User *User::loadInfoOneUser(int key, int whichInfo)
{
    vector<User *> users = User::loadInfoAllUser();

    switch (whichInfo)
    {
    case 1:
        if (key < users.size())
        {
            return users[key];
        }
        break;
    case 2:
        for (auto x : users)
        {
            if (x->getId() == key)
            {
                return x;
            }
        }
        break;
    }
    throw runtime_error("User does not exist...");
}

void User::updateAllUserInBinaryFile(vector<User *> users)
{
    fstream file(PathUser, ios::out | ios::binary);

    for (auto x : users)
    {
        x->saveInBinaryFile();
    }

    file.close();
}

void User::updateInfoThisUserInBinaryFile()
{
    vector<User *> users = User::loadInfoAllUser();
    int index;
    IsThereThisInfo<int, UserInfo>(id, UserInfo::Id, &index);
    if (index != -1)
    {
        users[index]->name = name;
        users[index]->username = username;
        users[index]->password = password;
        users[index]->phoneNumber = phoneNumber;
        users[index]->userAccount.setBalance(this->getBalance());

        User::updateAllUserInBinaryFile(users);
    }
}

bool User::isDuplicateUsername(string _username)
{
    return IsThereThisInfo<string>(_username, UserInfo::Username);
}

vector<string> User::createProfileStyle()
{
    short width, height;
    GetWidthHeight(&width, &height);

    string _id = to_string(id);
    string _name = name;
    string _type = enum_to_string<UserType>(type);
    string _username = username;
    string _password = password;
    string _phoneNumber = phoneNumber;
    string _balance = normalizeFloatString(to_string(userAccount.getBalance())) + " $";

    vector<string> info = {
        "ID           : " + _id,
        "Name         : " + _name,
        "Type         : " + _type,
        "Username     : " + _username,
        "Password     : " + _password,
        "Phone Number : " + _phoneNumber,
        "Balance      : " + _balance};

    int maxSize, profileTextSize;

    if (height <= 20)
    {
        maxSize = 18; // min size == 18  -->  "| Phone Number : aaa |"
        profileTextSize = 1;
    }
    else
    {
        maxSize = 21; // min size == 21  -->  "| Phone Number : aaaaaa |"
        profileTextSize = 2;
    }

    for (auto x : info)
    {
        if (x.size() > maxSize)
        {
            maxSize = x.size();
        }
    }

    vector<string> profileText = ProfileText(profileTextSize);
    vector<string> productStyle;
    string temp;

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // info text
    int profileTextLength = profileText[0].size();
    int numberOfSpace = (maxSize + 2 - profileTextLength) / 2;
    for (auto x : profileText)
    {
        temp += "|";
        for (int i = 0; i < numberOfSpace + (maxSize + 2 - profileTextLength) % 2; i++)
        {
            temp += " ";
        }
        temp += x;
        for (int i = 0; i < numberOfSpace; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // info
    int infoLength;
    for (auto x : info)
    {
        infoLength = x.size();
        temp += "| ";
        temp += x;
        for (int i = 0; i < maxSize - infoLength + 1; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    return productStyle;
}

void User::showProfile()
{
    vector<vector<string>> user = {this->createProfileStyle()};

    PrintBoxesInCenter("", "Press [Enter] to continue", user);
    cin.get();
}

//========================= Admin Class Functions

Admin::Admin(string _name, string _username, string _password, string _phoneNumber, UserType _type)
    : User(_name, _username, _password, _phoneNumber, _type) {}

// for load info
Admin::Admin(int _id, string _name, string _username, string _password, string _phoneNumber, UserType _type, float _balance)
    : User(_id, _name, _username, _password, _phoneNumber, _type, _balance) {}

void Admin::showProducts()
{
    vector<Pet *> pets = Pet::loadInfoAllPet();

    if (pets.size() != 0)
    {
        vector<vector<string>> products;

        for (auto x : pets)
        {
            products.push_back(x->createProductStyleForManaging());
        }

        ShowSomeBoxes(products);
    }
    else
    {
        cout << endl;
        cout << endl;
        PutMidlle(vector<string>{"-- There is no product --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
        cin.get();
    }
}

void Admin::acceptProduct()
{
    int selectedProduct;

    vector<Pet *> pets = Pet::loadInfoAllPet();
    vector<Pet *> tempPets;
    vector<vector<string>> products;
    while (1)
    {
        system("cls");

        for (auto x : pets)
        {
            if (x->getStatus() == false)
            {
                products.push_back(x->createProductStyleForManaging());
                tempPets.push_back(x);
            }
        }

        if (products.size() != 0)
        {
            selectedProduct = SelectBoxes(products, "Use [->] , [<-] key to navigate between items | Press [Enter] to choose the product and accept it | Press [Esc] to exit");

            if (selectedProduct != -1)
            {
                tempPets[selectedProduct]->setStatus(true);
                tempPets[selectedProduct]->updateInfoThisPetInBinaryFile();
                products.clear();
                tempPets.clear();
            }
            else
            {
                break;
            }
        }
        else
        {
            if (pets.size() == 0)
            {
                cout << endl;
                cout << endl;
                PutMidlle(vector<string>{"-- There is no product --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
                cin.get();
                break;
            }
            else
            {
                cout << endl;
                cout << endl;
                PutMidlle(vector<string>{"-- All products are accepted --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
                cin.get();
                break;
            }
        }
    }
}

void Admin::deleteProduct()
{
    int selectedProduct;
    vector<Pet *> pets;
    vector<Pet *> tempPets;
    vector<vector<string>> products;

    while (1)
    {
        pets = Pet::loadInfoAllPet();

        system("cls");

        for (auto x : pets)
        {
            products.push_back(x->createProductStyleForManaging());
            tempPets.push_back(x);
        }

        if (products.size() != 0)
        {
            selectedProduct = SelectBoxes(products, "Use [->] , [<-] key to navigate between items | Press [Enter] to choose the product and delete it | Press [Esc] to exit");

            if (selectedProduct != -1)
            {
                tempPets[selectedProduct]->deletePet();
                products.clear();
                tempPets.clear();
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
            break;
        }
    }
}

void Admin::discountOnProducts(vector<Pet *> pets, float discountAmount)
{
    for (auto x : pets)
    {
        x->setPrice((x->getPrice()) * (100 - discountAmount) / 100);
        x->updateInfoThisPetInBinaryFile();
    }
}

void Admin::allSalesHistory()
{
    vector<TransactionInfo> transactions = Account::loadAllTransaction();
    vector<TransactionInfo> tempTransactions;

    for (auto x : transactions)
    {
        if (x.type == TransactionType::Sell)
        {
            tempTransactions.push_back(x);
        }
    }

    if (tempTransactions.size() != 0)
    {
        int selectedTransaction = SelectTransaction(tempTransactions);

        if (selectedTransaction != -1)
        {
            system("cls");
            try
            {
                Pet *pet = Pet::loadInfoOnePet(tempTransactions[selectedTransaction].petId, 2);

                pet->showInfo();
            }
            catch (const runtime_error &e)
            {
                PutMidlle(vector<string>{"Pet has been deleted...", "", "Press [Enter] to continue"}, Horizontal | Vertical, CursorPlace::ZeroZero);
                cin.get();
            }
        }
    }
    else
    {
        cout << endl;
        cout << endl;
        PutMidlle(vector<string>{"-- There is no transaction --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
        cin.get();
    }
}

void Admin::manageUser(User *user, ManagingOption option)
{
    float amount;

    switch (option)
    {
    case ManagingOption::EditInfo:
        user->changeInfo();
        break;
    case ManagingOption::DeleteUser:
        user->deleteAccount();
        break;
    case ManagingOption::SendGift:
        userAccount.transfer(getId(), user->getId());
        break;

    default:
        break;
    }
}

//========================= Seller Class Functions

Seller::Seller(string _name, string _username, string _password, string _phoneNumber, UserType _type)
    : User(_name, _username, _password, _phoneNumber, _type) {}

// for load info
Seller::Seller(int _id, string _name, string _username, string _password, string _phoneNumber, UserType _type, float _balance)
    : User(_id, _name, _username, _password, _phoneNumber, _type, _balance) {}

void Seller::deleteAccount()
{
    vector<string> warnings{
        "",
        "** Warning **",
        "if you delete this account, this action cannot be undone",
        "by deleting this account, all information, transactions, balance and products will be lost",
        ""};

    PutMidlle(warnings, Horizontal, CursorPlace::BeginningNextLine);

    bool isAccepted = (SelectButton(vector<string>{"are you sure about that ?"}, vector<string>{"Accept", "Reject"}, Vertical, 2, 0, 1) == 0) ? true : false;

    if (isAccepted)
    {
        vector<User *> users = User::loadInfoAllUser();
        auto it = users.begin();
        for (; it != users.end(); it++)
        {
            if ((*it)->getId() == getId())
            {
                users.erase(it);
                break;
            }
        }
        User::updateAllUserInBinaryFile(users);

        vector<TransactionInfo> transactions = Account::loadAllTransaction();
        for (auto itTrans = transactions.begin(); itTrans != transactions.end(); itTrans++)
        {
            if ((*itTrans).userId == getId())
            {
                transactions.erase(itTrans);
                break;
            }
        }
        Account::updateAllTransactionInBinaryFile(transactions);

        vector<Pet *> pets = Pet::loadInfoAllPet();
        for (auto x : pets)
        {
            if (x->getSellerId() == getId())
            {
                x->deletePet();
            }
        }
    }
}

void Seller::addProduct()
{
    PrintVecStr(CreateTitle("Add Product Page"), Vertical);
    cout << "Enter the requested information:\n";
    cout << "       * Case sensitive *       \n\n";

    Pet *pet;

    string _sellerName = getName();
    int _sellerId = getId();
    bool _status = false;

    PetSpecies _species;
    _species = SelectOption<PetSpecies>("Which product would you like to add: ");

    string _name;
    cout << "Pet's Name : ";
    getline(cin, _name);

    int _age;
    cout << "Pet's Age [0-120]: ";
    cin >> _age;
    cin.get();

    float _price;
    cout << "Pet's Price: ";
    cin >> _price;
    cin.get();

    string _breed;
    cout << "Pet's Breed: ";
    getline(cin, _breed);

    Colors _color;
    _color = SelectOption<Colors>("Pet's Color: ");

    if (_species == PetSpecies::Bird)
    {
        float _flightHeight;
        cout << "How high can the bird Fly [0-100 meters]: ";
        cin >> _flightHeight;
        cin.get();

        VoiceType _sound;
        _sound = SelectOption<VoiceType>("Type of bird Sound: ");

        float _iq;
        cout << "IQ of bird [1-10]: ";
        cin >> _iq;
        cin.get();

        LoadingAnimation();

        pet = new Bird(_name, _age, _price, _breed, _color, _status, _sellerName, _sellerId, _flightHeight, _sound, _iq);
    }
    else if (_species == PetSpecies::Fish)
    {
        WaterType _water;
        _water = SelectOption<WaterType>("What kind of water do fish Need: ");

        float _aquariumSize;
        cout << "How many cubic meters should the aquarium have [0.001-10]: ";
        cin >> _aquariumSize;
        cin.get();

        SpeedUnitType _speedUnit;
        _speedUnit = SelectOption<SpeedUnitType>("First, choose the unit of swimming speed: ");

        float _swimmingSpeed;
        if (_speedUnit == SpeedUnitType::mps)
            cout << "How fast can it swim [0-50]: ";
        if (_speedUnit == SpeedUnitType::mpmin)
            cout << "How fast can it swim [0-3,000]: ";
        if (_speedUnit == SpeedUnitType::mph)
            cout << "How fast can it swim [0-180,000]: ";
        if (_speedUnit == SpeedUnitType::kmph)
            cout << "How fast can it swim [0-180]: ";
        cin >> _swimmingSpeed;
        cin.get();

        LoadingAnimation();

        pet = new Fish(_name, _age, _price, _breed, _color, _status, _sellerName, _sellerId, _water, _aquariumSize, _swimmingSpeed, _speedUnit);
    }
    else if (_species == PetSpecies::Pony)
    {
        SpeedUnitType _speedUnit;
        _speedUnit = SelectOption<SpeedUnitType>("First, select the running speed unit: ");

        float _runningSpeed;
        if (_speedUnit == SpeedUnitType::mps)
            cout << "How fast can it run [1-12.5]: ";
        if (_speedUnit == SpeedUnitType::mpmin)
            cout << "How fast can it run [60-750]: ";
        if (_speedUnit == SpeedUnitType::mph)
            cout << "How fast can it run [3,600-45,000]: ";
        if (_speedUnit == SpeedUnitType::kmph)
            cout << "How fast can it run [3.6-45]: ";
        cin >> _runningSpeed;
        cin.get();

        Colors _maneColor;
        _maneColor = SelectOption<Colors>("Choose the color of pony's mane: ");

        float _energyLevel;
        cout << "How much energy does it have [0-10]: ";
        cin >> _energyLevel;
        cin.get();

        LoadingAnimation();

        pet = new Pony(_name, _age, _price, _breed, _color, _status, _sellerName, _sellerId, _runningSpeed, _speedUnit, _maneColor, _energyLevel);
    }

    pet->saveInfoInBinaryFile();
}

void Seller::showProducts()
{
    vector<Pet *> pets = Pet::loadInfoAllPet();
    vector<vector<string>> products;

    if (pets.size() != 0)
    {
        for (auto x : pets)
        {
            if (x->getSellerId() == getId())
            {
                products.push_back(x->createProductStyleForManaging());
            }
        }

        if (products.size() != 0)
        {
            ShowSomeBoxes(products);
        }
        else
        {
            cout << endl;
            cout << endl;
            PutMidlle(vector<string>{"-- You have not added any products yet --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
            cin.get();
        }
    }
    else
    {
        cout << endl;
        cout << endl;
        PutMidlle(vector<string>{"-- There is no product --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
        cin.get();
    }
}

void Seller::editProduct()
{
    vector<Pet *> pets = Pet::loadInfoAllPet();
    vector<Pet *> tempPets;
    vector<vector<string>> products;

    if (pets.size() != 0)
    {
        for (auto x : pets)
        {
            if (x->getSellerId() == getId())
            {
                products.push_back(x->createProductStyleForManaging());
                tempPets.push_back(x);
            }
        }

        if (products.size() != 0)
        {
            int selectedProduct = SelectBoxes(products, "Use [->] , [<-] key to navigate between items | Press [Enter] to change the information of the selected item | Press [Esc] to exit");

            if (selectedProduct != -1)
            {
                system("cls");

                tempPets[selectedProduct]->changeInfo();
            }
        }
        else
        {
            cout << endl;
            cout << endl;
            PutMidlle(vector<string>{"-- You have not added any products yet --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
            cin.get();
        }
    }
    else
    {
        cout << endl;
        cout << endl;
        PutMidlle(vector<string>{"-- There is no product --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
        cin.get();
    }
}

void Seller::deleteProduct()
{
    int selectedProduct;

    vector<Pet *> pets;
    vector<Pet *> tempPets;
    vector<vector<string>> products;

    while (1)
    {
        pets = Pet::loadInfoAllPet();

        system("cls");

        for (auto x : pets)
        {
            if (x->getSellerId() == getId())
            {
                products.push_back(x->createProductStyleForManaging());
                tempPets.push_back(x);
            }
        }

        if (products.size() != 0)
        {

            selectedProduct = SelectBoxes(products, "Use [->] , [<-] key to navigate between pages | Press [Enter] to choose the product and delete it | Press [Esc] to exit");

            if (selectedProduct != -1)
            {
                tempPets[selectedProduct]->deletePet();
                products.clear();
                tempPets.clear();
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
            break;
        }
    }
}

void Seller::salesHistory()
{
    vector<TransactionInfo> transactions = Account::loadAllTransaction();
    vector<TransactionInfo> tempTransactions;

    for (auto x : transactions)
    {
        if (x.type == TransactionType::Sell)
        {
            if (x.sellerId == getId())
            {
                tempTransactions.push_back(x);
            }
        }
    }

    if (tempTransactions.size() != 0)
    {
        int selectedTransaction = SelectTransaction(tempTransactions);

        if (selectedTransaction != -1)
        {
            system("cls");
            try
            {
                Pet *pet = Pet::loadInfoOnePet(tempTransactions[selectedTransaction].petId, 2);

                pet->showInfo();
            }
            catch (const runtime_error &e)
            {
                PutMidlle(vector<string>{"Pet has been deleted...", "", "Press [Enter] to continue"}, Horizontal | Vertical, CursorPlace::ZeroZero);
                cin.get();
            }
        }
    }
    else
    {
        cout << endl;
        cout << endl;
        PutMidlle(vector<string>{"-- There is no transaction --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
        cin.get();
    }
}

//========================= Buyer Class Functions

Buyer::Buyer(string _name, string _username, string _password, string _phoneNumber, UserType _type)
    : User(_name, _username, _password, _phoneNumber, _type) {}

// for load info
Buyer::Buyer(int _id, string _name, string _username, string _password, string _phoneNumber, UserType _type, float _balance)
    : User(_id, _name, _username, _password, _phoneNumber, _type, _balance) {}

vector<Pet *> Buyer::searchProduct(SearchingItems whichGroup)
{
    vector<Pet *> allPets = Pet::loadInfoAllPet();
    vector<Pet *> targetPets;
    vector<Pet *> tempTargetPets;

    int tempKey = -1;

    string name = "-1";
    int minAge = -1;
    int maxAge = -1;
    float minPrice = -1;
    float maxPrice = -1;
    string breed = "-1";
    int indexOfColorSelected = -1;
    Colors color;
    string sellerName = "-1";
    float minRating = -1;
    float maxRating = -1;

    switch (whichGroup)
    {
    case SearchingItems::Bird:
    {
        float minFlightHeight = -1;
        float maxFlightHeight = -1;
        int indexOfSoundSelected = -1;
        VoiceType sound;
        float minIq = -1;
        float maxIq = -1;

        for (auto x : allPets)
        {
            if (x->getSpecies() == PetSpecies::Bird)
            {
                targetPets.push_back(x);
            }
        }

        string temp;
        int selectedInfo = 0;
        int key;

        PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
        PutMidlle(vector<string>{"Press [Tab] for start",
                                 "Press [Esc] for Exit",
                                 "** notice **",
                                 "Some search filters may have minimum and maximum values",
                                 "If you skip either the minimum or maximum values, the lowest or highest value will be used",
                                 "And if you enter a value outside the valid range, that value will be ignored"},
                  Horizontal, CursorPlace::BeginningNextLine);

        do
        {
            if (!(selectedInfo == 7 || selectedInfo == 13 || tempKey == 2 || tempKey == 3)) // 7 -> Color | 13 -> Sound | tempKey == 2 -> edit info again | tempKey == 3 -> reset info
            {
                key = getch();
                if (key == 0 || key == 224)
                {
                    key = getch();
                    continue;
                }
            }
            if (tempKey == 2 || tempKey == 3)
            {
                tempKey = -1;
            }

            if (key == '\t') // next
            {
                if (selectedInfo == 15)
                {
                    selectedInfo = 1;
                }
                else
                {
                    selectedInfo++;
                }

                if (selectedInfo == 1)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 1 && stof(temp) <= 10)
                        {
                            maxIq = stof(temp);
                        }
                        else
                        {
                            maxIq = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Name: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (name != "-1")
                    {
                        temp = name;
                        cout << temp;
                    }
                }
                else if (selectedInfo == 2)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = 120"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        name = temp;
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Age: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minAge != -1)
                    {
                        temp = to_string(minAge);
                        cout << temp;
                    }
                }
                else if (selectedInfo == 3)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            minAge = stoi(temp);
                        }
                        else
                        {
                            minAge = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Age: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxAge != -1)
                    {
                        temp = to_string(maxAge);
                        cout << temp;
                    }
                }
                else if (selectedInfo == 4)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = ..."},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            maxAge = stoi(temp);
                        }
                        else
                        {
                            maxAge = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Price: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minPrice != -1)
                    {
                        temp = normalizeFloatString(to_string(minPrice));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 5)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            minPrice = stof(temp);
                        }
                        else
                        {
                            minPrice = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Price: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxPrice != -1)
                    {
                        temp = normalizeFloatString(to_string(maxPrice));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 6)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            maxPrice = stof(temp);
                        }
                        else
                        {
                            maxPrice = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Breed: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (breed != "-1")
                    {
                        temp = breed;
                        cout << temp;
                    }
                }
                else if (selectedInfo == 7)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "Press [->] or [<-] for choosing or changing values"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        breed = temp;
                    }
                    temp.clear();
                    indexOfColorSelected = SelectOptionForSearching<Colors>("Color: ", indexOfColorSelected, key);
                }
                else if (selectedInfo == 8)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (indexOfColorSelected != -1)
                    {
                        color = static_cast<Colors>(indexOfColorSelected);
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Seller Name: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (sellerName != "-1")
                    {
                        temp = sellerName;
                        cout << temp;
                    }
                }
                else if (selectedInfo == 9)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = 5"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        sellerName = temp;
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Rating: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minRating != -1)
                    {
                        temp = normalizeFloatString(to_string(minRating));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 10)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            minRating = stof(temp);
                        }
                        else
                        {
                            minRating = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Rating: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxRating != -1)
                    {
                        temp = normalizeFloatString(to_string(maxRating));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 11)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = 100"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            maxRating = stof(temp);
                        }
                        else
                        {
                            maxRating = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Flight Height: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minFlightHeight != -1)
                    {
                        temp = normalizeFloatString(to_string(minFlightHeight));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 12)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 100)
                        {
                            minFlightHeight = stof(temp);
                        }
                        else
                        {
                            minFlightHeight = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Flight Height: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxFlightHeight != -1)
                    {
                        temp = normalizeFloatString(to_string(maxFlightHeight));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 13)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "Press [->] or [<-] for choosing or changing values"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 100)
                        {
                            maxFlightHeight = stof(temp);
                        }
                        else
                        {
                            maxFlightHeight = -1;
                        }
                    }
                    temp.clear();
                    indexOfSoundSelected = SelectOptionForSearching<VoiceType>("Sound: ", indexOfSoundSelected, key);
                }
                else if (selectedInfo == 14)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 1 | max = 10"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (indexOfSoundSelected != -1)
                    {
                        color = static_cast<Colors>(indexOfSoundSelected);
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum IQ: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minIq != -1)
                    {
                        temp = normalizeFloatString(to_string(minIq));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 15)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 1 && stof(temp) <= 10)
                        {
                            minIq = stof(temp);
                        }
                        else
                        {
                            minIq = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum IQ: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxIq != -1)
                    {
                        temp = normalizeFloatString(to_string(maxIq));
                        cout << temp;
                    }
                }
            }
            else if (key == ENTER_KEY && selectedInfo != 0) // starting searching
            {

                if (selectedInfo == 1)
                {
                    if (temp != "")
                    {
                        name = temp;
                    }
                }
                else if (selectedInfo == 2)
                {
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            minAge = stoi(temp);
                        }
                        else
                        {
                            minAge = -1;
                        }
                    }
                }
                else if (selectedInfo == 3)
                {
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            maxAge = stoi(temp);
                        }
                        else
                        {
                            maxAge = -1;
                        }
                    }
                }
                else if (selectedInfo == 4)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            minPrice = stof(temp);
                        }
                        else
                        {
                            minPrice = -1;
                        }
                    }
                }
                else if (selectedInfo == 5)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            maxPrice = stof(temp);
                        }
                        else
                        {
                            maxPrice = -1;
                        }
                    }
                }
                else if (selectedInfo == 6)
                {
                    if (temp != "")
                    {
                        breed = temp;
                    }
                }
                else if (selectedInfo == 7)
                {
                    if (indexOfColorSelected != -1)
                    {
                        color = static_cast<Colors>(indexOfColorSelected);
                    }
                }
                else if (selectedInfo == 8)
                {
                    if (temp != "")
                    {
                        sellerName = temp;
                    }
                }
                else if (selectedInfo == 9)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            minRating = stof(temp);
                        }
                        else
                        {
                            minRating = -1;
                        }
                    }
                }
                else if (selectedInfo == 10)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            maxRating = stof(temp);
                        }
                        else
                        {
                            maxRating = -1;
                        }
                    }
                }
                else if (selectedInfo == 11)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 100)
                        {
                            minFlightHeight = stof(temp);
                        }
                        else
                        {
                            minFlightHeight = -1;
                        }
                    }
                }
                else if (selectedInfo == 12)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 100)
                        {
                            maxFlightHeight = stof(temp);
                        }
                        else
                        {
                            maxFlightHeight = -1;
                        }
                    }
                }
                else if (selectedInfo == 13)
                {
                    if (indexOfSoundSelected != -1)
                    {
                        color = static_cast<Colors>(indexOfSoundSelected);
                    }
                }
                else if (selectedInfo == 14)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 1 && stof(temp) <= 10)
                        {
                            minIq = stof(temp);
                        }
                        else
                        {
                            minIq = -1;
                        }
                    }
                }
                else if (selectedInfo == 15)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 1 && stof(temp) <= 10)
                        {
                            maxIq = stof(temp);
                        }
                        else
                        {
                            maxIq = -1;
                        }
                    }
                }

                temp.clear();

                system("cls");
                PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                PutMidlle(vector<string>{"This information is going to be searched"}, Horizontal, CursorPlace::BeginningNextLine);
                cout << endl;

                if (name != "-1")
                {
                    string tempText = "Name: " + name;

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minAge != -1 || maxAge != -1)
                {
                    if (maxAge != -1 && (maxAge < minAge))
                    {
                        auto tempNum = maxAge;
                        maxAge = minAge;
                        minAge = tempNum;
                    }

                    string tempText = "Age: ";
                    tempText += (minAge == -1) ? to_string(0) : to_string(minAge);
                    tempText += "-";
                    tempText += (maxAge == -1) ? to_string(120) : to_string(maxAge);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minPrice != -1 || maxPrice != -1)
                {
                    if (maxPrice != -1 && (maxPrice < minPrice))
                    {
                        auto tempNum = maxPrice;
                        maxPrice = minPrice;
                        minPrice = tempNum;
                    }

                    string tempText = "Price: ";
                    tempText += (minPrice == -1) ? to_string(0) : normalizeFloatString(to_string(minPrice));
                    tempText += "-";
                    tempText += (maxPrice == -1) ? "..." : normalizeFloatString(to_string(maxPrice));

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (breed != "-1")
                {
                    string tempText = "Breed: " + breed;

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (indexOfColorSelected != -1)
                {
                    string tempText = "Color: " + enum_to_string<Colors>(color);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (sellerName != "-1")
                {
                    string tempText = "Seller Name: " + sellerName;

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minRating != -1 || maxRating != -1)
                {
                    if (maxRating != -1 && (maxRating < minRating))
                    {
                        auto tempNum = maxRating;
                        maxRating = minRating;
                        minRating = tempNum;
                    }

                    string tempText = "Rating: ";
                    tempText += (minRating == -1) ? to_string(0) : normalizeFloatString(to_string(minRating));
                    tempText += "-";
                    tempText += (maxRating == -1) ? to_string(5) : normalizeFloatString(to_string(maxRating));

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minFlightHeight != -1 || maxFlightHeight != -1)
                {
                    if (maxFlightHeight != -1 && (maxFlightHeight < minFlightHeight))
                    {
                        auto tempNum = maxFlightHeight;
                        maxFlightHeight = minFlightHeight;
                        minFlightHeight = tempNum;
                    }

                    string tempText = "Flight Height: ";
                    tempText += (minFlightHeight == -1) ? to_string(0) : normalizeFloatString(to_string(minFlightHeight));
                    tempText += "-";
                    tempText += (maxFlightHeight == -1) ? to_string(100) : normalizeFloatString(to_string(maxFlightHeight));

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (indexOfSoundSelected != -1)
                {
                    string tempText = "Sound: " + enum_to_string<VoiceType>(sound);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minIq != -1 || maxIq != -1)
                {
                    if (maxIq != -1 && (maxIq < minIq))
                    {
                        auto tempNum = maxIq;
                        maxIq = minIq;
                        minIq = tempNum;
                    }

                    string tempText = "Iq: ";
                    tempText += (minIq == -1) ? to_string(1) : normalizeFloatString(to_string(minIq));
                    tempText += "-";
                    tempText += (maxIq == -1) ? to_string(10) : normalizeFloatString(to_string(maxIq));

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }

                cout << endl;
                tempKey = SelectButton(vector<string>{"What do you want to do ?", "choose your option with [->] or [<-] key and press [Enter]"},
                                       vector<string>{"Search", "Exit", "Edit", "Reset All"}, Horizontal, 2, 2, 2);

                if (tempKey == 0)
                {
                    key = ENTER_KEY;
                    break;
                }
                else if (tempKey == 1)
                {
                    key = ESC_KEY;
                    break;
                }
                else if (tempKey == 2)
                {
                    selectedInfo = 0;
                    key = '\t';
                }
                else if (tempKey == 3)
                {
                    name = "-1";
                    minAge = -1;
                    maxAge = -1;
                    minPrice = -1;
                    maxPrice = -1;
                    breed = "-1";
                    indexOfColorSelected = -1;
                    sellerName = "-1";
                    minRating = -1;
                    maxRating = -1;
                    minFlightHeight = -1;
                    maxFlightHeight = -1;
                    indexOfSoundSelected = -1;
                    minIq = -1;
                    maxIq = -1;

                    selectedInfo = 0;
                    key = '\t';
                }
            }
            else if (key == ESC_KEY) // exit
            {
                break;
            }
            else if (selectedInfo != 0 &&
                     ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || key == '\b' ||
                      (key >= '0' && key <= '9') || key == ' ' || key == '.')) // write and save text
            {
                if (selectedInfo != 7 && selectedInfo != 13)
                {
                    if (key == '\b')
                    {
                        if (!temp.empty())
                        {
                            cout << "\b \b";
                            temp.pop_back();
                        }
                    }
                    else
                    {
                        if (key != ' ')
                        {
                            if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z'))
                            {
                                if (selectedInfo == 1 || selectedInfo == 6 || selectedInfo == 8) // 1 -> name | 6 -> breed | 8 -> sellerName
                                {
                                    cout << static_cast<char>(key);
                                    temp += static_cast<char>(key);
                                }
                            }
                            else
                            {
                                if (key == '.')
                                {
                                    if (selectedInfo == 4 || selectedInfo == 5 || selectedInfo == 9 || selectedInfo == 10 ||
                                        selectedInfo == 11 || selectedInfo == 12 || selectedInfo == 14 || selectedInfo == 15) // 4,5 -> price | 9,10 -> rating | 11,12 -> flightHeight | 14,15 -> iq
                                    {
                                        cout << static_cast<char>(key);
                                        temp += static_cast<char>(key);
                                    }
                                }
                                else
                                {
                                    cout << static_cast<char>(key);
                                    temp += static_cast<char>(key);
                                }
                            }
                        }
                        else if (key == ' ')
                        {
                            if (selectedInfo == 1 || selectedInfo == 6 || selectedInfo == 8) // 1 -> name | 6 -> breed | 8 -> sellerName
                            {
                                cout << static_cast<char>(key);
                                temp += static_cast<char>(key);
                            }
                        }
                    }
                }
            }
        } while (1);

        if (key == ENTER_KEY) // searching
        {
            if (name != "-1")
            {
                for (Pet *x : targetPets)
                {
                    if (x->getName().find(name) != string::npos)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minAge != -1 || maxAge != -1)
            {
                minAge = (minAge == -1) ? 0 : minAge;
                maxAge = (maxAge == -1) ? 120 : maxAge;

                for (Pet *x : targetPets)
                {
                    if (x->getAge() >= minAge && x->getAge() <= maxAge)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minPrice != -1 || maxPrice != -1)
            {
                minPrice = (minPrice == -1) ? 0 : minPrice;

                for (Pet *x : targetPets)
                {
                    if (maxPrice == -1)
                    {
                        if (x->getPrice() >= minPrice)
                        {
                            tempTargetPets.push_back(x);
                        }
                    }
                    else
                    {
                        if (x->getPrice() >= minPrice && x->getPrice() <= maxPrice)
                        {
                            tempTargetPets.push_back(x);
                        }
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (breed != "-1")
            {
                for (Pet *x : targetPets)
                {
                    if (x->getBreed().find(breed) != string::npos)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (indexOfColorSelected != -1)
            {
                for (Pet *x : targetPets)
                {
                    if (x->getColor() == color)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (sellerName != "-1")
            {
                for (Pet *x : targetPets)
                {
                    if (x->getSellerName().find(sellerName) != string::npos)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minRating != -1 || maxRating != -1)
            {
                minRating = (minRating == -1) ? 0 : minRating;
                maxRating = (maxRating == -1) ? 5 : maxRating;

                for (Pet *x : targetPets)
                {
                    if (x->getRating() >= minRating && x->getRating() <= maxRating)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minFlightHeight != -1 || maxFlightHeight != -1)
            {
                minFlightHeight = (minFlightHeight == -1) ? 0 : minFlightHeight;
                maxFlightHeight = (maxFlightHeight == -1) ? 100 : maxFlightHeight;

                for (Pet *x : targetPets)
                {
                    Bird *tempBird = dynamic_cast<Bird *>(x);
                    if (tempBird->getFlightHeight() >= minFlightHeight && tempBird->getFlightHeight() <= maxFlightHeight)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (indexOfSoundSelected != -1)
            {
                for (Pet *x : targetPets)
                {
                    Bird *tempBird = dynamic_cast<Bird *>(x);
                    if (tempBird->getSound() == sound)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minIq != -1 || maxIq != -1)
            {
                minIq = (minIq == -1) ? 1 : minIq;
                maxIq = (maxIq == -1) ? 10 : maxIq;

                for (Pet *x : targetPets)
                {
                    Bird *tempBird = dynamic_cast<Bird *>(x);
                    if (tempBird->getIq() >= minIq && tempBird->getIq() <= maxIq)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
        }
        else if (key == ESC_KEY)
        {
            targetPets.clear();
        }

        break;
    }
    case SearchingItems::Fish:
    {
        int indexOfWaterSelected = -1;
        WaterType water;
        float minAquariumSize = -1;
        float maxAquariumSize = -1;
        float minSwimmingSpeed = -1;
        float maxSwimmingSpeed = -1;
        int indexOfSpeedUnitSelected = -1;
        SpeedUnitType speedUnit;

        for (auto x : allPets)
        {
            if (x->getSpecies() == PetSpecies::Fish)
            {
                targetPets.push_back(x);
            }
        }

        string temp;
        int selectedInfo = 0;
        int key;

        PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
        PutMidlle(vector<string>{"Press [Tab] for start",
                                 "Press [Esc] for Exit",
                                 "** notice **",
                                 "Some search filters may have minimum and maximum values",
                                 "If you skip either the minimum or maximum values, the lowest or highest value will be used",
                                 "And if you enter a value outside the valid range, that value will be ignored"},
                  Horizontal, CursorPlace::BeginningNextLine);

        do
        {
            if (!(selectedInfo == 7 || selectedInfo == 11 || selectedInfo == 14 || tempKey == 2 || tempKey == 3)) // 7 -> Color | 11 -> Water | 14 -> SpeedUnit | tempKey == 2 -> edit info again | tempKey == 3 -> reset info
            {
                key = getch();
                if (key == 0 || key == 224)
                {
                    key = getch();
                    continue;
                }
            }
            if (tempKey == 2 || tempKey == 3)
            {
                tempKey = -1;
            }

            if (key == '\t') // next
            {
                if (selectedInfo == 16)
                {
                    selectedInfo = 1;
                }
                else
                {
                    selectedInfo++;
                    if (selectedInfo == 15 && indexOfSpeedUnitSelected == -1)
                    {
                        selectedInfo = 1;
                    }
                }

                if (selectedInfo == 1)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (speedUnit == SpeedUnitType::mps)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 50)
                            {
                                maxSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                maxSwimmingSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mpmin)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 3000)
                            {
                                maxSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                maxSwimmingSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180000)
                            {
                                maxSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                maxSwimmingSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::kmph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180)
                            {
                                maxSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                maxSwimmingSpeed = -1;
                            }
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Name: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (name != "-1")
                    {
                        temp = name;
                        cout << temp;
                    }
                }
                else if (selectedInfo == 2)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = 120"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        name = temp;
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Age: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minAge != -1)
                    {
                        temp = to_string(minAge);
                        cout << temp;
                    }
                }
                else if (selectedInfo == 3)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            minAge = stoi(temp);
                        }
                        else
                        {
                            minAge = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Age: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxAge != -1)
                    {
                        temp = to_string(maxAge);
                        cout << temp;
                    }
                }
                else if (selectedInfo == 4)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = ..."},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            maxAge = stoi(temp);
                        }
                        else
                        {
                            maxAge = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Price: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minPrice != -1)
                    {
                        temp = normalizeFloatString(to_string(minPrice));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 5)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            minPrice = stof(temp);
                        }
                        else
                        {
                            minPrice = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Price: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxPrice != -1)
                    {
                        temp = normalizeFloatString(to_string(maxPrice));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 6)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            maxPrice = stof(temp);
                        }
                        else
                        {
                            maxPrice = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Breed: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (breed != "-1")
                    {
                        temp = breed;
                        cout << temp;
                    }
                }
                else if (selectedInfo == 7)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "Press [->] or [<-] for choosing or changing values"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        breed = temp;
                    }
                    temp.clear();
                    indexOfColorSelected = SelectOptionForSearching<Colors>("Color: ", indexOfColorSelected, key);
                }
                else if (selectedInfo == 8)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (indexOfColorSelected != -1)
                    {
                        color = static_cast<Colors>(indexOfColorSelected);
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Seller Name: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (sellerName != "-1")
                    {
                        temp = sellerName;
                        cout << temp;
                    }
                }
                else if (selectedInfo == 9)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = 5"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        sellerName = temp;
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Rating: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minRating != -1)
                    {
                        temp = normalizeFloatString(to_string(minRating));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 10)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            minRating = stof(temp);
                        }
                        else
                        {
                            minRating = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Rating: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxRating != -1)
                    {
                        temp = normalizeFloatString(to_string(maxRating));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 11)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "Press [->] or [<-] for choosing or changing values"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            maxRating = stof(temp);
                        }
                        else
                        {
                            maxRating = -1;
                        }
                    }
                    temp.clear();
                    indexOfWaterSelected = SelectOptionForSearching<WaterType>("Water: ", indexOfWaterSelected, key);
                }
                else if (selectedInfo == 12)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0.001 | max = 10"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (indexOfWaterSelected != -1)
                    {
                        water = static_cast<WaterType>(indexOfWaterSelected);
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Aquarium Size: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minAquariumSize != -1)
                    {
                        temp = normalizeFloatString(to_string(minAquariumSize));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 13)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0.001 && stof(temp) <= 10)
                        {
                            minAquariumSize = stof(temp);
                        }
                        else
                        {
                            minAquariumSize = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Aquarium Size: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxAquariumSize != -1)
                    {
                        temp = normalizeFloatString(to_string(maxAquariumSize));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 14)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "Press [->] or [<-] for choosing or changing values",
                                             "",
                                             "min & max = [0-50] m/s",
                                             "min & max = [0-3,000] m/min",
                                             "min & max = [0-180,000] m/h",
                                             "min & max = [0-180] km/h"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0.001 && stof(temp) <= 10)
                        {
                            maxAquariumSize = stof(temp);
                        }
                        else
                        {
                            maxAquariumSize = -1;
                        }
                    }
                    temp.clear();
                    indexOfSpeedUnitSelected = SelectOptionForSearching<SpeedUnitType>("Unit Of Swimming Speed: ", indexOfSpeedUnitSelected, key);
                }
                else if (selectedInfo == 15)
                {
                    cout << endl;
                    if (indexOfSpeedUnitSelected != -1)
                    {
                        speedUnit = static_cast<SpeedUnitType>(indexOfSpeedUnitSelected);
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Swimming Speed: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minSwimmingSpeed != -1)
                    {
                        temp = normalizeFloatString(to_string(minSwimmingSpeed));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 16)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (speedUnit == SpeedUnitType::mps)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 50)
                            {
                                minSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                minSwimmingSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mpmin)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 3000)
                            {
                                minSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                minSwimmingSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180000)
                            {
                                minSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                minSwimmingSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::kmph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180)
                            {
                                minSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                minSwimmingSpeed = -1;
                            }
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Swimming Speed: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxSwimmingSpeed != -1)
                    {
                        temp = normalizeFloatString(to_string(maxSwimmingSpeed));
                        cout << temp;
                    }
                }
            }
            else if (key == ENTER_KEY && selectedInfo != 0) // starting searching
            {

                if (selectedInfo == 1)
                {
                    if (temp != "")
                    {
                        name = temp;
                    }
                }
                else if (selectedInfo == 2)
                {
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            minAge = stoi(temp);
                        }
                        else
                        {
                            minAge = -1;
                        }
                    }
                }
                else if (selectedInfo == 3)
                {
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            maxAge = stoi(temp);
                        }
                        else
                        {
                            maxAge = -1;
                        }
                    }
                }
                else if (selectedInfo == 4)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            minPrice = stof(temp);
                        }
                        else
                        {
                            minPrice = -1;
                        }
                    }
                }
                else if (selectedInfo == 5)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            maxPrice = stof(temp);
                        }
                        else
                        {
                            maxPrice = -1;
                        }
                    }
                }
                else if (selectedInfo == 6)
                {
                    if (temp != "")
                    {
                        breed = temp;
                    }
                }
                else if (selectedInfo == 7)
                {
                    if (indexOfColorSelected != -1)
                    {
                        color = static_cast<Colors>(indexOfColorSelected);
                    }
                }
                else if (selectedInfo == 8)
                {
                    if (temp != "")
                    {
                        sellerName = temp;
                    }
                }
                else if (selectedInfo == 9)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            minRating = stof(temp);
                        }
                        else
                        {
                            minRating = -1;
                        }
                    }
                }
                else if (selectedInfo == 10)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            maxRating = stof(temp);
                        }
                        else
                        {
                            maxRating = -1;
                        }
                    }
                }
                else if (selectedInfo == 11)
                {
                    if (indexOfWaterSelected != -1)
                    {
                        water = static_cast<WaterType>(indexOfWaterSelected);
                    }
                }
                else if (selectedInfo == 12)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0.001 && stof(temp) <= 10)
                        {
                            minAquariumSize = stof(temp);
                        }
                        else
                        {
                            minAquariumSize = -1;
                        }
                    }
                }
                else if (selectedInfo == 13)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0.001 && stof(temp) <= 10)
                        {
                            maxAquariumSize = stof(temp);
                        }
                        else
                        {
                            maxAquariumSize = -1;
                        }
                    }
                }
                else if (selectedInfo == 14)
                {
                    if (indexOfSpeedUnitSelected != -1)
                    {
                        speedUnit = static_cast<SpeedUnitType>(indexOfSpeedUnitSelected);
                    }
                }
                else if (selectedInfo == 15)
                {
                    if (temp != "")
                    {
                        if (speedUnit == SpeedUnitType::mps)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 50)
                            {
                                minSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                minSwimmingSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mpmin)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 3000)
                            {
                                minSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                minSwimmingSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180000)
                            {
                                minSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                minSwimmingSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::kmph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180)
                            {
                                minSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                minSwimmingSpeed = -1;
                            }
                        }
                    }
                }
                else if (selectedInfo == 16)
                {
                    if (temp != "")
                    {
                        if (speedUnit == SpeedUnitType::mps)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 50)
                            {
                                maxSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                maxSwimmingSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mpmin)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 3000)
                            {
                                maxSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                maxSwimmingSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180000)
                            {
                                maxSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                maxSwimmingSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::kmph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180)
                            {
                                maxSwimmingSpeed = stof(temp);
                            }
                            else
                            {
                                maxSwimmingSpeed = -1;
                            }
                        }
                    }
                }

                temp.clear();

                system("cls");
                PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                PutMidlle(vector<string>{"This information is going to be searched"}, Horizontal, CursorPlace::BeginningNextLine);
                cout << endl;

                if (name != "-1")
                {
                    string tempText = "Name: " + name;

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minAge != -1 || maxAge != -1)
                {
                    if (maxAge != -1 && (maxAge < minAge))
                    {
                        auto tempNum = maxAge;
                        maxAge = minAge;
                        minAge = tempNum;
                    }

                    string tempText = "Age: ";
                    tempText += (minAge == -1) ? to_string(0) : to_string(minAge);
                    tempText += "-";
                    tempText += (maxAge == -1) ? to_string(120) : to_string(maxAge);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minPrice != -1 || maxPrice != -1)
                {
                    if (maxPrice != -1 && (maxPrice < minPrice))
                    {
                        auto tempNum = maxPrice;
                        maxPrice = minPrice;
                        minPrice = tempNum;
                    }

                    string tempText = "Price: ";
                    tempText += (minPrice == -1) ? to_string(0) : normalizeFloatString(to_string(minPrice));
                    tempText += "-";
                    tempText += (maxPrice == -1) ? "..." : normalizeFloatString(to_string(maxPrice));

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (breed != "-1")
                {
                    string tempText = "Breed: " + breed;

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (indexOfColorSelected != -1)
                {
                    string tempText = "Color: " + enum_to_string<Colors>(color);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (sellerName != "-1")
                {
                    string tempText = "Seller Name: " + sellerName;

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minRating != -1 || maxRating != -1)
                {
                    if (maxRating != -1 && (maxRating < minRating))
                    {
                        auto tempNum = maxRating;
                        maxRating = minRating;
                        minRating = tempNum;
                    }

                    string tempText = "Rating: ";
                    tempText += (minRating == -1) ? to_string(0) : normalizeFloatString(to_string(minRating));
                    tempText += "-";
                    tempText += (maxRating == -1) ? to_string(5) : normalizeFloatString(to_string(maxRating));

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (indexOfWaterSelected != -1)
                {
                    string tempText = "Water: " + enum_to_string<WaterType>(water);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minAquariumSize != -1 || maxAquariumSize != -1)
                {
                    if (maxAquariumSize != -1 && (maxAquariumSize < minAquariumSize))
                    {
                        auto tempNum = maxAquariumSize;
                        maxAquariumSize = minAquariumSize;
                        minAquariumSize = tempNum;
                    }

                    string tempText = "Aquarium Size: ";
                    tempText += (minAquariumSize == -1) ? normalizeFloatString(to_string(0.001)) : normalizeFloatString(to_string(minAquariumSize));
                    tempText += "-";
                    tempText += (maxAquariumSize == -1) ? to_string(10) : normalizeFloatString(to_string(maxAquariumSize));

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (indexOfSpeedUnitSelected != -1)
                {
                    string tempText = "Unit Of Swimming Speed: " + enum_to_string<SpeedUnitType>(speedUnit);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minSwimmingSpeed != -1 || maxSwimmingSpeed != -1)
                {
                    if (maxSwimmingSpeed != -1 && (maxSwimmingSpeed < minSwimmingSpeed))
                    {
                        auto tempNum = maxSwimmingSpeed;
                        maxSwimmingSpeed = minSwimmingSpeed;
                        minSwimmingSpeed = tempNum;
                    }

                    string tempText = "Swimming Speed: ";
                    tempText += (minSwimmingSpeed == -1) ? to_string(0) : normalizeFloatString(to_string(minSwimmingSpeed));
                    tempText += "-";
                    if (speedUnit == SpeedUnitType::mps)
                    {
                        tempText += (maxSwimmingSpeed == -1) ? to_string(50) : normalizeFloatString(to_string(maxSwimmingSpeed));
                    }
                    else if (speedUnit == SpeedUnitType::mpmin)
                    {
                        tempText += (maxSwimmingSpeed == -1) ? to_string(3000) : normalizeFloatString(to_string(maxSwimmingSpeed));
                    }
                    else if (speedUnit == SpeedUnitType::mph)
                    {
                        tempText += (maxSwimmingSpeed == -1) ? to_string(180000) : normalizeFloatString(to_string(maxSwimmingSpeed));
                    }
                    else if (speedUnit == SpeedUnitType::kmph)
                    {
                        tempText += (maxSwimmingSpeed == -1) ? to_string(180) : normalizeFloatString(to_string(maxSwimmingSpeed));
                    }

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }

                cout << endl;
                tempKey = SelectButton(vector<string>{"What do you want to do ?", "choose your option with [->] or [<-] key and press [Enter]"},
                                       vector<string>{"Search", "Exit", "Edit", "Reset All"}, Horizontal, 2, 2, 2);

                if (tempKey == 0)
                {
                    key = ENTER_KEY;
                    break;
                }
                else if (tempKey == 1)
                {
                    key = ESC_KEY;
                    break;
                }
                else if (tempKey == 2)
                {
                    selectedInfo = 0;
                    key = '\t';
                }
                else if (tempKey == 3)
                {
                    name = "-1";
                    minAge = -1;
                    maxAge = -1;
                    minPrice = -1;
                    maxPrice = -1;
                    breed = "-1";
                    indexOfColorSelected = -1;
                    sellerName = "-1";
                    minRating = -1;
                    maxRating = -1;
                    indexOfWaterSelected = -1;
                    minAquariumSize = -1;
                    maxAquariumSize = -1;
                    minSwimmingSpeed = -1;
                    maxSwimmingSpeed = -1;
                    indexOfSpeedUnitSelected = -1;

                    selectedInfo = 0;
                    key = '\t';
                }
            }
            else if (key == ESC_KEY) // exit
            {
                break;
            }
            else if (selectedInfo != 0 &&
                     ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || key == '\b' ||
                      (key >= '0' && key <= '9') || key == ' ' || key == '.')) // write and save text
            {
                if (selectedInfo != 7 && selectedInfo != 11 && selectedInfo != 14)
                {
                    if (key == '\b')
                    {
                        if (!temp.empty())
                        {
                            cout << "\b \b";
                            temp.pop_back();
                        }
                    }
                    else
                    {
                        if (key != ' ')
                        {
                            if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z'))
                            {
                                if (selectedInfo == 1 || selectedInfo == 6 || selectedInfo == 8) // 1 -> name | 6 -> breed | 8 -> sellerName
                                {
                                    cout << static_cast<char>(key);
                                    temp += static_cast<char>(key);
                                }
                            }
                            else
                            {
                                if (key == '.')
                                {
                                    if (selectedInfo == 4 || selectedInfo == 5 || selectedInfo == 9 || selectedInfo == 10 ||
                                        selectedInfo == 12 || selectedInfo == 13 || selectedInfo == 15 || selectedInfo == 16) // 4,5 -> price | 9,10 -> rating | 12,13 -> aquariumSize | 15,16 -> swimmingSpeed
                                    {
                                        cout << static_cast<char>(key);
                                        temp += static_cast<char>(key);
                                    }
                                }
                                else
                                {
                                    cout << static_cast<char>(key);
                                    temp += static_cast<char>(key);
                                }
                            }
                        }
                        else if (key == ' ')
                        {
                            if (selectedInfo == 1 || selectedInfo == 6 || selectedInfo == 8) // 1 -> name | 6 -> breed | 8 -> sellerName
                            {
                                cout << static_cast<char>(key);
                                temp += static_cast<char>(key);
                            }
                        }
                    }
                }
            }
        } while (1);

        if (key == ENTER_KEY) // searching
        {
            if (name != "-1")
            {
                for (Pet *x : targetPets)
                {
                    if (x->getName().find(name) != string::npos)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minAge != -1 || maxAge != -1)
            {
                minAge = (minAge == -1) ? 0 : minAge;
                maxAge = (maxAge == -1) ? 120 : maxAge;

                for (Pet *x : targetPets)
                {
                    if (x->getAge() >= minAge && x->getAge() <= maxAge)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minPrice != -1 || maxPrice != -1)
            {
                minPrice = (minPrice == -1) ? 0 : minPrice;

                for (Pet *x : targetPets)
                {
                    if (maxPrice == -1)
                    {
                        if (x->getPrice() >= minPrice)
                        {
                            tempTargetPets.push_back(x);
                        }
                    }
                    else
                    {
                        if (x->getPrice() >= minPrice && x->getPrice() <= maxPrice)
                        {
                            tempTargetPets.push_back(x);
                        }
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (breed != "-1")
            {
                for (Pet *x : targetPets)
                {
                    if (x->getBreed().find(breed) != string::npos)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (indexOfColorSelected != -1)
            {
                for (Pet *x : targetPets)
                {
                    if (x->getColor() == color)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (sellerName != "-1")
            {
                for (Pet *x : targetPets)
                {
                    if (x->getSellerName().find(sellerName) != string::npos)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minRating != -1 || maxRating != -1)
            {
                minRating = (minRating == -1) ? 0 : minRating;
                maxRating = (maxRating == -1) ? 5 : maxRating;

                for (Pet *x : targetPets)
                {
                    if (x->getRating() >= minRating && x->getRating() <= maxRating)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (indexOfWaterSelected != -1)
            {
                for (Pet *x : targetPets)
                {
                    Fish *tempFish = dynamic_cast<Fish *>(x);
                    if (tempFish->getWater() == water)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minAquariumSize != -1 || maxAquariumSize != -1)
            {
                minAquariumSize = (minAquariumSize == -1) ? 0.001 : minAquariumSize;
                maxAquariumSize = (maxAquariumSize == -1) ? 10 : maxAquariumSize;

                for (Pet *x : targetPets)
                {
                    Fish *tempFish = dynamic_cast<Fish *>(x);
                    if (tempFish->getAquariumSize() >= minAquariumSize && tempFish->getAquariumSize() <= maxAquariumSize)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (indexOfSpeedUnitSelected != -1)
            {
                for (Pet *x : targetPets)
                {
                    Fish *tempFish = dynamic_cast<Fish *>(x);
                    if (tempFish->getUnitOfSpeed() == speedUnit)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minSwimmingSpeed != -1 || maxSwimmingSpeed != -1)
            {
                minSwimmingSpeed = (minSwimmingSpeed == -1) ? 0 : minSwimmingSpeed;
                if (speedUnit == SpeedUnitType::mps)
                {
                    maxSwimmingSpeed = (maxSwimmingSpeed == -1) ? 50 : maxSwimmingSpeed;
                }
                else if (speedUnit == SpeedUnitType::mpmin)
                {
                    maxSwimmingSpeed = (maxSwimmingSpeed == -1) ? 3000 : maxSwimmingSpeed;
                }
                else if (speedUnit == SpeedUnitType::mph)
                {
                    maxSwimmingSpeed = (maxSwimmingSpeed == -1) ? 180000 : maxSwimmingSpeed;
                }
                else if (speedUnit == SpeedUnitType::kmph)
                {
                    maxSwimmingSpeed = (maxSwimmingSpeed == -1) ? 180 : maxSwimmingSpeed;
                }

                for (Pet *x : targetPets)
                {
                    Fish *tempFish = dynamic_cast<Fish *>(x);
                    if (tempFish->getSwimmingSpeed() >= minSwimmingSpeed && tempFish->getSwimmingSpeed() <= maxSwimmingSpeed)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
        }
        else if (key == ESC_KEY)
        {
            targetPets.clear();
        }
        break;
    }
    case SearchingItems::Pony:
    {
        float minRunningSpeed = -1;
        float maxRunningSpeed = -1;
        int indexOfSpeedUnitSelected = -1;
        SpeedUnitType speedUnit;
        int indexOfManeColor = -1;
        Colors maneColor;
        float minEnergyLevel = -1;
        float maxEnergyLevel = -1;

        for (auto x : allPets)
        {
            if (x->getSpecies() == PetSpecies::Pony)
            {
                targetPets.push_back(x);
            }
        }

        string temp;
        int selectedInfo = 0;
        int key;

        PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
        PutMidlle(vector<string>{"Press [Tab] for start",
                                 "Press [Esc] for Exit",
                                 "** notice **",
                                 "Some search filters may have minimum and maximum values",
                                 "If you skip either the minimum or maximum values, the lowest or highest value will be used",
                                 "And if you enter a value outside the valid range, that value will be ignored"},
                  Horizontal, CursorPlace::BeginningNextLine);

        do
        {
            if (!(selectedInfo == 7 || selectedInfo == 11 || selectedInfo == 14 || tempKey == 2 || tempKey == 3)) // 7 -> Color | 11 -> SpeedUnit | 14 -> ManeColor | tempKey == 2 -> edit info again | tempKey == 3 -> reset info
            {
                key = getch();
                if (key == 0 || key == 224)
                {
                    key = getch();
                    continue;
                }
            }
            if (tempKey == 2 || tempKey == 3)
            {
                tempKey = -1;
            }

            if (key == '\t') // next
            {
                if (selectedInfo == 16)
                {
                    selectedInfo = 1;
                }
                else
                {
                    selectedInfo++;
                    if (selectedInfo == 12 && indexOfSpeedUnitSelected == -1)
                    {
                        selectedInfo = 14;
                    }
                }

                if (selectedInfo == 1)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 10)
                        {
                            maxEnergyLevel = stof(temp);
                        }
                        else
                        {
                            maxEnergyLevel = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Name: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (name != "-1")
                    {
                        temp = name;
                        cout << temp;
                    }
                }
                else if (selectedInfo == 2)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = 120"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        name = temp;
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Age: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minAge != -1)
                    {
                        temp = to_string(minAge);
                        cout << temp;
                    }
                }
                else if (selectedInfo == 3)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            minAge = stoi(temp);
                        }
                        else
                        {
                            minAge = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Age: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxAge != -1)
                    {
                        temp = to_string(maxAge);
                        cout << temp;
                    }
                }
                else if (selectedInfo == 4)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = ..."},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            maxAge = stoi(temp);
                        }
                        else
                        {
                            maxAge = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Price: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minPrice != -1)
                    {
                        temp = normalizeFloatString(to_string(minPrice));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 5)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            minPrice = stof(temp);
                        }
                        else
                        {
                            minPrice = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Price: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxPrice != -1)
                    {
                        temp = normalizeFloatString(to_string(maxPrice));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 6)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            maxPrice = stof(temp);
                        }
                        else
                        {
                            maxPrice = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Breed: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (breed != "-1")
                    {
                        temp = breed;
                        cout << temp;
                    }
                }
                else if (selectedInfo == 7)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "Press [->] or [<-] for choosing or changing values"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        breed = temp;
                    }
                    temp.clear();
                    indexOfColorSelected = SelectOptionForSearching<Colors>("Color: ", indexOfColorSelected, key);
                }
                else if (selectedInfo == 8)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (indexOfColorSelected != -1)
                    {
                        color = static_cast<Colors>(indexOfColorSelected);
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Seller Name: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (sellerName != "-1")
                    {
                        temp = sellerName;
                        cout << temp;
                    }
                }
                else if (selectedInfo == 9)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = 5"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        sellerName = temp;
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Rating: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minRating != -1)
                    {
                        temp = normalizeFloatString(to_string(minRating));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 10)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            minRating = stof(temp);
                        }
                        else
                        {
                            minRating = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Rating: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxRating != -1)
                    {
                        temp = normalizeFloatString(to_string(maxRating));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 11)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "Press [->] or [<-] for choosing or changing values",
                                             "",
                                             "min & max = [0-50] m/s",
                                             "min & max = [0-3,000] m/min",
                                             "min & max = [0-180,000] m/h",
                                             "min & max = [0-180] km/h"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            maxRating = stof(temp);
                        }
                        else
                        {
                            maxRating = -1;
                        }
                    }
                    temp.clear();
                    indexOfSpeedUnitSelected = SelectOptionForSearching<SpeedUnitType>("Unit Of Running Speed: ", indexOfSpeedUnitSelected, key);
                }
                else if (selectedInfo == 12)
                {
                    cout << endl;
                    if (indexOfSpeedUnitSelected != -1)
                    {
                        speedUnit = static_cast<SpeedUnitType>(indexOfSpeedUnitSelected);
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Running Speed: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minRunningSpeed != -1)
                    {
                        temp = normalizeFloatString(to_string(minRunningSpeed));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 13)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (speedUnit == SpeedUnitType::mps)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 50)
                            {
                                minRunningSpeed = stof(temp);
                            }
                            else
                            {
                                minRunningSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mpmin)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 3000)
                            {
                                minRunningSpeed = stof(temp);
                            }
                            else
                            {
                                minRunningSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180000)
                            {
                                minRunningSpeed = stof(temp);
                            }
                            else
                            {
                                minRunningSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::kmph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180)
                            {
                                minRunningSpeed = stof(temp);
                            }
                            else
                            {
                                minRunningSpeed = -1;
                            }
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Running Speed: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxRunningSpeed != -1)
                    {
                        temp = normalizeFloatString(to_string(maxRunningSpeed));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 14)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "Press [->] or [<-] for choosing or changing values"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (speedUnit == SpeedUnitType::mps)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 50)
                            {
                                maxRunningSpeed = stof(temp);
                            }
                            else
                            {
                                maxRunningSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mpmin)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 3000)
                            {
                                maxRunningSpeed = stof(temp);
                            }
                            else
                            {
                                maxRunningSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180000)
                            {
                                maxRunningSpeed = stof(temp);
                            }
                            else
                            {
                                maxRunningSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::kmph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180)
                            {
                                maxRunningSpeed = stof(temp);
                            }
                            else
                            {
                                maxRunningSpeed = -1;
                            }
                        }
                    }
                    temp.clear();
                    indexOfManeColor = SelectOptionForSearching<Colors>("Mane Color: ", indexOfManeColor, key);
                }
                else if (selectedInfo == 15)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = 10"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (indexOfManeColor != -1)
                    {
                        maneColor = static_cast<Colors>(indexOfManeColor);
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Energy Level: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minEnergyLevel != -1)
                    {
                        temp = normalizeFloatString(to_string(minEnergyLevel));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 16)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 10)
                        {
                            minEnergyLevel = stof(temp);
                        }
                        else
                        {
                            minEnergyLevel = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Energy Level: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxEnergyLevel != -1)
                    {
                        temp = normalizeFloatString(to_string(maxEnergyLevel));
                        cout << temp;
                    }
                }
            }
            else if (key == ENTER_KEY && selectedInfo != 0) // starting searching
            {

                if (selectedInfo == 1)
                {
                    if (temp != "")
                    {
                        name = temp;
                    }
                }
                else if (selectedInfo == 2)
                {
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            minAge = stoi(temp);
                        }
                        else
                        {
                            minAge = -1;
                        }
                    }
                }
                else if (selectedInfo == 3)
                {
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            maxAge = stoi(temp);
                        }
                        else
                        {
                            maxAge = -1;
                        }
                    }
                }
                else if (selectedInfo == 4)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            minPrice = stof(temp);
                        }
                        else
                        {
                            minPrice = -1;
                        }
                    }
                }
                else if (selectedInfo == 5)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            maxPrice = stof(temp);
                        }
                        else
                        {
                            maxPrice = -1;
                        }
                    }
                }
                else if (selectedInfo == 6)
                {
                    if (temp != "")
                    {
                        breed = temp;
                    }
                }
                else if (selectedInfo == 7)
                {
                    if (indexOfColorSelected != -1)
                    {
                        color = static_cast<Colors>(indexOfColorSelected);
                    }
                }
                else if (selectedInfo == 8)
                {
                    if (temp != "")
                    {
                        sellerName = temp;
                    }
                }
                else if (selectedInfo == 9)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            minRating = stof(temp);
                        }
                        else
                        {
                            minRating = -1;
                        }
                    }
                }
                else if (selectedInfo == 10)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            maxRating = stof(temp);
                        }
                        else
                        {
                            maxRating = -1;
                        }
                    }
                }
                else if (selectedInfo == 11)
                {
                    if (indexOfSpeedUnitSelected != -1)
                    {
                        speedUnit = static_cast<SpeedUnitType>(indexOfSpeedUnitSelected);
                    }
                }
                else if (selectedInfo == 12)
                {
                    if (temp != "")
                    {
                        if (speedUnit == SpeedUnitType::mps)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 50)
                            {
                                minRunningSpeed = stof(temp);
                            }
                            else
                            {
                                minRunningSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mpmin)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 3000)
                            {
                                minRunningSpeed = stof(temp);
                            }
                            else
                            {
                                minRunningSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180000)
                            {
                                minRunningSpeed = stof(temp);
                            }
                            else
                            {
                                minRunningSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::kmph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180)
                            {
                                minRunningSpeed = stof(temp);
                            }
                            else
                            {
                                minRunningSpeed = -1;
                            }
                        }
                    }
                }
                else if (selectedInfo == 13)
                {
                    if (temp != "")
                    {
                        if (speedUnit == SpeedUnitType::mps)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 50)
                            {
                                maxRunningSpeed = stof(temp);
                            }
                            else
                            {
                                maxRunningSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mpmin)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 3000)
                            {
                                maxRunningSpeed = stof(temp);
                            }
                            else
                            {
                                maxRunningSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::mph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180000)
                            {
                                maxRunningSpeed = stof(temp);
                            }
                            else
                            {
                                maxRunningSpeed = -1;
                            }
                        }
                        else if (speedUnit == SpeedUnitType::kmph)
                        {
                            if (stof(temp) >= 0 && stof(temp) <= 180)
                            {
                                maxRunningSpeed = stof(temp);
                            }
                            else
                            {
                                maxRunningSpeed = -1;
                            }
                        }
                    }
                }
                else if (selectedInfo == 14)
                {
                    if (indexOfManeColor != -1)
                    {
                        maneColor = static_cast<Colors>(indexOfManeColor);
                    }
                }
                else if (selectedInfo == 15)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 10)
                        {
                            minEnergyLevel = stof(temp);
                        }
                        else
                        {
                            minEnergyLevel = -1;
                        }
                    }
                }
                else if (selectedInfo == 16)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 10)
                        {
                            maxEnergyLevel = stof(temp);
                        }
                        else
                        {
                            maxEnergyLevel = -1;
                        }
                    }
                }

                temp.clear();

                system("cls");
                PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                PutMidlle(vector<string>{"This information is going to be searched"}, Horizontal, CursorPlace::BeginningNextLine);
                cout << endl;

                if (name != "-1")
                {
                    string tempText = "Name: " + name;

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minAge != -1 || maxAge != -1)
                {
                    if (maxAge != -1 && (maxAge < minAge))
                    {
                        auto tempNum = maxAge;
                        maxAge = minAge;
                        minAge = tempNum;
                    }

                    string tempText = "Age: ";
                    tempText += (minAge == -1) ? to_string(0) : to_string(minAge);
                    tempText += "-";
                    tempText += (maxAge == -1) ? to_string(120) : to_string(maxAge);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minPrice != -1 || maxPrice != -1)
                {
                    if (maxPrice != -1 && (maxPrice < minPrice))
                    {
                        auto tempNum = maxPrice;
                        maxPrice = minPrice;
                        minPrice = tempNum;
                    }

                    string tempText = "Price: ";
                    tempText += (minPrice == -1) ? to_string(0) : normalizeFloatString(to_string(minPrice));
                    tempText += "-";
                    tempText += (maxPrice == -1) ? "..." : normalizeFloatString(to_string(maxPrice));

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (breed != "-1")
                {
                    string tempText = "Breed: " + breed;

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (indexOfColorSelected != -1)
                {
                    string tempText = "Color: " + enum_to_string<Colors>(color);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (sellerName != "-1")
                {
                    string tempText = "Seller Name: " + sellerName;

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minRating != -1 || maxRating != -1)
                {
                    if (maxRating != -1 && (maxRating < minRating))
                    {
                        auto tempNum = maxRating;
                        maxRating = minRating;
                        minRating = tempNum;
                    }

                    string tempText = "Rating: ";
                    tempText += (minRating == -1) ? to_string(0) : normalizeFloatString(to_string(minRating));
                    tempText += "-";
                    tempText += (maxRating == -1) ? to_string(5) : normalizeFloatString(to_string(maxRating));

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (indexOfSpeedUnitSelected != -1)
                {
                    string tempText = "Unit Of Running Speed: " + enum_to_string<SpeedUnitType>(speedUnit);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minRunningSpeed != -1 || maxRunningSpeed != -1)
                {
                    if (maxRunningSpeed != -1 && (maxRunningSpeed < minRunningSpeed))
                    {
                        auto tempNum = maxRunningSpeed;
                        maxRunningSpeed = minRunningSpeed;
                        minRunningSpeed = tempNum;
                    }

                    string tempText = "Running Speed: ";
                    tempText += (minRunningSpeed == -1) ? to_string(0) : normalizeFloatString(to_string(minRunningSpeed));
                    tempText += "-";
                    if (speedUnit == SpeedUnitType::mps)
                    {
                        tempText += (maxRunningSpeed == -1) ? to_string(50) : normalizeFloatString(to_string(maxRunningSpeed));
                    }
                    else if (speedUnit == SpeedUnitType::mpmin)
                    {
                        tempText += (maxRunningSpeed == -1) ? to_string(3000) : normalizeFloatString(to_string(maxRunningSpeed));
                    }
                    else if (speedUnit == SpeedUnitType::mph)
                    {
                        tempText += (maxRunningSpeed == -1) ? to_string(180000) : normalizeFloatString(to_string(maxRunningSpeed));
                    }
                    else if (speedUnit == SpeedUnitType::kmph)
                    {
                        tempText += (maxRunningSpeed == -1) ? to_string(180) : normalizeFloatString(to_string(maxRunningSpeed));
                    }

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (indexOfManeColor != -1)
                {
                    string tempText = "Mane Color: " + enum_to_string<Colors>(maneColor);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minEnergyLevel != -1 || maxEnergyLevel != -1)
                {
                    if (maxEnergyLevel != -1 && (maxEnergyLevel < minEnergyLevel))
                    {
                        auto tempNum = maxEnergyLevel;
                        maxEnergyLevel = minEnergyLevel;
                        minEnergyLevel = tempNum;
                    }

                    string tempText = "Energy Level: ";
                    tempText += (minEnergyLevel == -1) ? normalizeFloatString(to_string(0)) : normalizeFloatString(to_string(minEnergyLevel));
                    tempText += "-";
                    tempText += (maxEnergyLevel == -1) ? to_string(10) : normalizeFloatString(to_string(maxEnergyLevel));

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }

                cout << endl;
                tempKey = SelectButton(vector<string>{"What do you want to do ?", "choose your option with [->] or [<-] key and press [Enter]"},
                                       vector<string>{"Search", "Exit", "Edit", "Reset All"}, Horizontal, 2, 2, 2);

                if (tempKey == 0)
                {
                    key = ENTER_KEY;
                    break;
                }
                else if (tempKey == 1)
                {
                    key = ESC_KEY;
                    break;
                }
                else if (tempKey == 2)
                {
                    selectedInfo = 0;
                    key = '\t';
                }
                else if (tempKey == 3)
                {
                    name = "-1";
                    minAge = -1;
                    maxAge = -1;
                    minPrice = -1;
                    maxPrice = -1;
                    breed = "-1";
                    indexOfColorSelected = -1;
                    sellerName = "-1";
                    minRating = -1;
                    maxRating = -1;
                    minRunningSpeed = -1;
                    maxRunningSpeed = -1;
                    indexOfSpeedUnitSelected = -1;
                    indexOfManeColor = -1;
                    minEnergyLevel = -1;
                    maxEnergyLevel = -1;

                    selectedInfo = 0;
                    key = '\t';
                }
            }
            else if (key == ESC_KEY) // exit
            {
                break;
            }
            else if (selectedInfo != 0 &&
                     ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || key == '\b' ||
                      (key >= '0' && key <= '9') || key == ' ' || key == '.')) // write and save text
            {
                if (selectedInfo != 7 && selectedInfo != 11 && selectedInfo != 14)
                {
                    if (key == '\b')
                    {
                        if (!temp.empty())
                        {
                            cout << "\b \b";
                            temp.pop_back();
                        }
                    }
                    else
                    {
                        if (key != ' ')
                        {
                            if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z'))
                            {
                                if (selectedInfo == 1 || selectedInfo == 6 || selectedInfo == 8) // 1 -> name | 6 -> breed | 8 -> sellerName
                                {
                                    cout << static_cast<char>(key);
                                    temp += static_cast<char>(key);
                                }
                            }
                            else
                            {
                                if (key == '.')
                                {
                                    if (selectedInfo == 4 || selectedInfo == 5 || selectedInfo == 9 || selectedInfo == 10 ||
                                        selectedInfo == 12 || selectedInfo == 13 || selectedInfo == 15 || selectedInfo == 16) // 4,5 -> price | 9,10 -> rating | 12,13 -> runningSpeed | 15,16 -> energyLevel
                                    {
                                        cout << static_cast<char>(key);
                                        temp += static_cast<char>(key);
                                    }
                                }
                                else
                                {
                                    cout << static_cast<char>(key);
                                    temp += static_cast<char>(key);
                                }
                            }
                        }
                        else if (key == ' ')
                        {
                            if (selectedInfo == 1 || selectedInfo == 6 || selectedInfo == 8) // 1 -> name | 6 -> breed | 8 -> sellerName
                            {
                                cout << static_cast<char>(key);
                                temp += static_cast<char>(key);
                            }
                        }
                    }
                }
            }
        } while (1);

        if (key == ENTER_KEY) // searching
        {
            if (name != "-1")
            {
                for (Pet *x : targetPets)
                {
                    if (x->getName().find(name) != string::npos)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minAge != -1 || maxAge != -1)
            {
                minAge = (minAge == -1) ? 0 : minAge;
                maxAge = (maxAge == -1) ? 120 : maxAge;

                for (Pet *x : targetPets)
                {
                    if (x->getAge() >= minAge && x->getAge() <= maxAge)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minPrice != -1 || maxPrice != -1)
            {
                minPrice = (minPrice == -1) ? 0 : minPrice;

                for (Pet *x : targetPets)
                {
                    if (maxPrice == -1)
                    {
                        if (x->getPrice() >= minPrice)
                        {
                            tempTargetPets.push_back(x);
                        }
                    }
                    else
                    {
                        if (x->getPrice() >= minPrice && x->getPrice() <= maxPrice)
                        {
                            tempTargetPets.push_back(x);
                        }
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (breed != "-1")
            {
                for (Pet *x : targetPets)
                {
                    if (x->getBreed().find(breed) != string::npos)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (indexOfColorSelected != -1)
            {
                for (Pet *x : targetPets)
                {
                    if (x->getColor() == color)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (sellerName != "-1")
            {
                for (Pet *x : targetPets)
                {
                    if (x->getSellerName().find(sellerName) != string::npos)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minRating != -1 || maxRating != -1)
            {
                minRating = (minRating == -1) ? 0 : minRating;
                maxRating = (maxRating == -1) ? 5 : maxRating;

                for (Pet *x : targetPets)
                {
                    if (x->getRating() >= minRating && x->getRating() <= maxRating)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (indexOfSpeedUnitSelected != -1)
            {
                for (Pet *x : targetPets)
                {
                    Pony *tempPony = dynamic_cast<Pony *>(x);
                    if (tempPony->getUnitOfSpeed() == speedUnit)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minRunningSpeed != -1 || maxRunningSpeed != -1)
            {
                minRunningSpeed = (minRunningSpeed == -1) ? 0 : minRunningSpeed;
                if (speedUnit == SpeedUnitType::mps)
                {
                    maxRunningSpeed = (maxRunningSpeed == -1) ? 50 : maxRunningSpeed;
                }
                else if (speedUnit == SpeedUnitType::mpmin)
                {
                    maxRunningSpeed = (maxRunningSpeed == -1) ? 3000 : maxRunningSpeed;
                }
                else if (speedUnit == SpeedUnitType::mph)
                {
                    maxRunningSpeed = (maxRunningSpeed == -1) ? 180000 : maxRunningSpeed;
                }
                else if (speedUnit == SpeedUnitType::kmph)
                {
                    maxRunningSpeed = (maxRunningSpeed == -1) ? 180 : maxRunningSpeed;
                }

                for (Pet *x : targetPets)
                {
                    Pony *tempPony = dynamic_cast<Pony *>(x);
                    if (tempPony->getRunningSpeed() >= minRunningSpeed && tempPony->getRunningSpeed() <= maxRunningSpeed)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (indexOfManeColor != -1)
            {
                for (Pet *x : targetPets)
                {
                    Pony *tempPony = dynamic_cast<Pony *>(x);
                    if (tempPony->getManeColor() == maneColor)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minEnergyLevel != -1 || maxEnergyLevel != -1)
            {
                minEnergyLevel = (minEnergyLevel == -1) ? 0 : minEnergyLevel;
                maxEnergyLevel = (maxEnergyLevel == -1) ? 10 : maxEnergyLevel;

                for (Pet *x : targetPets)
                {
                    Pony *tempPony = dynamic_cast<Pony *>(x);
                    if (tempPony->getEnergyLevel() >= minEnergyLevel && tempPony->getEnergyLevel() <= maxEnergyLevel)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
        }
        else if (key == ESC_KEY)
        {
            targetPets.clear();
        }

        break;
    }
    case SearchingItems::All:
    {
        targetPets = allPets;

        string temp;
        int selectedInfo = 0;
        int key;

        PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
        PutMidlle(vector<string>{"Press [Tab] for start",
                                 "Press [Esc] for Exit",
                                 "** notice **",
                                 "Some search filters may have minimum and maximum values",
                                 "If you skip either the minimum or maximum values, the lowest or highest value will be used",
                                 "And if you enter a value outside the valid range, that value will be ignored"},
                  Horizontal, CursorPlace::BeginningNextLine);

        do
        {
            if (!(selectedInfo == 7 || tempKey == 2 || tempKey == 3)) // 7 -> Color | 13 -> Sound | tempKey == 2 -> edit info again | tempKey == 3 -> reset info
            {
                key = getch();
                if (key == 0 || key == 224)
                {
                    key = getch();
                    continue;
                }
            }
            if (tempKey == 2 || tempKey == 3)
            {
                tempKey = -1;
            }

            if (key == '\t') // next
            {
                if (selectedInfo == 10)
                {
                    selectedInfo = 1;
                }
                else
                {
                    selectedInfo++;
                }

                if (selectedInfo == 1)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            maxRating = stof(temp);
                        }
                        else
                        {
                            maxRating = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Name: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (name != "-1")
                    {
                        temp = name;
                        cout << temp;
                    }
                }
                else if (selectedInfo == 2)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = 120"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        name = temp;
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Age: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minAge != -1)
                    {
                        temp = to_string(minAge);
                        cout << temp;
                    }
                }
                else if (selectedInfo == 3)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            minAge = stoi(temp);
                        }
                        else
                        {
                            minAge = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Age: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxAge != -1)
                    {
                        temp = to_string(maxAge);
                        cout << temp;
                    }
                }
                else if (selectedInfo == 4)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = ..."},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            maxAge = stoi(temp);
                        }
                        else
                        {
                            maxAge = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Price: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minPrice != -1)
                    {
                        temp = normalizeFloatString(to_string(minPrice));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 5)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            minPrice = stof(temp);
                        }
                        else
                        {
                            minPrice = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Price: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxPrice != -1)
                    {
                        temp = normalizeFloatString(to_string(maxPrice));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 6)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            maxPrice = stof(temp);
                        }
                        else
                        {
                            maxPrice = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Breed: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (breed != "-1")
                    {
                        temp = breed;
                        cout << temp;
                    }
                }
                else if (selectedInfo == 7)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "Press [->] or [<-] for choosing or changing values"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        breed = temp;
                    }
                    temp.clear();
                    indexOfColorSelected = SelectOptionForSearching<Colors>("Color: ", indexOfColorSelected, key);
                }
                else if (selectedInfo == 8)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (indexOfColorSelected != -1)
                    {
                        color = static_cast<Colors>(indexOfColorSelected);
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Seller Name: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (sellerName != "-1")
                    {
                        temp = sellerName;
                        cout << temp;
                    }
                }
                else if (selectedInfo == 9)
                {
                    system("cls");
                    PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                    PutMidlle(vector<string>{"Press [Tab] for go next (if we are in the end, it go back to the begin)",
                                             "** if you write anything and press [Tab] it will be skip **",
                                             "Press [Enter] for start to search",
                                             "Press [Esc] for Exit",
                                             "",
                                             "min = 0 | max = 5"},
                              Horizontal, CursorPlace::BeginningNextLine);
                    cout << endl;
                    if (temp != "")
                    {
                        sellerName = temp;
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Minimum Rating: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (minRating != -1)
                    {
                        temp = normalizeFloatString(to_string(minRating));
                        cout << temp;
                    }
                }
                else if (selectedInfo == 10)
                {
                    cout << endl;
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            minRating = stof(temp);
                        }
                        else
                        {
                            minRating = -1;
                        }
                    }
                    temp.clear();
                    PutMidlle(vector<string>{"Maximum Rating: "}, Horizontal, CursorPlace::RightWhereYouAre);
                    if (maxRating != -1)
                    {
                        temp = normalizeFloatString(to_string(maxRating));
                        cout << temp;
                    }
                }
            }
            else if (key == ENTER_KEY && selectedInfo != 0) // starting searching
            {

                if (selectedInfo == 1)
                {
                    if (temp != "")
                    {
                        name = temp;
                    }
                }
                else if (selectedInfo == 2)
                {
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            minAge = stoi(temp);
                        }
                        else
                        {
                            minAge = -1;
                        }
                    }
                }
                else if (selectedInfo == 3)
                {
                    if (temp != "")
                    {
                        if (stoi(temp) >= 0 && stoi(temp) <= 120)
                        {
                            maxAge = stoi(temp);
                        }
                        else
                        {
                            maxAge = -1;
                        }
                    }
                }
                else if (selectedInfo == 4)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            minPrice = stof(temp);
                        }
                        else
                        {
                            minPrice = -1;
                        }
                    }
                }
                else if (selectedInfo == 5)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0)
                        {
                            maxPrice = stof(temp);
                        }
                        else
                        {
                            maxPrice = -1;
                        }
                    }
                }
                else if (selectedInfo == 6)
                {
                    if (temp != "")
                    {
                        breed = temp;
                    }
                }
                else if (selectedInfo == 7)
                {
                    if (indexOfColorSelected != -1)
                    {
                        color = static_cast<Colors>(indexOfColorSelected);
                    }
                }
                else if (selectedInfo == 8)
                {
                    if (temp != "")
                    {
                        sellerName = temp;
                    }
                }
                else if (selectedInfo == 9)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            minRating = stof(temp);
                        }
                        else
                        {
                            minRating = -1;
                        }
                    }
                }
                else if (selectedInfo == 10)
                {
                    if (temp != "")
                    {
                        if (stof(temp) >= 0 && stof(temp) <= 5)
                        {
                            maxRating = stof(temp);
                        }
                        else
                        {
                            maxRating = -1;
                        }
                    }
                }

                temp.clear();

                system("cls");
                PutMidlle(CreateTitle("             Search Page             "), Horizontal, CursorPlace::RightWhereYouAre);
                PutMidlle(vector<string>{"This information is going to be searched"}, Horizontal, CursorPlace::BeginningNextLine);
                cout << endl;

                if (name != "-1")
                {
                    string tempText = "Name: " + name;

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minAge != -1 || maxAge != -1)
                {
                    if (maxAge != -1 && (maxAge < minAge))
                    {
                        auto tempNum = maxAge;
                        maxAge = minAge;
                        minAge = tempNum;
                    }

                    string tempText = "Age: ";
                    tempText += (minAge == -1) ? to_string(0) : to_string(minAge);
                    tempText += "-";
                    tempText += (maxAge == -1) ? to_string(120) : to_string(maxAge);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minPrice != -1 || maxPrice != -1)
                {
                    if (maxPrice != -1 && (maxPrice < minPrice))
                    {
                        auto tempNum = maxPrice;
                        maxPrice = minPrice;
                        minPrice = tempNum;
                    }

                    string tempText = "Price: ";
                    tempText += (minPrice == -1) ? to_string(0) : normalizeFloatString(to_string(minPrice));
                    tempText += "-";
                    tempText += (maxPrice == -1) ? "..." : normalizeFloatString(to_string(maxPrice));

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (breed != "-1")
                {
                    string tempText = "Breed: " + breed;

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (indexOfColorSelected != -1)
                {
                    string tempText = "Color: " + enum_to_string<Colors>(color);

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (sellerName != "-1")
                {
                    string tempText = "Seller Name: " + sellerName;

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }
                if (minRating != -1 || maxRating != -1)
                {
                    if (maxRating != -1 && (maxRating < minRating))
                    {
                        auto tempNum = maxRating;
                        maxRating = minRating;
                        minRating = tempNum;
                    }

                    string tempText = "Rating: ";
                    tempText += (minRating == -1) ? to_string(0) : normalizeFloatString(to_string(minRating));
                    tempText += "-";
                    tempText += (maxRating == -1) ? to_string(5) : normalizeFloatString(to_string(maxRating));

                    PutMidlle(vector<string>{tempText}, Horizontal, CursorPlace::RightWhereYouAre);

                    cout << endl;
                }

                cout << endl;
                tempKey = SelectButton(vector<string>{"What do you want to do ?", "choose your option with [->] or [<-] key and press [Enter]"},
                                       vector<string>{"Search", "Exit", "Edit", "Reset All"}, Horizontal, 2, 2, 2);

                if (tempKey == 0)
                {
                    key = ENTER_KEY;
                    break;
                }
                else if (tempKey == 1)
                {
                    key = ESC_KEY;
                    break;
                }
                else if (tempKey == 2)
                {
                    selectedInfo = 0;
                    key = '\t';
                }
                else if (tempKey == 3)
                {
                    name = "-1";
                    minAge = -1;
                    maxAge = -1;
                    minPrice = -1;
                    maxPrice = -1;
                    breed = "-1";
                    indexOfColorSelected = -1;
                    sellerName = "-1";
                    minRating = -1;
                    maxRating = -1;

                    selectedInfo = 0;
                    key = '\t';
                }
            }
            else if (key == ESC_KEY) // exit
            {
                break;
            }
            else if (selectedInfo != 0 &&
                     ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || key == '\b' ||
                      (key >= '0' && key <= '9') || key == ' ' || key == '.')) // write and save text
            {
                if (selectedInfo != 7)
                {
                    if (key == '\b')
                    {
                        if (!temp.empty())
                        {
                            cout << "\b \b";
                            temp.pop_back();
                        }
                    }
                    else
                    {
                        if (key != ' ')
                        {
                            if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z'))
                            {
                                if (selectedInfo == 1 || selectedInfo == 6 || selectedInfo == 8) // 1 -> name | 6 -> breed | 8 -> sellerName
                                {
                                    cout << static_cast<char>(key);
                                    temp += static_cast<char>(key);
                                }
                            }
                            else
                            {
                                if (key == '.')
                                {
                                    if (selectedInfo == 4 || selectedInfo == 5 || selectedInfo == 9 || selectedInfo == 10) // 4,5 -> price | 9,10 -> rating
                                    {
                                        cout << static_cast<char>(key);
                                        temp += static_cast<char>(key);
                                    }
                                }
                                else
                                {
                                    cout << static_cast<char>(key);
                                    temp += static_cast<char>(key);
                                }
                            }
                        }
                        else if (key == ' ')
                        {
                            if (selectedInfo == 1 || selectedInfo == 6 || selectedInfo == 8) // 1 -> name | 6 -> breed | 8 -> sellerName
                            {
                                cout << static_cast<char>(key);
                                temp += static_cast<char>(key);
                            }
                        }
                    }
                }
            }
        } while (1);

        if (key == ENTER_KEY) // searching
        {
            if (name != "-1")
            {
                for (Pet *x : targetPets)
                {
                    if (x->getName().find(name) != string::npos)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minAge != -1 || maxAge != -1)
            {
                minAge = (minAge == -1) ? 0 : minAge;
                maxAge = (maxAge == -1) ? 120 : maxAge;

                for (Pet *x : targetPets)
                {
                    if (x->getAge() >= minAge && x->getAge() <= maxAge)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minPrice != -1 || maxPrice != -1)
            {
                minPrice = (minPrice == -1) ? 0 : minPrice;

                for (Pet *x : targetPets)
                {
                    if (maxPrice == -1)
                    {
                        if (x->getPrice() >= minPrice)
                        {
                            tempTargetPets.push_back(x);
                        }
                    }
                    else
                    {
                        if (x->getPrice() >= minPrice && x->getPrice() <= maxPrice)
                        {
                            tempTargetPets.push_back(x);
                        }
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (breed != "-1")
            {
                for (Pet *x : targetPets)
                {
                    if (x->getBreed().find(breed) != string::npos)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (indexOfColorSelected != -1)
            {
                for (Pet *x : targetPets)
                {
                    if (x->getColor() == color)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (sellerName != "-1")
            {
                for (Pet *x : targetPets)
                {
                    if (x->getSellerName().find(sellerName) != string::npos)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
            if (minRating != -1 || maxRating != -1)
            {
                minRating = (minRating == -1) ? 0 : minRating;
                maxRating = (maxRating == -1) ? 5 : maxRating;

                for (Pet *x : targetPets)
                {
                    if (x->getRating() >= minRating && x->getRating() <= maxRating)
                    {
                        tempTargetPets.push_back(x);
                    }
                }
                targetPets = tempTargetPets;
                tempTargetPets.clear();
            }
        }
        else if (key == ESC_KEY)
        {
            targetPets.clear();
        }

        break;
    }

    default:
        break;
    }

    return targetPets;
}

void Buyer::showProducts()
{
    vector<Pet *> pets = Pet::loadInfoAllPet();

    if (pets.size() != 0)
    {
        vector<vector<string>> products;

        for (auto x : pets)
        {
            if (x->getStatus() == true)
            {
                products.push_back(x->createProductStyle());
            }
        }

        if (products.size() != 0)
        {
            ShowSomeBoxes(products);
        }
        else
        {
            cout << endl;
            cout << endl;
            PutMidlle(vector<string>{"-- There is no product --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
            cin.get();
        }
    }
    else
    {
        cout << endl;
        cout << endl;
        PutMidlle(vector<string>{"-- There is no product --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
        cin.get();
    }
}

void Buyer::ratingPet(Pet *pet, float score)
{
    while (1)
    {
        try
        {
            pet->setRating(score, 0);
            pet->updateInfoThisPetInBinaryFile();
            break;
        }
        catch (const setValuesException &e)
        {
            cout << endl;
            cerr << e.what() << endl;
            cout << "Please enter Pet's rating again: ";
            cin >> score;
            cin.get();
        }
    }
}

bool Buyer::buying(vector<Pet *> pets, int index)
{
    return userAccount.purchase(pets[index], getId());
}

void Buyer::purchaseHistory()
{
    vector<TransactionInfo> transactions = Account::loadAllTransaction();
    vector<TransactionInfo> tempTransactions;

    for (auto x : transactions)
    {
        if (x.type == TransactionType::Purchase)
        {
            if (x.userId == getId())
            {
                tempTransactions.push_back(x);
            }
        }
    }

    if (tempTransactions.size() != 0)
    {
        int selectedTransaction = SelectTransaction(tempTransactions);

        if (selectedTransaction != -1)
        {
            system("cls");
            try
            {
                Pet *pet = Pet::loadInfoOnePet(tempTransactions[selectedTransaction].petId, 2);

                pet->showInfo();
            }
            catch (const runtime_error &e)
            {
                PutMidlle(vector<string>{"Pet has been deleted...", "", "Press [Enter] to continue"}, Horizontal | Vertical, CursorPlace::ZeroZero);
                cin.get();
            }
        }
    }
    else
    {
        cout << endl;
        cout << endl;
        PutMidlle(vector<string>{"-- There is no transaction --", "", "Press [Enter] to continue"}, Horizontal, CursorPlace::ZeroZero);
        cin.get();
    }
}

//========================= Pet Class Functions

// temp objects
Pet::Pet() : petId(0) {}

Pet::Pet(string _name, int _age, float _price, string _breed, Colors _color, bool _status, string _sellerName, int _sellerId, PetSpecies _species) : petId(SetIds(ObjectType::Pet))
{
    bool areAllValuesOk = false;

    while (!areAllValuesOk)
    {
        try
        {
            setName(_name);
            setAge(_age);
            setPrice(_price);
            setBreed(_breed);
            setColor(_color);
            setStatus(_status);
            setSellerName(_sellerName);
            setSellerId(_sellerId);
            setSpecies(_species);
            rating = 0;
            ratings = 0;

            areAllValuesOk = true;
        }
        catch (const setValuesException &e)
        {
            cout << endl;
            cerr << e.what() << endl;
            cout << "Plese enter Pet's " << enum_to_string<VariablesToValidate>(e.getVariableName()) << " again: ";
            if (e.checkVariableName(VariablesToValidate::Age))
            {
                cin >> _age;
                cin.get();
            }
            else if (e.checkVariableName(VariablesToValidate::Price))
            {
                cin >> _price;
                cin.get();
            }
        }
    }
}

// for load info
Pet::Pet(int _petId, string _name, int _age, float _price, string _breed, Colors _color, bool _status, string _sellerName, int _sellerId, PetSpecies _species, float _rating, int _ratings)
    : petId(_petId), name(_name), age(_age), price(_price), breed(_breed), color(_color), status(_status), sellerName(_sellerName), sellerId(_sellerId), species(_species), rating(_rating), ratings(_ratings) {}

void Pet::setName(string _name)
{
    name = _name;
}

void Pet::setAge(int _age)
{
    if (_age < 0 || _age > 120)
        throw setValuesException("The age of pet must be between 0 and 120 years old... ", VariablesToValidate::Age);

    age = _age;
}

void Pet::setPrice(float _price)
{
    if (_price < 0)
        throw setValuesException("The price is invalid...", VariablesToValidate::Price);

    price = _price;
}

void Pet::setBreed(string _breed)
{
    breed = _breed;
}

void Pet::setColor(Colors _color)
{
    color = _color;
}

void Pet::setStatus(bool _status)
{
    status = _status;
}

void Pet::setSellerName(string _sellerName)
{
    sellerName = _sellerName;
}

void Pet::setSellerId(int _sellerId)
{
    sellerId = _sellerId;
}

void Pet::setSpecies(PetSpecies _species)
{
    species = _species;
}

// tmp == 0 -> calc and set
// tmp == 1 -> just set (for update info)
void Pet::setRating(float _rating, int tmp)
{
    if (_rating < 0 || _rating > 5)
        throw setValuesException("Pet rating must be between 0 and 5... ", VariablesToValidate::Rating);

    if (tmp == 0)
    {
        setRatings(ratings + 1);
        calculateRating(_rating);
    }
    else
    {
        rating = _rating;
    }
}

void Pet::setRatings(int _ratings)
{
    if (_ratings < 0)
        throw setValuesException("The ratings is invalid... ", VariablesToValidate::Ratings);

    ratings = _ratings;
}

int Pet::getId() const { return petId; }

string Pet::getName() const { return name; }

int Pet::getAge() const { return age; }

float Pet::getPrice() const { return price; }

string Pet::getBreed() const { return breed; }

Colors Pet::getColor() const { return color; }

bool Pet::getStatus() const { return status; }

string Pet::getSellerName() const { return sellerName; }

int Pet::getSellerId() const { return sellerId; }

PetSpecies Pet::getSpecies() const { return species; }

float Pet::getRating() const { return rating; }

int Pet::getRatings() const { return ratings; }

vector<Pet *> Pet::loadInfoAllPet()
{
    vector<Pet *> pets;

    int _petId;
    int sizeStr_name;
    string _name;
    int _age;
    float _price;
    int sizeStr_breed;
    string _breed;
    Colors _color;
    bool _status;
    int sizeStr_sellerName;
    string _sellerName;
    int _sellerId;
    PetSpecies _species;
    float _rating;
    int _ratings;

    float _flightHeight;
    VoiceType _sound;
    float _iq;
    WaterType _water;
    float _aquariumSize;
    float _swimmingSpeed;
    SpeedUnitType _speedUnit;
    float _runningSpeed;
    Colors _maneColor;
    float _energyLevel;

    fstream file(PathPet, ios::in | ios::binary);

    if (file)
    {
        while (file.read(reinterpret_cast<char *>(&_petId), sizeof(_petId)))
        {

            file.read(reinterpret_cast<char *>(&sizeStr_name), sizeof(sizeStr_name));
            _name.resize(sizeStr_name, '\0');
            file.read(_name.data(), sizeStr_name);

            file.read(reinterpret_cast<char *>(&_age), sizeof(_age));
            file.read(reinterpret_cast<char *>(&_price), sizeof(_price));

            file.read(reinterpret_cast<char *>(&sizeStr_breed), sizeof(sizeStr_breed));
            _breed.resize(sizeStr_breed, '\0');
            file.read(_breed.data(), sizeStr_breed);

            file.read(reinterpret_cast<char *>(&_color), sizeof(_color));
            file.read(reinterpret_cast<char *>(&_status), sizeof(_status));

            file.read(reinterpret_cast<char *>(&sizeStr_sellerName), sizeof(sizeStr_sellerName));
            _sellerName.resize(sizeStr_sellerName, '\0');
            file.read(_sellerName.data(), sizeStr_sellerName);

            file.read(reinterpret_cast<char *>(&_sellerId), sizeof(_sellerId));
            file.read(reinterpret_cast<char *>(&_species), sizeof(_species));
            file.read(reinterpret_cast<char *>(&_rating), sizeof(_rating));
            file.read(reinterpret_cast<char *>(&_ratings), sizeof(_ratings));

            if (_species == PetSpecies::Bird)
            {
                file.read(reinterpret_cast<char *>(&_flightHeight), sizeof(_flightHeight));
                file.read(reinterpret_cast<char *>(&_sound), sizeof(_sound));
                file.read(reinterpret_cast<char *>(&_iq), sizeof(_iq));

                pets.push_back(new Bird(_petId, _name, _age, _price, _breed, _color, _status, _sellerName, _sellerId, _rating, _ratings, _flightHeight, _sound, _iq));
            }
            else if (_species == PetSpecies::Fish)
            {
                file.read(reinterpret_cast<char *>(&_water), sizeof(_water));
                file.read(reinterpret_cast<char *>(&_aquariumSize), sizeof(_aquariumSize));
                file.read(reinterpret_cast<char *>(&_swimmingSpeed), sizeof(_swimmingSpeed));
                file.read(reinterpret_cast<char *>(&_speedUnit), sizeof(_speedUnit));

                pets.push_back(new Fish(_petId, _name, _age, _price, _breed, _color, _status, _sellerName, _sellerId, _rating, _ratings, _water, _aquariumSize, _swimmingSpeed, _speedUnit));
            }
            else if (_species == PetSpecies::Pony)
            {
                file.read(reinterpret_cast<char *>(&_runningSpeed), sizeof(_runningSpeed));
                file.read(reinterpret_cast<char *>(&_speedUnit), sizeof(_speedUnit));
                file.read(reinterpret_cast<char *>(&_maneColor), sizeof(_maneColor));
                file.read(reinterpret_cast<char *>(&_energyLevel), sizeof(_energyLevel));

                pets.push_back(new Pony(_petId, _name, _age, _price, _breed, _color, _status, _sellerName, _sellerId, _rating, _ratings, _runningSpeed, _speedUnit, _maneColor, _energyLevel));
            }
        }
    }

    file.close();

    return pets;
}

// whichInfo == 1 -> index of vector of all pet
// whichInfo == 2 -> pet id
Pet *Pet::loadInfoOnePet(int key, int whichInfo)
{
    vector<Pet *> pets = Pet::loadInfoAllPet();

    switch (whichInfo)
    {
    case 1:
        if (key < pets.size())
        {
            return pets[key];
        }
        break;
    case 2:
        for (auto x : pets)
        {
            if (x->getId() == key)
            {
                return x;
            }
        }
        break;
    }
    throw runtime_error("Pet does not exist...");
}

void Pet::updateAllPetInBinaryFile(vector<Pet *> pets)
{
    fstream file(PathPet, ios::out | ios::binary);

    for (auto x : pets)
    {
        x->saveInfoInBinaryFile();
    }

    file.close();
}

void Pet::deletePet()
{
    vector<Pet *> pets = Pet::loadInfoAllPet();

    for (auto it = pets.begin(); it != pets.end(); it++)
    {
        if ((*it)->getId() == getId())
        {
            pets.erase(it);
            break;
        }
    }

    Pet::updateAllPetInBinaryFile(pets);
}

void Pet::calculateRating(float score)
{
    float sumOfTheAllScore;
    sumOfTheAllScore = rating * (ratings - 1);
    sumOfTheAllScore += score;
    rating = sumOfTheAllScore / ratings;
}

//========================= Bird Class Functions

// temp objects
Bird::Bird() {}

Bird::Bird(string _name, int _age, float _price, string _breed, Colors _color, bool _status, string _sellerName, int _sellerId, float _flightHeight, VoiceType _sound, float _iq)
    : Pet(_name, _age, _price, _breed, _color, _status, _sellerName, _sellerId, PetSpecies::Bird)
{
    bool areAllValuesOk = false;

    while (!areAllValuesOk)
    {
        try
        {
            setFlightHeight(_flightHeight);
            setSound(_sound);
            setIq(_iq);

            areAllValuesOk = true;
        }
        catch (const setValuesException &e)
        {
            cout << endl;
            cerr << e.what() << endl;
            cout << "Plese enter Pet's " << enum_to_string<VariablesToValidate>(e.getVariableName()) << " again: ";
            if (e.checkVariableName(VariablesToValidate::FlightHeight))
            {
                cin >> _flightHeight;
                cin.get();
            }
            else if (e.checkVariableName(VariablesToValidate::Iq))
            {
                cin >> _iq;
                cin.get();
            }
        }
    }
}

// for load info
Bird::Bird(int _petId, string _name, int _age, float _price, string _breed, Colors _color, bool _status, string _sellerName, int _sellerId, float _rating, int _ratings, float _flightHeight, VoiceType _sound, float _iq)
    : Pet(_petId, _name, _age, _price, _breed, _color, _status, _sellerName, _sellerId, PetSpecies::Bird, _rating, _ratings), flightHeight(_flightHeight), sound(_sound), iq(_iq) {}

void Bird::setFlightHeight(float _flightHeight)
{
    if (_flightHeight < 0 || _flightHeight > 100)
        throw setValuesException("The bird's flight height must be between 0 and 100 meters... ", VariablesToValidate::FlightHeight);

    flightHeight = _flightHeight;
}

void Bird::setSound(VoiceType _sound)
{
    sound = _sound;
}

void Bird::setIq(float _iq)
{
    if (_iq < 1 || _iq > 10)
        throw setValuesException("The bird's IQ must be between 1 and 10... ", VariablesToValidate::Iq);

    iq = _iq;
}

float Bird::getFlightHeight() const { return flightHeight; }

VoiceType Bird::getSound() const { return sound; }

float Bird::getIq() const { return iq; }

void Bird::saveInfoInBinaryFile()
{
    int _petId = getId();
    int sizeStr_name = getName().size();
    string _name = getName();
    int _age = getAge();
    float _price = getPrice();
    int sizeStr_breed = getBreed().size();
    string _breed = getBreed();
    Colors _color = getColor();
    bool _status = getStatus();
    int sizeStr_sellerName = getSellerName().size();
    string _sellerName = getSellerName();
    int _sellerId = getSellerId();
    PetSpecies _species = getSpecies();
    float _rating = getRating();
    int _ratings = getRatings();

    float _flightHeight = flightHeight;
    VoiceType _sound = sound;
    float _iq = iq;

    fstream file(PathPet, ios::app | ios::binary);

    file.write(reinterpret_cast<char *>(&_petId), sizeof(_petId));

    file.write(reinterpret_cast<char *>(&sizeStr_name), sizeof(sizeStr_name));
    file.write(_name.data(), sizeStr_name);

    file.write(reinterpret_cast<char *>(&_age), sizeof(_age));
    file.write(reinterpret_cast<char *>(&_price), sizeof(_price));

    file.write(reinterpret_cast<char *>(&sizeStr_breed), sizeof(sizeStr_breed));
    file.write(_breed.data(), sizeStr_breed);

    file.write(reinterpret_cast<char *>(&_color), sizeof(_color));
    file.write(reinterpret_cast<char *>(&_status), sizeof(_status));

    file.write(reinterpret_cast<char *>(&sizeStr_sellerName), sizeof(sizeStr_sellerName));
    file.write(_sellerName.data(), sizeStr_sellerName);

    file.write(reinterpret_cast<char *>(&_sellerId), sizeof(_sellerId));
    file.write(reinterpret_cast<char *>(&_species), sizeof(_species));
    file.write(reinterpret_cast<char *>(&_rating), sizeof(_rating));
    file.write(reinterpret_cast<char *>(&_ratings), sizeof(_ratings));
    file.write(reinterpret_cast<char *>(&_flightHeight), sizeof(_flightHeight));
    file.write(reinterpret_cast<char *>(&_sound), sizeof(_sound));
    file.write(reinterpret_cast<char *>(&_iq), sizeof(_iq));

    file.close();
}

void Bird::updateInfoThisPetInBinaryFile()
{
    vector<Pet *> pets = Pet::loadInfoAllPet();
    int index;
    IsThereThisInfo<int, PetInfo>(getId(), PetInfo::PetId, &index);
    if (index != -1)
    {
        Bird *temp = dynamic_cast<Bird *>(pets[index]);

        temp->setName(getName());
        temp->setAge(getAge());
        temp->setPrice(getPrice());
        temp->setBreed(getBreed());
        temp->setColor(getColor());
        temp->setStatus(getStatus());
        temp->setSellerName(getSellerName());
        temp->setSellerId(getSellerId());
        temp->setRating(getRating(), 1);
        temp->setRatings(getRatings());
        temp->flightHeight = flightHeight;
        temp->sound = sound;
        temp->iq = iq;

        pets[index] = temp;

        Pet::updateAllPetInBinaryFile(pets);
    }
}

vector<string> Bird::createProductStyle()
{
    short width, height;
    GetWidthHeight(&width, &height);

    string _petId = to_string(getId());
    string _name = getName();
    string _age = to_string(getAge());
    string _price = normalizeFloatString(to_string(getPrice())) + " $";
    string _breed = getBreed();
    string _color = enum_to_string<Colors>(getColor());
    string _sellerName = getSellerName();
    string _species = enum_to_string<PetSpecies>(getSpecies());
    string _rating = normalizeFloatString(to_string(getRating()));
    string tempRatings = "Rated By ";
    tempRatings += to_string(getRatings());
    tempRatings += " Users";
    string _ratings = tempRatings;
    string _flightHeight = normalizeFloatString(to_string(flightHeight)) + " m";
    string _sound = enum_to_string<VoiceType>(sound);
    string _iq = normalizeFloatString(to_string(iq));

    vector<string> info = {
        "Pet ID        : " + _petId,
        "Name          : " + _name,
        "Age           : " + _age,
        "Price         : " + _price,
        "Breed         : " + _breed,
        "Color         : " + _color,
        "Seller Name   : " + _sellerName,
        "Species       : " + _species,
        "Rating        : " + _rating,
        "Ratings       : " + _ratings,
        "Flight Height : " + _flightHeight,
        "Sound         : " + _sound,
        "IQ            : " + _iq};

    int maxSize, petTextSize;

    if (height <= 25)
    {
        maxSize = 17; // min size == 17  -->  "| flightHeight : aa |"
        petTextSize = 1;
    }
    else
    {
        maxSize = 28; // min size == 28  -->  "| flightHeight : aaaaaaaaaaaaa |"
        petTextSize = 2;
    }

    for (auto x : info)
    {
        if (x.size() > maxSize)
        {
            maxSize = x.size();
        }
    }

    vector<string> petText = PetText(petTextSize);
    vector<string> productStyle;
    string temp;

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // pet text
    int petTextLength = petText[0].size();
    int numberOfSpace = (maxSize + 2 - petTextLength) / 2;
    for (auto x : petText)
    {
        temp += "|";
        for (int i = 0; i < numberOfSpace + (maxSize + 2 - petTextLength) % 2; i++)
        {
            temp += " ";
        }
        temp += x;
        for (int i = 0; i < numberOfSpace; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // info
    int infoLength;
    for (auto x : info)
    {
        infoLength = x.size();
        temp += "| ";
        temp += x;
        for (int i = 0; i < maxSize - infoLength + 1; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    return productStyle;
}

vector<string> Bird::createProductStyleForManaging()
{
    short width, height;
    GetWidthHeight(&width, &height);

    string _petId = to_string(getId());
    string _name = getName();
    string _age = to_string(getAge());
    string _price = normalizeFloatString(to_string(getPrice())) + " $";
    string _breed = getBreed();
    string _color = enum_to_string<Colors>(getColor());
    string _status = (getStatus()) ? "Accepted" : "Pending...";
    string _sellerName = getSellerName();
    string _sellerId = to_string(getSellerId());
    string _species = enum_to_string<PetSpecies>(getSpecies());
    string _rating = normalizeFloatString(to_string(getRating()));
    string tempRatings = "Rated By ";
    tempRatings += to_string(getRatings());
    tempRatings += " Users";
    string _ratings = tempRatings;
    string _flightHeight = normalizeFloatString(to_string(flightHeight)) + " m";
    string _sound = enum_to_string<VoiceType>(sound);
    string _iq = normalizeFloatString(to_string(iq));

    vector<string> info = {
        "Pet ID        : " + _petId,
        "Name          : " + _name,
        "Age           : " + _age,
        "Price         : " + _price,
        "Breed         : " + _breed,
        "Color         : " + _color,
        "Status        : " + _status,
        "Seller Name   : " + _sellerName,
        "Seller ID     : " + _sellerId,
        "Species       : " + _species,
        "Rating        : " + _rating,
        "Ratings       : " + _ratings,
        "Flight Height : " + _flightHeight,
        "Sound         : " + _sound,
        "IQ            : " + _iq};

    int maxSize, petTextSize;

    if (height <= 25)
    {
        maxSize = 17; // min size == 17  -->  "| flightHeight : aa |"
        petTextSize = 1;
    }
    else
    {
        maxSize = 28; // min size == 28  -->  "| flightHeight : aaaaaaaaaaaaa |"
        petTextSize = 2;
    }

    for (auto x : info)
    {
        if (x.size() > maxSize)
        {
            maxSize = x.size();
        }
    }

    vector<string> petText = PetText(petTextSize);
    vector<string> productStyle;
    string temp;

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // pet text
    int petTextLength = petText[0].size();
    int numberOfSpace = (maxSize + 2 - petTextLength) / 2;
    for (auto x : petText)
    {
        temp += "|";
        for (int i = 0; i < numberOfSpace + (maxSize + 2 - petTextLength) % 2; i++)
        {
            temp += " ";
        }
        temp += x;
        for (int i = 0; i < numberOfSpace; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // info
    int infoLength;
    for (auto x : info)
    {
        infoLength = x.size();
        temp += "| ";
        temp += x;
        for (int i = 0; i < maxSize - infoLength + 1; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    return productStyle;
}

void Bird::showInfo()
{
    vector<vector<string>> pet = {this->createProductStyleForManaging()};

    PrintBoxesInCenter("", "Press [Enter] to continue", pet);
    cin.get();
}

void Bird::changeInfo()
{
    PrintVecStr(CreateTitle("Pet Info Edit Page"), Vertical);
    cout << "Which information do you want to edit:\n\n";

    cout << "Pet ID: " << getId();
    cout << endl;
    cout << "Pet Species: " << enum_to_string<PetSpecies>(getSpecies());
    cout << endl;
    cout << "Seller Name: " << getSellerName();
    cout << endl;
    cout << "Seller ID: " << getSellerId();
    cout << endl;

    string _name;
    int _age;
    float _price;
    string _breed;
    Colors _color;
    float _flightHeight;
    VoiceType _sound;
    float _iq;

    string text_name = getName();
    string text_age = to_string(getAge());
    string text_price = normalizeFloatString(to_string(getPrice())) + " $";
    string text_breed = getBreed();
    string text_color = enum_to_string<Colors>(getColor());
    string text_flightHeight = normalizeFloatString(to_string(flightHeight)) + " m";
    string text_sound = enum_to_string<VoiceType>(sound);
    string text_iq = normalizeFloatString(to_string(iq));

    vector<string> optionsMenu{
        "Name: " + text_name,
        "Age: " + text_age,
        "Price: " + text_price,
        "Breed: " + text_breed,
        "Color: " + text_color,
        "Flight Height: " + text_flightHeight,
        "Sound: " + text_sound,
        "IQ: " + text_iq};

    int selected = SelectMenu("", optionsMenu);

    bool areAllValuesOk = false;

    switch (selected)
    {
    case 0:
        cout << "Pet's Name : ";
        getline(cin, _name);
        break;
    case 1:
        cout << "Pet's Age [0-120]: ";
        cin >> _age;
        cin.get();
        break;
    case 2:
        cout << "Pet's Price: ";
        cin >> _price;
        cin.get();
        break;
    case 3:
        cout << "Pet's Breed: ";
        getline(cin, _breed);
        break;
    case 4:
        _color = SelectOption<Colors>("Pet's Color: ");
        break;
    case 5:
        cout << "How high can the bird Fly [0-100 meters]: ";
        cin >> _flightHeight;
        cin.get();
        break;
    case 6:
        _sound = SelectOption<VoiceType>("Type of bird Sound: ");
        break;
    case 7:
        cout << "IQ of bird [1-10]: ";
        cin >> _iq;
        cin.get();
        break;

    default:
        break;
    }

    while (!areAllValuesOk)
    {
        try
        {
            switch (selected)
            {
            case 0:
                setName(_name);
                break;
            case 1:
                setAge(_age);
                break;
            case 2:
                setPrice(_price);
                break;
            case 3:
                setBreed(_breed);
                break;
            case 4:
                setColor(_color);
                break;
            case 5:
                setFlightHeight(_flightHeight);
                break;
            case 6:
                setSound(_sound);
                break;
            case 7:
                setIq(_iq);
                break;

            default:
                break;
            }

            LoadingAnimation();

            cout << "\nChanges saved successfully...";
            Sleep(700);

            setStatus(false);
            areAllValuesOk = true;
        }
        catch (const setValuesException &e)
        {
            LoadingAnimation();

            cout << endl;
            cerr << e.what() << endl;
            cout << "Plese enter Pet's " << enum_to_string<VariablesToValidate>(e.getVariableName()) << " again: ";
            if (e.checkVariableName(VariablesToValidate::Age))
            {
                cin >> _age;
                cin.get();
                setAge(_age);
            }
            else if (e.checkVariableName(VariablesToValidate::Price))
            {
                cin >> _price;
                cin.get();
                setPrice(_price);
            }
            else if (e.checkVariableName(VariablesToValidate::FlightHeight))
            {
                cin >> _flightHeight;
                cin.get();
                setFlightHeight(_flightHeight);
            }
            else if (e.checkVariableName(VariablesToValidate::Iq))
            {
                cin >> _iq;
                cin.get();
                setIq(_iq);
            }
        }
    }

    updateInfoThisPetInBinaryFile();
}

//========================= Fish Class Functions

// temp objects
Fish::Fish() {}

Fish::Fish(string _name, int _age, float _price, string _breed, Colors _color, bool _status, string _sellerName, int _sellerId, WaterType _water, float _aquariumSize, float _swimmingSpeed, SpeedUnitType _speedUnit)
    : Pet(_name, _age, _price, _breed, _color, _status, _sellerName, _sellerId, PetSpecies::Fish)
{
    bool areAllValuesOk = false;

    while (!areAllValuesOk)
    {
        try
        {
            setWater(_water);
            setAquariumSize(_aquariumSize);
            setSwimmingSpeed(_swimmingSpeed, _speedUnit);

            areAllValuesOk = true;
        }
        catch (const setValuesException &e)
        {
            cout << endl;
            cerr << e.what() << endl;
            cout << "Plese enter Pet's " << enum_to_string<VariablesToValidate>(e.getVariableName()) << " again: ";
            if (e.checkVariableName(VariablesToValidate::AquariumSize))
            {
                cin >> _aquariumSize;
                cin.get();
            }
            else if (e.checkVariableName(VariablesToValidate::SwimmingSpeed))
            {
                cin >> _swimmingSpeed;
                cin.get();
            }
        }
    }
}

// for load info
Fish::Fish(int _petId, string _name, int _age, float _price, string _breed, Colors _color, bool _status, string _sellerName, int _sellerId, float _rating, int _ratings, WaterType _water, float _aquariumSize, float _swimmingSpeed, SpeedUnitType _speedUnit)
    : Pet(_petId, _name, _age, _price, _breed, _color, _status, _sellerName, _sellerId, PetSpecies::Fish, _rating, _ratings), water(_water), aquariumSize(_aquariumSize), swimmingSpeed(_swimmingSpeed), speedUnit(_speedUnit) {}

void Fish::setWater(WaterType _water)
{
    water = _water;
}

void Fish::setAquariumSize(float _aquariumSize)
{
    if (_aquariumSize < 0.001 || _aquariumSize > 10)
        throw setValuesException("The aquarium size must be between 0.001 and 10 cubic meters... ", VariablesToValidate::AquariumSize);

    aquariumSize = _aquariumSize;
}

void Fish::setSwimmingSpeed(float _swimmingSpeed, SpeedUnitType _speedUnit)
{
    if (_speedUnit == SpeedUnitType::mps)
        if (_swimmingSpeed < 0 || _swimmingSpeed > 50)
            throw setValuesException("The fish's swimming speed must be between 0 and 50 meters per second... ", VariablesToValidate::SwimmingSpeed);
    if (_speedUnit == SpeedUnitType::mpmin)
        if (_swimmingSpeed < 0 || _swimmingSpeed > 3000)
            throw setValuesException("The fish's swimming speed must be between 0 and 3,000 meters per minute... ", VariablesToValidate::SwimmingSpeed);
    if (_speedUnit == SpeedUnitType::mph)
        if (_swimmingSpeed < 0 || _swimmingSpeed > 180000)
            throw setValuesException("The fish's swimming speed must be between 0 and 180,000 meters per hour... ", VariablesToValidate::SwimmingSpeed);
    if (_speedUnit == SpeedUnitType::kmph)
        if (_swimmingSpeed < 0 || _swimmingSpeed > 180)
            throw setValuesException("The fish's swimming speed must be between 0 and 180 kilometers per hour... ", VariablesToValidate::SwimmingSpeed);

    swimmingSpeed = _swimmingSpeed;
    speedUnit = _speedUnit;
}

WaterType Fish::getWater() const { return water; }

float Fish::getAquariumSize() const { return aquariumSize; }

float Fish::getSwimmingSpeed() const { return swimmingSpeed; }

SpeedUnitType Fish::getUnitOfSpeed() const { return speedUnit; }

void Fish::saveInfoInBinaryFile()
{
    int _petId = getId();
    int sizeStr_name = getName().size();
    string _name = getName();
    int _age = getAge();
    float _price = getPrice();
    int sizeStr_breed = getBreed().size();
    string _breed = getBreed();
    Colors _color = getColor();
    bool _status = getStatus();
    int sizeStr_sellerName = getSellerName().size();
    string _sellerName = getSellerName();
    int _sellerId = getSellerId();
    PetSpecies _species = getSpecies();
    float _rating = getRating();
    int _ratings = getRatings();

    WaterType _water = water;
    float _aquariumSize = aquariumSize;
    float _swimmingSpeed = swimmingSpeed;
    SpeedUnitType _speedUnit = speedUnit;

    fstream file(PathPet, ios::app | ios::binary);

    file.write(reinterpret_cast<char *>(&_petId), sizeof(_petId));

    file.write(reinterpret_cast<char *>(&sizeStr_name), sizeof(sizeStr_name));
    file.write(_name.data(), sizeStr_name);

    file.write(reinterpret_cast<char *>(&_age), sizeof(_age));
    file.write(reinterpret_cast<char *>(&_price), sizeof(_price));

    file.write(reinterpret_cast<char *>(&sizeStr_breed), sizeof(sizeStr_breed));
    file.write(_breed.data(), sizeStr_breed);

    file.write(reinterpret_cast<char *>(&_color), sizeof(_color));
    file.write(reinterpret_cast<char *>(&_status), sizeof(_status));

    file.write(reinterpret_cast<char *>(&sizeStr_sellerName), sizeof(sizeStr_sellerName));
    file.write(_sellerName.data(), sizeStr_sellerName);

    file.write(reinterpret_cast<char *>(&_sellerId), sizeof(_sellerId));
    file.write(reinterpret_cast<char *>(&_species), sizeof(_species));
    file.write(reinterpret_cast<char *>(&_rating), sizeof(_rating));
    file.write(reinterpret_cast<char *>(&_ratings), sizeof(_ratings));
    file.write(reinterpret_cast<char *>(&_water), sizeof(_water));
    file.write(reinterpret_cast<char *>(&_aquariumSize), sizeof(_aquariumSize));
    file.write(reinterpret_cast<char *>(&_swimmingSpeed), sizeof(_swimmingSpeed));
    file.write(reinterpret_cast<char *>(&_speedUnit), sizeof(_speedUnit));

    file.close();
}

void Fish::updateInfoThisPetInBinaryFile()
{
    vector<Pet *> pets = Pet::loadInfoAllPet();
    int index;
    IsThereThisInfo<int, PetInfo>(getId(), PetInfo::PetId, &index);
    if (index != -1)
    {
        Fish *temp = dynamic_cast<Fish *>(pets[index]);

        temp->setName(getName());
        temp->setAge(getAge());
        temp->setPrice(getPrice());
        temp->setBreed(getBreed());
        temp->setColor(getColor());
        temp->setStatus(getStatus());
        temp->setSellerName(getSellerName());
        temp->setSellerId(getSellerId());
        temp->setRating(getRating(), 1);
        temp->setRatings(getRatings());
        temp->water = water;
        temp->aquariumSize = aquariumSize;
        temp->swimmingSpeed = swimmingSpeed;
        temp->speedUnit = speedUnit;

        pets[index] = temp;

        Pet::updateAllPetInBinaryFile(pets);
    }
}

vector<string> Fish::createProductStyle()
{
    short width, height;
    GetWidthHeight(&width, &height);

    string _petId = to_string(getId());
    string _name = getName();
    string _age = to_string(getAge());
    string _price = normalizeFloatString(to_string(getPrice())) + " $";
    string _breed = getBreed();
    string _color = enum_to_string<Colors>(getColor());
    string _sellerName = getSellerName();
    string _species = enum_to_string<PetSpecies>(getSpecies());
    string _rating = normalizeFloatString(to_string(getRating()));
    string tempRatings = "Rated By ";
    tempRatings += to_string(getRatings());
    tempRatings += " Users";
    string _ratings = tempRatings;
    string _water = enum_to_string<WaterType>(water);
    string _aquariumSize = normalizeFloatString(to_string(aquariumSize)) + " cubic meters";
    string _swimmingSpeed = normalizeFloatString(to_string(swimmingSpeed)) + " " + enum_to_string<SpeedUnitType>(speedUnit);

    vector<string> info = {
        "Pet ID         : " + _petId,
        "Name           : " + _name,
        "Age            : " + _age,
        "Price          : " + _price,
        "Breed          : " + _breed,
        "Color          : " + _color,
        "Seller Name    : " + _sellerName,
        "Species        : " + _species,
        "Rating         : " + _rating,
        "Ratings        : " + _ratings,
        "Water          : " + _water,
        "Aquarium Size  : " + _aquariumSize,
        "Swimming Speed : " + _swimmingSpeed};

    int maxSize, petTextSize;

    if (height <= 25)
    {
        maxSize = 17; // min size == 17  -->  "| flightHeight : aa |"
        petTextSize = 1;
    }
    else
    {
        maxSize = 28; // min size == 28  -->  "| flightHeight : aaaaaaaaaaaaa |"
        petTextSize = 2;
    }

    for (auto x : info)
    {
        if (x.size() > maxSize)
        {
            maxSize = x.size();
        }
    }

    vector<string> petText = PetText(petTextSize);
    vector<string> productStyle;
    string temp;

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // pet text
    int petTextLength = petText[0].size();
    int numberOfSpace = (maxSize + 2 - petTextLength) / 2;
    for (auto x : petText)
    {
        temp += "|";
        for (int i = 0; i < numberOfSpace + (maxSize + 2 - petTextLength) % 2; i++)
        {
            temp += " ";
        }
        temp += x;
        for (int i = 0; i < numberOfSpace; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // info
    int infoLength;
    for (auto x : info)
    {
        infoLength = x.size();
        temp += "| ";
        temp += x;
        for (int i = 0; i < maxSize - infoLength + 1; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    return productStyle;
}

vector<string> Fish::createProductStyleForManaging()
{
    short width, height;
    GetWidthHeight(&width, &height);

    string _petId = to_string(getId());
    string _name = getName();
    string _age = to_string(getAge());
    string _price = normalizeFloatString(to_string(getPrice())) + " $";
    string _breed = getBreed();
    string _color = enum_to_string<Colors>(getColor());
    string _status = (getStatus()) ? "Accepted" : "Pending...";
    string _sellerName = getSellerName();
    string _sellerId = to_string(getSellerId());
    string _species = enum_to_string<PetSpecies>(getSpecies());
    string _rating = normalizeFloatString(to_string(getRating()));
    string tempRatings = "Rated By ";
    tempRatings += to_string(getRatings());
    tempRatings += " Users";
    string _ratings = tempRatings;
    string _water = enum_to_string<WaterType>(water);
    string _aquariumSize = normalizeFloatString(to_string(aquariumSize)) + " cubic meters";
    string _swimmingSpeed = normalizeFloatString(to_string(swimmingSpeed)) + " " + enum_to_string<SpeedUnitType>(speedUnit);

    vector<string> info = {
        "Pet ID         : " + _petId,
        "Name           : " + _name,
        "Age            : " + _age,
        "Price          : " + _price,
        "Breed          : " + _breed,
        "Color          : " + _color,
        "Status         : " + _status,
        "Seller Name    : " + _sellerName,
        "Seller ID      : " + _sellerId,
        "Species        : " + _species,
        "Rating         : " + _rating,
        "Ratings        : " + _ratings,
        "Water          : " + _water,
        "Aquarium Size  : " + _aquariumSize,
        "Swimming Speed : " + _swimmingSpeed};

    int maxSize, petTextSize;

    if (height <= 25)
    {
        maxSize = 17; // min size == 17  -->  "| flightHeight : aa |"
        petTextSize = 1;
    }
    else
    {
        maxSize = 28; // min size == 28  -->  "| flightHeight : aaaaaaaaaaaaa |"
        petTextSize = 2;
    }

    for (auto x : info)
    {
        if (x.size() > maxSize)
        {
            maxSize = x.size();
        }
    }

    vector<string> petText = PetText(petTextSize);
    vector<string> productStyle;
    string temp;

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // pet text
    int petTextLength = petText[0].size();
    int numberOfSpace = (maxSize + 2 - petTextLength) / 2;
    for (auto x : petText)
    {
        temp += "|";
        for (int i = 0; i < numberOfSpace + (maxSize + 2 - petTextLength) % 2; i++)
        {
            temp += " ";
        }
        temp += x;
        for (int i = 0; i < numberOfSpace; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // info
    int infoLength;
    for (auto x : info)
    {
        infoLength = x.size();
        temp += "| ";
        temp += x;
        for (int i = 0; i < maxSize - infoLength + 1; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    return productStyle;
}

void Fish::showInfo()
{
    vector<vector<string>> pet = {this->createProductStyleForManaging()};

    PrintBoxesInCenter("", "Press [Enter] to continue", pet);
    cin.get();
}

void Fish::changeInfo()
{
    PrintVecStr(CreateTitle("Pet Info Edit Page"), Vertical);
    cout << "Which information do you want to edit:\n\n";

    cout << "Pet ID: " << getId();
    cout << endl;
    cout << "Pet Species: " << enum_to_string<PetSpecies>(getSpecies());
    cout << endl;
    cout << "Seller Name: " << getSellerName();
    cout << endl;
    cout << "Seller ID: " << getSellerId();
    cout << endl;

    string _name;
    int _age;
    float _price;
    string _breed;
    Colors _color;
    WaterType _water;
    float _aquariumSize;
    float _swimmingSpeed;

    string text_name = getName();
    string text_age = to_string(getAge());
    string text_price = normalizeFloatString(to_string(getPrice())) + " $";
    string text_breed = getBreed();
    string text_color = enum_to_string<Colors>(getColor());
    string text_water = enum_to_string<WaterType>(water);
    string text_aquariumSize = normalizeFloatString(to_string(aquariumSize)) + " cubic meters";
    SpeedUnitType _speedUnit = speedUnit;
    string text_swimmingSpeed = normalizeFloatString(to_string(swimmingSpeed)) + " " + enum_to_string<SpeedUnitType>(_speedUnit);

    vector<string> optionsMenu{
        "Name: " + text_name,
        "Age: " + text_age,
        "Price: " + text_price,
        "Breed: " + text_breed,
        "Color: " + text_color,
        "Water Type: " + text_water,
        "Aquarium Size: " + text_aquariumSize,
        "Swimming Speed: " + text_swimmingSpeed};

    int selected = SelectMenu("", optionsMenu);

    bool areAllValuesOk = false;

    switch (selected)
    {
    case 0:
        cout << "Pet's Name : ";
        getline(cin, _name);
        break;
    case 1:
        cout << "Pet's Age [0-120]: ";
        cin >> _age;
        cin.get();
        break;
    case 2:
        cout << "Pet's Price: ";
        cin >> _price;
        cin.get();
        break;
    case 3:
        cout << "Pet's Breed: ";
        getline(cin, _breed);
        break;
    case 4:
        _color = SelectOption<Colors>("Pet's Color: ");
        break;
    case 5:
        _water = SelectOption<WaterType>("What kind of water do fish Need: ");
        break;
    case 6:
        cout << "How many cubic meters should the aquarium have [0.001-10]: ";
        cin >> _aquariumSize;
        cin.get();
        break;
    case 7:
        _speedUnit = SelectOption<SpeedUnitType>("First, choose the unit of swimming speed: ");

        if (_speedUnit == SpeedUnitType::mps)
            cout << "How fast can it swim [0-50]: ";
        if (_speedUnit == SpeedUnitType::mpmin)
            cout << "How fast can it swim [0-3,000]: ";
        if (_speedUnit == SpeedUnitType::mph)
            cout << "How fast can it swim [0-180,000]: ";
        if (_speedUnit == SpeedUnitType::kmph)
            cout << "How fast can it swim [0-180]: ";
        cin >> _swimmingSpeed;
        cin.get();
        break;

    default:
        break;
    }

    while (!areAllValuesOk)
    {
        try
        {
            switch (selected)
            {
            case 0:
                setName(_name);
                break;
            case 1:
                setAge(_age);
                break;
            case 2:
                setPrice(_price);
                break;
            case 3:
                setBreed(_breed);
                break;
            case 4:
                setColor(_color);
                break;
            case 5:
                setWater(_water);
                break;
            case 6:
                setAquariumSize(_aquariumSize);
                break;
            case 7:
                setSwimmingSpeed(_swimmingSpeed, _speedUnit);
                break;

            default:
                break;
            }

            LoadingAnimation();

            cout << "\nChanges saved successfully...";
            Sleep(700);

            setStatus(false);
            areAllValuesOk = true;
        }
        catch (const setValuesException &e)
        {
            LoadingAnimation();

            cout << endl;
            cerr << e.what() << endl;
            cout << "Plese enter Pet's " << enum_to_string<VariablesToValidate>(e.getVariableName()) << " again: ";
            if (e.checkVariableName(VariablesToValidate::Age))
            {
                cin >> _age;
                cin.get();
                setAge(_age);
            }
            else if (e.checkVariableName(VariablesToValidate::Price))
            {
                cin >> _price;
                cin.get();
                setPrice(_price);
            }
            else if (e.checkVariableName(VariablesToValidate::AquariumSize))
            {
                cin >> _aquariumSize;
                cin.get();
                setAquariumSize(_aquariumSize);
            }
            else if (e.checkVariableName(VariablesToValidate::SwimmingSpeed))
            {
                cin >> _swimmingSpeed;
                cin.get();
                setSwimmingSpeed(_swimmingSpeed, _speedUnit);
            }
        }
    }

    updateInfoThisPetInBinaryFile();
}

//========================= Pony Class Functions

// temp objects
Pony::Pony() {}

Pony::Pony(string _name, int _age, float _price, string _breed, Colors _color, bool _status, string _sellerName, int _sellerId, float _runningSpeed, SpeedUnitType _speedUnit, Colors _maneColor, float _energyLevel)
    : Pet(_name, _age, _price, _breed, _color, _status, _sellerName, _sellerId, PetSpecies::Pony)
{
    bool areAllValuesOk = false;

    while (!areAllValuesOk)
    {
        try
        {
            setRunningSpeed(_runningSpeed, _speedUnit);
            setManeColor(_maneColor);
            setEnergyLevel(_energyLevel);

            areAllValuesOk = true;
        }
        catch (const setValuesException &e)
        {
            cout << endl;
            cerr << e.what() << endl;
            cout << "Plese enter Pet's " << enum_to_string<VariablesToValidate>(e.getVariableName()) << " again: ";
            if (e.checkVariableName(VariablesToValidate::RunningSpeed))
            {
                cin >> _runningSpeed;
                cin.get();
            }
            else if (e.checkVariableName(VariablesToValidate::EnergyLevel))
            {
                cin >> _energyLevel;
                cin.get();
            }
        }
    }
}

// for load info
Pony::Pony(int _petId, string _name, int _age, float _price, string _breed, Colors _color, bool _status, string _sellerName, int _sellerId, float _rating, int _ratings, float _runningSpeed, SpeedUnitType _speedUnit, Colors _maneColor, float _energyLevel)
    : Pet(_petId, _name, _age, _price, _breed, _color, _status, _sellerName, _sellerId, PetSpecies::Pony, _rating, _ratings), runningSpeed(_runningSpeed), speedUnit(_speedUnit), maneColor(_maneColor), energyLevel(_energyLevel) {}

void Pony::setRunningSpeed(float _runningSpeed, SpeedUnitType _speedUnit)
{
    if (_speedUnit == SpeedUnitType::mps)
        if (_runningSpeed < 1 || _runningSpeed > 12.5)
            throw setValuesException("The pony's running speed must be between 1 and 12.5 meters per second... ", VariablesToValidate::RunningSpeed);
    if (_speedUnit == SpeedUnitType::mpmin)
        if (_runningSpeed < 60 || _runningSpeed > 750)
            throw setValuesException("The pony's running speed must be between 60 and 750 meters per minute... ", VariablesToValidate::RunningSpeed);
    if (_speedUnit == SpeedUnitType::mph)
        if (_runningSpeed < 3600 || _runningSpeed > 45000)
            throw setValuesException("The pony's running speed must be between 3,600 and 45,000 meters per hour... ", VariablesToValidate::RunningSpeed);
    if (_speedUnit == SpeedUnitType::kmph)
        if (_runningSpeed < 3.6 || _runningSpeed > 45)
            throw setValuesException("The pony's running speed must be between 3.6 and 45 kilometers per hour... ", VariablesToValidate::RunningSpeed);

    runningSpeed = _runningSpeed;
    speedUnit = _speedUnit;
}

void Pony::setManeColor(Colors _maneColor)
{
    maneColor = _maneColor;
}

void Pony::setEnergyLevel(float _energyLevel)
{
    if (_energyLevel < 0 || _energyLevel > 10)
        throw setValuesException("The pony's energy level must be between 0 and 10... ", VariablesToValidate::EnergyLevel);

    energyLevel = _energyLevel;
}

float Pony::getRunningSpeed() const { return runningSpeed; }

SpeedUnitType Pony::getUnitOfSpeed() const { return speedUnit; }

Colors Pony::getManeColor() const { return maneColor; }

float Pony::getEnergyLevel() const { return energyLevel; }

void Pony::saveInfoInBinaryFile()
{
    int _petId = getId();
    int sizeStr_name = getName().size();
    string _name = getName();
    int _age = getAge();
    float _price = getPrice();
    int sizeStr_breed = getBreed().size();
    string _breed = getBreed();
    Colors _color = getColor();
    bool _status = getStatus();
    int sizeStr_sellerName = getSellerName().size();
    string _sellerName = getSellerName();
    int _sellerId = getSellerId();
    PetSpecies _species = getSpecies();
    float _rating = getRating();
    int _ratings = getRatings();

    float _runningSpeed = runningSpeed;
    SpeedUnitType _speedUnit = speedUnit;
    Colors _maneColor = maneColor;
    float _energyLevel = energyLevel;

    fstream file(PathPet, ios::app | ios::binary);

    file.write(reinterpret_cast<char *>(&_petId), sizeof(_petId));

    file.write(reinterpret_cast<char *>(&sizeStr_name), sizeof(sizeStr_name));
    file.write(_name.data(), sizeStr_name);

    file.write(reinterpret_cast<char *>(&_age), sizeof(_age));
    file.write(reinterpret_cast<char *>(&_price), sizeof(_price));

    file.write(reinterpret_cast<char *>(&sizeStr_breed), sizeof(sizeStr_breed));
    file.write(_breed.data(), sizeStr_breed);

    file.write(reinterpret_cast<char *>(&_color), sizeof(_color));
    file.write(reinterpret_cast<char *>(&_status), sizeof(_status));

    file.write(reinterpret_cast<char *>(&sizeStr_sellerName), sizeof(sizeStr_sellerName));
    file.write(_sellerName.data(), sizeStr_sellerName);

    file.write(reinterpret_cast<char *>(&_sellerId), sizeof(_sellerId));
    file.write(reinterpret_cast<char *>(&_species), sizeof(_species));
    file.write(reinterpret_cast<char *>(&_rating), sizeof(_rating));
    file.write(reinterpret_cast<char *>(&_ratings), sizeof(_ratings));
    file.write(reinterpret_cast<char *>(&_runningSpeed), sizeof(_runningSpeed));
    file.write(reinterpret_cast<char *>(&_speedUnit), sizeof(_speedUnit));
    file.write(reinterpret_cast<char *>(&_maneColor), sizeof(_maneColor));
    file.write(reinterpret_cast<char *>(&_energyLevel), sizeof(_energyLevel));

    file.close();
}

void Pony::updateInfoThisPetInBinaryFile()
{
    vector<Pet *> pets = Pet::loadInfoAllPet();
    int index;
    IsThereThisInfo<int, PetInfo>(getId(), PetInfo::PetId, &index);
    if (index != -1)
    {
        Pony *temp = dynamic_cast<Pony *>(pets[index]);

        temp->setName(getName());
        temp->setAge(getAge());
        temp->setPrice(getPrice());
        temp->setBreed(getBreed());
        temp->setColor(getColor());
        temp->setStatus(getStatus());
        temp->setSellerName(getSellerName());
        temp->setSellerId(getSellerId());
        temp->setRating(getRating(), 1);
        temp->setRatings(getRatings());
        temp->runningSpeed = runningSpeed;
        temp->speedUnit = speedUnit;
        temp->maneColor = maneColor;
        temp->energyLevel = energyLevel;

        pets[index] = temp;

        Pet::updateAllPetInBinaryFile(pets);
    }
}

vector<string> Pony::createProductStyle()
{
    short width, height;
    GetWidthHeight(&width, &height);

    string _petId = to_string(getId());
    string _name = getName();
    string _age = to_string(getAge());
    string _price = normalizeFloatString(to_string(getPrice())) + " $";
    string _breed = getBreed();
    string _color = enum_to_string<Colors>(getColor());
    string _sellerName = getSellerName();
    string _species = enum_to_string<PetSpecies>(getSpecies());
    string _rating = normalizeFloatString(to_string(getRating()));
    string tempRatings = "Rated By ";
    tempRatings += to_string(getRatings());
    tempRatings += " Users";
    string _ratings = tempRatings;
    string _runningSpeed = normalizeFloatString(to_string(runningSpeed)) + " " + enum_to_string<SpeedUnitType>(speedUnit);
    string _maneColor = enum_to_string<Colors>(maneColor);
    string _energyLevel = normalizeFloatString(to_string(energyLevel));

    vector<string> info = {
        "Pet ID        : " + _petId,
        "Name          : " + _name,
        "Age           : " + _age,
        "Price         : " + _price,
        "Breed         : " + _breed,
        "Color         : " + _color,
        "Seller Name   : " + _sellerName,
        "Species       : " + _species,
        "Rating        : " + _rating,
        "Ratings       : " + _ratings,
        "Running Speed : " + _runningSpeed,
        "Mane Color    : " + _maneColor,
        "Energy Level  : " + _energyLevel};

    int maxSize, petTextSize;

    if (height <= 25)
    {
        maxSize = 17; // min size == 17  -->  "| flightHeight : aa |"
        petTextSize = 1;
    }
    else
    {
        maxSize = 28; // min size == 28  -->  "| flightHeight : aaaaaaaaaaaaa |"
        petTextSize = 2;
    }

    for (auto x : info)
    {
        if (x.size() > maxSize)
        {
            maxSize = x.size();
        }
    }

    vector<string> petText = PetText(petTextSize);
    vector<string> productStyle;
    string temp;

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // pet text
    int petTextLength = petText[0].size();
    int numberOfSpace = (maxSize + 2 - petTextLength) / 2;
    for (auto x : petText)
    {
        temp += "|";
        for (int i = 0; i < numberOfSpace + (maxSize + 2 - petTextLength) % 2; i++)
        {
            temp += " ";
        }
        temp += x;
        for (int i = 0; i < numberOfSpace; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // info
    int infoLength;
    for (auto x : info)
    {
        infoLength = x.size();
        temp += "| ";
        temp += x;
        for (int i = 0; i < maxSize - infoLength + 1; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    return productStyle;
}

vector<string> Pony::createProductStyleForManaging()
{
    short width, height;
    GetWidthHeight(&width, &height);

    string _petId = to_string(getId());
    string _name = getName();
    string _age = to_string(getAge());
    string _price = normalizeFloatString(to_string(getPrice())) + " $";
    string _breed = getBreed();
    string _color = enum_to_string<Colors>(getColor());
    string _status = (getStatus()) ? "Accepted" : "Pending...";
    string _sellerName = getSellerName();
    string _sellerId = to_string(getSellerId());
    string _species = enum_to_string<PetSpecies>(getSpecies());
    string _rating = normalizeFloatString(to_string(getRating()));
    string tempRatings = "Rated By ";
    tempRatings += to_string(getRatings());
    tempRatings += " Users";
    string _ratings = tempRatings;
    string _runningSpeed = normalizeFloatString(to_string(runningSpeed)) + " " + enum_to_string<SpeedUnitType>(speedUnit);
    string _maneColor = enum_to_string<Colors>(maneColor);
    string _energyLevel = normalizeFloatString(to_string(energyLevel));

    vector<string> info = {
        "Pet ID        : " + _petId,
        "Name          : " + _name,
        "Age           : " + _age,
        "Price         : " + _price,
        "Breed         : " + _breed,
        "Color         : " + _color,
        "Status        : " + _status,
        "Seller Name   : " + _sellerName,
        "Seller ID     : " + _sellerId,
        "Species       : " + _species,
        "Rating        : " + _rating,
        "Ratings       : " + _ratings,
        "Running Speed : " + _runningSpeed,
        "Mane Color    : " + _maneColor,
        "Energy Level  : " + _energyLevel};

    int maxSize, petTextSize;

    if (height <= 25)
    {
        maxSize = 17; // min size == 17  -->  "| flightHeight : aa |"
        petTextSize = 1;
    }
    else
    {
        maxSize = 28; // min size == 28  -->  "| flightHeight : aaaaaaaaaaaaa |"
        petTextSize = 2;
    }

    for (auto x : info)
    {
        if (x.size() > maxSize)
        {
            maxSize = x.size();
        }
    }

    vector<string> petText = PetText(petTextSize);
    vector<string> productStyle;
    string temp;

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // pet text
    int petTextLength = petText[0].size();
    int numberOfSpace = (maxSize + 2 - petTextLength) / 2;
    for (auto x : petText)
    {
        temp += "|";
        for (int i = 0; i < numberOfSpace + (maxSize + 2 - petTextLength) % 2; i++)
        {
            temp += " ";
        }
        temp += x;
        for (int i = 0; i < numberOfSpace; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // info
    int infoLength;
    for (auto x : info)
    {
        infoLength = x.size();
        temp += "| ";
        temp += x;
        for (int i = 0; i < maxSize - infoLength + 1; i++)
        {
            temp += " ";
        }
        temp += "|";
        productStyle.push_back(temp);
        temp.clear();
    }

    // line (|      |)
    temp += "|";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += " ";
    }
    temp += "|";
    productStyle.push_back(temp);
    temp.clear();

    // line (+------+)
    temp += "+";
    for (int i = 0; i < maxSize + 2; i++)
    {
        temp += "-";
    }
    temp += "+";
    productStyle.push_back(temp);
    temp.clear();

    return productStyle;
}

void Pony::showInfo()
{
    vector<vector<string>> pet = {this->createProductStyleForManaging()};

    PrintBoxesInCenter("", "Press [Enter] to continue", pet);
    cin.get();
}

void Pony::changeInfo()
{
    PrintVecStr(CreateTitle("Pet Info Edit Page"), Vertical);
    cout << "Which information do you want to edit:\n\n";

    cout << "Pet ID: " << getId();
    cout << endl;
    cout << "Pet Species: " << enum_to_string<PetSpecies>(getSpecies());
    cout << endl;
    cout << "Seller Name: " << getSellerName();
    cout << endl;
    cout << "Seller ID: " << getSellerId();
    cout << endl;

    string _name;
    int _age;
    float _price;
    string _breed;
    Colors _color;
    float _runningSpeed;
    Colors _maneColor;
    float _energyLevel;

    string text_name = getName();
    string text_age = to_string(getAge());
    string text_price = normalizeFloatString(to_string(getPrice())) + " $";
    string text_breed = getBreed();
    string text_color = enum_to_string<Colors>(getColor());
    SpeedUnitType _speedUnit = speedUnit;
    string text_runningSpeed = normalizeFloatString(to_string(runningSpeed)) + " " + enum_to_string<SpeedUnitType>(_speedUnit);
    string text_maneColor = enum_to_string<Colors>(maneColor);
    string text_energyLevel = normalizeFloatString(to_string(energyLevel));

    vector<string> optionsMenu{
        "Name: " + text_name,
        "Age: " + text_age,
        "Price: " + text_price,
        "Breed: " + text_breed,
        "Color: " + text_color,
        "Running Speed: " + text_runningSpeed,
        "Mane Color: " + text_maneColor,
        "Energy Level: " + text_energyLevel};

    int selected = SelectMenu("", optionsMenu);

    bool areAllValuesOk = false;

    switch (selected)
    {
    case 0:
        cout << "Pet's Name: ";
        getline(cin, _name);
        break;
    case 1:
        cout << "Pet's Age [0-120]: ";
        cin >> _age;
        cin.get();
        break;
    case 2:
        cout << "Pet's Price: ";
        cin >> _price;
        cin.get();
        break;
    case 3:
        cout << "Pet's Breed: ";
        getline(cin, _breed);
        break;
    case 4:
        _color = SelectOption<Colors>("Pet's Color: ");
        break;
    case 5:
        _speedUnit = SelectOption<SpeedUnitType>("First, select the running speed unit: ");

        if (_speedUnit == SpeedUnitType::mps)
            cout << "How fast can it run [0-50]: ";
        if (_speedUnit == SpeedUnitType::mpmin)
            cout << "How fast can it run [0-3,000]: ";
        if (_speedUnit == SpeedUnitType::mph)
            cout << "How fast can it run [0-180,000]: ";
        if (_speedUnit == SpeedUnitType::kmph)
            cout << "How fast can it run [0-180]: ";
        cin >> _runningSpeed;
        cin.get();
        break;
    case 6:
        _maneColor = SelectOption<Colors>("Choose the color of pony's mane: ");
        break;
    case 7:
        cout << "How much energy does it have [0-10]: ";
        cin >> _energyLevel;
        cin.get();
        break;

    default:
        break;
    }

    while (!areAllValuesOk)
    {
        try
        {
            switch (selected)
            {
            case 0:
                setName(_name);
                break;
            case 1:
                setAge(_age);
                break;
            case 2:
                setPrice(_price);
                break;
            case 3:
                setBreed(_breed);
                break;
            case 4:
                setColor(_color);
                break;
            case 5:
                setRunningSpeed(_runningSpeed, _speedUnit);
                break;
            case 6:
                setManeColor(_maneColor);
                break;
            case 7:
                setEnergyLevel(_energyLevel);
                break;

            default:
                break;
            }

            LoadingAnimation();

            cout << "\nChanges saved successfully...";
            Sleep(700);

            setStatus(false);
            areAllValuesOk = true;
        }
        catch (const setValuesException &e)
        {
            LoadingAnimation();

            cout << endl;
            cerr << e.what() << endl;
            cout << "Plese enter Pet's " << enum_to_string<VariablesToValidate>(e.getVariableName()) << " again: ";
            if (e.checkVariableName(VariablesToValidate::Age))
            {
                cin >> _age;
                cin.get();
                setAge(_age);
            }
            else if (e.checkVariableName(VariablesToValidate::Price))
            {
                cin >> _price;
                cin.get();
                setPrice(_price);
            }
            else if (e.checkVariableName(VariablesToValidate::RunningSpeed))
            {
                cin >> _runningSpeed;
                cin.get();
                setRunningSpeed(_runningSpeed, _speedUnit);
            }
            else if (e.checkVariableName(VariablesToValidate::EnergyLevel))
            {
                cin >> _energyLevel;
                cin.get();
                setEnergyLevel(_energyLevel);
            }
        }
    }

    updateInfoThisPetInBinaryFile();
}
