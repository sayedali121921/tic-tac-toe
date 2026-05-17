#pragma once
#include "Player.h"

/**
 * @brief The HumanPlayer class
 * Demonstrates Inheritance from the Player base class.
 */
class HumanPlayer : public Player {
public:
    HumanPlayer(const QString& n, char sym) : Player(n, sym) {}
    
    // Override pure virtual function
    bool isAI() const override { return false; }
};
