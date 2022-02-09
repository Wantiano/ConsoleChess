#include "chessmodel.h"
#include "../View/chessview.h"

void ChessModel::newGame()
{
    gameOver = false;
    currentPlayer = false;
    resetTable();
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
    gameOver = true;
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

    // Unable to step there
    if (!table[y_from][x_from]->step(x_to, y_to, table))
        throw Exceptions::ILLEGALMOVE;

    // Opponent's puppet
    if (currentPlayer != table[y_from][x_from]->playerColor())
        throw Exceptions::ILLEGALMOVE;

    if (table[y_to][x_to] != nullptr)
    {
        // Step on self puppet
        if (currentPlayer == table[y_to][x_to]->playerColor())
            throw Exceptions::ILLEGALMOVE;

        delete table[y_to][x_to];
    }

    table[y_from][x_from]->setCoords(x_to, y_to);
    table[y_to][x_to] = table[y_from][x_from];
    table[y_from][x_from] = nullptr;

    currentPlayer = !currentPlayer;
    view->updateTable();

    if (checkIfCheck(currentPlayer))
    {
        if (checkIfCheckMate(currentPlayer))
            giveUp();
        else
            view->alarmForCheck();
    }
}

//Returns if after step is check
bool ChessModel::whatIfStep(int x_from, int y_from, int x_to, int y_to, bool player)
{
    // Unable to step there
    if (!table[y_from][x_from]->step(x_to, y_to, table))
        return true;

    Piece *tempPiece = nullptr;

    if (table[y_to][x_to] != nullptr)
    {
        // Step on self puppet
        if (currentPlayer == table[y_to][x_to]->playerColor())
            return true;

        tempPiece = table[y_to][x_to];
    }

    table[y_from][x_from]->setCoords(x_to, y_to);
    table[y_to][x_to] = table[y_from][x_from];
    table[y_from][x_from] = nullptr;

    bool isCheck = checkIfCheck(player);

    table[y_from][x_from] = table[y_to][x_to];
    table[y_to][x_to] = tempPiece;
    table[y_from][x_from]->setCoords(x_from, y_from);

    return isCheck;
}

bool ChessModel::kingCantStep(bool player, std::pair<int, int> &kingCoords)
{
    std::vector<std::pair<int, int>> steps;
    if (kingCoords.first > 0)
    {
        steps.push_back(std::make_pair<int, int>(kingCoords.first - 1, kingCoords.second + 0));
        if (kingCoords.second > 0)
            steps.push_back(std::make_pair<int, int>(kingCoords.first - 1, kingCoords.second - 1));
    }

    if (kingCoords.second > 0)
    {
        steps.push_back(std::make_pair<int, int>(kingCoords.first + 0, kingCoords.second - 1));
        if (kingCoords.first < 8)
            steps.push_back(std::make_pair<int, int>(kingCoords.first + 1, kingCoords.second - 1));
    }

    if (kingCoords.second < 8)
    {
        steps.push_back(std::make_pair<int, int>(kingCoords.first + 0, kingCoords.second + 1));
        if (kingCoords.first > 0)
            steps.push_back(std::make_pair<int, int>(kingCoords.first - 1, kingCoords.second + 1));
    }

    if (kingCoords.first < 8)
    {
        steps.push_back(std::make_pair<int, int>(kingCoords.first + 1, kingCoords.second + 0));
        if (kingCoords.second < 8)
            steps.push_back(std::make_pair<int, int>(kingCoords.first + 1, kingCoords.second + 1));
    }

    bool cantStep = true;

    for (const std::pair<int, int> &oneStep : steps)
        cantStep &= whatIfStep(kingCoords.first, kingCoords.second, oneStep.first, oneStep.second, player);

    return cantStep;
}

bool ChessModel::othersCanStep(bool player)
{
    for (std::vector<Piece *> v : table)
    {
        for (Piece *p : v)
        {
            if(p != nullptr)
            {
                std::pair<int,int> coords = p->getCoords();
                if (p->playerColor() == player)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            if(!whatIfStep(coords.first, coords.second, i, j, player))
                                return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool ChessModel::checkIfCheck(bool player)
{
    std::pair<int, int> kingCoords;

    for (std::vector<Piece *> v : table)
        for (Piece *p : v)
            if (p != nullptr && p->playerColor() == player && p->getType() == PieceEnum::KING)
                kingCoords = p->getCoords();

    for (std::vector<Piece *> v : table)
        for (Piece *p : v)
            if (p != nullptr && p->playerColor() == !player && p->step(kingCoords.first, kingCoords.second, table))
                return true;

    return false;
}

bool ChessModel::checkIfCheckMate(bool player)
{
    std::pair<int, int> kingCoords;
    Piece *king = nullptr;

    for (const std::vector<Piece *> &v : table)
        for (Piece *p : v)
            if (p != nullptr && p->playerColor() == player && p->getType() == PieceEnum::KING)
                king = p;

    kingCoords = king->getCoords();

    bool checkMate = kingCantStep(player, kingCoords) && othersCanStep(player);

    return checkMate;
}