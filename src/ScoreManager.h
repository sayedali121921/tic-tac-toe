#pragma once
#include <QString>

/**
 * @brief The ScoreManager class
 * Handles File I/O for saving and loading scores.
 */
class ScoreManager {
private:
    int wins;
    int losses;
    int draws;
    QString filename;

public:
    explicit ScoreManager(const QString& file = "scores.txt");
    
    void loadScores();
    void saveScores() const;

    void addWin() { wins++; saveScores(); }
    void addLoss() { losses++; saveScores(); }
    void addDraw() { draws++; saveScores(); }

    int getWins() const { return wins; }
    int getLosses() const { return losses; }
    int getDraws() const { return draws; }
    
    void resetScores() { wins = losses = draws = 0; saveScores(); }
};
