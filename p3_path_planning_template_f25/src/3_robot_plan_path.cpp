#include <iostream>
#include <cmath>
#include <string>

#include <mbot_bridge/robot.h>

#include <path_planning/utils/graph_utils.h>
#include <path_planning/utils/math_helpers.h>
#include <path_planning/utils/viz_utils.h>
#include <path_planning/graph_search/graph_search.h>
#include <path_planning/graph_search/distance_transform.h>

using namespace std;

int main(int argc, char const *argv[])
{
    float goal_x = 0, goal_y = 0;

    if (argc < 2)
    {
        std::cerr << "Please provide the path to a map file as input.\n";
        return -1;
    }

    if (argc == 4)
    {
        goal_x = std::stof(argv[2]);
        goal_y = std::stof(argv[3]);
    } else {
        std::cout << "Input goal x: \n";
        std::cin >> goal_x;
        std::cout << "Input goal y: \n";
        std::cin >> goal_y;
    }

    std::string map_file = argv[1];
    GridGraph graph;

    // Load the graph and make sure that it is loaded successfully.
    if (!loadFromFile(map_file, graph))
    {
        std::cerr << "ERROR: Failed to load map file: " << map_file << std::endl;
        std::cerr << "Please check that the file exists and is a valid map file." << std::endl;
        return -1;
    }

    // Verify the graph is properly loaded
    if (!isLoaded(graph))
    {
        std::cerr << "ERROR: Graph failed validation after loading." << std::endl;
        return -1;
    }

    //distanceTransformManhattan(graph);
    // Use a reasonable collision radius - the loadFromFile already set it to ROBOT_RADIUS + meters_per_cell
    // But we can adjust it if needed. Using ROBOT_RADIUS with a small safety margin.
    graph.collision_radius = .1;  // ~0.187m, more reasonable than 0.25m

    // Print graph information
    std::cout << "Graph loaded successfully:" << std::endl;
    std::cout << "  Size: " << graph.width << " x " << graph.height << " cells" << std::endl;
    std::cout << "  Origin: (" << graph.origin_x << ", " << graph.origin_y << ") meters" << std::endl;
    std::cout << "  Meters per cell: " << graph.meters_per_cell << std::endl;
    std::cout << "  Valid x range: [" << graph.origin_x << ", " 
              << (graph.origin_x + graph.width * graph.meters_per_cell) << "] meters" << std::endl;
    std::cout << "  Valid y range: [" << graph.origin_y << ", " 
              << (graph.origin_y + graph.height * graph.meters_per_cell) << "] meters" << std::endl;
    std::cout << "  Collision radius: " << graph.collision_radius << " meters" << std::endl;
    std::cout << "  Robot radius: " << ROBOT_RADIUS << " meters" << std::endl;

    Cell goal = posToCell(goal_x, goal_y, graph);

    // Initialize the robot.
    mbot_bridge::MBot robot;
    // Get the robot's SLAM pose.
    std::vector<float> pose = robot.readSlamPose();

    // Verify pose was read successfully
    if (pose.size() < 2)
    {
        std::cerr << "ERROR: Failed to read robot pose. Got " << pose.size() << " values, expected at least 2." << std::endl;
        return -1;
    }

    std::cout << "Robot pose: x=" << pose[0] << ", y=" << pose[1] << std::endl;
    Cell start = posToCell(pose[0], pose[1], graph);
    
    std::cout << "Start cell: (" << start.i << ", " << start.j << ")" << std::endl;
    std::cout << "Goal cell: (" << goal.i << ", " << goal.j << ")" << std::endl;
    
    // Validate that start and goal cells are within bounds
    if (!isCellInBounds(start.i, start.j, graph))
    {
        std::cerr << "ERROR: Start cell (" << start.i << ", " << start.j 
                  << ") is out of bounds. Graph size: " << graph.width 
                  << " x " << graph.height << std::endl;
        std::cerr << "Robot position: x=" << pose[0] << ", y=" << pose[1] << std::endl;
        return -1;
    }
    
    if (!isCellInBounds(goal.i, goal.j, graph))
    {
        std::cerr << "ERROR: Goal cell (" << goal.i << ", " << goal.j 
                  << ") is out of bounds. Graph size: " << graph.width 
                  << " x " << graph.height << std::endl;
        std::cerr << "Goal position: x=" << goal_x << ", y=" << goal_y << std::endl;
        std::cerr << "Valid coordinate range: x=[" << graph.origin_x << ", " 
                  << (graph.origin_x + graph.width * graph.meters_per_cell) 
                  << "], y=[" << graph.origin_y << ", " 
                  << (graph.origin_y + graph.height * graph.meters_per_cell) << "]" << std::endl;
        std::cerr << "Please use goal coordinates within the valid range." << std::endl;
        return -1;
    }
    
    // Check if goal cell is valid
    int goal_idx = cellToIdx(goal.i, goal.j, graph);
    int start_idx = cellToIdx(start.i, start.j, graph);
    bool goal_occupied = isIdxOccupied(goal_idx, graph);
    bool goal_collision = checkCollision(goal_idx, graph);
    bool start_occupied = isIdxOccupied(start_idx, graph);
    bool start_collision = checkCollision(start_idx, graph);
    
    std::cout << "Start cell index: " << start_idx << std::endl;
    std::cout << "Start cell occupied: " << (start_occupied ? "true" : "false") << std::endl;
    std::cout << "Start cell collision: " << (start_collision ? "true" : "false") << std::endl;
    std::cout << "Goal cell index: " << goal_idx << std::endl;
    std::cout << "Goal cell occupied: " << (goal_occupied ? "true" : "false") << std::endl;
    std::cout << "Goal cell collision: " << (goal_collision ? "true" : "false") << std::endl;
    
    if (goal_occupied || goal_collision)
    {
        std::cerr << "WARNING: Goal cell is occupied or in collision! Path may not be reachable." << std::endl;
    }
    if (start_occupied || start_collision)
    {
        std::cerr << "WARNING: Start cell is occupied or in collision!" << std::endl;
    }
    
    std::cout << "Starting path search..." << std::endl;
    std::vector<Cell> path = breadthFirstSearch(graph, start, goal);
    //std::vector<Cell> path = aStarSearch(graph, start, goal);
    
    if (path.empty())
    {
        std::cerr << "ERROR: No path found from start to goal!" << std::endl;
        return -1;
    }
    
    std::cout << "Found path of length: " << path.size() << std::endl;
    
    // Debug: Check if goal was actually reached
    int goal_parent = getParent(goal_idx, graph);
    std::cout << "Debug: Goal cell index: " << goal_idx << std::endl;
    std::cout << "Debug: Goal parent index: " << goal_parent << std::endl;
    std::cout << "Debug: Goal visited: " << (graph.cell_nodes[goal_idx].visited ? "true" : "false") << std::endl;
    std::cout << "Debug: Goal cost: " << graph.cell_nodes[goal_idx].cost << std::endl;
    
    if (path.size() == 1)
    {
        std::cerr << "WARNING: Path has only 1 cell. The goal may not have been reached during search." << std::endl;
        std::cerr << "The goal's parent is " << goal_parent << " (should not be -1 if goal was reached)." << std::endl;
    }
    
    // Print first few and last few cells of path for debugging
    if (path.size() > 0)
    {
        std::cout << "Path start: (" << path[0].i << ", " << path[0].j << ")" << std::endl;
        if (path.size() > 1)
        {
            std::cout << "Path end: (" << path.back().i << ", " << path.back().j << ")" << std::endl;
        }
    }
    robot.drivePath(cellsToPoses(path, graph));

    // Save the path output file for visualization in the nav app.
    generatePlanFile(start, goal, path, graph);

    return 0;
}
