#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Player.h"
#include "EnemyManager.h"

class HighScoreManager
{
public:
    HighScoreManager();
    void SaveHighScore(int HighScore);
    int LoadHighScore();
    int test;

private:
    const std::string filename = "highscore.txt";
};

#endif