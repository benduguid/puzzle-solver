#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>
#include <fstream>
#include <chrono>
#include <iomanip>

#define GRID_SIZE 9

using namespace std;

using namespace std::chrono;

void printBoard(int grid[][9]);
bool isValidPlacement(int grid[][9], int n, int row, int col);
bool checkRow(int grid[][9], int n, int row);
bool checkCol(int grid[][9], int n, int col);
bool solveBoard(int grid[][9]);
bool checkNeighbours(int grid[][9], int n, int row, int col);
void menu(int grid[][9]);
void randomizeSudoku(int grid[][9]);

int main() {
  int grid[9][9] = {{8,0,0,0,0,0,0,0,0},
                    {0,0,3,6,0,0,0,0,0},
                    {0,7,0,0,9,0,2,0,0},
                    {0,5,0,0,0,7,0,0,0},
                    {0,0,0,0,4,5,7,0,0},
                    {0,0,0,1,0,0,0,3,0},
                    {0,0,1,0,0,0,0,6,8},
                    {0,0,8,5,0,0,0,1,0},
                    {0,9,0,0,0,0,4,0,0},
                  };
  for(int i=0; i<5; i++){
    menu(grid);
  }

  return 0;
}

void menu(int grid[][9])
{
  int userchoice;
  string confirm;
  do
  {
    cout<<"1. Randomize Sudoku";
    cout<<"\n2. Solve This Sudoku";
    cout<<"\nEnter your choice(1 or 2):";
    cin>>userchoice;
    switch (userchoice)
    {
      case 1:
        randomizeSudoku(grid);
        printBoard(grid);
        break;
      case 2:
      {
        //Start point before the puzzle is solved for timer
        auto start = high_resolution_clock::now();
        if (solveBoard(grid)) {
          auto stop = high_resolution_clock::now();

          //Post solve point
          auto duration = duration_cast<microseconds>(stop - start);

          //Subtracting the two points and converting microseconds into seconds
          //Multiplying by 1.0 is an easy way to convert from an integer to float
          float time = duration.count()  * 1.0 / 1000000;

          std::cout << std::fixed;
          std::cout << std::setprecision(6); //Accuracy of 6 significant figures
          cout << "\nSolved successfully! in " << time << "s \n\n";
        }
        else {
          cout << "\n\t\t\t\tUnsolvable board :(\n";
        }
        printBoard(grid);
        break;
      }
      default:
        cout<<"invalid";
        break;
    }
    cout<<"Press y or Y to solve:";
    cin>>confirm;
    if(confirm == "y" || confirm == "Y"){
      //Start point before the puzzle is solved
      auto start = high_resolution_clock::now();
      if (solveBoard(grid)) {
        auto stop = high_resolution_clock::now();

        //Post solve point
        auto duration = duration_cast<microseconds>(stop - start);

        //Subtracting the two points and converting microseconds into seconds
        //Multiplying by 1.0 is an easy way to convert integer to float
        float time = duration.count()  * 1.0 / 1000000;

        std::cout << std::fixed;
        std::cout << std::setprecision(6);
        cout << "\nSolved successfully! in " << time << "s \n\n";
      }
      else {
        cout << "\n\t\t\t\tUnsolvable board :(\n";
      }
      printBoard(grid);
      break;
    }
  } while (confirm != "y" || confirm != "Y");
}


void printBoard(int grid[][9]) {
    for(int row=0;row<GRID_SIZE;row++)
    {
        for(int col=0;col<GRID_SIZE;col++)
        {
            cout<<" "<<grid[row][col];
        }
        cout<<endl;
    }

    cout << "\n\n\n\n";
}


bool isValidPlacement(int grid[][9], int n, int row, int col)
{
    return (!checkRow(grid, n, row) && !checkCol(grid, n, col) && !checkNeighbours(grid, n, row, col));
}

bool checkRow(int grid[][9], int n, int row) {
    for (int i = 0; i < GRID_SIZE; i++) {
      if (grid[row][i] == n) {
        return true;
      }
    }
    return false;
}

bool checkCol(int grid[][9], int n, int col) {
    for (int i = 0; i < GRID_SIZE; i++) {
      if (grid[i][col] == n) {
        return true;
      }
    }
    return false;
}

bool checkNeighbours(int grid[][9], int n, int row, int col) {
    int neighbourRow = row - row % 3;
    int neighbourCol = col - col % 3;

    for (int i = neighbourRow; i < neighbourRow + 3; i++) {
      for (int j = neighbourCol; j < neighbourCol + 3; j++) {
        if (grid[i][j] == n) {
          return true;
        }
      }
    }
    return false;
}

bool solveBoard(int grid[][9])
{
    for (int row = 0; row < GRID_SIZE; row++) {
      for (int col = 0; col < GRID_SIZE; col++) {
        if (grid[row][col] == 0) {
          for (int testNumber = 1; testNumber <= GRID_SIZE; testNumber++) {
            if (isValidPlacement(grid, testNumber, row, col)) {
              grid[row][col] = testNumber;

              if (solveBoard(grid)) {
                return true;
              }
              else {
                grid[row][col] = 0;
              }
            }
          }
          return false;
        }
      }
    }
    return true;
}

void randomizeSudoku(int grid[][9])
{
  string line;
  vector<string> lines;
  vector<int> numVector;
  int num;
  string temp = "";
  string longSudoku;

  srand(time(0));

  //input file stream
  ifstream file("sudokuGen.txt");

  //count number of total lines in the file and store the lines in the string vector
  int total_lines=0;
  while(getline(file,line))
  {
     total_lines++;
     lines.push_back(line);
  }

  //generate a random number between 0 and count of total lines
  int randNum=rand()%total_lines;

  //fetch the line where line index (starting from 0) matches with the random number
  longSudoku = lines[randNum];

  for(int i=0; i<81; i++)
  {
    num = 0;
    temp = longSudoku[i];
    num = stoi(temp);
    numVector.insert(numVector.end(), 1, num);
  }


  for(int row=0;row<GRID_SIZE;row++)
  {
      for(int col=0;col<GRID_SIZE;col++)
      {
          grid[row][col] = numVector[col];
      }
      for(int i=0; i<9; i++){
        numVector.erase(numVector.begin());
      }
  }
}
