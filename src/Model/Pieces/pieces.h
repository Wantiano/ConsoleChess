#ifndef PIECES_HEADER
#define PIECES_HEADER

#include <utility>
#include <cmath>
#include <vector>

enum PieceEnum
{
    EMPTY = 0,
    KING = 1,
    QUEEN = 2,
    ROOK = 3,
    BISHOP = 4,
    KNIGHT = 5,
    PAWN = 6,
};

class Piece
{
protected:
    int x, y;
    bool color; // true-black false-white
    PieceEnum type;

public:
    Piece(int x, int y, bool color, PieceEnum type) : x(x), y(y), color(color), type(type) {}
    virtual ~Piece() {}

    virtual bool step(int, int, const std::vector<std::vector<Piece *>> &) = 0;
    virtual bool clearWayVertHor(int, int, int, int, const std::vector<std::vector<Piece *>> &) final;
    virtual bool clearWayCross(int, int, int, int, const std::vector<std::vector<Piece *>> &) final;
    virtual bool playerColor() final { return color; }
    virtual PieceEnum getType() final { return type; }
    virtual std::pair<int, int> getCoords() final { return std::pair<int, int>(x, y); }
    virtual void setCoords(int x, int y) final
    {
        if (x < 0 || y < 0 || x > 7 || y > 7)
            return;

        this->x = x;
        this->y = y;
    }
};

class King : public Piece
{
public:
    King(int x, int y, bool color) : Piece(x, y, color, KING) {}
    bool step(int, int, const std::vector<std::vector<Piece *>> &) override;
};

class Queen : public Piece
{
public:
    Queen(int x, int y, bool color) : Piece(x, y, color, QUEEN) {}
    bool step(int, int, const std::vector<std::vector<Piece *>> &) override;
};

class Bishop : public Piece
{
public:
    Bishop(int x, int y, bool color) : Piece(x, y, color, BISHOP) {}
    bool step(int, int, const std::vector<std::vector<Piece *>> &) override;
};

class Rook : public Piece
{
public:
    Rook(int x, int y, bool color) : Piece(x, y, color, ROOK) {}
    bool step(int, int, const std::vector<std::vector<Piece *>> &) override;
};

class Knight : public Piece
{
public:
    Knight(int x, int y, bool color) : Piece(x, y, color, KNIGHT) {}
    bool step(int, int, const std::vector<std::vector<Piece *>> &) override;
};

class Pawn : public Piece
{
public:
    Pawn(int x, int y, bool color) : Piece(x, y, color, PAWN) {}
    bool step(int, int, const std::vector<std::vector<Piece *>> &) override;
};

#endif /*PIECES_HEADER*/