// Programmer Homework - by Michael "HELLCAT"

#include "ErrorException.h"

ErrorException::ErrorException(std::string errorMessage)
{
    message = errorMessage;
}

std::string ErrorException::GetErrorMessage()
{
    return message;
}
