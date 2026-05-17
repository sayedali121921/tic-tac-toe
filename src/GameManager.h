#pragma once
#include <vector>
#include <memory>
#include "Player.h"
#include "ScoreManager.h"

enum class GameState {
    Menu,
    Playing,
    GameOver
};

/**
 * @brief The GameManager class
 * Handles the core logic and state of the game.
 * Demonstrates clean architecture and separation of concerns.
 */
class GameManager {
private:
    std::vector<char> board;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    Player* currentPlayer;
    
    GameState state;
    ScoreManager scoreManager;
    bool isVsAI;

public:
    GameManager();
    
    void startGame(bool vsAI);
    void resetBoard();
    bool makeMove(int index);
    void switchTurn();
    
    bool checkWin(char symbol) const;
    bool checkDraw() const;
    
    // Getters
    char getCurrentSymbol() const { return currentPlayer ? currentPlayer->getSymbol() : ' '; }
    Player* getCurrentPlayer() const { return currentPlayer; }
    const std::vector<char>& getBoard() const { return board; }
    GameState getState() const { return state; }
    bool getIsVsAI() const { return isVsAI; }
    ScoreManager& getScoreManager() { return scoreManager; }
    
    // Setters
    void setState(GameState s) { state = s; }
};
