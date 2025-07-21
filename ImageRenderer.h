#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "image.h"
#include <cstdlib>
class ImageRenderer
{
public:
    static void WriteBMP(const image &img, const std::string &filename)
    {
        int width = img.getwidth();
        int height = img.getheight();
        int rowSize = width * 3;
        int padding = (4 - (rowSize % 4)) % 4;
        int dataSize = (rowSize + padding) * height;
        int fileSize = 14 + 40 + dataSize;

        std::ofstream file(filename, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file for writing.\n";
            return;
        }

        // BMP Header
        file.put('B');
        file.put('M');
        file.write(reinterpret_cast<char *>(&fileSize), 4);
        file.write("\0\0\0\0", 4);
        int dataOffset = 14 + 40;
        file.write(reinterpret_cast<char *>(&dataOffset), 4);

        // DIB Header
        int headerSize = 40;
        file.write(reinterpret_cast<char *>(&headerSize), 4);
        file.write(reinterpret_cast<char *>(&width), 4);
        file.write(reinterpret_cast<char *>(&height), 4);
        uint16_t planes = 1, bpp = 24;
        file.write(reinterpret_cast<char *>(&planes), 2);
        file.write(reinterpret_cast<char *>(&bpp), 2);
        int compression = 0;
        file.write(reinterpret_cast<char *>(&compression), 4);
        file.write(reinterpret_cast<char *>(&dataSize), 4);
        int res = 0;
        file.write(reinterpret_cast<char *>(&res), 4); // X ppm
        file.write(reinterpret_cast<char *>(&res), 4); // Y ppm
        file.write(reinterpret_cast<char *>(&res), 4); // Colors used
        file.write(reinterpret_cast<char *>(&res), 4); // Important Colors

        // Pixel data (top-down)
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                Color c = img.get(y, x);
                uint8_t r = static_cast<uint8_t>(c.getR());
                uint8_t g = static_cast<uint8_t>(c.getG());
                uint8_t b = static_cast<uint8_t>(c.getB());
                file.put(b);
                file.put(g);
                file.put(r);
            }
            for (int i = 0; i < padding; i++)
                file.put(0);
        }

        file.close();
    }

    static image ReadBMP(const std::string &filename)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file for reading.\n";
            return image();
        }

        // Skip BMP Header
        file.ignore(10);
        int dataOffset;
        file.read(reinterpret_cast<char *>(&dataOffset), 4);

        // DIB Header
        int headerSize;
        file.read(reinterpret_cast<char *>(&headerSize), 4);
        int width, height;
        file.read(reinterpret_cast<char *>(&width), 4);
        file.read(reinterpret_cast<char *>(&height), 4);
        uint16_t planes, bpp;
        file.read(reinterpret_cast<char *>(&planes), 2);
        file.read(reinterpret_cast<char *>(&bpp), 2);

        if (bpp != 24)
        {
            std::cerr << "Only 24-bit BMP files are supported.\n";
            return image();
        }

        // Skip the rest of the DIB header
        file.ignore(headerSize - 16);

        // Setup image
        cout << "height :" << height << "| width " << width << endl;
        image img(width, height); // matches your writer's (h, w)
        int rowSize = width * 3;
        int padding = (4 - (rowSize % 4)) % 4;

        // Read pixels top-down (as written)
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                uint8_t b = file.get();
                uint8_t g = file.get();
                uint8_t r = file.get();
                img.set(x, y, Color(r, g, b));
            }
            file.ignore(padding);
        }

        file.close();
        return img;
    }
};

#endif // IMAGERENDERER_H
