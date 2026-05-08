# ♟️ Chess Game — OOP Final Project

A fully functional Chess game built in **C++** using **Object-Oriented Programming** principles and the **SFML** graphics library.

---

## Team Members
- Member 1 — Uzwa Shahid
- Member 2 — Muhammad Usman

---

## Built With
- C++ (OOP)
- SFML 3 (Graphics Library)
- Visual Studio 2026

---

## Project Structure

| File | Description |
|------|-------------|
| `Piece.h` | Base class for all chess pieces |
| `Position.h` | Handles board positions |
| `Pawn.cpp/h` | Pawn movement logic |
| `Knight.cpp/h` | Knight movement logic |
| `Bishop.cpp/h` | Bishop movement logic |
| `Rook.cpp/h` | Rook movement logic |
| `Queen.cpp/h` | Queen movement logic |
| `King.cpp/h` | King movement logic |
| `Board.cpp/h` | Board setup and game state |
| `gui_main.cpp` | SFML GUI and main game loop |
| `assets/` | Chess piece images (PNG) |
| `game_results.txt` | Stores game results |

---

##  How to Run

1. Clone the repository:
```bash
   git clone https://github.com/Usman-0515/Chess-Game-OOP-Project-.git
```
2. Open `OOP_Final.slnx` in **Visual Studio 2022**
3. Make sure **SFML 3** is linked in project properties
4. Build and run the project (**Release** or **Debug** mode)

---

## Features
- Full chess board rendered with SFML
- All 6 piece types with valid move logic
- Two-player mode (local)
- Game result logging to `game_results.txt`

---

## OOP Concepts Used
- **Inheritance** — All pieces inherit from `Piece` base class
- **Polymorphism** — Each piece overrides movement methods
- **Encapsulation** — Data hidden within classes
- **Abstraction** — Clean interfaces via header files

---

## License
This project was developed as a Final Project for the Object-Oriented Programming course.

