#include "GameManager.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

GameManager::GameManager() 
    : board(9, ' '), currentPlayer(nullptr), state(GameState::Menu), isVsAI(false) {
}

void GameManager::startGame(bool vsAI) {
    this->isVsAI = vsAI;
    
    player1 = std::make_unique<HumanPlayer>("Player 1", 'X');
    
    if (vsAI) {
        player2 = std::make_unique<AIPlayer>("AI", 'O');
    } else {
        player2 = std::make_unique<HumanPlayer>("Player 2", 'O');
    }
    
    resetBoard();
}

void GameManager::resetBoard() {
    std::fill(board.begin(), board.end(), ' ');
    currentPlayer = player1.get();
    state = GameState::Playing;
}

bool GameManager::makeMove(int index) {
    if (index < 0 || index >= 9 || board[index] != ' ' || state != GameState::Playing) {
        return false;
    }
    
    board[index] = currentPlayer->getSymbol();
    return true;
}

void GameManager::switchTurn() {
    if (currentPlayer == player1.get()) {
        currentPlayer = player2.get();
    } else {
        currentPlayer = player1.get();
    }
}

bool GameManager::checkWin(char symbol) const {
    const int winningCombos[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };
    
    for (const auto& combo : winningCombos) {
        if (board[combo[0]] == symbol && 
            board[combo[1]] == symbol && 
            board[combo[2]] == symbol) {
            return true;
        }
    }
    
    return false;
}

bool GameManager::checkDraw() const {
    for (char cell : board) {
        if (cell == ' ') return false;
    }
    return true;
}
