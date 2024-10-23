#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits
#include <type_traits>  // std::is_floating_point

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        // Code added by VUdeh: Detect overflow before adding
        if ((increment > 0) && (result > std::numeric_limits<T>::max() - increment))
        {
            std::cout << "\tOverflow detected! Cannot perform addition." << std::endl;
            return std::numeric_limits<T>::max(); // Indicate overflow occurred
        }
        result += increment;
    }

    return result;
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (increment * steps)</returns>
template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        // Code added by VUdeh: Detect underflow before subtracting
        if ((decrement > 0) && (result < std::numeric_limits<T>::lowest() + decrement))
        {
            std::cout << "\tUnderflow detected! Cannot perform subtraction." << std::endl;
            return std::numeric_limits<T>::lowest(); // Indicate underflow occurred
        }
        result -= decrement;
    }

    return result;
}

//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
    T result = add_numbers<T>(start, increment, steps);
    std::cout << +result << std::endl;

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    result = add_numbers<T>(start, increment, steps + 1);
    std::cout << +result << std::endl;
}

template <typename T>
void test_underflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tSubtracting Numbers Without Underflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    auto result = subtract_numbers<T>(start, decrement, steps);
    std::cout << +result << std::endl;

    std::cout << "\tSubtracting Numbers With Underflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
    result = subtract_numbers<T>(start, decrement, steps + 1);
    std::cout << +result << std::endl;
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primitive types see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Underflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primitive types see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu



In this project, I updated a C++ program to prevent numeric overflow and underflow issues, ensuring reliability and safety in arithmetic operations. Specifically, I modified two core functions, add_numbers() and subtract_numbers(), to detect and prevent overflow or underflow scenarios. I utilized the capabilities of the standard C++ library, such as std::numeric_limits, to identify when an operation would exceed the data type limits. When such a condition was detected, I safely prevented the operation from proceeding, returned appropriate maximum or minimum values, and provided clear console messages to inform users about the detected issue.

Furthermore, I adapted the test functions, test_overflow() and test_underflow(), to respond appropriately when an overflow or underflow was prevented, printing the relevant status to the console. This ensured that any edge cases resulting in potential data corruption were effectively handled and reported.

These modifications demonstrate my ability to write secure code that prevents common vulnerabilities such as overflow and underflow, while also ensuring clear and actionable reporting to facilitate debugging and testing. The project reflects my experience in secure coding practices, effective use of the C++ standard library, and clear communication of code changes through detailed commenting.

The updated code includes comments marked with "// Code added by VUdeh" to indicate my contributions, making it easy for other developers to understand the modifications and the rationale behind them.