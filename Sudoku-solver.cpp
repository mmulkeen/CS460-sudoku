// Sudoku Solver
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

bool solve ( char *board[9] );
bool done ( bool ary[] );
char * construct (string input, char *board[9], int lineo);
int checkCell(char *board[9], int idx);
bool ary[81] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int main (int argc, char * argv []) {

  char *board[9];

  for ( int i = 0; i < 9; i++){
    board[i] = new char[9];
  }
  
  if (argc < 2)
    {
      cerr << "Usage: " << argv[0] << " <filename>\n";
      exit (1);
    }

  ifstream infile (argv[1]);

  if (infile.fail())
    {
      cerr << "File: " << argv[1] << " not found.\n";
      exit (2);
    }

  string line;
  int lineno = 0;

  while (getline (infile, line))
    {
      construct(line, board, lineno);
      lineno++;
    }
  infile.close();
  
  for( int i = 0; i < 9; i++) {
    for( int j = 0; j < 9; j++) {
      cout << board[i][j] << ' ';
    }
    cout << endl;
  }

  for( int i = 0; i < 81; i++) {
    cout << ary[i];
  }
  cout << endl;
  
  solve(board);
  
  return 0;
}

char * construct (string input, char *board[9], int lineno) {
  
  for ( int j = 0; j < 9; j++) {
    board[lineno][j] = input[j];
    if ( input[j] != '0' ) {
      ary[j+(lineno*9)] = 1;
    }	
  }
  return *board;
}

bool solve(char *board[9] ) {
  // check to see if every node was visited.
  // If not start with first open space.
  // Check the row collumn and box for available #'s
  // For each value available check all posibilities.
  
}

int checkCell(char *board[9], int idx) {

  int available[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1);
  
  int row = idx / 9;
  int col = idx % 9;

  // Check rows
  for( int i = 0; i < 9; i++) {
    if( board[row][i] != 0 )
      available[ board[row][i] -1 ] = 0;
  }

  // Check cols
  for( int j = 0; j < 9; j++) {
    if( board[j][col] != 0 )
      available[ board[j][col] -1 ] = 0;
  }

  int startSectorCol = (col / 3) * 3;
  int startSectorRow = (row / 3) * 3;
  // Check sector
  for( int i = startSectorRow; i < 3; i++) {
    for( int j = startSectorCol; j < 3; j++) {
      if( board[startSectorRow][startSectorCol] != 0 )
	available[ board[startSectorRow][startSectorCol] - 1 ] = 0;
    }
  }

  return available;
}

bool done( bool ary[] ) {
  
  
  for ( int i = 0; i < 81; i++) {
    if (ary[i] == 0){return false;}
  }
  
}
