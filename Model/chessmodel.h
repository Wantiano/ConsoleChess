#ifndef CHESS_MODEL
#define CHESS_MODEL

#include "Pieces/pieces.h"
#include <vector>

class ChessView;

class ChessModel
{
private:
    ChessView *view;
    std::vector<std::vector<Piece *>> table;
    bool currentPlayer;
    bool whatIfStep(int, int, int, int, bool);
    bool gameOver;
    bool kingCantStep(bool, std::pair<int, int> &);
    bool othersCanStep(bool);
    void pawnPromotion(int,int);

// public because of tests
public:
    void clearTable();
    void resetTable();
    bool checkIfCheck(bool);
    bool checkIfCheckMate(bool);

// public:
    enum Exceptions
    {
        OUTOFTABLE,
        EMPTYFIELD,
        ILLEGALMOVE
    };

    ChessModel(ChessView *view) : view(view) {}
    ~ChessModel() { clearTable(); }

    PieceEnum getField(int x, int y);
    bool getFieldColor(int x, int y);
    int getPlayer() { return currentPlayer; }
    bool isGameOver() { return gameOver; }

    void newGame();
    void step(int x_from, int y_from, int x_to, int y_to);
    void giveUp();
};

#endif /*CHESS_MODEL*/
