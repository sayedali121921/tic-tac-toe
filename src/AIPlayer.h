#pragma once
#include "Player.h"
#include <vector>

/**
 * @brief The AIPlayer class
 * Demonstrates Inheritance and Polymorphism.
 */
class AIPlayer : public Player {
public:
    AIPlayer(const QString& n, char sym) : Player(n, sym) {}
    
    // Override pure virtual function
    bool isAI() const override { return true; }
    
    // Simple logic to get AI move
    int getMove(const std::vector<char>& board) const;
};
