# tetris-cpp
A simple **Tetris game** implemented in **C++** for the Windows console.

## Features
- **Classic Tetris gameplay**
- **Colored blocks** in console
- **Shadow system** (shows where the piece will land)
- **Keyboard controls** for moving, rotating, and dropping pieces
- **Score system** and levels

## Requirements
- **Windows OS**
- **g++ (MinGW)** or **MSVC compiler**
- **Console** with ANSI/Windows API support

## Build
- **Compile with g++: `g++ -std=c++11 tetris.cpp -o tetris`**
- **Run: `tetris.exe`**

## Controls
- **`a` → Move Left**
- **`d` → Move Right**
- **`s` → Move Down (fast)**
- **`x` → Hard Drop (instantly drop piece)**
- **`e` → Rotate Clockwise**
- **`q` → Rotate Counter-Clockwise**

## Known Issues / Limitations
- **Uses many global variables, making code harder to maintain.**
- **Works only on Windows (`conio.h`, `windows.h`, `Sleep`, `Beep`).**
- **Uses `system("cls")` which is not safe or portable.**
- **Shadow block is not clearly visible (same character as empty space).**
- **Random number generator is reseeded (`srand`) multiple times instead of once.**
- **Functions `canGoDown`, `canGoLeft`, `canGoRight` have duplicated logic.**
- **Rotation logic is simplistic and may fail for some tetromino shapes.**
- **Whole code is in one file (no modularization with classes).**

## Future Improvements
- **Refactor code to use classes (`Board`, `Piece`, `Game`) instead of global variables.**
- **Make the game cross-platform (Linux, macOS).**
- **Replace `system("cls")` with proper screen handling.**
- **Improve rotation system (e.g., SRS like in modern Tetris).**
- **Add unit tests for core functions.**
- **Add music or better sound handling.**
- **Add high score system and save progress.**

## License
**This project is licensed under the MIT License.**
