#include "King.h"

King::King(char s) : Piece(s) {}

bool King::isValidMove(int sx, int sy, int dx, int dy, Board* board) {
	return abs(dx - sx) <= 1 && abs(dy - sy) <= 1;
}