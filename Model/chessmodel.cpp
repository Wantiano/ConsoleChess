#include "chessmodel.h"
#include "../View/chessview.h"
#include <iostream>

void ChessModel::newGame()
{
    currentPlayer = false;
    resetTable();
    view->NewGameStarted();
}

PieceEnum ChessModel::getField(int x, int y)
{
    if (table[y][x] == nullptr)
        return EMPTY;
    return table[y][x]->getType();
}

bool ChessModel::getFieldColor(int x, int y)
{
    if (table[y][x] == nullptr)
        return true;

    return !table[y][x]->playerColor();
}

void ChessModel::giveUp()
{
    view->GameOver();
}

void ChessModel::clearTable()
{
    for (std::vector<Piece *> vec : table)
        for (Piece *piece : vec)
            delete piece;

    table.clear();
}

void ChessModel::resetTable()
{
    clearTable();

    table.resize(8);

    table[0] = std::vector<Piece *>({new Rook(0, 0, true),
                                     new Knight(1, 0, true),
                                     new Bishop(2, 0, true),
                                     new Queen(3, 0, true),
                                     new King(4, 0, true),
                                     new Bishop(5, 0, true),
                                     new Knight(6, 0, true),
                                     new Rook(7, 0, true)});

    table[1] = std::vector<Piece *>({new Pawn(0, 1, true),
                                     new Pawn(1, 1, true),
                                     new Pawn(2, 1, true),
                                     new Pawn(3, 1, true),
                                     new Pawn(4, 1, true),
                                     new Pawn(5, 1, true),
                                     new Pawn(6, 1, true),
                                     new Pawn(7, 1, true)});

    for (int i = 2; i < 6; i++)
        table[i] = std::vector<Piece *>({nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr});

    table[6] = std::vector<Piece *>({new Pawn(0, 6, false),
                                     new Pawn(1, 6, false),
                                     new Pawn(2, 6, false),
                                     new Pawn(3, 6, false),
                                     new Pawn(4, 6, false),
                                     new Pawn(5, 6, false),
                                     new Pawn(6, 6, false),
                                     new Pawn(7, 6, false)});

    table[7] = std::vector<Piece *>({new Rook(0, 7, false),
                                     new Knight(1, 7, false),
                                     new Bishop(2, 7, false),
                                     new Queen(3, 7, false),
                                     new King(4, 7, false),
                                     new Bishop(5, 7, false),
                                     new Knight(6, 7, false),
                                     new Rook(7, 7, false)});
}

void ChessModel::step(int x_from, int y_from, int x_to, int y_to)
{
    if (x_from < 0 || x_to < 0 || y_from < 0 || y_to < 0 || x_from > 7 || x_to > 7 || y_from > 7 || y_to > 7)
        throw Exceptions::OUTOFTABLE;

    if (table[y_from][x_from] == nullptr)
        throw Exceptions::EMPTYFIELD;

    if (currentPlayer != table[y_from][x_from]->playerColor())
        throw Exceptions::ILLEGALMOVE;

    if (!table[y_from][x_from]->step(x_to, y_to, table))
        throw Exceptions::ILLEGALMOVE;

    bool king = false;

    if (table[y_to][x_to] != nullptr)
    {
        if (currentPlayer == table[y_to][x_to]->playerColor())
            throw Exceptions::ILLEGALMOVE;

        king = table[y_to][x_to]->getType() == KING;

        delete table[y_to][x_to];
    }

    table[y_from][x_from]->setCoords(x_to, y_to);
    table[y_to][x_to] = table[y_from][x_from];
    table[y_from][x_from] = nullptr;

    currentPlayer = !currentPlayer;
    view->UpdateTable();
    if (king)
        giveUp();
}