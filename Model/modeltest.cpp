#define CATCH_CONFIG_MAIN
#include "../View/chessview.h"
#include "../catch.hpp"

ChessView view;
ChessModel *model = &view.getModel();

TEST_CASE("Testing checkmate")
{
    model->newGame();
    model->step(5, 6, 5, 5);
    model->step(4, 1, 4, 2);
    model->step(6, 6, 6, 4);
    model->step(3, 0, 7, 4);
    CHECK(model->isGameOver());
}

TEST_CASE("Testing check but not checkmate")
{
    model->newGame();
    model->step(2, 6, 2, 5);
    model->step(4, 1, 4, 3);
    model->step(3, 7, 2, 6);
    model->step(5, 1, 5, 3);
    model->step(5, 6, 5, 5);
    model->step(3, 0, 7, 4);
    CHECK_FALSE(model->isGameOver());
}

TEST_CASE("Testing check but not checkmate because other piece can step in way")
{
    model->newGame();
    model->step(0, 6, 0, 5);
    model->step(6, 0, 7, 2);
    model->step(0, 7, 0, 6);
    model->step(7, 2, 6, 4);
    model->step(0, 5, 0, 4);
    model->step(6, 4, 4, 3);
    model->step(0, 6, 0, 5);
    model->step(4, 3, 5, 5);
    CHECK_FALSE(model->isGameOver());
}