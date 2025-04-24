#include "../src/tictactoe.cpp"
#include <gtest/gtest.h>

TEST(PlayerTest, ConstructorAndGetters)
{
    Player p1('X', "Alice");
    EXPECT_EQ(p1.getSymbol(), 'X');
    EXPECT_EQ(p1.getName(), "Alice");

    Player p2;
    EXPECT_EQ(p2.getSymbol(), 'X');
    EXPECT_EQ(p2.getName(), "Player X");
}

TEST(BoardTest, Initialization)
{
    Board board;
    EXPECT_FALSE(board.isFull());
    EXPECT_EQ(board.getFilledCellsCount(), 0);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            EXPECT_TRUE(board.isValidMove(i, j));
        }
    }
}

TEST(BoardTest, MakeMoveAndWinCheck)
{
    Board board;

    // Верные ходы
    EXPECT_TRUE(board.isValidMove(0, 0));
    board.makeMove(0, 0, 'X');
    EXPECT_FALSE(board.isValidMove(0, 0));
    EXPECT_EQ(board.getFilledCellsCount(), 1);

    // Крестики выйграли
    board.makeMove(0, 1, 'X');
    board.makeMove(0, 2, 'X');
    EXPECT_TRUE(board.checkWin('X'));

    // Проверка линий
    Board board2;
    board2.makeMove(0, 1, 'O');
    board2.makeMove(1, 1, 'O');
    board2.makeMove(2, 1, 'O');
    EXPECT_TRUE(board2.checkWin('O'));

    // Проверка диагонали
    Board board3;
    board3.makeMove(0, 0, 'X');
    board3.makeMove(1, 1, 'X');
    board3.makeMove(2, 2, 'X');
    EXPECT_TRUE(board3.checkWin('X'));
}

TEST(BoardTest, FullBoardCheck)
{
    Board board;
    char symbol = 'X';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            EXPECT_FALSE(board.isFull());
            board.makeMove(i, j, symbol);
            symbol = (symbol == 'X') ? 'O' : 'X';
        }
    }

    EXPECT_TRUE(board.isFull());
    EXPECT_EQ(board.getFilledCellsCount(), 9);
}

TEST(GameTest, PlayerSwitch)
{
    TicTacToe game;
    Player &p1 = game.getCurrentPlayer();
    EXPECT_EQ(p1.getSymbol(), 'X');

    game.switchTurn();
    Player &p2 = game.getCurrentPlayer();
    EXPECT_EQ(p2.getSymbol(), 'O');

    game.switchTurn();
    Player &p3 = game.getCurrentPlayer();
    EXPECT_EQ(p3.getSymbol(), 'X');
}

TEST(PlayerTest, DefaultSymbolIsX)
{
    Player p;
    EXPECT_EQ(p.getSymbol(), 'X');
}

TEST(PlayerTest, CanChangeSymbol)
{
    Player p('O', "Player O");
    EXPECT_EQ(p.getSymbol(), 'O');
}

TEST(BoardTest, InvalidMoveOutsideBounds)
{
    Board board;
    EXPECT_FALSE(board.isValidMove(-1, 0));
    EXPECT_FALSE(board.isValidMove(3, 1));
    EXPECT_FALSE(board.isValidMove(1, -1));
    EXPECT_FALSE(board.isValidMove(2, 3));
}

TEST(BoardTest, CannotOverwriteCell)
{
    Board board;
    board.makeMove(0, 0, 'X');
    EXPECT_FALSE(board.isValidMove(0, 0));
}

TEST(BoardTest, ClearBoardFunctionality)
{
    Board board;
    // Заполняем доску
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board.makeMove(i, j, 'X');
        }
    }
    // Проверяем, что доска полная
    EXPECT_TRUE(board.isFull());
}

TEST(GameTest, InitialCurrentPlayerIsX)
{
    TicTacToe game;
    EXPECT_EQ(game.getCurrentPlayer().getSymbol(), 'X');
}

TEST(GameTest, SwitchTurnChangesPlayer)
{
    TicTacToe game;
    game.switchTurn();
    EXPECT_EQ(game.getCurrentPlayer().getSymbol(), 'O');
    game.switchTurn();
    EXPECT_EQ(game.getCurrentPlayer().getSymbol(), 'X');
}

TEST(ErrorTest, InvalidPlayerSymbol)
{
    // Player p('Z', "Invalid"); // Должен ли это вызывать ошибку?
    // EXPECT_NE(p.getSymbol(), 'Z');
}

TEST(ErrorTest, BoardStateAfterInvalidMove)
{
    Board board;
    board.makeMove(0, 0, 'X');
    int initialFilled = board.getFilledCellsCount();

    // недопустимый ход
    board.makeMove(0, 0, 'O');
    EXPECT_EQ(board.getFilledCellsCount(), initialFilled);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
