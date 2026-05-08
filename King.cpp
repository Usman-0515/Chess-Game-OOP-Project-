#include "King.h"
#include "Board.h"
King::King(char s) : Piece(s) {}
bool King::isValidMove(int sx, int sy, int dx, int dy, Board* board) {
    if (sx == dx && sy == dy) return false;  
    return abs(dx - sx) <= 1 && abs(dy - sy) <= 1;
}