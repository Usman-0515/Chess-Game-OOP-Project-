#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(char s) : Piece(s) {}

bool Pawn::isValidMove(int sx, int sy, int dx, int dy, Board* board) {

    if (symbol == 'P') {  // White pawn — moves downward (row increases)

        // Normal 1-square forward move (must be empty)
        if (dx == sx + 1 && dy == sy && board->getPiece(dx, dy) == nullptr)
            return true;

        // First move: 2 squares forward (both squares must be empty)
        if (sx == 1 && dx == sx + 2 && dy == sy
            && board->getPiece(sx + 1, sy) == nullptr
            && board->getPiece(dx, dy) == nullptr)
            return true;

        // Diagonal capture (must have an enemy piece there)
        if (dx == sx + 1 && abs(dy - sy) == 1 && board->getPiece(dx, dy) != nullptr)
            return true;
    }
    else {  // Black pawn — moves upward (row decreases)

        // Normal 1-square forward move (must be empty)
        if (dx == sx - 1 && dy == sy && board->getPiece(dx, dy) == nullptr)
            return true;

        // First move: 2 squares forward (both squares must be empty)
        if (sx == 6 && dx == sx - 2 && dy == sy
            && board->getPiece(sx - 1, sy) == nullptr
            && board->getPiece(dx, dy) == nullptr)
            return true;

        // Diagonal capture (must have an enemy piece there)
        if (dx == sx - 1 && abs(dy - sy) == 1 && board->getPiece(dx, dy) != nullptr)
            return true;
    }

    return false;
}