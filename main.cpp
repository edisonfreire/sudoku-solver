#include "SudokuSolver.hpp"
#include <iostream>
using namespace std;

// g++ -std=c++17 main.cpp SudokuSolver.cpp -o main

int main()
{
    SudokuSolver puzzle;
    puzzle.display();
    cout<<puzzle.isPuzzleSolvable()<<endl;

    SudokuSolver puzzle2("puzzle1.csv");
    puzzle2.display();
    cout<<puzzle2.isPuzzleSolvable()<<endl;
}