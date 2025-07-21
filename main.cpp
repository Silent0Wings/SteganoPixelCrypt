#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <locale>
#include <codecvt>
#include <random>
#include <algorithm>
#include <unordered_set>
#include <cstdint>
#include "Color.cpp"

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

void printGrid(const std::vector<std::vector<char32_t>> &grid)
{
    for (const auto &row : grid)
    {
        for (const auto &ch : row)
        {
            std::cout << std::setw(10) << (ch); // 4-space column
        }
        std::cout << '\n';
    }
}
void printGridColor(const std::vector<std::vector<Color>> &grid)
{
    for (const auto &row : grid)
    {
        for (const auto &ch : row)
        {
            std::cout << std::setw(10) << ch; // 4-space column
        }
        std::cout << '\n';
    }
}
void printGridChar(const std::vector<std::vector<char32_t>> &grid)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;

    for (const auto &row : grid)
    {
        for (const auto &ch : row)
        {
            std::string out = convert.to_bytes(ch);
            std::cout << std::setw(4) << out << " ";
        }
        std::cout << '\n';
    }
}
void charVector()
{
    std::u32string text = U"Hello 🌍🌟🚀🔥🎉 你好 мир 🌈✨💡🧠💻📚📦⚙️📝🔐🎨♻️🧪🧬🔢🧊🎮🥽🍕🥑🚴‍♂️🏔️📷🎧🕹️🗺️🌌🚧🔭🪐💬🕰️👾🐍🦾⛩️🌪️🧘‍♂️⚡🔋🛰️🤖∞∑λ∫πΩ≠≈√∇";

    std::array<size_t, 2> WH = figureDimensions(text.size());
    cout << "size :" << text.size() << endl;
    cout << dec << WH[0] << "  " << WH[1] << endl;

    size_t overfill = (WH[0] * WH[1]) - text.size();
    cout << dec << "overfill :" << overfill << endl;

    std::vector<std::vector<char32_t>> grid(WH[1], std::vector<char32_t>(WH[0]));

    size_t increment = 0;
    for (size_t i = 0; i < WH[1]; i++)
    {
        for (size_t j = 0; j < WH[0]; j++)
        {
            if (increment < text.size())

                grid[i][j] = text.at(increment++);
        }
    }

    printGrid(grid);
    printGridChar(grid);
}
vector<Color> generatUniquetriplets(const size_t size)
{
    /*
    Choose how many groups of 3 numbers you want.

    Make a list of random numbers (no repeats).

    Mix the list.

    Split into groups of 3.

    Check if any number shows up twice.

    Show the groups and say if there's a repeat.
    */

    vector<Color> ColorPool;
    const int tripletCount = size;
    const int totalNeeded = tripletCount * 3;

    std::vector<int> pool;
    for (int i = 1; i <= totalNeeded; ++i)
        pool.push_back(i);

    std::shuffle(pool.begin(), pool.end(), std::mt19937{std::random_device{}()});

    std::unordered_set<int> seen;
    bool hasDuplicate = false;

    for (int i = 0; i < tripletCount; ++i)
    {
        int a = pool[i * 3];
        int b = pool[i * 3 + 1];
        int c = pool[i * 3 + 2];

        if (!seen.insert(a).second || !seen.insert(b).second || !seen.insert(c).second)
        {
            hasDuplicate = true;
        }
        ColorPool.push_back(Color(a, b, c));
        // std::cout  << "{" << a << "," << b << "," << c << "}\n";
    }

    if (hasDuplicate)
        std::cout << "Duplicate found\n";
    else
    {
        std::cout << "All values are unique\n";
        return ColorPool;
    }
    return {};
}
void generateKey()
{
    std::array<size_t, 2> WH = {1113, 1001};
    cout << dec << WH[0] << "  " << WH[1] << endl;

    std::vector<std::vector<char32_t>> grid(WH[1], std::vector<char32_t>(WH[0]));
    std::vector<std::vector<Color>> colorGrid(WH[1], std::vector<Color>(WH[0]));
    std::vector<Color> colorPool = generatUniquetriplets(1113 * 1001);
    size_t increment = 0;
    for (size_t i = 0; i < WH[1]; i++)
    {
        for (size_t j = 0; j < WH[0]; j++)
        {
            if (increment <= 1114111)
            {
                grid[i][j] = increment++;
            }
            else
            {
                grid[i][j] = 0;
            }
            colorGrid[i][j] = colorPool[increment];
        }
    }

    // printGrid(grid);
    // printGridChar(grid);
    printGridColor(colorGrid);
}

int main()
{
    decimalUniCode();
    cout << "---------" << endl;
    charToUnicode();
    cout << "---------" << endl;
    cout << dec << figureDimensions(300)[0] << "  " << figureDimensions(300)[1] << endl;
    cout << "---------" << endl;
    charVector();
    cout << "---------" << endl;
    generateKey();
    cout << "---------" << endl;
    // generatUniquetriplets(10);
    return 0;
}
