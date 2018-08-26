// Sudoku Solver
// poop
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;
void printAry();
void printGrid(int *board[9]) {for( int i = 0; i < 9; i++) {for( int j = 0; j < 9; j++) {cout << board[i][j] << ' '; }  cout << endl;} }
bool solve ( int *board[9] );
void checkCell(int *board[9], int idx);
int getStart ();
bool done ();
int available[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
void printA() { for (int i = 0;i<9;i++){cout<< available[i];}cout << endl;}
void resetA() { for (int i = 0; i<9; i++){available[i] = 1;}}
int *construct (string input, int *board[9], int lineo);
bool ary[81] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int main (int argc, char * argv [])
{
	int *board[9];
	for ( int i = 0; i < 9; i++){
		board[i] = new int[9];
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

	solve(board);

        return 0;
}

int *construct (string input, int *board[9], int lineno) {
	
	for ( int j = 0; j < 9; j++) {
		int tmp = input[j]-'0';
		board[lineno][j] = tmp;
		if ( input[j] != '0' ) {
			ary[j+(lineno*9)] = 1;
		}	
	//cout<< board[lineno][j] << endl;
	}
	return *board;
}

bool solve(int *board[9] ) {
	//cout << "CALLING DONE" << endl;
	printGrid(board);
	printAry();
	cout << "----------------------" << endl;
	if ( done() ) {return true;}
	//cout << "DONE CALLED" << endl;
	int start = getStart();
	int row = start / 9;
        int col = start % 9;
	//printA();
	resetA();
	//int available[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	checkCell(board, start);
	printA();
	for (int i = 0;i<9;i++ ) {
		if ( available[i] != 0) {
			//cout << "INDEX OF AVAILABLE" << i
			board[row][col] =i + 1;
			cout << "VALUE TO PLACE IN BOARD" << i + 1 << endl;
			//available[i] = 0;
			ary[col+(row*9)] = 1;
			if (solve(board)) {
				return true;
			}
			resetA();
			board[row][col] = 0;
			ary[col+(row*9)] = 0;
		}
	}
	// check to see if every node was visited.
	// If not start with first open space.
	// Check the row collumn and box for available #'s
	// For each value available check all posibilities.
	/*
	for ( int i = 0; i<9;i++){
		for (int j=0;j<9;j++){
			cout << board[i][j] << endl;
		}
	}
	*/
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
void checkCell(int *board[9], int idx) {
	//cout << "START INDEX: " << idx << endl;
  	int row = idx / 9;
  	int col = idx % 9;
	//cout << "ROW & COL: " << row << " | " <<col << endl;	
  	for( int i = 0; i < 9; i++) {
    		if( board[row][i] != 0 ){
			int temp = board[row][i];
			int tmp = (int)temp;
			//cout << "VALUE OF BOARD: " << tmp << endl; 
      			available[ temp - 1 ] = 0;
		}
  	}
	//return available;
	//cout << "ROWS CHECKED" << endl;
  	// Check cols
  	for( int j = 0; j < 9; j++) {
    		if( board[j][col] != 0 ) {
      			int temp = board[j][col];
			available[ temp - 1 ] = 0;
		}
  	}	
	//cout << "COLS CHECKED" << endl;
	//return available;
  	int startSectorCol = (col % 3) * 3;
  	int startSectorRow = (row / 3) * 3;
  	// Check sector
	
  	for( int i = startSectorRow; i < 3; i++) {
    		for( int j = startSectorCol; j < 3; j++) {
      			if( board[startSectorRow][startSectorCol] != 0 ) {
				int temp = board[startSectorRow][startSectorCol];
				//cout << "VALUE IN BOARD: " << temp <<"| VALUES IN i & j: " << i << " " << j << endl;
				available[temp - 1] = 0;
			}
    		}
  	}
	
}
void printAry() { for (int i = 0;i<81;i++){cout<< ary[i];}cout << endl;}

