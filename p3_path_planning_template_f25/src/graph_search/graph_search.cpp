#include <iostream>
#include <cmath>
#include <queue>
#include <functional>

#include <path_planning/utils/math_helpers.h>
#include <path_planning/utils/graph_utils.h>

#include <path_planning/graph_search/graph_search.h>

using namespace std;

/**
 * General graph search instructions:
 *
 * First, define the correct data type to keep track of your visited cells
 * and add the start cell to it. If you need to initialize any properties
 * of the start cell, do that too.
 *
 * Next, implement the graph search function. Save the result in the path
 * variable defined for you.
 *
 * To visualize which cells are visited in the navigation webapp, save each
 * visited cell in the vector in the graph struct as follows:
 *      graph.visited_cells.push_back(c);
 * where c is a Cell struct corresponding to the visited cell you want to
 * visualize.
 *
 * The tracePath() function will return a path (which you should assign to
 * the path variable above) given the goal index, if you have kept track
 * of the parent of each node correctly and have implemented the
 * getParent() function. If you do not find a path, return an empty path
 * vector.
*/

// *** Task: Implement this function if completing the advanced extensions *** //
std::vector<Cell> depthFirstSearch(GridGraph &graph, const Cell &start, const Cell &goal)
{
    std::vector<Cell> path; // The final path should be placed here.

    initGraph(graph); // Make sure all the node values are reset.

    int start_idx = cellToIdx(start.i, start.j, graph);

    /* BEGIN STUDENT CODE. */
    /* END STUDENT CODE. */

    return path;
}

std::vector<Cell> breadthFirstSearch(GridGraph &graph, const Cell &start, const Cell &goal)
{
    initGraph(graph); // Make sure all the node values are reset.

    int start_idx = cellToIdx(start.i, start.j, graph);

    std::queue<int> visit_queue;


    visit_queue.push(start_idx);
    graph.cell_nodes[start_idx].cost = 0;
    graph.cell_nodes[start_idx].visited = true;

    while (!visit_queue.empty())
    {
        // Define current node
        int current_node_index = visit_queue.front();
        visit_queue.pop();

        CellNode& current_node = graph.cell_nodes[current_node_index];

        cout << "Current node i | j: " << current_node.i << " | " << current_node.j << endl;

        // Check if current node is the goal
        if (current_node.i == goal.i && current_node.j == goal.j) {
            cout << current_node.i << " | " << current_node.j << " is the goal" << endl;
            cout << current_node.parent << " is the goal's parent" << endl;
            break;
        }

        const vector<int>& nbrs = findNeighbors(current_node_index, graph);
        // const vector<float>& costs = getEdgeCosts(current_node_index, g);

        for (int j = 0; j < nbrs.size(); j++)
        {
            float nbr_idx = nbrs[j];
            CellNode& nbr = graph.cell_nodes[nbr_idx];
            // float edge_cost = costs[j];
            float edge_cost = graph.meters_per_cell;
            if (abs(nbr.i - current_node.i) > 0 && abs(nbr.j - current_node.j) > 0) {
                edge_cost *= 1.01;
            }

            // cout << "Current neighbor: " << nbr.i << " | " << nbr.j << endl;
            if(current_node.cost + edge_cost < nbr.cost && !isIdxOccupied(nbr_idx, graph) && !checkCollision(nbr_idx, graph)) {
                nbr.cost = current_node.cost + edge_cost;
                nbr.parent = current_node_index;
                visit_queue.push(nbr_idx);
                cout << "Updated neighbor parent: " << nbr.parent << endl;
            }

            if (!nbr.visited) {
                nbr.visited = true;
            }
        }
    }   

    
    std::vector<Cell> path = tracePath(cellToIdx(goal.i, goal.j, graph), graph);
    cout << "Path Size: " << path.size() << endl;
    // END STUDENT CODE
    return path;
}

// *** Task: Implement this function if completing the advanced extensions *** //
std::vector<Cell> iterativeDeepeningSearch(GridGraph &graph, const Cell &start, const Cell &goal)
{
    std::vector<Cell> path; // The final path should be placed here.

    initGraph(graph); // Make sure all the node values are reset.

    int start_idx = cellToIdx(start.i, start.j, graph);

    /* BEGIN STUDENT CODE. */
    /* END STUDENT CODE. */

    return path;
}

// *** Task: Implement this function if completing the advanced extensions *** //
std::vector<Cell> aStarSearch(GridGraph &graph, const Cell &start, const Cell &goal)
{
    std::vector<Cell> path; // The final path should be placed here.

    initGraph(graph); // Make sure all the node values are reset.

    int start_idx = cellToIdx(start.i, start.j, graph);

    /* BEGIN STUDENT CODE. */
    /* END STUDENT CODE. */

    return path;
}
