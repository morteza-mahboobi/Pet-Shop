#pragma once

#include <exception>
#include <stdexcept>
using std::logic_error;

enum class VariablesToValidate
{
    Balance,
    Username,
    Password,
    PhoneNumber,
    Age,
    Price,
    Rating,
    Ratings,
    FlightHeight,
    Iq,
    AquariumSize,
    SwimmingSpeed,
    RunningSpeed,
    EnergyLevel
};

class setValuesException : public logic_error
{
    VariablesToValidate variableName;

public:
    setValuesException(string explanation, VariablesToValidate _variableName) : logic_error(explanation)
    {
        setVariableName(_variableName);
    }

    void setVariableName(VariablesToValidate _variableName)
    {
        variableName = _variableName;
    }

    VariablesToValidate getVariableName() const
    {
        return variableName;
    }

    bool checkVariableName(VariablesToValidate _variableName) const
    {
        bool check = (_variableName == variableName);
        return check;
    }
};
