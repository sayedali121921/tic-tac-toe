#include "AIPlayer.h"
#include <cstdlib>
#include <ctime>

int AIPlayer::getMove(const std::vector<char>& board) const {
    std::vector<int> available;
    
    // Find all empty spots
    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            available.push_back(i);
        }
    }
    
    if (available.empty()) {
        return -1; // No moves available
    }

    // Very simple AI: Pick a random available spot
    // This meets the requirement of being easy to explain
    srand(static_cast<unsigned int>(time(nullptr)));
    int randomIndex = rand() % available.size();
    
    return available[randomIndex];
}
