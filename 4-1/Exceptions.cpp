// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <stdexcept>

// Custom exception derived from std::exception
class CustomException : public std::exception {
public:
    const char* what() const _NOEXCEPT override { // Updated to use _NOEXCEPT
        return "Custom exception occurred.";
    }
};

bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception
    // Code added by VUdeh
    std::cout << "Running Even More Custom Application Logic." << std::endl;
    throw std::runtime_error("Standard exception thrown in do_even_more_custom_application_logic.");
    return true;
}

void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        // Wrap the call to do_even_more_custom_application_logic() with an exception handler
        // Code added by VUdeh
        if (do_even_more_custom_application_logic()) {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& e) {
        // Catch std::exception and display a message along with exception.what()
        // Code added by VUdeh
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    // TODO: Throw a custom exception derived from std::exception
    // Throwing CustomException here
    // Code added by VUdeh
    throw CustomException();

    std::cout << "Leaving Custom Application Logic." << std::endl;
}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using a standard C++ defined exception
    // Code added by VUdeh
    if (den == 0) {
        throw std::overflow_error("Division by zero error.");
    }
    return (num / den);
}

void do_division() // Removed noexcept
{
    float numerator = 10.0f;
    float denominator = 0;

    try {
        // Create an exception handler to capture ONLY the exception thrown by divide
        // Code added by VUdeh
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::overflow_error& e) {
        // Catch division by zero exception and display a message
        // Code added by VUdeh
        std::cout << "Exception caught in do_division: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    try {
        // Wrap the whole main function with exception handlers
        // Code added by VUdeh
        do_division();
        do_custom_application_logic();
    }
    catch (const CustomException& e) {
        // Catch custom exception
        // Code added by VUdeh
        std::cout << "Custom exception caught in main: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // Catch any std::exception
        // Code added by VUdeh
        std::cout << "Standard exception caught in main: " << e.what() << std::endl;
    }
    catch (...) {
        // Catch all other uncaught exceptions
        // Code added by VUdeh
        std::cout << "An unknown exception was caught in main." << std::endl;
    }

    return 0;
}
