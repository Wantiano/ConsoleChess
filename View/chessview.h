#ifndef CHESS_VIEW
#define CHESS_VIEW

#include <iostream>

#include "../Model/chessmodel.h"

class ChessModel;

void clearConsole();

class ChessView
{
private:
    ChessModel model;
    std::vector<Piece *> table;
    bool gameOver;

    std::pair<int, int> getFieldFromString(std::string);

public:
    enum Exceptions
    {
        INVALIDFIELD
    };

    ChessView() : model(this) {}

    void run();
    void newGame();

    void NewGameStarted();
    void UpdateTable();
    void GameOver();

    std::string getPiece(int, int);
    void printHelp(int);
    void playerSteps();
};

#endif /*CHESS_VIEW*/
