#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <optional>

const unsigned int TILE = 80;
const unsigned int BOARD_PX = TILE * 8;

int main() {
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(BOARD_PX, BOARD_PX)),
        "Chess"
    );
    window.setFramerateLimit(60);

    
    std::map<char, sf::Texture> textures;
    std::string symbols = "KQRBNPkqrbnp";
    for (char c : symbols) {
        std::string color = std::isupper((unsigned char)c) ? "w" : "b";
        std::string upper(1, (char)std::toupper((unsigned char)c));
        std::string path = "assets/" + color + upper + ".png";
        sf::Texture t;
        if (!t.loadFromFile(path)) {
            std::cerr << "Failed to load " << path << "\n";
            return 1;
        }
        textures[c] = t;
    }

    Board board;
    int selRow = -1, selCol = -1;
    std::string statusMsg = "";
    bool gameOver = false;

    while (window.isOpen()) {
      
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (gameOver) continue;
                if (mb->button != sf::Mouse::Button::Left) continue;

                int col = mb->position.x / (int)TILE;
                int row = mb->position.y / (int)TILE;
                if (row < 0 || row >= 8 || col < 0 || col >= 8) continue;

                if (selRow == -1) {
                    Piece* p = board.getPiece(row, col);
                    if (p) {
                        char s = p->getSymbol();
                        bool pieceIsWhite = (s >= 'A' && s <= 'Z');
                        if (pieceIsWhite == board.getTurn()) {
                            selRow = row;
                            selCol = col;
                        }
                    }
                }
                else {
                    if (board.movePiece(selRow, selCol, row, col)) {
                        bool sideToMove = board.getTurn();
                        if (board.isCheckmate(sideToMove)) {
                            statusMsg = "CHECKMATE";
                            gameOver = true;
                        }
                        else if (board.isStalemate(sideToMove)) {
                            statusMsg = "STALEMATE";
                            gameOver = true;
                        }
                        else if (board.isCheck(sideToMove)) {
                            statusMsg = "CHECK";
                        }
                        else {
                            statusMsg = "";
                        }
                    }
                    selRow = -1;
                    selCol = -1;
                }
            }
        }

        window.clear();

        // Squares
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                sf::RectangleShape sq(sf::Vector2f((float)TILE, (float)TILE));
                sq.setPosition(sf::Vector2f((float)(c * (int)TILE),
                    (float)(r * (int)TILE)));
                bool light = (r + c) % 2 == 0;
                sq.setFillColor(light ? sf::Color(240, 217, 181)
                    : sf::Color(181, 136, 99));
                window.draw(sq);
            }
        }

        // Highlight selected square
        if (selRow != -1) {
            sf::RectangleShape hl(sf::Vector2f((float)TILE, (float)TILE));
            hl.setPosition(sf::Vector2f((float)(selCol * (int)TILE),
                (float)(selRow * (int)TILE)));
            hl.setFillColor(sf::Color(255, 255, 0, 110));
            window.draw(hl);
        }

        // Pieces
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                Piece* p = board.getPiece(r, c);
                if (!p) continue;
                char s = p->getSymbol();
                auto it = textures.find(s);
                if (it == textures.end()) continue;
                sf::Sprite spr(it->second);
                auto sz = it->second.getSize();
                spr.setScale(sf::Vector2f((float)TILE / sz.x,
                    (float)TILE / sz.y));
                spr.setPosition(sf::Vector2f((float)(c * (int)TILE),
                    (float)(r * (int)TILE)));
                window.draw(spr);
            }
        }

        // Status in title bar
        std::string title = "Chess - ";
        title += (board.getTurn() ? "White" : "Black");
        title += " to move";
        if (!statusMsg.empty()) title += "  |  " + statusMsg;
        window.setTitle(title);

        window.display();
    }
    return 0;
}