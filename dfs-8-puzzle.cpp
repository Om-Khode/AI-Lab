#include <bits/stdc++.h>
using namespace std;

struct Node
{
    vector<vector<int>> state;
    int x, y, depth;
    Node *parent;
};

pair<int, int> findBlank(vector<vector<int>> state)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state[i][j] == 0)
            {
                return make_pair(i, j);
            }
        }
    }
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

vector<vector<int>> move(vector<vector<int>> state, int x, int y, int newX, int newY)
{
    vector<vector<int>> newState = state;

    swap(newState[x][y], newState[newX][newY]);

    return newState;
}

vector<Node *> getNeighbour(Node *node)
{
    int x = node->x;
    int y = node->y;

    vector<Node *> neighbours;

    vector<pair<int, int>> dir = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    for (int i = 0; i < dir.size(); i++)
    {
        int newX = x + dir[i].first;
        int newY = y + dir[i].second;

        if (newX >= 0 && newX <= 2 && newY >= 0 && newY <= 2)
        {
            vector<vector<int>> neighbourState = move(node->state, x, y, newX, newY);
            neighbours.push_back(new Node({neighbourState, newX, newY, node->depth + 1, node}));
        }
    }

    return neighbours;
}

string serialize(vector<vector<int>> state)
{
    string serial;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            serial += to_string(state[i][j]);
        }
    }

    return serial;
}

bool isGoalState(vector<vector<int>> state)
{
    vector<vector<int>> goalState = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}};

    return state == goalState;
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

void dfs(vector<vector<int>> startState)
{
    pair<int, int> blank = findBlank(startState);

    Node *startNode = new Node({startState, blank.first, blank.second, 0});

    stack<Node *> s;
    set<string> visited;

    s.push(startNode);
    visited.insert(serialize(startState));

    while (!s.empty())
    {
        Node *current = s.top();
        s.pop();

        if (isGoalState(current->state))
        {
            cout << "Goal Found!\n";
            printPath(current);
            return;
        }

        vector<Node *> neighbours = getNeighbour(current);
        for (int i = 0; i < neighbours.size(); i++)
        {
            if (visited.find(serialize(neighbours[i]->state)) == visited.end())
            {
                s.push(neighbours[i]);
                visited.insert(serialize(current->state));
            }
        }
    }

    cout << "No Solution Found!";
}

int main()
{
    vector<vector<int>> startState = {
        {0, 2, 3},
        {1, 8, 4},
        {7, 6, 5},
    };

    dfs(startState);

    return 0;
}