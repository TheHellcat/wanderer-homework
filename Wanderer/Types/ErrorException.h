// Programmer Homework - by Michael "HELLCAT"

#pragma once

#include <string>

class ErrorException : public std::exception
{
public:
    ErrorException(std::string errorMessage);
    std::string GetErrorMessage();

private:
    std::string message;
};
