#pragma once
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <vector>

/**
 * @brief The GameBoard class
 * Represents the 3x3 Tic-Tac-Toe grid UI component.
 */
class GameBoard : public QWidget {
    Q_OBJECT
    
private:
    std::vector<QPushButton*> buttons;
    QGridLayout* layout;

public:
    explicit GameBoard(QWidget *parent = nullptr);
    
    void updateBoard(const std::vector<char>& board);
    void resetBoardUI();
    void setButtonsEnabled(bool enabled);

signals:
    void cellClicked(int index);

private slots:
    void handleButtonClicked();
};
