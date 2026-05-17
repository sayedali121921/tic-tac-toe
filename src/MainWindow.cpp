#include "MainWindow.h"
#include "AIPlayer.h"
#include <QMessageBox>
#include <QApplication>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Tic Tac Toe - Premium Edition");
    setFixedSize(500, 650);
    
    setupUI();
    applyStyles();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    // Title
    titleLabel = new QLabel("TIC TAC TOE");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("titleLabel");
    mainLayout->addWidget(titleLabel);

    // Score Board
    scoreLabel = new QLabel("Wins: 0 | Losses: 0 | Draws: 0");
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setObjectName("scoreLabel");
    mainLayout->addWidget(scoreLabel);

    // Menu Widget (Mode Selection)
    menuWidget = new QWidget();
    QVBoxLayout* menuLayout = new QVBoxLayout(menuWidget);
    menuLayout->setAlignment(Qt::AlignCenter);
    menuLayout->setSpacing(15);
    
    btnPvP = new QPushButton("Player vs Player");
    btnPvP->setCursor(Qt::PointingHandCursor);
    
    btnPvAI = new QPushButton("Player vs AI");
    btnPvAI->setCursor(Qt::PointingHandCursor);
    
    menuLayout->addWidget(btnPvP);
    menuLayout->addWidget(btnPvAI);
    
    // Game Widget (Board and Controls)
    gameWidget = new QWidget();
    QVBoxLayout* gameLayout = new QVBoxLayout(gameWidget);
    gameLayout->setAlignment(Qt::AlignCenter);
    
    statusLabel = new QLabel("Turn: X");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setObjectName("statusLabel");
    
    gameBoard = new GameBoard();
    
    QHBoxLayout* controlsLayout = new QHBoxLayout();
    btnRestart = new QPushButton("Restart");
    btnRestart->setCursor(Qt::PointingHandCursor);
    
    btnBackToMenu = new QPushButton("Menu");
    btnBackToMenu->setCursor(Qt::PointingHandCursor);
    
    controlsLayout->addWidget(btnRestart);
    controlsLayout->addWidget(btnBackToMenu);
    
    gameLayout->addWidget(statusLabel);
    gameLayout->addWidget(gameBoard);
    gameLayout->addLayout(controlsLayout);
    
    // Add both to main layout, but only show one
    mainLayout->addWidget(menuWidget);
    mainLayout->addWidget(gameWidget);
    
    gameWidget->hide();

    // Event Connections
    connect(btnPvP, &QPushButton::clicked, this, &MainWindow::onPvPClicked);
    connect(btnPvAI, &QPushButton::clicked, this, &MainWindow::onPvAIClicked);
    connect(btnRestart, &QPushButton::clicked, this, &MainWindow::onRestartClicked);
    connect(btnBackToMenu, &QPushButton::clicked, [this]() {
        gameManager.setState(GameState::Menu);
        gameWidget->hide();
        menuWidget->show();
        updateScoreUI();
    });
    connect(gameBoard, &GameBoard::cellClicked, this, &MainWindow::onCellClicked);

    updateScoreUI();
}

void MainWindow::applyStyles() {
    QString css = R"(
        QMainWindow {
            background-color: #1E1E2E;
        }
        QLabel {
            color: #CDD6F4;
            font-family: 'Segoe UI', Arial, sans-serif;
        }
        #titleLabel {
            font-size: 36px;
            font-weight: bold;
            color: #89B4FA;
            margin-bottom: 5px;
            letter-spacing: 2px;
        }
        #scoreLabel {
            font-size: 14px;
            font-weight: bold;
            color: #A6ADC8;
            background-color: #313244;
            padding: 10px 20px;
            border-radius: 10px;
        }
        #statusLabel {
            font-size: 22px;
            font-weight: bold;
            margin-bottom: 10px;
            color: #F38BA8;
        }
        QPushButton {
            background-color: #89B4FA;
            color: #11111B;
            border: none;
            border-radius: 10px;
            padding: 12px 25px;
            font-size: 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #B4BEFE;
        }
        QPushButton:pressed {
            background-color: #74C7EC;
        }
        .boardButton {
            background-color: #313244;
            color: #CDD6F4;
            font-size: 48px;
            font-weight: bold;
            border-radius: 15px;
            border: 2px solid #45475A;
        }
        .boardButton:hover {
            background-color: #45475A;
        }
        .boardButton[player="X"] {
            color: #F38BA8;
        }
        .boardButton[player="O"] {
            color: #A6E3A1;
        }
    )";
    qApp->setStyleSheet(css);
}

void MainWindow::updateScoreUI() {
    auto& scores = gameManager.getScoreManager();
    scoreLabel->setText(QString("Wins: %1 | Losses: %2 | Draws: %3")
                        .arg(scores.getWins())
                        .arg(scores.getLosses())
                        .arg(scores.getDraws()));
}

void MainWindow::onPvPClicked() {
    gameManager.startGame(false);
    menuWidget->hide();
    gameWidget->show();
    gameBoard->resetBoardUI();
    gameBoard->setButtonsEnabled(true);
    
    statusLabel->setText("Turn: Player 1 (X)");
    statusLabel->setStyleSheet("color: #F38BA8;");
}

void MainWindow::onPvAIClicked() {
    gameManager.startGame(true);
    menuWidget->hide();
    gameWidget->show();
    gameBoard->resetBoardUI();
    gameBoard->setButtonsEnabled(true);
    
    statusLabel->setText("Turn: Player 1 (X)");
    statusLabel->setStyleSheet("color: #F38BA8;");
}

void MainWindow::onRestartClicked() {
    if (gameManager.getIsVsAI()) {
        onPvAIClicked();
    } else {
        onPvPClicked();
    }
}

void MainWindow::onCellClicked(int index) {
    if (gameManager.getState() != GameState::Playing) return;
    
    if (gameManager.makeMove(index)) {
        gameBoard->updateBoard(gameManager.getBoard());
        
        char currentSym = gameManager.getCurrentSymbol();
        
        // Check win or draw
        if (gameManager.checkWin(currentSym)) {
            QString winner = gameManager.getCurrentPlayer()->getName();
            bool isLoss = gameManager.getCurrentPlayer()->isAI();
            handleGameOver(winner + " Wins!", false, isLoss);
            return;
        } else if (gameManager.checkDraw()) {
            handleGameOver("It's a Draw!", true);
            return;
        }
        
        // Switch turn
        gameManager.switchTurn();
        
        // Update UI for next turn
        char nextSym = gameManager.getCurrentSymbol();
        QString nextName = gameManager.getCurrentPlayer()->getName();
        statusLabel->setText(QString("Turn: %1 (%2)").arg(nextName).arg(nextSym));
        statusLabel->setStyleSheet(nextSym == 'X' ? "color: #F38BA8;" : "color: #A6E3A1;");
        
        // If next player is AI, trigger its move
        if (gameManager.getCurrentPlayer()->isAI()) {
            gameBoard->setButtonsEnabled(false);
            QTimer::singleShot(500, this, &MainWindow::processAIMove); // 500ms delay
        }
    }
}

void MainWindow::processAIMove() {
    if (gameManager.getState() != GameState::Playing) return;
    
    AIPlayer* ai = dynamic_cast<AIPlayer*>(gameManager.getCurrentPlayer());
    if (ai) {
        int move = ai->getMove(gameManager.getBoard());
        if (move != -1) {
            gameBoard->setButtonsEnabled(true);
            onCellClicked(move);
        }
    }
}

void MainWindow::handleGameOver(const QString& message, bool isDraw, bool isLoss) {
    gameManager.setState(GameState::GameOver);
    statusLabel->setText(message);
    statusLabel->setStyleSheet("color: #F9E2AF;"); // Yellow for game over
    
    if (gameManager.getIsVsAI()) {
        if (isDraw) {
            gameManager.getScoreManager().addDraw();
        } else if (isLoss) {
            gameManager.getScoreManager().addLoss();
        } else {
            gameManager.getScoreManager().addWin();
        }
    } else {
        // For PvP, we just track Player 1 stats relative to the file.
        // It's a simple semester project, so this approach is fine.
        if (isDraw) {
            gameManager.getScoreManager().addDraw();
        } else if (gameManager.getCurrentSymbol() == 'X') {
            gameManager.getScoreManager().addWin();
        } else {
            gameManager.getScoreManager().addLoss();
        }
    }
    
    updateScoreUI();
    showGameOverMessage(message);
}

void MainWindow::showGameOverMessage(const QString& message) {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Game Over");
    msgBox.setText(message);
    
    // Simple custom styling for QMessageBox to match the theme
    msgBox.setStyleSheet(R"(
        QMessageBox { background-color: #1E1E2E; }
        QLabel { color: #CDD6F4; font-size: 16px; font-weight: bold; }
        QPushButton { 
            background-color: #89B4FA; 
            color: #11111B; 
            padding: 8px 20px; 
            border-radius: 6px; 
            font-weight: bold;
        }
        QPushButton:hover { background-color: #B4BEFE; }
    )");
    
    msgBox.exec();
}
