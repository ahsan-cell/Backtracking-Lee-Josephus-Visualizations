# Maze Solver and Josephus Problem Solver

This C++ program includes solutions for the "Rat in a Maze" problem using both stack-based backtracking and queue-based Lee's Algorithm. It also solves the Josephus problem using a Queue data structure.

## Maze Solver

### Overview
The maze solver provides two solutions for the Rat in a Maze problem:

1. **Stack-Based Solution: Backtracking**
   - The rat moves in four directions: Right, Down, Left, Up.
   - Hurdles are randomly placed in the maze.
   - The path from the maze entry to the destination is marked and printed in the 2-D maze matrix.

2. **Queue-Based Solution: Lee’s Algorithm**
   - A queue of reachable squares is used.
   - The queue has initially the position of the source cell empty, and the source square/cell has a distance value of 0.
   - The program dequeues the cell position, examines unreached, unblocked squares adjacent to this cell, and marks them with the distance.
   - If the destination cell is reached, it traces back the path till the source.

### How to Run Maze Solver
1. Compile and run the program. The Program is made on SFML library so make sure that the library is installed and linked properly. 
2. Follow the prompts to enter the dimensions of the maze and source/destination cells.
3. Observe the graphical representation of the maze with highlighted blocked cells and the final path.

## Josephus Problem Solver

### Overview
The Josephus problem solver uses a Queue data structure to simulate the problem:

1. People (any number N > 1) are standing in a circle waiting to be executed.
2. Counting begins at a specified point (S selected randomly) in the circle and proceeds around the circle in a clockwise direction.
3. After a specified number of people are skipped (k-1), the next (kth) person is executed.
4. The procedure is repeated until only one person remains and is freed.

### How to Run Josephus Problem Solver
1. Compile and run the program. The Program is made on SFML library so make sure that the library is installed and linked properly. 
2. Enter the total number of people (N) and the count for skipping (k).
3. Observe the graphical representation of each move in the circle.

## Additional Notes
Feel free to explore the code and experiment with different maze configurations and Josephus problem scenarios.
