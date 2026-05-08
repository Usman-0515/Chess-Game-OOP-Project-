#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <optional>
#include <fstream>

const unsigned int TILE = 80;
const unsigned int BOARD_PX = TILE * 8;
const unsigned int SIDEBAR_WIDTH = 260;

void saveResult(const std::string& whitePlayer,
    const std::string& blackPlayer,
    const std::string& winner,
    const std::string& winningSide)
{
    std::ofstream file("game_results.txt", std::ios::app);

    if (file.is_open()) {
        file << "White Player : " << whitePlayer << "\n";
        file << "Black Player : " << blackPlayer << "\n";
        file << "Winner       : " << winner << "\n";
        file << "Winning Side : " << winningSide << "\n";
        file << "---------------------------------\n";
        file.close();
    }
}

int main() {

    std::string whitePlayer;
    std::string blackPlayer;

    std::cout << "Enter White Player Name: ";
    std::getline(std::cin, whitePlayer);

    std::cout << "Enter Black Player Name: ";
    std::getline(std::cin, blackPlayer);

    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(BOARD_PX + SIDEBAR_WIDTH, BOARD_PX)),
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

    sf::Font font;

    bool fontLoaded =
        font.openFromFile("C:/Windows/Fonts/arial.ttf");

    Board board;

    int selRow = -1;
    int selCol = -1;

    std::string statusMsg = "";
    bool gameOver = false;
    bool resultSaved = false;

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            else if (const auto* mb =
                event->getIf<sf::Event::MouseButtonPressed>()) {

                if (gameOver)
                    continue;

                if (mb->button != sf::Mouse::Button::Left)
                    continue;

                if (mb->position.x >= (int)BOARD_PX)
                    continue;

                int col = mb->position.x / (int)TILE;
                int row = mb->position.y / (int)TILE;

                if (row < 0 || row >= 8 || col < 0 || col >= 8)
                    continue;

                if (selRow == -1) {

                    Piece* p = board.getPiece(row, col);

                    if (p) {

                        char s = p->getSymbol();

                        bool pieceIsWhite =
                            (s >= 'A' && s <= 'Z');

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

                            if (!resultSaved) {

                                if (sideToMove) {

                                    saveResult(
                                        whitePlayer,
                                        blackPlayer,
                                        blackPlayer,
                                        "Black"
                                    );
                                }

                                else {

                                    saveResult(
                                        whitePlayer,
                                        blackPlayer,
                                        whitePlayer,
                                        "White"
                                    );
                                }

                                resultSaved = true;
                            }
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

        for (int r = 0; r < 8; r++) {

            for (int c = 0; c < 8; c++) {

                sf::RectangleShape sq(
                    sf::Vector2f((float)TILE, (float)TILE));

                sq.setPosition(
                    sf::Vector2f(
                        (float)(c * (int)TILE),
                        (float)(r * (int)TILE)));

                bool light = (r + c) % 2 == 0;

                sq.setFillColor(
                    light
                    ? sf::Color(240, 217, 181)
                    : sf::Color(181, 136, 99));

                window.draw(sq);
            }
        }

        if (selRow != -1) {

            sf::RectangleShape hl(
                sf::Vector2f((float)TILE, (float)TILE));

            hl.setPosition(
                sf::Vector2f(
                    (float)(selCol * (int)TILE),
                    (float)(selRow * (int)TILE)));

            hl.setFillColor(
                sf::Color(255, 255, 0, 110));

            window.draw(hl);
        }

        for (int r = 0; r < 8; r++) {

            for (int c = 0; c < 8; c++) {

                Piece* p = board.getPiece(r, c);

                if (!p)
                    continue;

                char s = p->getSymbol();

                auto it = textures.find(s);

                if (it == textures.end())
                    continue;

                sf::Sprite spr(it->second);

                auto sz = it->second.getSize();

                spr.setScale(
                    sf::Vector2f(
                        (float)TILE / sz.x,
                        (float)TILE / sz.y));

                spr.setPosition(
                    sf::Vector2f(
                        (float)(c * (int)TILE),
                        (float)(r * (int)TILE)));

                window.draw(spr);
            }
        }

        sf::RectangleShape sidebar(
            sf::Vector2f((float)SIDEBAR_WIDTH,
                (float)BOARD_PX));

        sidebar.setPosition(
            sf::Vector2f((float)BOARD_PX, 0));

        sidebar.setFillColor(
            sf::Color(40, 40, 40));

        window.draw(sidebar);

        if (fontLoaded) {

            sf::Text title(font);
            title.setCharacterSize(28);
            title.setFillColor(sf::Color::White);
            title.setString("CHESS INFO");
            title.setPosition(sf::Vector2f(660.f, 20.f));
            window.draw(title);

            sf::Text playerInfo(font);
            playerInfo.setCharacterSize(22);
            playerInfo.setFillColor(sf::Color::Cyan);

            std::string turnText =
                board.getTurn()
                ? whitePlayer + " (White)"
                : blackPlayer + " (Black)";

            playerInfo.setString(
                "Current Turn:\n" + turnText);

            playerInfo.setPosition(
                sf::Vector2f(660.f, 90.f));

            window.draw(playerInfo);

            sf::Text status(font);
            status.setCharacterSize(24);

            if (statusMsg == "CHECK")
                status.setFillColor(sf::Color::Yellow);

            else if (statusMsg == "CHECKMATE")
                status.setFillColor(sf::Color::Red);

            else
                status.setFillColor(sf::Color::White);

            std::string displayMsg = "";

            if (statusMsg == "CHECK")
                displayMsg = "CHECK!";

            else if (statusMsg == "CHECKMATE") {

                std::string winner =
                    board.getTurn()
                    ? blackPlayer
                    : whitePlayer;

                displayMsg =
                    "CHECKMATE!\nWinner:\n" + winner;
            }

            else if (statusMsg == "STALEMATE")
                displayMsg = "STALEMATE!";

            status.setString(displayMsg);

            status.setPosition(
                sf::Vector2f(660.f, 240.f));

            window.draw(status);

            sf::Text instructions(font);

            instructions.setCharacterSize(18);
            instructions.setFillColor(sf::Color::White);

            instructions.setString(
                "Instructions:\n"
                "- Click piece\n"
                "- Click destination\n"
                "- Yellow = Selected\n"
                "- Game saves winner\n"
                "  automatically");

            instructions.setPosition(
                sf::Vector2f(660.f, 420.f));

            window.draw(instructions);
        }

        std::string title =
            "Chess - ";

        title +=
            (board.getTurn()
                ? "White"
                : "Black");

        title += " to move";

        if (!statusMsg.empty())
            title += " | " + statusMsg;

        window.setTitle(title);

        window.display();
    }

    return 0;
}
