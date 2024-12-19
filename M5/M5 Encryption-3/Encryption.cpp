// Encryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

/// <summary>
/// encrypt or decrypt a source string using the provided key
/// </summary>
/// <param name="source">input string to process</param>
/// <param name="key">key to use in encryption / decryption</param>
/// <returns>transformed string</returns>
std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
    // get lengths now instead of calling the function every time.
    // this would have most likely been inlined by the compiler, but design for performance.
    const auto key_length = key.length();
    const auto source_length = source.length();

    // assert that our input data is good
    assert(key_length > 0);
    assert(source_length > 0);

    std::string output = source;

    // loop through the source string char by char
    for (size_t i = 0; i < source_length; ++i)
    { 
        // TODO: student need to change the next line from output[i] = source[i]
        // transform each character based on an xor of the key modded constrained to key length using a mod
        output[i] = source[i] ^ key[i % key_length]; // Code Created by VUdeh: XOR encryption implementation
    }

    // our output length must equal our source length
    assert(output.length() == source_length);

    // return the transformed string
    return output;
}

std::string read_file(const std::string& filename)
{
    std::string file_text = "John Q. Smith\nThis is my test string";

    // TODO: implement loading the file into a string
    std::ifstream file(filename); // Code Created by VUdeh: Open the file for reading
    std::ostringstream buffer;
    if (file)
    {
        buffer << file.rdbuf(); // Code Created by VUdeh: Read file content into buffer
        file_text = buffer.str(); // Code Created by VUdeh: Convert buffer to string
    }

    return file_text;
}

std::string get_student_name(const std::string& string_data)
{
    std::string student_name;

    // find the first newline
    size_t pos = string_data.find('\n');
    // did we find a newline
    if (pos != std::string::npos)
    { 
        // we did, so copy that substring as the student name
        student_name = string_data.substr(0, pos);
    }

    return student_name;
}

void save_data_file(const std::string& filename, const std::string& student_name, const std::string& key, const std::string& data)
{
    //  TODO: implement file saving
    //  file format
    //  Line 1: student name
    //  Line 2: timestamp (yyyy-mm-dd)
    //  Line 3: key used
    //  Line 4+: data
    std::ofstream file(filename); // Code Created by VUdeh: Open file for writing
    if (file)
    {
        // Get current date
        std::time_t now = std::time(nullptr);
        struct tm local;
        localtime_s(&local, &now); // Code Created by VUdeh: Replaced localtime with localtime_s for thread safety

        file << student_name << "\n"; // Code Created by VUdeh: Write student name
        file << (1900 + local.tm_year) << "-" << (1 + local.tm_mon) << "-" << local.tm_mday << "\n"; // Code Created by VUdeh: Write current date
        file << key << "\n"; // Code Created by VUdeh: Write encryption key
        file << data << "\n"; // Code Created by VUdeh: Write encrypted or decrypted data
    }
}

int main()
{
    std::cout << "Encryption Decryption Test!" << std::endl;

    // input file format
    // Line 1: <student's name>
    // Line 2: <Lorem Ipsum Generator website used> https://pirateipsum.me/
    // Lines 3+: <lorem ipsum generated with 3 paragraphs>
    const std::string file_name = "inputdatafile.txt";
    const std::string encrypted_file_name = "encrypteddatafile.txt";
    const std::string decrypted_file_name = "decrypteddatafile.txt";
    const std::string source_string = read_file(file_name);
    const std::string key = "password";

    // get the student name from the data file
    const std::string student_name = get_student_name(source_string);

    // encrypt sourceString with key
    const std::string encrypted_string = encrypt_decrypt(source_string, key);

    // save encrypted_string to file
    save_data_file(encrypted_file_name, student_name, key, encrypted_string);

    // decrypt encryptedString with key
    const std::string decrypted_string = encrypt_decrypt(encrypted_string, key);

    // save decrypted_string to file
    save_data_file(decrypted_file_name, student_name, key, decrypted_string);

    std::cout << "Read File: " << file_name << " - Encrypted To: " << encrypted_file_name << " - Decrypted To: " << decrypted_file_name << std::endl;

    // students submit input file, encrypted file, decrypted file, source code file, and key used
}
