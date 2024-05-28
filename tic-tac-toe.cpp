#include <iostream>
#include <string>

using namespace std;

void display(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        cout << "     " << "|" << "     " << "|" << "     " << endl;
        cout << "  " << board[i][0] << "  " << "|" << "  " << board[i][1] << "  " << "|" << "  " << board[i][2] << endl;
        cout << "     " << "|" << "     " << "|" << "     " << endl;
        if (i != 2)
        {
            cout << "-----" << "|" << "-----" << "|" << "-----" << endl;
        }
    }
}

int main()
{
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    const char playerX = 'X';
    const char playerO = 'O';
    char currentPlayer = playerX;
    char winner = ' ';
    int r = -1, c = -1;

    for (int i = 0; i < 9; i++)
    {
        display(board);

        cout << "Current Player: " << currentPlayer << endl
             << endl;

        while (true)
        {
            cout << "Enter the row and column where you want to play: ";
            cin >> r >> c;

            if (r < 0 || r > 2 || c < 0 || c > 2)
            {
                cout << "Please enter valid row and column!" << endl;
            }
            else if (board[r][c] != ' ')
            {
                cout << "Invalid move! Try again" << endl;
            }
            else
            {
                break;
            }
            r = -1;
            c = -1;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        board[r][c] = currentPlayer;

        for (int r = 0; r < 3; r++)
        {
            if (board[r][0] != ' ' && board[r][0] == board[r][1] && board[r][1] == board[r][2])
            {
                winner = currentPlayer;
            }
        }

        for (int c = 0; c < 3; c++)
        {
            if (board[0][c] != ' ' && board[0][c] == board[1][c] && board[1][c] == board[2][c])
            {
                winner = currentPlayer;
            }
        }

        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        {
            winner = currentPlayer;
        }

        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        {
            winner = currentPlayer;
        }

        if (winner != ' ')
        {
            display(board);
            cout << "The winner of the game is: " << currentPlayer;
            break;
        }

        currentPlayer = (currentPlayer == playerX) ? playerO : playerX;
    }

    if (winner == ' ')
    {
        display(board);
        cout << "Draw!";
    }

    return 0;
}