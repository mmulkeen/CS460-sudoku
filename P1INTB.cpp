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
//int available[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
void printA(int *available) { for (int i = 0;i<9;i++){cout<< available[i];}cout << endl;}
//void resetA(int available[9]) { for (int i = 0; i<9; i++){available[i] = 1;}}
int *construct (string input, int *board[9], int lineo);
bool ary[81] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int count = 0;
int main ()
{
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
	/*
	for( int i = 0; i < 9; i++) {
    		for( int j = 0; j < 9; j++) {
      			cout << board[i][j] << ' ';
    		}	
    	cout << endl;
  	}
	*/
	//int available[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

	if( solve(board) )
	  printGrid(board);
	else
	  cout << "A solution could not be generated for the given Sudoku puzzle\n";
	//cout << "This took " << count << "tries to complete\n";

        return 0;
}

int *construct (string input, int *board[9], int lineno) {

  int i = 0;
  int idx = 0;
  
  while( i < input.length()) {

    if( input[idx] != ' ' ) {
      int tmp = input[i]-'0';
      board[lineno][idx] = tmp;
      if ( input[i] != '0' ) {
	ary[idx+(lineno*9)] = 1;
      }
      idx++;
    }
    //cout<< board[lineno][j] << endl;
    i++;
  }
  return *board;
}

bool solve(int *board[9] ) {
	//cout << "CALLING DONE" << endl;
  //printGrid(board);
  //	printAry();
  //cout << "----------------------" << endl;
	if ( done() ) {return true;}
	//cout << "DONE CALLED" << endl;
	int start = getStart();
	int row = start / 9;
        int col = start % 9;
	//printA();
	//resetA();

	int available[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	
	checkCell(board, start, available);
	//	printA(available);
	//cout << available << endl;
	for (int i = 0;i<9;i++ ) {
		if ( available[i] != 0) {
		  count++;
			//cout << "INDEX OF AVAILABLE" << i
			board[row][col] =i + 1;
			//cout << "VALUE TO PLACE IN BOARD: " << i + 1 << endl;
			available[i] = 0;
			ary[col+(row*9)] = 1;
			if (solve(board)) {
				return true;
			}
			//resetA();
			//available = {1, 1, 1, 1, 1, 1, 1, 1, 1};
			board[row][col] = 0;
			ary[col+(row*9)] = 0;
		}
	}
	//printA(available);
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
	//printA(available);
	// Check cols
  	for( int j = 0; j < 9; j++) {
    		if( board[j][col] != 0 ) {
      			int temp = board[j][col];
			available[ temp - 1 ] = 0;
		}
  	}	

	//printA(available);
	//return available;
  	int startSectorCol = (col / 3) * 3;
  	int startSectorRow = (row / 3) * 3;
  	// Check sector
	
  	for( int i = startSectorRow; i < startSectorRow + 3; i++) {
    		for( int j = startSectorCol; j < startSectorCol + 3; j++) {
      			if( board[i][j] != 0 ) {
			  //cout << "NUMBER FOUND IN SECTOR: " << board[i][j] << endl;
				int temp = board[i][j];
				//cout << "VALUE IN BOARD: " << temp <<"| VALUES IN i & j: " << i << " " << j << endl;
				available[temp - 1] = 0;
			}
    		}
  	}

	/*
	cout << "SECTORS CHECKED" << endl;
	cout << "AVAIlABLE LIST: ";
	printA(available);
	*/
}
void printAry() { for (int i = 0;i<81;i++){cout<< ary[i];}cout << endl;}

