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
    void newGame();

    std::string getPiece(int, int);
    void printHelp(int);
    void playerSteps();
    void NewGameStarted();

public:
    enum Exceptions
    {
        INVALIDFIELD
    };

    ChessView() : model(this) {}
    void run();

    void GameOver();
    void alarmForCheck();
    int alarmForPromotion(bool);
    void updateTable();
    bool isGameOver() { return gameOver; }

    //because of tests
    ChessModel& getModel() { return model; }
};

#endif /*CHESS_VIEW*/
