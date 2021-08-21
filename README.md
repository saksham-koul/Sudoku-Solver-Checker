# Sudoku Solver & Checker
A C++ program that could solve a sudoku provided to it or check the correctness of the solution provided by a user for a sudoku.

## Introduction
* Sudoku is a logic-based number puzzle featuring a 9x9 board divided into rows, columns, and 3x3 square blocks. 
* The goal of the game is to fill each row, column, and block with unique numbers in the range 1 through 9. 
* A Sudoku starts with some cells containing numbers (clues), and the goal is to solve the remaining cells.
* Proper Sudokus have a unique solution.
* Variations of sudoku have used larger boards, such as hexadoku: sudoku with a 16x16 board.

## Algorithm
* A backtracking algorithm is a recursive algorithm that attempts to solve a given problem by testing all possible paths towards a solution until a solution is found. 
* Each time a path is tested, if a solution is not found, the algorithm ‘backtracks’ to test another possible path and so on till a solution is found or all paths have been tested.
* Based on Depth – First search.

![Sudoku_solved_by_bactracking](https://user-images.githubusercontent.com/78582744/130322282-da94db88-e0c1-4be0-b19f-3729ea5e2be4.gif)
(Img source : [Wikipedia](https://en.wikipedia.org/wiki/Sudoku_solving_algorithms#/media/File:Sudoku_solved_by_bactracking.gif))

### Advantages of the backtracking algorithm
* It is guaranteed to find a solution if there is one, simply because it eventually tries every possible number in every possible location. 
* Solving time is mostly unrelated to degree of difficulty.
* The algorithm (and therefore the program code) is simpler than other algorithms. 

## Implementation
* The code for the project has been written in C++.
* OOP paradigm has been efficiently employed. 
* The program presents the user/player with 2 options : 
    * to either enter a sudoku (which the program shall solve)
    * to solve a sudoku given by the program
* The program also uses the functionality of file handling in C++ to store sudokus and their solutions in a text file.
* Sudokus of varying difficulty levels are also stored in separate text files.
* The program uses a backtracking strategy to solve a sudoku.
