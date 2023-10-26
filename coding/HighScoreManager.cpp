#include "HighScoreManager.h"
#include <fstream>
#include <iostream>

HighScoreManager::HighScoreManager()
{
    // constructor
    std::cout << "test" << std::endl;
    // Check if the highscore.txt file exists
    std::ifstream inFile(filename);
    if (!inFile)
    {
        // If the file doesn't exist, create it and set an initial value of 0
        std::cout << filename << std::endl;
        SaveHighScore(0);
    }
}

void HighScoreManager::SaveHighScore(int highScore)
{
    std::ofstream outFile(filename);
    if (outFile.is_open())
    {
        outFile << highScore;
        outFile.close();
    }
    else
    {
        // Handle error (e.g., print a message or log the error)
    }
}
int HighScoreManager::LoadHighScore()
{
    int highScore = 0;
    std::ifstream inFile(filename);
    if (inFile.is_open())
    {
        inFile >> highScore;
        inFile.close();
    }
    else
    {
        // Handle error (e.g., assume it's the first time running and the file doesn't exist yet)
    }
    return highScore;
}