// Purpose: PF2 - HW1: Recursive Maze Solver
// Author:  [LOGAN M CAMPBELL]
// UAID:    [010 641 227]

#include <iostream>
#include <fstream>
using namespace std;

// Global Constants
const int MAX_ROWS = 10;
const int MAX_COLS = 10;

const char WALL    = '*';
const char SPACE   = '_';
const char PATH    = '!';

// Reads the maze description from the given file into the given maze.
// Returns true if the operation succeeds and false if the file couldn't be opened.
bool loadMaze(const string& filename, char maze[MAX_ROWS][MAX_COLS])
{
    // TODO: Implement
   ifstream loadFile;
   // OPEN FILE AND CHECK IT'S EXISTIENCE
   loadFile.open(filename.c_str());
   if (loadFile.fail())
   {
      return false;
   }
      //LOAD ARRAY
      for(int x = 0; x < MAX_ROWS; x++)
      {
         for(int z = 0; z < MAX_COLS; z++)
         {
            loadFile >> maze[x][z];
         }
      }
      
   loadFile.close();
   
   return true;
}

// Prints the given maze to the console.
void printMaze(const char maze[MAX_ROWS][MAX_COLS])
{
    // TODO: Implement
    for (int x = 0; x < MAX_ROWS; x++)
    {
       for (int z = 0; z < MAX_COLS; z++)
       {
         cout << maze[x][z] << ' ' ;
         
       }
         cout << endl;
    }
    
}

// Returns true if the proposed move (r,c) is a valid one. Valid moves are within
// the range of the board, do not move into a wall, and do not move to a cell
// we have already seen.
bool validMove(const int r, const int c, const char maze[MAX_ROWS][MAX_COLS], const bool seen[MAX_ROWS][MAX_COLS])
{
    // TODO: Implement
    if ( (r < MAX_ROWS) && (c < MAX_COLS) && (maze[r][c] != WALL) && (seen[r][c] == false) && (maze[r][c] == SPACE) )
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

// Returns true if the given cell is an entry point for the maze. Entry points
// must be on the outer edge and must not be walls.
bool entryPoint(const int r, const int c, const char maze[MAX_ROWS][MAX_COLS])
{
    // TODO: Implement
    if ((r == 0 || c == 0 || r == MAX_ROWS - 1 || c == MAX_COLS -  1) && (maze[r][c] == SPACE))
    {
        return true;
    }
    else
    {
            return false;
  
    }
}
// Searches the maze for a valid entry point. If one is found, the 
// coordinates will be saved in 'startRow' and 'startCol'. If one is not found,
// the function will return false and 'startRow' and 'startCol' will be set
// to -1.
bool findEntryPoint(const char maze[MAX_ROWS][MAX_COLS], int& startRow, int& startCol)
{
    //two nested loop... find a match... you are going to set. this is a search
    
    for (int row = 0; row < MAX_ROWS; row++)
    {
        for (int col = 0; col < MAX_COLS; col++)
        {
            if (entryPoint(row, col, maze))
            {
                startRow = row;
                startCol = col;
                return true;
            }
            
        }
    }
    
    //return the startrow and startcol  as -1 : if there isn't an entry point. 
    startRow = -1;
    startCol = -1;
    return false;
}

// Recursively finds a solution to the given maze.
//
// Inputs:
// 'maze' is the maze we're searching.
// 'startRow' and 'startCol' hold the entry point into the maze.
// 'r' and 'c' tell us which cell we're currently working on.
//
// Outputs:
// 'seen' tells us whether or not we've already been to a given cell.
// 'solution' will hold the final answer once we're done (if there is one).
//
// This function will return true when a solution is found and false if there
// is no such solution. 
bool solveHelper(
    const char maze[MAX_ROWS][MAX_COLS], 
    const int startRow, const int startCol, 
    const int r, const int c, 
    bool seen[MAX_ROWS][MAX_COLS], 
    char solution[MAX_ROWS][MAX_COLS])
{
    // TODO: Implement
    
    //BASS CASE!!!
    
     if (entryPoint(r,c,maze) == true  && (r != startRow && c != startCol))
    {
        solution[r][c] = PATH;
        return true;
    }
        
    else
    {   
        // recursive :
        seen[r][c] = true; // make the current element seen.
        
        // LET'S MOVE : down = r +1 | up = r - 1 | right = c + 1 | left = c - 1
        if (validMove(r + 1, c, maze, seen) && solveHelper(maze,startRow,startCol,r + 1,c,seen,solution))
        {
            solution[r + 1][c] = PATH;
            return true;
        }
        if (validMove(r - 1, c, maze, seen) && solveHelper(maze,startRow,startCol,r - 1,c,seen,solution))
        {
            solution[r - 1][c] = PATH;
            return true;
        }
        if (validMove(r, c + 1, maze, seen) && solveHelper(maze,startRow,startCol,r,c + 1,seen,solution))
        {
         
            solution[r][c + 1] = PATH;
            return true;
        }
        if (validMove(r, c - 1, maze, seen) && solveHelper(maze,startRow,startCol,r,c - 1,seen,solution))
        {
            solution[r][c - 1] = PATH;
            return true;
        }
        else
        {
            return false;
        }
    
    } 
}

    
// Attempts to find a solution to the given maze. If one is found, it will be
// placed in 'solution' and true will be returned. Otherwise, false will be
// returned.
bool solve(const char maze[MAX_ROWS][MAX_COLS], char solution[MAX_ROWS][MAX_COLS])
{
    // TODO: Implement. 
    
    // 1. Create and initialize the 'seen' 2D array.
    
    // make everything not seen. 
    bool seen[MAX_ROWS][MAX_COLS] = {{false}};
    
    // 2. Find an entry point using the findEntryPoint() function.
    
    //intialize at zero and search the entry point at zero.
    int placeRow = 0;
    int placeCol = 0;
    findEntryPoint (maze,placeRow,placeCol);
    
    //if it doesn't find a entrypoint within the whole maze it's return false.
    if (!findEntryPoint(maze, placeRow, placeCol))
    {
        return false;
    } 
    else
    {
        //solution array // duplicate maze size to solution array
        
        for (int x = 0; x < MAX_ROWS; x++)
        {
            for (int z = 0; z < MAX_COLS; z++)
            {
                solution[x][z] = maze[x][z];
            }
        }
    
    //initial the first entry point as a PATH CHARACTER
    solution[placeRow][placeCol] = PATH;
    
    // 4. Call solveHelper() with the proper parameters to get the recursion started.
        //This might be redundant
    int replaceR = placeRow;
    int replaceC = placeCol;
    
    return 
    
    //recursively call with placeRow and placeCol
    solveHelper(maze,placeRow,placeCol, replaceR , replaceC, seen, solution);
    }
} 
            

int main()
{
    // Variables
    char maze[MAX_ROWS][MAX_COLS];
    char solution[MAX_ROWS][MAX_COLS];
    
    // Get the maze filename from the user
    cout << "Please enter the name of the maze file: " << endl;
    string filename;
    getline(cin, filename);
    
    // Try to load the maze description from the file
    if (!loadMaze(filename, maze))
    {
        cout << "Unable to read file. Please try again." << endl;
        return 1;
    }

    // Print the original maze
    cout << "Maze: " << endl;
    printMaze(maze);
    cout << endl;
    
    // Find the solution or show that there is none.
    if (solve(maze, solution))
    {
        cout << "Solution: " << endl;
        printMaze(solution);
    }
    else
    {
        cout << "No solution." << endl;
    }
    
    return 0;
}