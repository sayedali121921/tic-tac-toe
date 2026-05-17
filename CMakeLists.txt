cmake_minimum_required(VERSION 3.10)
project(TicTacToe VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/GameBoard.cpp
    src/GameBoard.h
    src/GameManager.cpp
    src/GameManager.h
    src/Player.h
    src/HumanPlayer.h
    src/AIPlayer.cpp
    src/AIPlayer.h
    src/ScoreManager.cpp
    src/ScoreManager.h
)

add_executable(TicTacToe ${PROJECT_SOURCES})

target_link_libraries(TicTacToe PRIVATE Qt5::Widgets)
