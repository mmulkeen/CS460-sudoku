// Sudoku Solver
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;
bool solve ( char *board[9] );
bool done ( bool ary[] );
char construct (string input, char *board[9], int lineo);
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
	       /*
	       	 for ( int j = 0; j < 9; j++) {
                	board[lineno][j] = line[j];
                	if ( line[j] != '0' ) {
                        	ary[j+(lineno*9)] = 1;
			}

			lineno++;
		}
		*/
	       lineno++;
        }
        infile.close();

	solve(board);

        return 0;
}

char construct (string input, char *board[9], int lineno) {
	
	for ( int j = 0; j < 9; j++) {
		board[lineno][j] = input[j];
		if ( input[j] != '0' ) {
			ary[j+(lineno*9)] = 1;
		//cout<< board[lineno][j] << endl;
		}	
	cout<< board[lineno][j] << endl;
	}
	return 'c';
}

bool solve(char *board[9] ) {
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
}
bool done( bool ary[] ) {
	
	
	for ( int i = 0; i < 81; i++) {
		if (ary[i] == 0){return false;}
	}

}

