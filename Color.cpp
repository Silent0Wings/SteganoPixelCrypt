#include <array>
#include <iostream>

class Color
{
private:
    std::array<unsigned char, 3> rgb; // R, G, B (0–255)

public:
    // Constructor
    Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0)
    {
        set(r, g, b);
    }

    // Set all at once
    void set(unsigned char r, unsigned char g, unsigned char b)
    {
        rgb[0] = r;
        rgb[1] = g;
        rgb[2] = b;
    }

    // Set individual channels
    void setR(unsigned char r) { rgb[0] = r; }
    void setG(unsigned char g) { rgb[1] = g; }
    void setB(unsigned char b) { rgb[2] = b; }

    // Get individual channels
    unsigned char getR() const { return rgb[0]; }
    unsigned char getG() const { return rgb[1]; }
    unsigned char getB() const { return rgb[2]; }

    // Get whole array
    std::array<unsigned char, 3> getRGB() const { return rgb; }

    // Print color
    void print() const
    {
        std::cout << "RGB(" << +rgb[0] << ", " << +rgb[1] << ", " << +rgb[2] << ")\n";
    }
};
