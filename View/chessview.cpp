#include "chessview.h"
#include "../Model/chessmodel.h"

void ChessView::printHelp(int a)
{
    if (a == 0)
    {
        std::cout
            << "|--------------------------------|" << std::endl
            << "| Command list:                  |" << std::endl
            << "| help -> Command list           |" << std::endl
            << "| quit -> Quit from game         |" << std::endl
            << "| new game -> Start a new game   |" << std::endl
            << "| howtoplay -> How to play chess |" << std::endl
            << "|--------------------------------|" << std::endl;
    }
    else
    {
        std::cout
            << "|-----------------------------|" << std::endl
            << "| In-game command list:       |" << std::endl
            << "| help -> Command list        |" << std::endl
            << "| leave -> Give up, end game  |" << std::endl
            << "| step -> Make a step         |" << std::endl
            << "|-----------------------------|" << std::endl;
    }
}

void ChessView::run()
{
    clearConsole();

    std::cout << std::endl
              << "Welcome traveller!" << std::endl
              << "Type \"help\" for help." << std::endl;

    std::string inp = "";
    while (inp != "quit")
    {
        std::cout << " > ";
        getline(std::cin, inp);

        if (inp == "help")
            printHelp(0);
        else if (inp == "quit")
            std::cout << "Thanks for playing!" << std::endl;
        else if (inp == "new game")
            newGame();
        else if (inp == "howtoplay")
            std::cout << "www.google.com" << std::endl;
        else
            std::cout << "Unknown command! Type \"help\" for help." << std::endl;
    }
}

void ChessView::newGame()
{
    std::cout << "Starting new game.." << std::endl;
    model.newGame();
    gameOver = false;
    NewGameStarted();
}

void ChessView::NewGameStarted()
{
    std::cout << "New game started"
              << "\nType \"help\" for help." << std::endl;

    clearConsole();
    updateTable();

    std::string inp = "";

    while (!gameOver)
    {
        if (model.getPlayer())
            std::cout << "\e[1;32m";
        std::cout << " > ";
        getline(std::cin, inp);

        if (inp == "help")
            printHelp(1);
        else if (inp == "leave")
            model.giveUp();
        else if (inp == "step")
            playerSteps();
        else if (inp != "")
            std::cout << "Unknown command! Type \"help\" for help." << std::endl;
        std::cout << "\u001b[0m";
    }
}

void ChessView::playerSteps()
{
    std::cout << "Give the fields <from to> your step: " << std::endl;
    std::cout << " > ";

    std::string from, to;

    std::cin >> from >> to;
    getchar();

    if (from.length() != 2 || to.length() != 2)
        return;

    std::pair<int, int> p_from = getFieldFromString(from), p_to = getFieldFromString(to);

    try
    {
        model.step(p_from.first, p_from.second, p_to.first, p_to.second);
    }
    catch (ChessModel::Exceptions ex)
    {
        if (ex == ChessModel::Exceptions::EMPTYFIELD)
            std::cout << "There is no piece of yours on the field." << std::endl;
        else if (ex == ChessModel::Exceptions::OUTOFTABLE)
            std::cout << "Field does not exist." << std::endl;
        else if (ex == ChessModel::Exceptions::ILLEGALMOVE)
            std::cout << "Illegal move." << std::endl;
    }
}

void ChessView::updateTable()
{
    clearConsole();

    std::cout << "    A  B  C  D  E  F  G  H    " << std::endl;
    for (int j = 0; j < 8; ++j)
    {
        std::cout << " " << 8 - j << " ";
        for (int i = 0; i < 8; ++i)
            std::cout << '[' << getPiece(i, j) << ']';
        std::cout << " " << 8 - j << " ";
        if (j == 1)
            std::cout << "  Step: " << (!model.getPlayer() ? "White" : "\e[1;32mGreen\u001b[0m");
        std::cout << std::endl;
    }
    std::cout << "    A  B  C  D  E  F  G  H    " << std::endl
              << std::endl;
}

void ChessView::GameOver()
{
    std::cout << "\u001b[0m"
              << "Game has ended, the winner is " << (model.getPlayer() ? "White!" : "Green!") << std::endl
              << "You are headed back to menu." << std::endl
              << "Type \"help\" for help." << std::endl;
    gameOver = true;
}

void ChessView::alarmForCheck()
{
    std::cout << "\u001b[0m"
              << "Watch out " << (model.getPlayer() ? "Green!" : "White!") << " The king is attacked!" << std::endl;
}

std::string ChessView::getPiece(int x, int y)
{
    PieceEnum p = model.getField(x, y);

    std::string piece;

    if (model.getFieldColor(x, y))
        piece = "\e[1;37m";
    else
        piece = "\e[1;32m";

    switch (p)
    {
    case KING:
        piece += "K";
        break;
    case QUEEN:
        piece += "Q";
        break;
    case ROOK:
        piece += "R";
        break;
    case KNIGHT:
        piece += "N";
        break;
    case BISHOP:
        piece += "B";
        break;
    case PAWN:
        piece += "P";
        break;
    case EMPTY:
        piece += " ";
        break;
    default:
        piece += "0";
        break;
    }

    piece += "\u001b[0m";

    return piece;
}

std::pair<int, int> ChessView::getFieldFromString(std::string field)
{
    std::pair<int, int> p;
    p.first = field[0] - (field[0] > 96 ? 97 : 65);
    p.second = 8 - (field[1] - 48);
    return p;
}

int ChessView::alarmForPromotion(bool player)
{
    std::string inp = "";
    int piece;
    do
    {
        std::cout << "Your pawn reached the last field. What would you like to exchange it for?" << std::endl
                  << "1. Queen" << std::endl
                  << "2. Rook" << std::endl
                  << "3. Bishop" << std::endl
                  << "4. Knight" << std::endl
                  << "5. Pawn" << std::endl
                  << " > ";
        std::cin >> inp;
        piece = atoi(inp.c_str());
    } while (piece < 1 || piece > 5);
    return piece;
}

void clearConsole()
{
    if (std::system("clear") == -1)
    {
        std::cout << "System clear error" << std::endl;
        exit(1);
    }
}