#include <bits/stdc++.h>
using namespace std;

struct Node
{
    vector<vector<int>> state;
    int x, y;
    int depth;
    Node *parent;
    int cost;
    int totalCost;

    bool operator>(const Node &other) const
    {
        return totalCost > other.totalCost;
    }
};

pair<int, int> findBlank(vector<vector<int>> state)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state[i][j] == 0)
                return make_pair(i, j);
        }
    }
}

bool isGoalState(vector<vector<int>> state)
{
    vector<vector<int>> goalState = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5},
    };

    return goalState == state;
}

int manhattanDistance(vector<vector<int>> state)
{
    vector<vector<int>> goal = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5},
    };

    int distance = 0;

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

vector<vector<int>> move(vector<vector<int>> state, int x, int y, int newX, int newY)
{
    vector<vector<int>> newState = state;

    swap(newState[x][y], newState[newX][newY]);

    return newState;
}

vector<Node *> getNeighbour(Node *node)
{
    vector<Node *> neighbours;

    int x = node->x;
    int y = node->y;

    vector<pair<int, int>> direction = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    for (int i = 0; i < direction.size(); i++)
    {
        int newX = x + direction[i].first;
        int newY = y + direction[i].second;

        if (newX >= 0 && newX <= 2 && newY >= 0 && newY <= 2)
        {
            Node *neighbour = new Node({move(node->state, x, y, newX, newY), newX, newY, node->depth + 1, node, 0, 0});
            neighbour->cost = manhattanDistance(neighbour->state);
            neighbour->totalCost = neighbour->depth + neighbour->cost;
            neighbours.push_back(neighbour);
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
            serial += state[i][j];
        }
    }

    return serial;
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

void astar(vector<vector<int>> startState)
{
    pair<int, int> blank = findBlank(startState);

    Node *startNode = new Node({startState, blank.first, blank.second, 0, nullptr, manhattanDistance(startState), manhattanDistance(startState)});

    priority_queue<Node *, vector<Node *>, greater<Node *>> pq;

    set<string> visited;

    pq.push(startNode);

    while (!pq.empty())
    {
        Node *current = pq.top();
        pq.pop();

        if (isGoalState(current->state))
        {
            cout << "Goal Found\n";
            printPath(current);
            return;
        }

        vector<Node *> neighbours = getNeighbour(current);
        for (int i = 0; i < neighbours.size(); i++)
        {
            string neighbourState = serialize(neighbours[i]->state);
            if (visited.find(neighbourState) == visited.end())
            {
                pq.push(neighbours[i]);
                visited.insert(neighbourState);
            }
            else
            {
                delete neighbours[i];
            }
        }
    }

    cout << "No Solution Found";
}

int main()
{
    vector<vector<int>> startState = {
        {7, 5, 2},
        {4, 0, 1},
        {6, 8, 3},
    };

    astar(startState);

    return 0;
}