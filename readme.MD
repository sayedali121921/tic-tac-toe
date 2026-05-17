====================================================================
               TIC-TAC-TOE: PREMIUM QT EDITION
====================================================================

--------------------------------------------------------------------
1. WHAT WE DID
--------------------------------------------------------------------
We built a complete, modern, GUI-based Tic-Tac-Toe game from scratch 
using C++ and the Qt Widgets framework. The goal was to create a 
polished, semester-level project that clearly demonstrates core 
Object-Oriented Programming (OOP) principles while remaining 
understandable and easy to present.

Features Implemented:
- Player vs Player (PvP) mode.
- Player vs AI (PvAI) mode.
- Automatic score tracking (Wins, Losses, Draws).
- Persistent score saving and loading using file handling (scores.txt).
- A modern, dark-themed GUI with soft colors and hover animations.
- Win/Draw detection logic.
- Clean separation of UI logic and underlying game logic.

--------------------------------------------------------------------
2. HOW WE DID IT (ARCHITECTURE & OOP PRINCIPLES)
--------------------------------------------------------------------
We designed the system using a highly modular architecture. Instead 
of writing all the code in one giant file, we separated the logic 
into distinct classes to fulfill the Single Responsibility Principle:

A. Core OOP Implementation:
   - ENCAPSULATION: All classes use private/protected member variables. 
     For example, in the `Player` class, the `name` and `symbol` are 
     protected, and can only be accessed via public getter methods 
     like `getName()` and `getSymbol()`.
   - ABSTRACTION: We created an abstract base class `Player` with a 
     pure virtual function `isAI() = 0`.
   - INHERITANCE: `HumanPlayer` and `AIPlayer` inherit from `Player`.
   - POLYMORPHISM: The `GameManager` class manages the game using base 
     class pointers (`Player* currentPlayer`). At runtime, it dynamically 
     calls the correct overridden methods depending on whether the 
     player is a Human or an AI.

B. Key Classes:
   - GameManager: The "brain" of the game. It knows nothing about the 
     GUI. It only manages the 3x3 array, checks for win/draw conditions, 
     and handles turn switching.
   - MainWindow: The main application window. It binds the visual elements 
     (buttons, labels) to the `GameManager` logic.
   - GameBoard: A dedicated UI component for the 3x3 grid. It handles 
     button clicks and lightweight click animations using `QPropertyAnimation`.
   - ScoreManager: Handles File I/O. It reads from and writes to a text 
     file (`scores.txt`) using `QFile` and `QTextStream`.

--------------------------------------------------------------------
3. HOW WE DID IT (TECHNOLOGY & STYLING)
--------------------------------------------------------------------
- Language & Framework: Standard C++17 with Qt 5 Widgets.
- Build System: CMake was used to manage the build process, making 
  the project compatible with CLion, Qt Creator, or standard command 
  line builds.
- GUI Design: Instead of using QML (which can be overly complex for a 
  standard OOP class), we used standard Qt Widgets (QPushButton, QLabel) 
  and styled them heavily using Qt Style Sheets (QSS). 
  We applied a premium dark theme palette (inspired by modern developer 
  themes like Catppuccin) to make the UI look professional without 
  needing heavy graphical assets.
- AI Logic: To keep the project manageable and easy to explain during a 
  viva, the AI uses a lightweight approach: it collects all available 
  empty spots on the board into a vector and uses a random number 
  generator to select its move.

--------------------------------------------------------------------
4. HOW TO BUILD AND RUN
--------------------------------------------------------------------
Prerequisites: C++ compiler, CMake, and Qt5 development packages.

Commands:
1. cd "tic tac toe"
2. mkdir build && cd build
3. cmake ..
4. make
5. ./TTT

Enjoy the game!
