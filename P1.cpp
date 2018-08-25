// Sudoku Solver
#include <iostream>
#include <string>
using namespace std;
string construct (string input);
int ary[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
int main (int argc, char * argv [])
{
	string board[9][9];

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
               board = construct(line, board);
	       lineno++;
        }
        infile.close();

	solve(board);

        return 0;
}

string construct (input, board, lineno) {
	
	for ( int j = 0; j < 9; j++) {
		board[lineno][j] = input[j];
		if ( input[j] != '0' ) {
			ary[lineno*j] = 1;
		}	
	}
	return board
}
bool solve( board ) {
	// check to see if every node was visited.
	// If not start with first open space.
	// Check the row collumn and box for available #'s
	// For each value available check all posibilities.

}
bool done( ary ) {
	
	for ( int i = 0; i < 81; i++) {
		if (ary[i] == 0){return false;}
	}

}

