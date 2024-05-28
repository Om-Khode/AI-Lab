#include <bits/stdc++.h>
using namespace std;

bool isSafe(vector<int> board, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
        {
            return false;
        }
    }

    return true;
}

void printSolutions(vector<int> board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i] == j)
            {
                cout << "Q ";
            }
            else
            {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void solveNQueens(vector<int> &board, int row, int n, vector<vector<int>> &solutions)
{
    if (row == n)
    {
        solutions.push_back(board);
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (isSafe(board, row, col))
        {
            board[row] = col;
            solveNQueens(board, row + 1, n, solutions);
            board[row] = -1;
        }
    }
}

void nQueens(int n)
{
    vector<int> board(n, -1);
    vector<vector<int>> solutions;
    solveNQueens(board, 0, n, solutions);
    for (int i = 0; i < solutions.size(); i++)
    {
        printSolutions(solutions[i]);
    }
}

int main()
{
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    nQueens(n);

    return 0;
}