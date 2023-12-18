/*
Edison Freire
5/2/23
*/
#ifndef SudokuSolver_hpp
#define SudokuSolver_hpp

#include <iostream>
#include <fstream>
#include <sstream>

//We define Location within the Sudoku namespace.
//To use Location, you must specify the namespace Sudoku::Location
//Just like you do when using the standard namespace std::
namespace Sudoku
{
  struct Location
  {
    int row;
    int col;
  };
}

class SudokuSolver
{
public:
  /**
      Default constructor.
      The default constructor initializes an empty board, that is, a 
      board filled with zeros (an array of 9 arrays, each filled with 9 zeros). 
      This board will be marked unsolvable. 
  */
  SudokuSolver();

  /**
      Parameterized constructor.
      @param: a string indicating input file name
      The parameterized constructor reads the input file to initialize the board.
      The input files consist of 9 digits on each row separated by commas, and 
      9 rows separated by new line characters \n, corresponding to a sudoku board. 
      Empty squares contain the digit 0. After reading the puzzle, the constructor 
      tries to solve it and records whether the puzzle has a solution or not.
  */
  SudokuSolver(const std::string &input_file);

  /**
      @post: Creates 2D array and sets private member variable 
            puzzle_ equal to it.
  */
  void create2Darray();

  /**
      @return: returns true if the puzzle is solvable, false otherwise.
                We suggest you keep track of this when solving the problem at construction, 
                rather than solving the puzzle again each time this function is called.
  */
  bool isPuzzleSolvable() const;

  /**
      @post: records the puzzle as being solvable
  */
  void setSolvable();

  /**
      @return: the  2D pointer array representing the puzzle
  */
  int **getPuzzleNumbers() const;

  /**
      @param: 2D pointer array
      @param: sets the  2D pointer array representing the puzzle to the value of the parameter 
  */
  void setPuzzleNumbers(int **puzzle);

  /**
      @return: returns a Location object with the coordinates of the first 0 found in the 2D pointer array,
              meaning that it is an empty square in the sudoku board. To find the first empty square you 
              must read the 2D array from top-left (0,0) to bottom right (8,8), one row at a time. Set the
              row and col of the Location to the indices at which the first 0 is found in the 2D array. If 
              there are no empty squares the Location object should have row and col values of -1.
  */
  Sudoku::Location returnNextEmpty() const;

  /**
      @return: returns true if the value parameter (which can take on values 1-9) can legally be placed at
              the given location in the 2D array without breaking the rules of sudoku. It returns false 
              if placing value at location is not a legal move. Remember, in order to be a valid move, 
              the value must be unique with a row, column, and sub-grid.
  */
  bool checkLegalValue(int val, Sudoku::Location loc) const;

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
  void display() const;

  /**
      @return: returns whether the puzzle is solvable.
      Solves the puzzle using backtracking.
  */
  bool solve();


private:
  int **puzzle_;
  bool isSolvable_;
};

#endif
