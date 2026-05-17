#include "GameBoard.h"
#include <QPropertyAnimation>
#include <QStyle>

GameBoard::GameBoard(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);
    
    for (int i = 0; i < 9; ++i) {
        QPushButton* btn = new QPushButton("");
        btn->setFixedSize(100, 100);
        btn->setProperty("class", "boardButton");
        btn->setCursor(Qt::PointingHandCursor);
        
        connect(btn, &QPushButton::clicked, this, &GameBoard::handleButtonClicked);
        
        buttons.push_back(btn);
        layout->addWidget(btn, i / 3, i % 3);
    }
}

void GameBoard::handleButtonClicked() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        int index = -1;
        for (int i = 0; i < 9; ++i) {
            if (buttons[i] == btn) {
                index = i;
                break;
            }
        }
        
        if (index != -1) {
            emit cellClicked(index);
        }
    }
}

void GameBoard::updateBoard(const std::vector<char>& board) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 'X' || board[i] == 'O') {
            if (buttons[i]->text().isEmpty()) {
                buttons[i]->setText(QString(board[i]));
                buttons[i]->setProperty("player", QString(board[i]));
                
                // Unpolish and polish to reapply QSS based on dynamic properties
                buttons[i]->style()->unpolish(buttons[i]);
                buttons[i]->style()->polish(buttons[i]);
                
                // Add a simple pop animation (scaling) using QPropertyAnimation
                // Note: QPropertyAnimation needs a property. Since QWidget's geometry is animatable:
                QRect geom = buttons[i]->geometry();
                QPropertyAnimation* animation = new QPropertyAnimation(buttons[i], "geometry");
                animation->setDuration(150);
                animation->setStartValue(QRect(geom.x() + 5, geom.y() + 5, geom.width() - 10, geom.height() - 10));
                animation->setEndValue(geom);
                animation->start(QAbstractAnimation::DeleteWhenStopped);
            }
        } else {
            buttons[i]->setText("");
            buttons[i]->setProperty("player", QVariant());
        }
    }
}

void GameBoard::resetBoardUI() {
    for (auto btn : buttons) {
        btn->setText("");
        btn->setProperty("player", QVariant());
        btn->style()->unpolish(btn);
        btn->style()->polish(btn);
    }
}

void GameBoard::setButtonsEnabled(bool enabled) {
    for (auto btn : buttons) {
        btn->setEnabled(enabled);
    }
}
