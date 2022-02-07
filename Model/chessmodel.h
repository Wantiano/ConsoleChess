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

    void clearTable();
    void resetTable();

public:
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

    void newGame();
    void giveUp();
    void step(int x_from, int y_from, int x_to, int y_to);
};

#endif /*CHESS_MODEL*/
