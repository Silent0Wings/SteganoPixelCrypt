#include <array>
#include <iostream>
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
#include "ImageRenderer.h"
using namespace std;
class PixelCrypt
{

private:
public:
    const static size_t UnicodeRange = 1114111;
    image imgData;
    image imgKey;
    // std::vector<std::vector<char32_t>> charGrid;
    std::vector<std::vector<Color>> colorGrid;
    PixelCrypt()
    {
        generateKey();
    }

    bool areAllColorsUnique(const std::vector<std::vector<Color>> &grid)
    {
        std::unordered_set<uint32_t> seen;

        for (const auto &row : grid)
        {
            for (const auto &c : row)
            {
                uint32_t hash = (c.getR() << 16) | (c.getG() << 8) | c.getB();
                if (!seen.insert(hash).second)
                    return false; // Duplicate found
            }
        }
        return true; // All colors unique
    }

    std::vector<Color> generateUniqueTriplets(size_t size)
    {
        std::unordered_set<uint32_t> used;
        std::vector<Color> pool;
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, 255);

        while (pool.size() < size)
        {
            int r = dist(rng);
            int g = dist(rng);
            int b = dist(rng);

            uint32_t hash = (r << 16) | (g << 8) | b;

            if (used.insert(hash).second) // Only insert if unique
                pool.emplace_back(r, g, b);
        }

        std::cout << "All values are unique\n";
        return pool;
    }

    /*
    void printGrid()
    {
        for (const auto &row : charGrid)
        {
            for (const auto &ch : row)
            {
                std::cout << std::setw(10) << (ch); // 4-space column
            }
            std::cout << '\n';
        }
    }
    */
    void printGridColor()
    {
        for (const auto &row : colorGrid)
        {
            for (const auto &ch : row)
            {
                std::cout << std::setw(10) << ch; // 4-space column
            }
            std::cout << '\n';
        }
    }

    void generateKey()
    {
        std::array<size_t, 2> WH = {1113, 1001};
        cout << dec << WH[0] << "  " << WH[1] << endl;
        cout << "size :" << 1113 * 1001 << endl;
        // charGrid = std::vector<std::vector<char32_t>>(WH[1], std::vector<char32_t>(WH[0]));
        colorGrid = std::vector<std::vector<Color>>(WH[1], std::vector<Color>(WH[0]));
        cout << dec << WH[0] << "  " << WH[1] << endl;
        imgKey = image(WH[1], WH[0]);

        std::vector<Color> colorPool = generateUniqueTriplets(1113 * 1001);
        size_t increment = 0;

        for (size_t i = 0; i < WH[1]; i++)
        {
            for (size_t j = 0; j < WH[0]; j++)
            {

                /*
                if (increment <= 1114111)
                {
                    charGrid[i][j] = increment++;
                }
                else
                {
                    charGrid[i][j] = 0;
                }
                */
                colorGrid[i][j] = colorPool[increment++];
                imgKey.set(i, j, colorGrid[i][j]);
            }
        }

        try
        {
            if (areAllColorsUnique(colorGrid))
            {
                std::cout << "All values are unique\n";
            }
            else
            {
                throw "not all colors are unique";
            }
        }
        catch (const char *msg)
        {
            std::cerr << "Exception: " << msg << std::endl;
        }

        // printGrid(grid);
        // printGridChar(grid);
        ImageRenderer::WriteBMP(imgKey, "Key.bmp");
    }
    std::array<size_t, 2> figureDimensions(size_t size)
    {
        // Start with width close to the square root of size
        size_t width = static_cast<size_t>(std::ceil(std::sqrt(size)));

        // Calculate the smallest height so that width * height >= size
        size_t height = (size + width - 1) / width;

        // Return the result as {width, height}
        return {width, height};
    }

    void processsString(const std::u32string text)
    {
        if (colorGrid.size() == 0 || text.size() == 0)
        {

            throw std::runtime_error("colorGrid empty or the string is empty");
        }

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
        imgData = image(WH[1], WH[0]);

        for (size_t i = 0; i < grid.size(); i++)
        {
            for (size_t j = 0; j < grid[i].size(); j++)
            {
                size_t index = static_cast<size_t>(grid[i][j]);
                // cout << "grid " << grid[i][j] << endl;
                size_t width = colorGrid[0].size(); // width = columns
                size_t row = index / width;
                size_t col = index % width;
                // cout << "row " << row << " col " << col << endl;
                Color tempc = colorGrid[row][col];
                // cout << "color : " <<tempc << endl;
                imgData.set(i, j, tempc);
            }
        }

        // printGrid(grid);
        // printGridChar(grid);
        ImageRenderer::WriteBMP(imgData, "Data.bmp");
    }
};
