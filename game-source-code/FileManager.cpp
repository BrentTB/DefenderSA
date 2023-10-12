#include "FileManager.h"

FileManager::FileManager() {}

sf::Texture FileManager::getTexture(const string &texturePath)
{
    auto loadedTexture = sf::Texture{};
    if (!loadedTexture.loadFromFile(texturePath))
    {
        throw std::runtime_error("Texture " + texturePath + " does not exist or could not be opened.");
    }
    return loadedTexture;
}

sf::Font FileManager::getFont(const string &fontPath)
{
    auto loadedFont = sf::Font{};
    if (!loadedFont.loadFromFile(fontPath))
    {
        throw std::runtime_error("Font " + fontPath + " does not exist or could not be opened.");
    }
    return loadedFont;
}

vector<string> FileManager::getLinesFromFile(const string &filePath)
{
    auto allLines = vector<string>{};
    ifstream inputFile;
    inputFile.open(filePath);

    if (!inputFile.is_open())
        throw std::runtime_error("File " + filePath + " does not exist or could not be opened.");

    auto line = string{};
    while (getline(inputFile, line))
    {
        allLines.push_back(line);
    }
    inputFile.close();
    return allLines;
}

void FileManager::setFile(const string &filePath, const string &text)
{
    ofstream outputFile;
    outputFile.open(filePath, ios::trunc);

    if (!outputFile.is_open())
        throw std::runtime_error("File " + filePath + " does not exist or could not be opened.");

    outputFile << text;
    outputFile.close();
}

FileManager::~FileManager(){};