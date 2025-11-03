#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "planning.h"


void printPath(std::vector<int>& path, Graph& g) {

    if (path.size() < 1)
    {
        std::cout << "No path found :(\n";
        return;
    }

    std::cout << "Path: ";
    for (int i = 0; i < path.size() - 1; i++)
    {
        std::cout << g.data[path[i]] << " -> ";
    }
    std::cout <<  g.data[path.back()] << "\n";
};

std::vector<int> tracePath(int n, Graph& g) {
    std::vector<int> path;
    int curr = n;
    do {
        path.push_back(curr);
        curr = getParent(curr, g);
    } while (curr != -1);

    // Since we built the path backwards, we need to reverse it.
    std::reverse(path.begin(), path.end());
    return path;
};

// *** Task: Implement this function *** //
std::vector<int> getNeighbors(int n, Graph& g)
{
    // BEGIN STUDENT CODE
    // END STUDENT CODE
    return g.edges[n];
}

// *** Task: Implement this function *** //
std::vector<float> getEdgeCosts(int n, Graph& g)
{
    // BEGIN STUDENT CODE
    // END STUDENT CODE

    return g.edge_costs[n];
}

// *** Task: Implement this function *** //
int getParent(int n, Graph& g)
{
    // BEGIN STUDENT CODE
    // END STUDENT CODE
    int parent = g.nodes[n].parent;

    //replace this with your code
    return parent;
}

void initGraph(Graph& g)
{
    g.nodes.clear();
    for (int i = 0; i < g.data.size(); i++)
    {
        Node n;
        n.city = g.data[i];
        g.nodes.push_back(n);
    }
}

// *** Task: Implement this function *** //
std::vector<int> bfs(int start, int goal, Graph& g)
{
    initGraph(g);

    std::queue<int> visit_queue;


    visit_queue.push(start);
    g.nodes[start].cost = 0;
    g.nodes[start].visited = true;

    while (!visit_queue.empty())
    {
        // Define current node
        int current_node_index = visit_queue.front();
        visit_queue.pop();

        Node& current_node = g.nodes[current_node_index];

        cout << "Current node: " << current_node.city << endl;

        // Check if current node is the goal
        if (current_node_index == goal) {
            cout << current_node.city << " is the goal" << endl;
            cout << current_node.parent << " is the goal's parent" << endl;
            break;
        }

        const vector<int>& nbrs = getNeighbors(current_node_index, g);
        const vector<float>& costs = getEdgeCosts(current_node_index, g);

        for (int j = 0; j < nbrs.size(); j++)
        {
            float nbr_idx = nbrs[j];
            Node& nbr = g.nodes[nbr_idx];
            float edge_cost = costs[j];

            cout << "Current neighbor: " << nbr.city << endl;

            cout << "Current edge cost for neighbor: " << nbr.cost << endl;

            cout << "Parent to edge cost for neighbor: "<< edge_cost << endl;

            if(current_node.cost + edge_cost < nbr.cost) {
                nbr.cost = current_node.cost + edge_cost;
                nbr.parent = current_node_index;
                cout << "Updated neighbor parent: " << nbr.parent << endl;
            }

            if (!nbr.visited) {
                nbr.visited = true;
                visit_queue.push(nbr_idx);
            }
        }
    }   

    
    std::vector<int> path = tracePath(goal, g);
    cout << "Path Size: " << path.size() << endl;
    // END STUDENT CODE
    return path;
}

// *** Task: Implement this function if completing the advanced extension *** //
std::vector<int> dfs(int start, int goal, Graph& g)
{
    initGraph(g);
    std::vector<int> path;

    std::stack<int> visit_stack;

    // BEGIN STUDENT CODE
    // END STUDENT CODE
    return path;
}
