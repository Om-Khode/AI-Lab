#include <iostream>
using namespace std;

#define COMPUTER 1
#define HUMAN 2
#define SIZE 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void printBoard(char board[][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << " " << board[i][j] << (j != SIZE - 1 ? " |" : " ");
        }
        cout << endl
             << (i != SIZE - 1 ? "-----------" : "") << endl;
    }
}

void showBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << " " << (i * SIZE) + j + 1 << (j != SIZE - 1 ? " |" : " ");
        }
        cout << endl
             << (i != SIZE - 1 ? "-----------" : "") << endl;
    }
}

bool checkBoard(char board[][SIZE])
{
    for (int r = 0; r < SIZE; r++)
    {
        if (board[r][0] != ' ' && board[r][0] == board[r][1] && board[r][1] == board[r][2])
        {
            return true;
        }
    }

    for (int c = 0; c < SIZE; c++)
    {
        if (board[0][c] != ' ' && board[0][c] == board[1][c] && board[1][c] == board[2][c])
        {
            return true;
        }
    }

    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return true;
    }

    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return true;
    }

    return false;
}

int minmax(char board[][SIZE], int depth, bool isAI)
{
    if (checkBoard(board))
    {
        return isAI ? -1 : 1;
    }

    if (depth == SIZE * SIZE)
    {
        return 0;
    }

    int bestScore = isAI ? -999 : 999;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = isAI ? COMPUTERMOVE : HUMANMOVE;
                int score = minmax(board, depth + 1, !isAI);
                board[i][j] = ' ';
                bestScore = isAI ? max(score, bestScore) : min(score, bestScore);
            }
        }
    }

    return bestScore;
}

int bestMove(char board[][SIZE], int depth)
{
    int bestScore = -999, move = -1;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = COMPUTERMOVE;
                int score = minmax(board, depth + 1, false);
                board[i][j] = ' ';
                if (score > bestScore)
                {
                    bestScore = score;
                    move = (i * SIZE) + j + 1;
                }
            }
        }
    }

    return move;
}

int main()
{
    char board[SIZE][SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    int moves = 0;
    int currentMove = HUMAN;

    showBoard();

    while (moves < SIZE * SIZE && !checkBoard(board))
    {
        int move;
        if (currentMove == HUMAN)
        {
            cout << "Enter a number from 1 to 9 to put X in it: ";
            cin >> move;

            while (move < 1 || move > 9 || board[move / SIZE][(move % SIZE) - 1] != ' ')
            {
                cout << "Invalid Move! Try Again: ";
                cin >> move;
            }

            board[move / SIZE][(move % SIZE) - 1] = HUMANMOVE;
            currentMove = COMPUTER;
        }
        else
        {
            move = bestMove(board, moves);
            board[move / SIZE][(move % SIZE) - 1] = COMPUTERMOVE;
            currentMove = HUMAN;
        }
        moves++;
        printBoard(board);
    }

    if (checkBoard(board))
    {
        if (currentMove == COMPUTER)
        {
            cout << "You Won!";
        }
        else
        {
            cout << "Computer Won!";
        }
    }
    else
    {
        cout << "Draw";
    }

    return 0;
}