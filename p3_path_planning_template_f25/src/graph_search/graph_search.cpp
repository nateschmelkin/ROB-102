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

    bool goal_reached = false;
    while (!visit_queue.empty())
    {
        // Define current node
        int current_node_index = visit_queue.front();
        visit_queue.pop();

        CellNode& current_node = graph.cell_nodes[current_node_index];

        // Check if current node is the goal
        if (current_node.i == goal.i && current_node.j == goal.j) {
            goal_reached = true;
            break;
        }

        const vector<int>& nbrs = findNeighbors(current_node_index, graph);
        // const vector<float>& costs = getEdgeCosts(current_node_index, g);

        for (int j = 0; j < nbrs.size(); j++)
        {
            int nbr_idx = nbrs[j];
            CellNode& nbr = graph.cell_nodes[nbr_idx];
            // float edge_cost = costs[j];
            float delta_x = nbr.i - current_node.i;
            float delta_y = nbr.j - current_node.j;
            float edge_cost = sqrt(delta_x * delta_x + delta_y * delta_y);

            // Check if neighbor is valid (not occupied and no collision)
            if (!isIdxOccupied(nbr_idx, graph) && !checkCollision(nbr_idx, graph)) {
                // Update cost and parent if we found a better path
                if(current_node.cost + edge_cost < nbr.cost) {
                    nbr.cost = current_node.cost + edge_cost;
                    nbr.parent = current_node_index;
                }

                // If not visited yet, mark as visited and add to queue
                if (!nbr.visited) {
                    nbr.visited = true;
                    visit_queue.push(nbr_idx);
                }
            }
        }
    }   

    int goal_idx = cellToIdx(goal.i, goal.j, graph);
    if (!goal_reached)
    {
        std::cerr << "WARNING: Goal was not reached during BFS search. Queue emptied." << std::endl;
        std::cerr << "Debug: Goal cell: (" << goal.i << ", " << goal.j << "), index: " << goal_idx << std::endl;
        std::cerr << "Debug: Goal visited: " << (graph.cell_nodes[goal_idx].visited ? "true" : "false") << std::endl;
        std::cerr << "Debug: Goal parent: " << graph.cell_nodes[goal_idx].parent << std::endl;
        std::cerr << "Debug: Goal cost: " << graph.cell_nodes[goal_idx].cost << std::endl;
    }
    else
    {
        std::cout << "Debug: Goal reached successfully during BFS search." << std::endl;
    }
    
    std::vector<Cell> path = tracePath(goal_idx, graph);
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
