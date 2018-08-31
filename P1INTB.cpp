// Sudoku Solver
// Matthew Mulkeen & Adam May
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

void printAry();
void printGrid(int *board[9]) {for( int i = 0; i < 9; i++) {for( int j = 0; j < 9; j++) {cout << board[i][j] << ' '; }  cout << endl;} }
bool solve ( int *board[9] );
void checkCell(int *board[9], int idx, int *available);
int getStart ();
bool done ();
void printA(int *available) { for (int i = 0;i<9;i++){cout<< available[i];}cout << endl;}
int *construct (string input, int *board[9], int lineo);

// Boolean Array of completed cells
bool ary[81] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int count = 0; // Count of how many guesses have been made so far

int main ()
{
	// Initialize 2d board array
	int *board[9];
	for ( int i = 0; i < 9; i++){
		board[i] = new int[9];
	}

	string filename;
	cout << "Enter puzzle file: ";
	cin >> filename;
	
        ifstream infile (filename);
        if (infile.fail())
	  {
	  cerr << "File: " << filename << " not found.\n";
	  exit (2);
        }
	
        string line;
        int lineno = 0;
        while (getline (infile, line))
	  {
	    if( line == "" )
	      break;
	    construct(line, board, lineno);
	    lineno++;
        }
        infile.close();

	if( solve(board) )
	  printGrid(board);
	else
	  cout << "A solution could not be generated for the given Sudoku puzzle\n";
	
	//cout << "This took " << count << "tries to complete\n";

        return 0;
}

int *construct (string input, int *board[9], int lineno) {

  int i = 0; 	// line position
  int idx = 0; 	// index of current row
  
  while( i < input.length()) {

    if( input[idx] != ' ' ) {
      int tmp = input[i]-'0';
      board[lineno][idx] = tmp;
      if ( input[i] != '0' ) {
	ary[idx+(lineno*9)] = 1;
      }
      idx++;
    }
    i++;
  }
  return *board;
}

bool solve(int *board[9] ) {
	
	if ( done() ) return true;
	
	int start = getStart();	// Get next blank square
	
	// Convert ary position to 2d array grid
	int row = start / 9;
        int col = start % 9;

	int available[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	
	// Find available moves to make for current cell
	checkCell(board, start, available);
	
	for (int i = 0;i<9;i++ ) {
		if ( available[i] != 0) {
			count++;
			
			board[row][col] =i + 1;
			available[i] = 0;
			ary[col+(row*9)] = 1;	// use start instead?
			if (solve(board)) {
				return true;
			}
			
			// If we made a wrong guess, reset the board changes
			board[row][col] = 0;
			ary[col+(row*9)] = 0;
		}
	}
	
	return false;
}

bool done() {
	
	for ( int i = 0; i < 81; i++) {
		if (ary[i] == 0){return false;}
	}

	return true;
}

int getStart() {
	
	for (int i=0;i<81;i++){
		if (ary[i] == 0){return i;}
	}
	
}
void checkCell(int *board[9], int idx, int *available) {
	
	// Convert ary position to 2d grid position
  	int row = idx / 9;
  	int col = idx % 9;
	
	// Check rows
  	for( int i = 0; i < 9; i++) {
    		if( board[row][i] != 0 ){
			int temp = board[row][i];
      			available[ temp - 1 ] = 0;
		}
  	}
	
	// Check cols
  	for( int j = 0; j < 9; j++) {
    		if( board[j][col] != 0 ) {
      			int temp = board[j][col];
			available[ temp - 1 ] = 0;
		}
  	}	

  	// Check sector
	
	// Get top left corner indexes of the current sector
	int startSectorCol = (col / 3) * 3;
  	int startSectorRow = (row / 3) * 3;
  	for( int i = startSectorRow; i < startSectorRow + 3; i++) {
    		for( int j = startSectorCol; j < startSectorCol + 3; j++) {
      			if( board[i][j] != 0 ) {
				int temp = board[i][j];
				available[temp - 1] = 0;
			}
    		}
  	}

}
void printAry() { for (int i = 0;i<81;i++){cout<< ary[i];}cout << endl;}

