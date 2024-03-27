#include <iostream>
#include <fstream>

struct Pixel
{
    std::uint8_t red;
    std::uint8_t green;
    std::uint8_t blue;
};

struct BMP_Image
{
    std::uint32_t size;
    std::uint32_t contentStart;
    std::uint32_t columns;
    std::uint32_t rows;
    std::ifstream in;
};

void toGrayscale(Pixel& pixel);

bool loadImage(BMP_Image& image, const char* inputFile);

bool toGrayscale(BMP_Image& image, const char* outputFile);

std::uint32_t readFourBytesFrom(std::ifstream& in, std::size_t startPosition)
{
    std::uint32_t result;

    in.seekg(startPosition);
    in.read(reinterpret_cast<char*>(&result), sizeof(std::uint32_t));

    return result;
}

int main (int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Wrong number of command arguments!" << std::endl;
        return 1;
    }

    BMP_Image image;
    if (!loadImage(image, argv[1]))
    {
        return 1;
    }

    if (!toGrayscale(image, argv[2]))
    {
        image.in.close();
        return 1;
    }

    image.in.close();

    return 0;
}

void toGrayscale(Pixel& pixel)
{
    std::uint8_t newValue = (pixel.red + pixel.green + pixel.blue) / 3;
    
    pixel.red = pixel.green = pixel.blue = newValue;
}

bool loadImage(BMP_Image& image, const char* inputFile)
{
    image.in.open(inputFile, std::ios::binary);
    if (!image.in)
    {
        std::cout << "Problem while opening the file" << std::endl;
        return false;
    }

    image.size = readFourBytesFrom(image.in, 2);
    image.contentStart = readFourBytesFrom(image.in, 10);
    image.columns = readFourBytesFrom(image.in, 18);
    image.rows = readFourBytesFrom(image.in, 22);

    return true;
}

bool toGrayscale(BMP_Image& image, const char* outputFile)
{
    std::ofstream out(outputFile, std::ios::binary);
    if (!out)
    {
        std::cout << "Problem while opening the file" << std::endl;
        return false;
    }

    image.in.seekg(0);

    char* metadata = new (std::nothrow) char[image.contentStart + 1];
    if (!metadata)
    {
        std::cout << "Memory problem!" << std::endl;
        out.close();

        return false;
    }

    image.in.read(metadata, image.contentStart);
    out.write(metadata, image.contentStart);

    delete[] metadata;

    std::size_t imageWidth = image.columns * 3;
    std::size_t paddingLength = imageWidth % 4;

    for (std::uint32_t i = 0; i < image.rows; ++i)
    {
        for (std::uint32_t j = 0; j < image.columns; ++j)
        {
            Pixel currentPixel;
            image.in.read(reinterpret_cast<char*>(&currentPixel), sizeof(Pixel));
            toGrayscale(currentPixel);
            out.write(reinterpret_cast<const char*>(&currentPixel), sizeof(Pixel));
        }

        char* padding = new (std::nothrow) char[paddingLength + 1];
        if (!padding)
        {
            std::cout << "Memory problem!" << std::endl;
            out.close();

            return false;
        }

        image.in.read(padding, paddingLength);
        out.write(padding, paddingLength);

        delete[] padding;
    }

    out.close();

    return true;
}