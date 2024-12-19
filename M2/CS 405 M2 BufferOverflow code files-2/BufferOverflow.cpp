// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <cstring> //code added by Vudeh

int main()
{
    std::cout << "Buffer Overflow Example" << std::endl;

    // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
    //  even though it is a constant and the compiler buffer overflow checks are on.
    //  You need to modify this method to prevent buffer overflow without changing the account_number
    //  variable, and its position in the declaration. It must always be directly before the variable used for input.
    //  You must notify the user if they entered too much data.

    const std::string account_number = "CharlieBrown42";
    char user_input[20];
    
    std::cout << "Enter a value: ";
    std::cin.width(sizeof(user_input)); //code added by Vudeh: Limit the input width to prevent buffer overflow
    std::cin >> user_input;
    
    // Check if input exceeds the buffer limit
    if (std::cin.gcount() > sizeof(user_input) - 1) {
        std::cerr << "Error: Input exceeded buffer limit." << std::endl; //code added by Vudeh: Notify user of input exceeding buffer size
        return 1;
    }
    
    std::cout << "You entered: " << user_input << std::endl;
    std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
