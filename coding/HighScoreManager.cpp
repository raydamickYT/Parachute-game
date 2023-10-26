#include "HighScoreManager.h"
#include <fstream>
#include <iostream>

HighScoreManager::HighScoreManager()
{
    // constructor
    std::ifstream inFile(filename);
    if (!inFile)
    {
        // If the file doesn't exist, create it and set an initial value of 0
        SaveHighScore(0);
        std::cout << filename << std::endl;
    }
    else
    {
        // do something if you want when the file already exists. not really a point.
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
        // Handle error 
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
        // Handle error 
    }
    return highScore;
}