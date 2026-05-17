#include "ScoreManager.h"
#include <QFile>
#include <QTextStream>

ScoreManager::ScoreManager(const QString& file) : wins(0), losses(0), draws(0), filename(file) {
    loadScores();
}

void ScoreManager::loadScores() {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        if (!in.atEnd()) wins = in.readLine().toInt();
        if (!in.atEnd()) losses = in.readLine().toInt();
        if (!in.atEnd()) draws = in.readLine().toInt();
        file.close();
    }
}

void ScoreManager::saveScores() const {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << wins << "\n" << losses << "\n" << draws << "\n";
        file.close();
    }
}
