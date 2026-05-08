<div align="center">

# ♟️ ChessForge

### *Where chess meets clean code.*

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-8CC445?style=for-the-badge&logo=sfml&logoColor=white)
![OOP](https://img.shields.io/badge/OOP-Final%20Project-blueviolet?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)

> **A fully functional two-player Chess game forged from scratch in C++ with an SFML graphical interface.**  
> Every rule. Every piece. Every move — validated from the ground up.

</div>

---

## 📁 Project Structure

```
ChessForge/
│
├── 📄 Piece.h              ← Abstract base class (the heart of OOP design)
│
├── ♙ Pawn.cpp / .h
├── ♖ Rook.cpp / .h
├── ♘ Knight.cpp / .h
├── ♗ Bishop.cpp / .h
├── ♛ Queen.cpp / .h
├── ♔ King.cpp / .h
│
├── 🧠 Board.cpp / .h       ← Game logic, check / checkmate / stalemate
├── 📍 Position.h           ← Coordinate utility
├── 🖥️ gui_main.cpp         ← SFML window, click handling, rendering
│
└── 🖼️ assets/
    ├── wK.png  wQ.png  wR.png  wB.png  wN.png  wP.png
    └── bK.png  bQ.png  bR.png  bB.png  bN.png  bP.png
```

## 📸 Preview

> *<img src="https://github.com/user-attachments/assets/d9300ed2-4471-4fd2-9c0a-b74865652f3a" width="600" alt="ChessForge Preview"/>*

---

---

## ⚙️ Features

### ♟️ Gameplay
- ✅ Full two-player local chess
- ✅ Turn enforcement — White moves first, then Black
- ✅ Click to select, click to move (SFML GUI)
- ✅ Selected piece highlighted in **yellow**
- ✅ King highlighted in **red** when in check

### 🧩 Piece Rules
| Piece | Rule Implemented |
|-------|-----------------|
| ♙ Pawn | 1-square move, 2-square opening, diagonal capture |
| ♖ Rook | Horizontal & vertical, path must be clear |
| ♘ Knight | L-shaped jump, can leap over pieces |
| ♗ Bishop | Diagonal only, path must be clear |
| ♛ Queen | Any direction, path must be clear |
| ♔ King | 1 square any direction, cannot move into check |

### 🛡️ Chess Logic
- ✅ **Check detection** — sliding pieces blocked by pawns cannot cause phantom check
- ✅ **Checkmate detection** — tries every possible escape move
- ✅ **Stalemate detection** — no legal moves but not in check
- ✅ **Block check** — any piece can block the attack on the king
- ✅ **Illegal move prevention** — cannot move into check
- ✅ **Own piece capture prevention** — in both real moves and simulations

### 🖥️ GUI & Display
- ✅ Classic chessboard colors (cream & brown)
- ✅ On-screen **status bar** — shows turn, CHECK, CHECKMATE, STALEMATE
- ✅ Color-coded bar — orange for check, red for game over
- ✅ Window title updates with game state

---

## 🏗️ OOP Design

```
                        ┌─────────────┐
                        │   Piece.h   │  ← Abstract Base Class
                        │  symbol: char│
                        │ isValidMove()│  ← Pure Virtual Function
                        └──────┬──────┘
                               │  inherits
          ┌──────────┬─────────┼──────────┬──────────┬──────────┐
          │          │         │          │          │          │
       ┌──┴──┐   ┌───┴─┐  ┌───┴──┐  ┌───┴──┐  ┌────┴─┐  ┌────┴─┐
       │Pawn │   │Rook │  │Knight│  │Bishop│  │Queen │  │ King │
       └──┬──┘   └───┬─┘  └───┬──┘  └───┬──┘  └────┬─┘  └────┬─┘
          │          │         │          │          │          │
          └──────────┴─────────┴──────────┴──────────┴──────────┘
                               │  used by
                        ┌──────┴──────┐
                        │   Board.h   │  ← Manages grid, turns,
                        │  grid[8][8] │    check/checkmate logic
                        └──────┬──────┘
                               │  rendered by
                        ┌──────┴──────┐
                        │ gui_main.cpp│  ← SFML window & input
                        └─────────────┘
```

### Core OOP Concepts Applied

| Concept | How it's used |
|---|---|
| **Abstraction** | `Piece` is abstract — `isValidMove()` is pure virtual, cannot instantiate `Piece` directly |
| **Inheritance** | All 6 piece classes extend `Piece` and override `isValidMove()` |
| **Polymorphism** | `grid[i][j]->isValidMove(...)` calls the right piece's logic at runtime |
| **Encapsulation** | `Board` owns and protects the grid; pieces encapsulate their own movement rules |

---

## 🚀 Getting Started

### Prerequisites
- C++17 or later
- [SFML 3.x](https://www.sfml-dev.org/download.php)
- Visual Studio / g++

### Build & Run

**Visual Studio:**
1. Clone the repo
2. Open the `.sln` file
3. Link SFML in project properties
4. Place `assets/` folder in the output directory
5. Hit **Run**

**g++ (Linux/Mac):**
```bash
git clone https://github.com/Usman-0515/ChessForge.git
cd ChessForge
g++ -o ChessForge gui_main.cpp Board.cpp Pawn.cpp Rook.cpp \
    Knight.cpp Bishop.cpp Queen.cpp King.cpp \
    -lsfml-graphics -lsfml-window -lsfml-system
./ChessForge
```

---

## 🎮 How to Play

1. **White** always moves first (top side)
2. **Click** a piece to select it — it highlights yellow
3. **Click** the destination square to move
4. If the move is **invalid**, the status bar tells you why
5. The **king flashes red** when in check
6. Game ends on **Checkmate** or **Stalemate**

---

## 👥 Team

| Name | Contribution |
|------|------|
| **Usman** | Game logic design, piece movement rules, check/checkmate/stalemate engine, move validation & simulation, bug fixing |
| **Uzwa** | Core OOP architecture, Board class, SFML GUI implementation, piece rendering, game loop & input handling |

> 📚 Final Project — Object Oriented Programming  
> 🏫 FAST NUCES

---

<div align="center">

**⭐ If you like ChessForge, give it a star!**

*Built with passion, debugged with patience.*  
♟️ **ChessForge** — 64 squares. 6 pieces. Zero compromises.

</div>
