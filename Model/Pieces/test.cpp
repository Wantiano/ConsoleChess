#define CATCH_CONFIG_MAIN
#include "pieces.h"
#include "../../catch.hpp"

std::vector<std::vector<Piece *>> table;

TEST_CASE("Testing if king would be able to step on specified field", "")
{
    table.resize(8);
    for (int i = 0; i < 8; ++i)
        table[i].resize(8);

    King king(3, 3, true);
    CHECK(king.step(2, 2, table));
    CHECK(king.step(2, 3, table));
    CHECK(king.step(2, 4, table));
    CHECK(king.step(3, 2, table));
    CHECK(king.step(3, 4, table));
    CHECK(king.step(4, 2, table));
    CHECK(king.step(4, 3, table));
    CHECK(king.step(4, 4, table));

    CHECK_FALSE(king.step(3, 3, table));
    CHECK_FALSE(king.step(5, 3, table));
    CHECK_FALSE(king.step(3, 5, table));
    CHECK_FALSE(king.step(4, 5, table));
    CHECK_FALSE(king.step(5, 4, table));

    King king2(7, 7, false);

    CHECK_FALSE(king2.step(8, 7, table));
    CHECK_FALSE(king2.step(7, 8, table));
    CHECK_FALSE(king2.step(8, 8, table));
}

TEST_CASE("Testing if queen would be able to step on specified field", "")
{
    Queen queen(4, 3, true);
    CHECK(queen.step(5, 4, table));
    CHECK(queen.step(3, 2, table));
    CHECK(queen.step(5, 2, table));
    CHECK(queen.step(3, 4, table));

    CHECK(queen.step(7, 6, table));
    CHECK(queen.step(1, 0, table));
    CHECK(queen.step(1, 6, table));
    CHECK(queen.step(7, 0, table));
    CHECK(queen.step(2, 5, table));

    CHECK(queen.step(0, 3, table));
    CHECK(queen.step(7, 3, table));
    CHECK(queen.step(4, 0, table));
    CHECK(queen.step(4, 7, table));

    CHECK_FALSE(queen.step(4, 3, table));
    CHECK_FALSE(queen.step(1, 1, table));

    Queen queen2(4, 0, false);
    CHECK_FALSE(queen2.step(4, -1, table));
    CHECK_FALSE(queen2.step(4, 8, table));
    CHECK_FALSE(queen2.step(0, 8, table));
    CHECK_FALSE(queen2.step(0, -1, table));
    CHECK_FALSE(queen2.step(8, 7, table));
}

TEST_CASE("Testing if bishop would be able to step on specified field", "")
{
    Bishop bishop(4, 3, true);
    CHECK(bishop.step(5, 4, table));
    CHECK(bishop.step(3, 2, table));
    CHECK(bishop.step(5, 2, table));
    CHECK(bishop.step(3, 4, table));

    CHECK(bishop.step(7, 6, table));
    CHECK(bishop.step(1, 0, table));
    CHECK(bishop.step(1, 6, table));
    CHECK(bishop.step(7, 0, table));
    CHECK(bishop.step(2, 5, table));

    CHECK_FALSE(bishop.step(4, 3, table));
    CHECK_FALSE(bishop.step(4, 4, table));
    CHECK_FALSE(bishop.step(0, 0, table));

    Bishop bishop2(4, 0, false);
    CHECK_FALSE(bishop2.step(3, -1, table));
    CHECK_FALSE(bishop2.step(8, 4, table));
}

TEST_CASE("Testing if rook would be able to step on specified field", "")
{
    Rook rook(4, 4, true);
    CHECK(rook.step(5, 4, table));
    CHECK(rook.step(7, 4, table));
    CHECK(rook.step(4, 0, table));
    CHECK(rook.step(4, 7, table));

    CHECK_FALSE(rook.step(7, 6, table));
    CHECK_FALSE(rook.step(1, 0, table));
    CHECK_FALSE(rook.step(1, 6, table));
    CHECK_FALSE(rook.step(2, 5, table));
    CHECK_FALSE(rook.step(8, 4, table));
    CHECK_FALSE(rook.step(4, 8, table));
    CHECK_FALSE(rook.step(4, -1, table));
    CHECK_FALSE(rook.step(-1, 4, table));

    CHECK_FALSE(rook.step(5, 5, table));
    CHECK_FALSE(rook.step(5, 6, table));
    CHECK_FALSE(rook.step(2, 2, table));

    Rook rook2(4, 0, false);
    CHECK_FALSE(rook2.step(4, -1, table));
    CHECK_FALSE(rook2.step(8, 0, table));
}

TEST_CASE("Testing if knight would be able to step on specified field", "")
{
    Knight knight(2, 2, true);
    CHECK(knight.step(0, 1, table));
    CHECK(knight.step(0, 3, table));
    CHECK(knight.step(4, 1, table));
    CHECK(knight.step(4, 3, table));

    CHECK_FALSE(knight.step(2, 2, table));
    CHECK_FALSE(knight.step(2, 4, table));
    CHECK_FALSE(knight.step(4, 2, table));
    CHECK_FALSE(knight.step(4, 4, table));
    CHECK_FALSE(knight.step(6, 4, table));
    CHECK_FALSE(knight.step(4, 6, table));

    Knight knight2(1, 1, false);
    CHECK_FALSE(knight2.step(-1, 2, table));
    CHECK_FALSE(knight2.step(-1, 0, table));
}

TEST_CASE("Testing if pawn would be able to step on specified field", "")
{
    Pawn white_pawn(2, 6, false);
    CHECK(white_pawn.step(2, 5, table));
    CHECK(white_pawn.step(2, 4, table));

    CHECK_FALSE(white_pawn.step(2, 6, table));
    CHECK_FALSE(white_pawn.step(2, 7, table));
    CHECK_FALSE(white_pawn.step(1, 4, table));
    CHECK_FALSE(white_pawn.step(1, 5, table));
    CHECK_FALSE(white_pawn.step(1, 6, table));
    CHECK_FALSE(white_pawn.step(3, 4, table));
    CHECK_FALSE(white_pawn.step(3, 5, table));
    CHECK_FALSE(white_pawn.step(3, 6, table));

    Pawn black_pawn(2, 2, true);
    CHECK(black_pawn.step(2, 3, table));

    CHECK_FALSE(black_pawn.step(2, 4, table));
    CHECK_FALSE(black_pawn.step(2, 2, table));
    CHECK_FALSE(black_pawn.step(2, 1, table));
    CHECK_FALSE(black_pawn.step(2, 0, table));
    CHECK_FALSE(black_pawn.step(3, 1, table));
    CHECK_FALSE(black_pawn.step(3, 2, table));
    CHECK_FALSE(black_pawn.step(3, 3, table));
    CHECK_FALSE(black_pawn.step(1, 1, table));
    CHECK_FALSE(black_pawn.step(1, 2, table));
    CHECK_FALSE(black_pawn.step(1, 3, table));
}