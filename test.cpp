#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<time.h>
#include<vector>
#include<string>

using namespace std;

int main() {
  string line;
  vector<string> lines;
  int tempArray[81];
  int num;
  string longSudoku;

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
  string temp = "";
  for(int i=0; i<81; i++)
  {
    num = 0;
    temp = longSudoku[i];
    num = stoi(temp);
    tempArray[i] = num;
  }

  for(int row=0;row<9;row++)
  {
      for(int col=0;col<9;col++)
      {
          grid[row][col] = tempArray[row + col*2];
      }
  }

  for(int row=0;row<9;row++)
  {
      for(int col=0;col<9;col++)
      {
          cout<<" "<<grid[row][col];
      }
      cout<<endl;
  }

  return 0;
}
