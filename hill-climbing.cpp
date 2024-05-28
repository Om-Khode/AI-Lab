#include <bits/stdc++.h>
using namespace std;

struct Node
{
    vector<vector<int>> state;
    int x, y;
    int hurestics;
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

vector<vector<int>> move(vector<vector<int>> state, int x, int y, int newX, int newY)
{
    vector<vector<int>> newState = state;
    swap(newState[x][y], newState[newX][newY]);
    return newState;
}

bool isGoalState(vector<vector<int>> state)
{
    vector<vector<int>> goalState = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5},
    };

    return state == goalState;
}

int manhattanDistance(vector<vector<int>> state)
{
    int distance = 0;

    vector<vector<int>> goal = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5},
    };

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state[i][j] != 0)
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        if (state[i][j] == goal[k][l])
                        {
                            distance += (abs(i - k) + abs(j - l));
                        }
                    }
                }
            }
        }
    }

    return distance;
}

vector<Node *> getNeighbour(Node *node)
{
    vector<Node *> neighbours;

    int x = node->x;
    int y = node->y;

    vector<pair<int, int>> directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    for (int i = 0; i < directions.size(); i++)
    {
        int newX = x + directions[i].first;
        int newY = y + directions[i].second;

        if (newX >= 0 && newX <= 2 && newY >= 0 && newY <= 2)
        {
            Node *neighbour = new Node({move(node->state, x, y, newX, newY), newX, newY, 0, node});
            neighbour->hurestics = -manhattanDistance(neighbour->state);
            neighbours.push_back(neighbour);
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

void hillClimbing(vector<vector<int>> startState)
{
    pair<int, int> blank = findBlank(startState);

    Node *current = new Node({startState, blank.first, blank.second, -manhattanDistance(startState), nullptr});

    Node *next;

    while (true)
    {
        vector<Node *> neighbours = getNeighbour(current);
        next = nullptr;

        for (int i = 0; i < neighbours.size(); i++)
        {
            if (next == nullptr || next->hurestics < neighbours[i]->hurestics)
            {
                next = neighbours[i];
            }
        }

        if (next == nullptr || next->hurestics <= current->hurestics)
        {
            break;
        }

        current = next;
    }

    if (isGoalState(current->state))
    {
        cout << "Goal State Reached!" << endl;
    }
    else
    {
        cout << "Local Maxima Reached!" << endl;
    }
    printPath(current);
}

int main()
{
    vector<vector<int>> startState = {
        {2, 3, 0},
        {1, 8, 4},
        {7, 6, 5},
    };

    hillClimbing(startState);

    return 0;
}