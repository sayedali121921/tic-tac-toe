#pragma once
#include <QString>

/**
 * @brief The Player class
 * Abstract base class demonstrating OOP Principles:
 * Encapsulation (protected fields with getters)
 * Abstraction and Polymorphism (pure virtual function isAI)
 */
class Player {
protected:
    QString name;
    char symbol; // 'X' or 'O'

public:
    Player(const QString& n, char sym) : name(n), symbol(sym) {}
    virtual ~Player() = default;

    QString getName() const { return name; }
    char getSymbol() const { return symbol; }
    
    // Abstract method to demonstrate polymorphism
    virtual bool isAI() const = 0;
};
