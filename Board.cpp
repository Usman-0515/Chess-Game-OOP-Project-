#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <iostream>

using namespace std;

Board::Board() {
	whiteturn = true;
	initialize();
}

void Board::initialize() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			grid[i][j] = nullptr;

	//Pawns
	for (int i = 0; i < 8; i++) {
		grid[1][i] = new Pawn('P');
		grid[6][i] = new Pawn('p');
	}

	//Rooks
	grid[0][0] = new Rook('R');
	grid[0][7] = new Rook('R');
	grid[7][0] = new Rook('r');
	grid[7][7] = new Rook('r');

	//Knights
	grid[0][1] = new Knight('N');
	grid[0][6] = new Knight('N');
	grid[7][1] = new Knight('n');
	grid[7][6] = new Knight('n');

	//Bishops
	grid[0][2] = new Bishop('B');
	grid[0][5] = new Bishop('B');
	grid[7][2] = new Bishop('b');
	grid[7][5] = new Bishop('b');

	//Queens
	grid[0][3] = new Queen('Q');
	grid[7][3] = new Queen('q');

	//Kings
	grid[0][4] = new King('K');
	grid[7][4] = new King('k');
}

//Display

void Board::display() {
	cout << "\n";

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (grid[i][j])
				cout << grid[i][j]->getSymbol() << " ";
			else
				cout << ". ";
		}
		cout << endl;
	}
}

bool Board::movePiece(int sx, int sy, int dx, int dy) {

	Piece* p = grid[sx][sy];
	if (!p) return false;

	// BUG 5 FIX: make sure the player is moving their OWN piece
	char s = p->getSymbol();
	if (whiteturn && s >= 'a') return false;   // white tried to move black piece
	if (!whiteturn && s <= 'Z') return false;  // black tried to move white piece

	if (!p->isValidMove(sx, sy, dx, dy, this))
		return false;

	Piece* dest = grid[dx][dy];

	// prevent capturing own piece
	if (dest) {
		if ((whiteturn && dest->getSymbol() <= 'Z') ||
			(!whiteturn && dest->getSymbol() >= 'a'))
			return false;
	}

	// path check for sliding pieces
	if (dynamic_cast<Rook*>(p) ||
		dynamic_cast<Bishop*>(p) ||
		dynamic_cast<Queen*>(p)) {

		if (!isPathClear(sx, sy, dx, dy))
			return false;
	}

	// BUG 4 FIX: simulate move, reject if it leaves own king in check
	grid[dx][dy] = p;
	grid[sx][sy] = nullptr;

	bool movePutsKingInCheck = isCheck(whiteturn);

	if (movePutsKingInCheck) {
		// undo the move
		grid[sx][sy] = p;
		grid[dx][dy] = dest;
		return false;
	}

	whiteturn = !whiteturn;
	return true;
}

//PathClear check

bool Board::isPathClear(int sx, int sy, int dx, int dy) {

	int stepX = (dx > sx) ? 1 : (dx < sx ? -1 : 0);
	int stepY = (dy > sy) ? 1 : (dy < sy ? -1 : 0);

	int x = sx + stepX;
	int y = sy + stepY;

	while (x != dx || y != dy) {

		if (grid[x][y] != nullptr)
			return false;

		x += stepX;
		y += stepY;
	}

	return true;
}

//ischeck

bool Board::isCheck(bool white)
{
	Position king = findKing(white);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] == nullptr)
				continue;

			char s = grid[i][j]->getSymbol();

			if ((white && s >= 'a') ||
				(!white && s <= 'Z'))
			{
				if (grid[i][j]->isValidMove(
					i, j,
					king.getX(),
					king.getY(), this))
					return true;
			}
		}

	return false;
}

//Checkmate

bool Board::isCheckmate(bool white)
{
	if (!isCheck(white))
		return false;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] == nullptr)
				continue;

			char s = grid[i][j]->getSymbol();

			if ((white && s <= 'Z') ||
				(!white && s >= 'a'))
			{
				for (int x = 0; x < 8; x++)
					for (int y = 0; y < 8; y++)
					{
						if (!grid[i][j]->isValidMove(i, j, x, y, this))
							continue;

						if ((dynamic_cast<Rook*>(grid[i][j]) ||
							dynamic_cast<Bishop*>(grid[i][j]) ||
							dynamic_cast<Queen*>(grid[i][j]))
							&& !isPathClear(i, j, x, y))
							continue;

						Piece* temp = grid[x][y];
						Piece* moving = grid[i][j];

						grid[x][y] = moving;
						grid[i][j] = nullptr;

						bool stillInCheck = isCheck(white);

						grid[i][j] = moving;
						grid[x][y] = temp;

						if (!stillInCheck)
							return false;
					}
			}
		}

	return true;
}

//Stalemate

bool Board::isStalemate(bool white)
{
	if (isCheck(white))
		return false;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] == nullptr)
				continue;

			char s = grid[i][j]->getSymbol();

			if ((white && s <= 'Z') ||
				(!white && s >= 'a'))
			{
				for (int x = 0; x < 8; x++)
					for (int y = 0; y < 8; y++)
					{
						if (!grid[i][j]->isValidMove(i, j, x, y, this))
							continue;

						Piece* temp = grid[x][y];
						Piece* moving = grid[i][j];

						grid[x][y] = moving;
						grid[i][j] = nullptr;

						bool stillCheck = isCheck(white);

						grid[i][j] = moving;
						grid[x][y] = temp;

						if (!stillCheck)
							return false;
					}
			}
		}

	return true;
}

//find king

Position Board::findKing(bool white)
{
	char king = white ? 'K' : 'k';

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (grid[i][j] &&
				grid[i][j]->getSymbol() == king)
				return Position(i, j);

	return Position(-1, -1);
}

//GetPiece

Piece* Board::getPiece(int x, int y) {
	return grid[x][y];
}

//Turn

bool Board::getTurn() {
	return whiteturn;
}