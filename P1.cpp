// Sudoku Solver
// poop
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;
int to_int(char c) { return c;}
bool solve ( char *board[9] );
int *checkCell(char *board[9], int idx, int available[9]);
int getStart ();
bool done ();
char *construct (string input, char *board[9], int lineo);
bool ary[81] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int main (int argc, char * argv [])
{
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

	solve(board);

        return 0;
}

char *construct (string input, char *board[9], int lineno) {
	
	for ( int j = 0; j < 9; j++) {
		board[lineno][j] = input[j];
		if ( input[j] != '0' ) {
			ary[j+(lineno*9)] = 1;
		}	
	//cout<< board[lineno][j] << endl;
	}
	return *board;
}

bool solve(char *board[9] ) {
	done();
	int start = getStart();
	int available[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	checkCell(board, start, available);
	for (int i = 0;i<8;i++){
		cout<<available[i]<<endl;
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
	return true;
}
bool done() {
	
	
	for ( int i = 0; i < 81; i++) {
		if (ary[i] == 0){return false;}
	}

	return true;

}

int getStart() {
	for (int i=0;i<81;i++){
		if (ary[i] == 0){return ary[i];}
	}
	
}
int *checkCell(char *board[9], int idx, int available[9]) {
	cout << "START INDEX: " << idx << endl;
  	int row = idx / 9;
  	int col = idx % 9;
	cout << "ROW & COL: " << row << " | " <<col << endl;	
  	for( int i = 0; i < 9; i++) {
    		if( board[row][i] != '0' ){
			char temp = board[row][i];
			//int tmp = (int)temp-48;
			int tmp = temp-'0';
			cout << "VALUE OF BOARD: " << tmp << endl; 
      			available[ temp - 1 ] = 0;
		}
  	}
	//return available;
	cout << "ROWS CHECKED" << endl;
  	// Check cols
  	for( int j = 0; j < 9; j++) {
    		if( board[j][col] != '0' ) {
      			int temp = board[j][col];
			available[ temp - 1 ] = 0;
		}
  	}	
	cout << "COLS CHECKED" << endl;
	//return available;
  	int startSectorCol = (col % 3) * 3;
  	int startSectorRow = (row / 3) * 3;
  	// Check sector
	
  	for( int i = startSectorRow; i < 3; i++) {
    		for( int j = startSectorCol; j < 3; j++) {
      			if( board[startSectorRow][startSectorCol] != '0' ) {
				char temp = board[startSectorRow][startSectorCol];
				cout << "VALUE IN BOARD: " << temp <<"| VALUES IN i & j: " << i << " " << j << endl;
				available[temp - 1] = 0;
			}
    		}
  	}
	
  	return available;
}

