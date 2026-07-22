#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;

//=========================
// enum & struct
//=========================

enum class AccountAction
{
    Signup,
    Login,
    Logout,
    DeleteAccount
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

enum class UserType
{
    Admin,
    Seller,
    Buyer
};

enum class ManagingOption
{
    EditInfo,
    DeleteUser,
    SendGift
};

enum class PetSpecies
{
    Bird,
    Fish,
    Pony
};

enum class SearchingItems
{
    Bird,
    Fish,
    Pony,
    All
};

enum class VoiceType
{
    Chrip,   // jick jick
    Coo,     // ghoo ghoo
    screech, // jigh
    Whistle, // soot
    Mimic,   // taghlid seda
    Sing     // avaz
};

enum class WaterType
{
    FreshWater,
    SaltWater
};

enum class SpeedUnitType
{
    mps,   // meters per second
    mpmin, // meters per minute
    mph,   // meters per hour
    kmph   // kilometers per hour
};

enum class Colors
{
    Red,
    Blue,
    Yellow,
    Green,
    Orange,
    Purple,
    Pink,
    Brown,
    Black,
    White,
    Gray
};

//=========================
// main class
//=========================

class Pet;

class Account
{
    float balance;

public:
    Account();
    Account(float);

    void setBalance(float);

    float getBalance() const;

    string showBalance();
    void deposit(int);
    void withdraw(int);
    void transfer(int, int);
    bool purchase(Pet *, int);
    static void saveTransaction(const TransactionInfo &);
    static vector<TransactionInfo> loadAllTransaction();
    static void updateThisTransaction(const TransactionInfo &);
    static void updateAllTransactionInBinaryFile(const vector<TransactionInfo> &);
    void transactionHistory(vector<TransactionInfo>);
};

class User
{
    const int id;
    string name;
    string username;
    string password;
    string phoneNumber;
    UserType type;

protected:
    Account userAccount;

public:
    User(string, string, string, string, UserType);
    User(int, string, string, string, string, UserType, float);

    void setType(UserType);
    void setName(string);
    void setUsername(string);
    void setPassword(string);
    void setPhoneNumber(string);
    void setBalance(float);

    int getId() const;
    UserType getType() const;
    string getName() const;
    string getUsername() const;
    string getPassword() const;
    string getPhoneNumber() const;
    float getBalance() const;

    static User *signup();
    static User *login();
    virtual void deleteAccount();
    void changeInfo();
    void manageWallet();

    void saveInBinaryFile();
    static vector<User *> loadInfoAllUser();
    static User *loadInfoOneUser(int, int);
    static void updateAllUserInBinaryFile(vector<User *>);
    void updateInfoThisUserInBinaryFile();
    bool isDuplicateUsername(string);

    vector<string> createProfileStyle();
    void showProfile();
    virtual void showProducts() = 0;
};

class Admin : public User
{
public:
    Admin(string, string, string, string, UserType);
    Admin(int, string, string, string, string, UserType, float);

    void showProducts() override; // all products
    void acceptProduct();
    void deleteProduct();
    void discountOnProducts(vector<Pet *>, float);
    void allSalesHistory();
    void manageUser(User *, ManagingOption);
};

class Seller : public User
{
public:
    Seller(string, string, string, string, UserType);
    Seller(int, string, string, string, string, UserType, float);

    void deleteAccount() override;

    void addProduct();
    void showProducts() override; // seller products
    void editProduct();
    void deleteProduct();
    void salesHistory();
};

class Buyer : public User
{
public:
    Buyer(string, string, string, string, UserType);
    Buyer(int, string, string, string, string, UserType, float);

    vector<Pet *> searchProduct(SearchingItems);

    void showProducts() override; // accepted products
    void ratingPet(Pet *, float);
    bool buying(vector<Pet *>, int);
    void purchaseHistory();
};

class Pet
{
    const int petId;
    string name;
    int age;
    float price;
    string breed;
    Colors color;
    bool status;
    string sellerName;
    int sellerId;
    PetSpecies species;
    float rating;
    int ratings; // Number of people who rated

public:
    Pet();
    Pet(string, int, float, string, Colors, bool, string, int, PetSpecies);
    Pet(int, string, int, float, string, Colors, bool, string, int, PetSpecies, float, int);

    void setName(string);
    void setAge(int);
    void setPrice(float);
    void setBreed(string);
    void setColor(Colors);
    void setStatus(bool);
    void setSellerName(string);
    void setSellerId(int);
    void setSpecies(PetSpecies);
    void setRating(float = 0, int = 0);
    void setRatings(int = 0);

    int getId() const;
    string getName() const;
    int getAge() const;
    float getPrice() const;
    string getBreed() const;
    Colors getColor() const;
    bool getStatus() const;
    string getSellerName() const;
    int getSellerId() const;
    PetSpecies getSpecies() const;
    float getRating() const;
    int getRatings() const;

    virtual void saveInfoInBinaryFile() = 0;
    virtual void updateInfoThisPetInBinaryFile() = 0;
    virtual vector<string> createProductStyle() = 0;
    virtual vector<string> createProductStyleForManaging() = 0;
    virtual void showInfo() = 0;
    virtual void changeInfo() = 0;

    static Pet *loadInfoOnePet(int, int);
    static vector<Pet *> loadInfoAllPet();
    static void updateAllPetInBinaryFile(vector<Pet *>);
    void deletePet();
    void calculateRating(float);
};

class Bird : public Pet
{
    float flightHeight;
    VoiceType sound;
    float iq;

public:
    Bird();
    Bird(string, int, float, string, Colors, bool, string, int, float, VoiceType, float);
    Bird(int, string, int, float, string, Colors, bool, string, int, float, int, float, VoiceType, float);

    void setFlightHeight(float);
    void setSound(VoiceType);
    void setIq(float);

    float getFlightHeight() const;
    VoiceType getSound() const;
    float getIq() const;

    void saveInfoInBinaryFile() override;
    void updateInfoThisPetInBinaryFile() override;
    vector<string> createProductStyle() override;
    vector<string> createProductStyleForManaging() override;
    void showInfo() override;
    void changeInfo() override;
};

class Fish : public Pet
{
    WaterType water;
    float aquariumSize;
    float swimmingSpeed;
    SpeedUnitType speedUnit;

public:
    Fish();
    Fish(string, int, float, string, Colors, bool, string, int, WaterType, float, float, SpeedUnitType);
    Fish(int, string, int, float, string, Colors, bool, string, int, float, int, WaterType, float, float, SpeedUnitType);

    void setWater(WaterType);
    void setAquariumSize(float);
    void setSwimmingSpeed(float, SpeedUnitType);

    WaterType getWater() const;
    float getAquariumSize() const;
    float getSwimmingSpeed() const;
    SpeedUnitType getUnitOfSpeed() const;

    void saveInfoInBinaryFile() override;
    void updateInfoThisPetInBinaryFile() override;
    vector<string> createProductStyle() override;
    vector<string> createProductStyleForManaging() override;
    void showInfo() override;
    void changeInfo() override;
};

class Pony : public Pet
{
    float runningSpeed;
    SpeedUnitType speedUnit;
    Colors maneColor;
    float energyLevel;

public:
    Pony();
    Pony(string, int, float, string, Colors, bool, string, int, float, SpeedUnitType, Colors, float);
    Pony(int, string, int, float, string, Colors, bool, string, int, float, int, float, SpeedUnitType, Colors, float);

    void setRunningSpeed(float, SpeedUnitType);
    void setManeColor(Colors);
    void setEnergyLevel(float);

    float getRunningSpeed() const;
    SpeedUnitType getUnitOfSpeed() const;
    Colors getManeColor() const;
    float getEnergyLevel() const;

    void saveInfoInBinaryFile() override;
    void updateInfoThisPetInBinaryFile() override;
    vector<string> createProductStyle() override;
    vector<string> createProductStyleForManaging() override;
    void showInfo() override;
    void changeInfo() override;
};
