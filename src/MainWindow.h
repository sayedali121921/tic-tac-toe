#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include "GameBoard.h"
#include "GameManager.h"

/**
 * @brief The MainWindow class
 * The main application window containing the UI logic.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCellClicked(int index);
    void onPvPClicked();
    void onPvAIClicked();
    void onRestartClicked();
    void processAIMove();

private:
    void setupUI();
    void applyStyles();
    void updateScoreUI();
    void showGameOverMessage(const QString& message);
    void handleGameOver(const QString& message, bool isDraw = false, bool isLoss = false);

    GameManager gameManager;
    GameBoard* gameBoard;
    
    QLabel* titleLabel;
    QLabel* statusLabel;
    QLabel* scoreLabel;
    
    QWidget* menuWidget;
    QWidget* gameWidget;
    
    QPushButton* btnPvP;
    QPushButton* btnPvAI;
    QPushButton* btnRestart;
    QPushButton* btnBackToMenu;
};
