#ifndef FILEMANAGER
#define FILEMANAGER

/**
 * @file FileManager.h
 * @brief Controls the input and output of files 
 */
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;

/**
 * @class FileManager
 * @brief Class that controls the loading in and out of files.
 * 
 */
class FileManager
{
public:
    /**
     * @brief Construct a new File Manager object
     */
    FileManager();
    /**
     * @brief Get the Texture object
     * 
     * @param texturePath - The location of the texture file in resources/
     * @return sf::Texture - The SFML texture
     */
    sf::Texture getTexture(const string &texturePath);
    /**
     * @brief Get the Font object
     * 
     * @param texturePath - The location of the font file in resources/
     * @return sf::Font - The SFML font
     */
    sf::Font getFont(const string &texturePath);
    /**
     * @brief Get the Lines From File object
     * 
     * @param filePath - The location of the file that holds the highschore
     * @return vector<string> - The string from the file
     */
    vector<string> getLinesFromFile(const string &filePath);
    /**
     * @brief Set the File object
     * Writes to the output file to update the highscore 
     * @param filePath - The location of the file that holds the highschore
     * @param text - Text to update the file with
     */
    void setFile(const string &filePath, const string& text);
    /**
     * @brief Destroy the File Manager object
     */
    ~FileManager();
};

#endif