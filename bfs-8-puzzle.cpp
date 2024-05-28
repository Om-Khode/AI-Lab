#include <bits/stdc++.h>
using namespace std;

struct Node
{
    vector<vector<int>> state;
    int x;
    int y;
    int depth;
    Node *parent;
};

bool isGoalState(const vector<vector<int>> &state)
{
    vector<vector<int>> goal = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5},
    };

    return state == goal;
}

pair<int, int> findBlank(vector<vector<int>> &state)
{
    int x, y;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state[i][j] == 0)
            {
                x = i;
                y = j;
                return make_pair(x, y);
            }
        }
    }
}

string serialize(vector<vector<int>> &state)
{
    string s;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            s += to_string(state[i][j]) + (i == 2 && j == 2 ? "" : ", ");
        }
    }

    return s;
}

vector<vector<int>> swap(vector<vector<int>> state, int x, int y, int newX, int newY)
{
    vector<vector<int>> newState = state;

    int temp = newState[x][y];
    newState[x][y] = newState[newX][newY];
    newState[newX][newY] = temp;

    return newState;
}

void print(vector<vector<int>> state)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << state[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<Node *> getNeighbours(Node *node)
{
    vector<Node *> neighbours;

    int x = node->x;
    int y = node->y;

    vector<pair<int, int>> directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}}; // L, U, R, D

    for (int i = 0; i < directions.size(); i++)
    {
        int newX = x + directions[i].first;
        int newY = y + directions[i].second;

        if (newX >= 0 && newX <= 2 && newY >= 0 && newY <= 2)
        {
            vector<vector<int>> neighbourState = swap(node->state, x, y, newX, newY);
            neighbours.push_back(new Node({neighbourState, newX, newY, node->depth + 1, node}));
        }
    }

    return neighbours;
}

void printPath(Node *node)
{
    vector<Node *> path;

    while (node != nullptr)
    {
        path.push_back(node);
        node = node->parent;
    }

    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cout << path[i]->state[j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void bfs(vector<vector<int>> startState)
{
    set<string> visited;
    queue<Node *> q;

    pair<int, int> blank = findBlank(startState);
    Node *node = new Node({startState, blank.first, blank.second, 0, nullptr});

    q.push(node);
    visited.insert(serialize(node->state));

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();

        if (isGoalState(current->state))
        {
            cout << "Goal found" << endl;
            printPath(current);
            return;
        }

        vector<Node *> neighbours = getNeighbours(current);
        for (int i = 0; i < neighbours.size(); i++)
        {
            string neighbourState = serialize(neighbours[i]->state);
            if (visited.find(neighbourState) == visited.end())
            {
                q.push(neighbours[i]);
                visited.insert(neighbourState);
            }
            else
            {
                delete neighbours[i];
            }
        }
    }

    cout << "No Solution found!";
}

int main()
{

    vector<vector<int>> startState = {
        {7, 5, 2},
        {4, 0, 1},
        {6, 8, 3},
    };

    bfs(startState);

    return 0;
}