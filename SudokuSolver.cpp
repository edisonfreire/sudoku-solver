/*
Edison Freire
5/2/23
*/
#include "SudokuSolver.hpp"

/**
    Default constructor.
    The default constructor initializes an empty board, that is, a 
    board filled with zeros (an array of 9 arrays, each filled with 9 zeros). 
    This board will be marked unsolvable. 
*/
SudokuSolver::SudokuSolver()
{
    isSolvable_ = false;
    create2Darray();
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            puzzle_[i][j] = 0;
        }
    }
}

/**
    Parameterized constructor.
    @param: a string indicating input file name
    The parameterized constructor reads the input file to initialize the board.
    The input files consist of 9 digits on each row separated by commas, and 
    9 rows separated by new line characters \n, corresponding to a sudoku board. 
    Empty squares contain the digit 0. After reading the puzzle, the constructor 
    tries to solve it and records whether the puzzle has a solution or not.
*/
SudokuSolver::SudokuSolver(const std::string &input_file)
{
    create2Darray();
    std::ifstream file(input_file);
    std::string line;

    int row = 0;
    while (std::getline(file, line) && row < 9)
    {
        std::string val;
        std::stringstream ss(line);
        int col=0;
        while (std::getline(ss, val, ','))
        {
            puzzle_[row][col] = stoi(val);
            col++;
        }
        row++;
    }

    isSolvable_ = solve();
}

/**
    @post: Creates 2D array and sets private member variable 
           puzzle_ equal to it.
*/
void SudokuSolver::create2Darray()
{
    puzzle_ = new int *[9];

    for (int i = 0; i < 9; i++)
    {
        puzzle_[i] = new int[9];
    }
}

/**
    @return: returns true if the puzzle is solvable, false otherwise.
              We suggest you keep track of this when solving the problem at construction, 
              rather than solving the puzzle again each time this function is called.
*/
bool SudokuSolver::isPuzzleSolvable() const
{
    return isSolvable_;
}

/**
    @post: records the puzzle as being solvable
*/
void SudokuSolver::setSolvable()
{
    isSolvable_ = true;
}

/**
    @return: the  2D pointer array representing the puzzle
*/
int **SudokuSolver::getPuzzleNumbers() const
{
    return puzzle_;
}

/**
    @param: 2D pointer array
    @param: sets the  2D pointer array representing the puzzle to the value of the parameter 
*/
void SudokuSolver::setPuzzleNumbers(int **puzzle)
{
    puzzle_ = puzzle;
}

/**
    @return: returns a Location object with the coordinates of the first 0 found in the 2D pointer array,
             meaning that it is an empty square in the sudoku board. To find the first empty square you 
             must read the 2D array from top-left (0,0) to bottom right (8,8), one row at a time. Set the
             row and col of the Location to the indices at which the first 0 is found in the 2D array. If 
             there are no empty squares the Location object should have row and col values of -1.
*/
Sudoku::Location SudokuSolver::returnNextEmpty() const
{
    Sudoku::Location loc;
    Sudoku::Location empty_loc = {-1, -1};

    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (puzzle_[row][col] == 0)
            {
                loc = {row, col};
                return loc;
            }
        }
    }
    return empty_loc;
}

/**
    @return: returns true if the value parameter (which can take on values 1-9) can legally be placed at
             the given location in the 2D array without breaking the rules of sudoku. It returns false 
             if placing value at location is not a legal move. Remember, in order to be a valid move, 
             the value must be unique with a row, column, and sub-grid.
*/
bool SudokuSolver::checkLegalValue(int val, Sudoku::Location loc) const
{
    int row = loc.row;
    int col = loc.col;
    int start_row = row - row % 3;
    int start_colum = col - col % 3;

    for (int i = 0; i < 9; i++)
    {
        if (puzzle_[i][col] == val && i != row)
        {

            return false;
        }
    }

    for (int j = 0; j < 9; j++)
    {
        if (puzzle_[row][j] == val && j != col)
        {

            return false;
        }
    }

    for (int i = start_row; i < start_row + 3; i++)
    {
        for (int j = start_colum; j < start_colum + 3; j++)
        {
            if (puzzle_[i][j] == val)
            {
                if (i == row && j == col)
                {
                    continue;
                }
                return false;
            }
        }
    }
    return true;
}

/**
    @post: will display the board as illustrated below: 
        Example:
        N X X  | N X N  | X X N
        N X N  | X N N  | X X X
        N X N  | N X X  | X X X
        - - - - - - - - - - - - 
        X N X  | N X N  | N X X
        X X X  | X N X  | X X X
        X X N  | N X N  | X N X
        - - - - - - - - - - - - 
        X X X  | X X N  | N X N
        X X X  | N N X  | N X N
        N X X  | N X N  | X X N
    N is an integer 1-9 (the function displays the actual integer not an N)
    X represents a blank box where there is a zero (the function displays the X not the zero)
    After every 3 numbers (columns), we have a " | " to separate sub-grids. Note that each " | " is preceded by two space characters and followed by a single space character.
    After every 3 rows, we have 12 dashes " - " to separate the sub-grids.  
*/
void SudokuSolver::display() const
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (puzzle_[row][col] == 0)
            {
                if (col == 2 || col == 5)
                    std::cout << "X  | ";
                else if (col == 8)
                    std::cout << "X\n";
                else
                    std::cout << "X ";
            }
            else
            {
                if (col == 2 || col == 5)
                {
                    std::cout << puzzle_[row][col] << "  | ";
                }
                else if (col == 8)
                {
                    std::cout << puzzle_[row][col] << std::endl;
                }
                else
                {
                    std::cout << puzzle_[row][col] << " ";
                }
            }
        }
        if (row == 2 || row == 5)
        {
            std::cout << "- - - - - - - - - - - - " << std::endl;
        }
    }
}

/**
    @return: returns whether the puzzle is solvable.
    Solves the puzzle using backtracking.
*/
bool SudokuSolver::solve()
{
    Sudoku::Location loc = returnNextEmpty();
    if (loc.col == -1 && loc.row == -1)
    {
        setSolvable();

        return true;
    }
    for (int i = 1; i < 10; i++)
    {
        if (checkLegalValue(i, loc))
        {
            puzzle_[loc.row][loc.col] = i;
            if (solve())
            {
                setSolvable();
                return true;
            }
            else
            {
                puzzle_[loc.row][loc.col] = 0;
            }
        }
    }
    return false;
}