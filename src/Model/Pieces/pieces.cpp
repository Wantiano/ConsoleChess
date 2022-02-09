#include "pieces.h"

bool King::step(int x, int y, const std::vector<std::vector<Piece *>> &table)
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
        if (x != this->x || y != this->y)
            if (abs(x - this->x) < 2 && abs(y - this->y) < 2)
                return true;

    return false;
}

bool Queen::step(int x, int y, const std::vector<std::vector<Piece *>> &table)
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        if (!(x == this->x && y == this->y))
        {
            if (x == this->x || y == this->y)
            {
                if (clearWayVertHor(this->x, this->y, x, y, table))
                    return true;
            }
            else if (abs(x - this->x) == abs(y - this->y))
            {
                if (clearWayCross(this->x, this->y, x, y, table))
                    return true;
            }
        }
    }

    return false;
}

bool Bishop::step(int x, int y, const std::vector<std::vector<Piece *>> &table)
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
        if (x != this->x || y != this->y)
            if (abs(x - this->x) == abs(y - this->y))
                if (clearWayCross(this->x, this->y, x, y, table))
                    return true;

    return false;
}

bool Rook::step(int x, int y, const std::vector<std::vector<Piece *>> &table)
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
        if (x != this->x || y != this->y)
            if (x == this->x || y == this->y)
                if (clearWayVertHor(this->x, this->y, x, y, table))
                    return true;

    return false;
}

bool Knight::step(int x, int y, const std::vector<std::vector<Piece *>> &table)
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
        if (x != this->x || y != this->y)
            if ((abs(x - this->x) == 2 && abs(y - this->y) == 1) || (abs(x - this->x) == 1 && abs(y - this->y) == 2))
                return true;

    return false;
}

bool Pawn::step(int x, int y, const std::vector<std::vector<Piece *>> &table)
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        if (y != this->y)
        {
            if (x == this->x && table[y][x] == nullptr)
            {
                if (this->color)
                {
                    if (y == this->y + 1 || (y == this->y + 2 && this->y == 1))
                        if (clearWayVertHor(this->x, this->y, x, y, table))
                            return true;
                }
                else
                {
                    if (y == this->y - 1 || (y == this->y - 2 && this->y == 6))
                        if (clearWayVertHor(this->x, this->y, x, y, table))
                            return true;
                }
            }
            else if (table[y][x] != nullptr)
            {
                if (this->color && y == this->y + 1 && abs(x - this->x) == 1)
                    return true;

                if (!this->color && y == this->y - 1 && abs(x - this->x) == 1)
                    return true;
            }
        }
    }

    return false;
}

bool Piece::clearWayVertHor(int from_x, int from_y, int to_x, int to_y, const std::vector<std::vector<Piece *>> &table)
{
    if (from_x != to_x)
    {
        int less = std::min(from_x, to_x) + 1,
            greater = std::max(from_x, to_x);

        for (; less < greater; ++less)
            if (table[from_y][less] != nullptr)
                return false;
    }
    if (from_y != to_y)
    {
        int less = std::min(from_y, to_y) + 1,
            greater = std::max(from_y, to_y);

        for (; less < greater; ++less)
            if (table[less][from_x] != nullptr)
                return false;
    }

    return true;
}

bool Piece::clearWayCross(int from_x, int from_y, int to_x, int to_y, const std::vector<std::vector<Piece *>> &table)
{
    std::pair<int, int> less, greater;
    if (from_x < to_x)
    {
        less = std::pair<int, int>(from_x, from_y);
        greater = std::pair<int, int>(to_x, to_y);
    }
    else
    {
        less = std::pair<int, int>(to_x, to_y);
        greater = std::pair<int, int>(from_x, from_y);
    }

    int addToY = greater.second - less.second < 0 ? -1 : 1;

    less.first += 1;
    less.second += addToY;

    for (; less.first < greater.first; ++less.first, less.second += addToY)
        if (table[less.second][less.first] != nullptr)
            return false;

    return true;
}