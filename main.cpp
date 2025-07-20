#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <array>
#include <cmath>

const size_t UnicodeRange = 1114111;

using namespace std;

void decimalUniCode()
{

    uint32_t decimal = 127757; // example: 🌍
    stringstream hexStream;
    hexStream << "0x" << hex << uppercase << decimal;
    string hexString = hexStream.str();

    cout << "Hex: " << hexString << endl;
}

void charToUnicode()
{
    u32string text = U"Hello 🌍";
    for (char32_t c : text)
    {
        cout << hex << showbase << static_cast<uint32_t>(c) << '\n';
    }
}

// This function finds a width and height such that:
// width * height is at least 'size'

std::array<size_t, 2> figureDimensions(size_t size)
{
    // Start with width close to the square root of size
    size_t width = static_cast<size_t>(std::ceil(std::sqrt(size)));

    // Calculate the smallest height so that width * height >= size
    size_t height = (size + width - 1) / width;

    // Return the result as {width, height}
    return {width, height};
}

void charVector()
{
    vector<vector<char32_t>> Grid;
}
int main()
{

    decimalUniCode();
    cout << "---------" << endl;
    charToUnicode();
    cout << "---------" << endl;
    cout << dec << figureDimensions(300)[0] << "  " << figureDimensions(300)[1];
    return 0;
}
