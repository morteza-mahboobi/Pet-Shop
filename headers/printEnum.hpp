#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include "myClass.hpp"
#include "myException.hpp"
using std::is_same_v;
using std::string;
using std::vector;

template <typename X>
string enum_to_string(X enumValue)
{
    if constexpr (is_same_v<X, AccountAction>)
    {
        switch (enumValue)
        {
        case AccountAction::Signup:
            return "Signup";
        case AccountAction::Login:
            return "Login";
        case AccountAction::Logout:
            return "Logout";
        case AccountAction::DeleteAccount:
            return "Delete Account";
        }

        return "\nUnknown AccountAction...\n";
    }
    else if constexpr (is_same_v<X, TransactionType>)
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
    else if constexpr (is_same_v<X, UserType>)
    {
        switch (enumValue)
        {
        case UserType::Admin:
            return "Admin";
        case UserType::Seller:
            return "Seller";
        case UserType::Buyer:
            return "Buyer";
        }

        return "\nUnknown UserType...\n";
    }
    else if constexpr (is_same_v<X, ManagingOption>)
    {
        switch (enumValue)
        {
        case ManagingOption::EditInfo:
            return "Edit Info";
        case ManagingOption::DeleteUser:
            return "Delete User";
        case ManagingOption::SendGift:
            return "Send Gift";
        }

        return "\nUnknown ManagingOption...\n";
    }
    else if constexpr (is_same_v<X, PetSpecies>)
    {
        switch (enumValue)
        {
        case PetSpecies::Bird:
            return "Bird";
        case PetSpecies::Fish:
            return "Fish";
        case PetSpecies::Pony:
            return "Pony";
        }

        return "\nUnknown PetSpecies...\n";
    }
    else if constexpr (is_same_v<X, SearchingItems>)
    {
        switch (enumValue)
        {
        case SearchingItems::Bird:
            return "Bird";
        case SearchingItems::Fish:
            return "Fish";
        case SearchingItems::Pony:
            return "Pony";
        case SearchingItems::All:
            return "All";
        }

        return "\nUnknown SearchingItems...\n";
    }
    else if constexpr (is_same_v<X, VoiceType>)
    {
        switch (enumValue)
        {
        case VoiceType::Chrip:
            return "Chrip";
        case VoiceType::Coo:
            return "Coo";
        case VoiceType::screech:
            return "screech";
        case VoiceType::Whistle:
            return "Whistle";
        case VoiceType::Mimic:
            return "Mimic";
        case VoiceType::Sing:
            return "Sing";
        }

        return "\nUnknown VoiceType...\n";
    }
    else if constexpr (is_same_v<X, WaterType>)
    {
        switch (enumValue)
        {
        case WaterType::FreshWater:
            return "Fresh Water";
        case WaterType::SaltWater:
            return "Salt Water";
        }

        return "\nUnknown WaterType...\n";
    }
    else if constexpr (is_same_v<X, SpeedUnitType>)
    {
        switch (enumValue)
        {
        case SpeedUnitType::mps:
            return "m/s";
        case SpeedUnitType::mpmin:
            return "m/min";
        case SpeedUnitType::mph:
            return "m/h";
        case SpeedUnitType::kmph:
            return "km/h";
        }

        return "\nUnknown SpeedUnitType...\n";
    }
    else if constexpr (is_same_v<X, Colors>)
    {
        switch (enumValue)
        {
        case Colors::Red:
            return "Red";
        case Colors::Blue:
            return "Blue";
        case Colors::Yellow:
            return "Yellow";
        case Colors::Green:
            return "Green";
        case Colors::Orange:
            return "Orange";
        case Colors::Purple:
            return "Purple";
        case Colors::Pink:
            return "Pink";
        case Colors::Brown:
            return "Brown";
        case Colors::Black:
            return "Black";
        case Colors::White:
            return "White";
        case Colors::Gray:
            return "Gray";
        }

        return "\nUnknown Colors...\n";
    }
    else if constexpr (is_same_v<X, VariablesToValidate>)
    {
        switch (enumValue)
        {
        case VariablesToValidate::Balance:
            return "Balance";
        case VariablesToValidate::Username:
            return "Username";
        case VariablesToValidate::Password:
            return "Password";
        case VariablesToValidate::PhoneNumber:
            return "Phone Number";
        case VariablesToValidate::Age:
            return "Age";
        case VariablesToValidate::Price:
            return "Price";
        case VariablesToValidate::Rating:
            return "Rating";
        case VariablesToValidate::Ratings:
            return "Ratings";
        case VariablesToValidate::FlightHeight:
            return "Flight Height";
        case VariablesToValidate::Iq:
            return "IQ";
        case VariablesToValidate::AquariumSize:
            return "Aquarium Size";
        case VariablesToValidate::SwimmingSpeed:
            return "Swimming Speed";
        case VariablesToValidate::RunningSpeed:
            return "Running Speed";
        case VariablesToValidate::EnergyLevel:
            return "Energy Level";
        }

        return "\nUnknown VariablesToValidate...\n";
    }
}

template <typename X>
vector<string> enumMember()
{
    vector<string> members;

    if constexpr (is_same_v<X, AccountAction>)
    {
        members.push_back("Signup");
        members.push_back("Login");
        members.push_back("Logout");
        members.push_back("Delete Account");
    }
    else if constexpr (is_same_v<X, TransactionType>)
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
    else if constexpr (is_same_v<X, UserType>)
    {
        members.push_back("Admin");
        members.push_back("Seller");
        members.push_back("Buyer");
    }
    else if constexpr (is_same_v<X, ManagingOption>)
    {
        members.push_back("Edit Info");
        members.push_back("Delete User");
        members.push_back("Send Gift");
    }
    else if constexpr (is_same_v<X, PetSpecies>)
    {
        members.push_back("Bird");
        members.push_back("Fish");
        members.push_back("Pony");
    }
    else if constexpr (is_same_v<X, SearchingItems>)
    {
        members.push_back("Bird");
        members.push_back("Fish");
        members.push_back("Pony");
        members.push_back("All");
    }
    else if constexpr (is_same_v<X, VoiceType>)
    {
        members.push_back("Chrip");
        members.push_back("Coo");
        members.push_back("screech");
        members.push_back("Whistle");
        members.push_back("Mimic");
        members.push_back("Sing");
    }
    else if constexpr (is_same_v<X, WaterType>)
    {
        members.push_back("Fresh Water");
        members.push_back("Salt Water");
    }
    else if constexpr (is_same_v<X, SpeedUnitType>)
    {
        members.push_back("m/s");
        members.push_back("m/min");
        members.push_back("m/h");
        members.push_back("km/h");
    }
    else if constexpr (is_same_v<X, Colors>)
    {
        members.push_back("Red");
        members.push_back("Blue");
        members.push_back("Yellow");
        members.push_back("Green");
        members.push_back("Orange");
        members.push_back("Purple");
        members.push_back("Pink");
        members.push_back("Brown");
        members.push_back("Black");
        members.push_back("White");
        members.push_back("Gray");
    }
    else if constexpr (is_same_v<X, VariablesToValidate>)
    {
        members.push_back("Balance");
        members.push_back("Username");
        members.push_back("Password");
        members.push_back("Phone Number");
        members.push_back("Age");
        members.push_back("Price");
        members.push_back("Rating");
        members.push_back("Ratings");
        members.push_back("Flight Height");
        members.push_back("IQ");
        members.push_back("Aquarium Size");
        members.push_back("Swimming Speed");
        members.push_back("Running Speed");
        members.push_back("Energy Level");
    }

    return members;
}
