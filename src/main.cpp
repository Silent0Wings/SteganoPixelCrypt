
#include "SteganoPixelCrypt.cpp"

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

void generateKey()
{
    std::array<size_t, 2> WH = {1113, 1001};
    cout << dec << WH[0] << "  " << WH[1] << endl;
    cout << "size :" << 1113 * 1001 << endl;
    std::vector<std::vector<char32_t>> grid(WH[1], std::vector<char32_t>(WH[0]));
    std::vector<std::vector<Color>> colorGrid(WH[1], std::vector<Color>(WH[0]));
    std::vector<Color> colorPool = generateUniqueTriplets((size_t)(1113 * 1001));
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
    // printGridColor(colorGrid);
}

std::u32string loadUTF32FromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string utf8Text((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    return converter.from_bytes(utf8Text);
}

void saveUTF32ToFile(const std::u32string &text, const std::string &filename)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::string utf8Text = converter.to_bytes(text);

    std::ofstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    file << utf8Text;
}

void testSteganoPixelCrypt()
{
    std::u32string text;
    try
    {
        text = loadUTF32FromFile("srcFile.txt");
        std::cout << "First char code: " << static_cast<uint32_t>(text[0]) << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    if (text.size() == 0)
    {
        cerr << "Loading the file failed !" << endl;
        return;
    }

    saveUTF32ToFile(text, "output.txt");

    for (size_t i = 0; i < 0; i++)
    {
        text += U"Hello 🌍🌟🚀🔥🎉 你好 мир 🌈✨💡🧠💻📚📦⚙️📝🔐🎨♻️🧪🧬🔢🧊🎮🥽🍕🥑🚴‍♂️🏔️📷🎧🕹️🗺️🌌🚧🔭🪐💬🕰️👾🐍🦾⛩️🌪️🧘‍♂️⚡🔋🛰️🤖∞∑λ∫πΩ≠≈√∇";
    }
    SteganoPixelCrypt pc;

    // pc.printGridColor();
    pc.processsString(text);

    std::vector<std::vector<Color>> colorGrid;

    image tempData = ImageRenderer::ReadBMP("Data.bmp");

    cout << "Data : " << tempData.size() << endl;

    image tempKey = ImageRenderer::ReadBMP("Key.bmp");
    cout << "Key : " << tempKey.size() << endl;

    /*
    SteganoPixelCrypt pc1(tempKey, tempData);

    std::u32string text1 = pc1.reconstructSourceString();
    */
}

void testSteganoPixelCryptBook()
{
    std::u32string text;
    try
    {
        text = loadUTF32FromFile("./Book/Universal_Declaration_of_Human_Rights.txt");
        std::cout << "First char code: " << static_cast<uint32_t>(text[0]) << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    if (text.size() == 0)
    {
        cerr << "Loading the file failed !" << endl;
        return;
    }

    SteganoPixelCrypt pc;

    // pc.printGridColor();
    pc.processsString(text);

    std::vector<std::vector<Color>> colorGrid;

    image tempData = ImageRenderer::ReadBMP("Data.bmp");

    cout << "Data : " << tempData.size() << endl;

    image tempKey = ImageRenderer::ReadBMP("Key.bmp");
    cout << "Key : " << tempKey.size() << endl;

    /*
    SteganoPixelCrypt pc1(tempKey, tempData);

    std::u32string text1 = pc1.reconstructSourceString();
    */
}

void testSteganoPixelCryptBookWrite()
{
    std::u32string text;

    text = loadUTF32FromFile("../assets/Book/Dracula_by_Bram_Stoker.txt");
    std::cout << "First char code: " << static_cast<uint32_t>(text[0]) << '\n';

    SteganoPixelCrypt pc;

    pc.processsString(text);
}

int main()
{
    /*
    decimalUniCode();
    cout << "---------" << endl;
    charToUnicode();
    cout << "---------" << endl;
    cout << dec << figureDimensions(300)[0] << "  " << figureDimensions(300)[1] << endl;
    cout << "---------" << endl;
    charVector();
    cout << "---------" << endl;
    generatUniquetriplets(10);
    cout << "---------" << endl;
    generateKey();
    cout << "---------" << endl;
    testSteganoPixelCrypt();
    cout << "---------" << endl;
    testSteganoPixelCryptBook();
    */
    cout << "---------" << endl;
    testSteganoPixelCryptBookWrite();
    cout << "---------" << endl;

    return 0;
}

/*
cd ./src
cls
rm main.exe
g++ -std=c++17 -o main main.cpp -Wall
./main.exe
*/