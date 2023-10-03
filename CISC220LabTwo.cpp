/* Luke Fanizzi, Angelina Gargiulo, Robert Perez
 * Lauren Olson
 * 2/15/2020
 * This file contains functions for lab 2. They all work together in the given main
 * function to create the executable MineSweeper game.
 */

#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

void getSize(int &size);
int **makeBoard(int boardsize);
void printBoard(int **mat, int size);
void placeBombs(int **mat, int size);
void placeCounts(int **mat, int size);
int checkBox(int row, int column, int size, int **mat);
char **visible = NULL;
char**makeVisibleBoard(int size);
void printVisible(int size, char **array);
bool chooseSquare(int **array,char **visible  , int size);
bool addBomb(char **visible, int size, int *bombsFound);
void removeBomb(char **visible, int size, int *bombsFound);
bool checkForWin(int **mat,char **visible  , int size);
void removeBoard(int **mat, int size);
void removeVisible(char **visible, int size);

int main(){
	srand(time(NULL));
	int size = 0;
	int bombsfound = 0;
	getSize(size);
	cout << "Size is " << size << endl;
	visible = new char *[size];
	for(int i = 0; i < size; i ++){
	  	 visible[i] = new char[size];
    }
	int **mat = makeBoard(size);
	//printBoard(mat, size); - for testing purposes
	placeBombs(mat,size);
	//printBoard(mat, size); - for testing purposes
	placeCounts(mat, size);
	//printBoard(mat, size); - for testing purposes
	char **visible = makeVisibleBoard(size);

	//For testing purposes:
	//cout<<"***TEST printVisible***"<<endl;
	//printVisible(size,visible);
	//cout<<"***TEST chooseSquare***"<<endl;
	//chooseSquare(mat,visible,size);
	//cout<<"***TEST printVisible***"<<endl;
	//printVisible(size,visible);
	//cout<<"***TEST addBomb***"<<endl;
	//addBomb(visible, size, &bombsfound);
	//printVisible(size,visible);
	//cout<<"***TEST removeBomb***"<<endl;
	//removeBomb(visible, size, &bombsfound);
	//printVisible(size,visible);
	//cout<<"***TEST checkForWin***"<<endl;
	//checkForWin(mat, visible, size);
	//End of testing

	char c;
	bool flag = true;
	char again = 'n';
	while (flag) {
		cout << "***TEST printVisible***" << endl;
		printVisible(size,visible);
		cout << "Choose: A for choose square, B for add Bomb, C for remove bomb: " << endl;
		cin >> c;
		if (c == 'A' || c == 'a') {
			cout << "***TEST chooseSquare***" << endl;
			flag = chooseSquare(mat, visible, size);
			if (!flag) {
				cout << "YOU LOSE! YOU HIT A BOMB!!" << endl;
				cout << "***TEST printBoard***" << endl;
				printBoard(mat, size);
				cout << "\n\nDo you want to play again?" <<endl;
				cin >> again;
			}
		}
		if (c == 'B' || c == 'b') {
			cout<<"***TEST addBomb***"<<endl;
			if (addBomb(visible, size, &bombsfound)) {
				cout << "Bombs found: " << bombsfound << endl;
				cout << "You appear to think you've found all the bombs" << endl;
				cout << "Choose: D for check for Win, or C for remove bomb:" << endl;
				cin >> c;
				if (c == 'D' || c == 'd') {
					cout<<"***TEST checkForWin***"<<endl;
					if (checkForWin(mat, visible, size)) {
						cout << "YOU WON!!! WOO WOO!!!" << endl;
						cout << "***TEST printBoard***" << endl;
						printBoard(mat, size);
					} else {
						cout <<"Sorry, you were wrong. Boo hoo." << endl;
						cout << "***TEST printBoard***" << endl;
						printBoard(mat, size);
					}
					cout << "***TEST removeBoard***" << endl;
					removeBoard(mat, size);
					cout << "***TEST removeVisible***" << endl;
					removeVisible(visible, size);
					bombsfound = 0;
					flag = false;
					cout << "\n\nDo you want to play again? (y or n)" <<endl;
					cin >> again;
				}
			}
		}
		if (c == 'C' || c == 'c') {
			cout<<"***TEST removeBomb***"<<endl;
			removeBomb(visible, size, &bombsfound);
		}
		if (!flag && (again == 'y' || again == 'Y')) {
			flag = true;
			bombsfound = 0;
			getSize(size);
			cout << "Size is " << size << endl;
			mat = makeBoard(size);
			placeBombs(mat,size);
			placeCounts(mat, size);
			visible = makeVisibleBoard(size);
		}
	}
	return 0;
}

/********************************FUNCTION DEFINITIONS GO HERE***************************************/

/* Function #1 : getSize
 * This uses call by reference to modify the integer input parameter to a random
 * number between 7 and 20 (not including 20). This will be the size of the board.
 * The "size" parameter is a pointer that is called by the reference of the size.
 */
void getSize(int &size){
	srand (time(NULL)); //randomizes a number
	size = rand() % 14 + 6; //looks at modulus 14 and adds 6
}

/* Function #2 : makeBoard
 * This function takes in an input as an integer, which is the length and width of
 * the board (it's a square board). The function should create an integer matrix (a
 * 2-D array) on the heap, fill the matrix with 0's and return the pointer to the matrix.
 */
int **makeBoard(int boardsize){
	int **arr = new int *[boardsize]; //pointer to array and sets it to a new integer of pointer "boardsize"
	for (int i = 0; i < boardsize; i++){ //iterates through i values
		arr[i] = new int[boardsize];
	}
	int a = 0;
	for (int i = 0; i < boardsize; i++){ //goes through the rows
		for (int j = 0; j < boardsize; j++){ //goes through the columns
			arr[i][j] = a;
		}
	}
	return arr;
}

/* Function #3 : printBoard
 * This method takes as input a pointer to a matrix (a 2-D function) of integers and an
 *  integer for the size (the length and the width - it's a square). It returns nothing.
 *  It should print out the matrix, only it should print a space instead of a 0.
 */
void printBoard(int **mat, int size){
	cout << "Printing" << endl;
	for(int i = 0; i < size; i++){  //iterates through "x"
 		 for(int j = 0; j < size; j++){ //iterates through "y"
 			 if(mat[i][j] == 0){ //replaces board at x,y with blank symbols
 				 cout << " " << " ";
 			 } else {
 				 cout << mat[i][j] << " "; //when done prints whole board

 			 }
 		 }
 		 cout << endl;
 	 }
 	 cout << "Done printing." << endl;
}

/* Function #4 : placeBombs
 * This function takes as an input parameter a pointer to the 2-D matrix
 * of integers (the board) and an  integer (the size). It places size + 1 "bombs"
 * randomly on the 2-D matrix.
 */
void placeBombs(int **mat, int size){
	int numberOfBombsPlaced = 0; //int representing number of bombs placed
	while(numberOfBombsPlaced < size+1){ //// while statement that runs while number of bombs is less than size + 1
		int randomRowIndex = rand() % size; //indexes random row
		int randomColumnIndex = rand() % size; //indexes random column
		if (mat[randomRowIndex][randomColumnIndex] != 9){ //if value is not equal to a bomb
			mat[randomRowIndex][randomColumnIndex] = 9; //replace it to a bomb or 9
			numberOfBombsPlaced++; //iterates on "bombplaced"
		}
	}
}

/* Function #5 : placeCounts
 * This function takes as input parameters a pointer to the 2-D integer matrix that is the board, an integer
 * representing the size of the board. It returns nothing. This function places the counts on the board.
 */
void placeCounts(int **mat, int size){
	for(int row = 0; row < size; row++){ //iterates through the row
		for(int column = 0; column < size; column++){ //iterates through the column
			if(mat[row][column] != 9){ //checks if the value is not a bomb
				mat[row][column] = checkBox(row, column, size, mat);  //runs check box on the row and columns not bombs
			}
		}
	}
}

/* Function #6 : **makeVisibleBoard
 * This function takes as an input parameter the integer for the size of the 2-D matrix of characters that will
 * be created in this function and returned from this function. The 2-D matrix will be initialized to all '-'.
 */
char** makeVisibleBoard(int size){
	char visibleBoard[size][size];  //initializes a visible board of size [size][size]
	char **arr = NULL ; //sets pointer of the array to null
    arr = new char *[size]; //sets the array to a new array of size
    for(int i = 0; i < size; i ++){ //iterates through the array through size
    	 arr[i] = new char[size]; //for "i" in the array creates a character there
    }
	for(int i = 0; i < size; i++){ //iterates through "x"
		for(int j = 0; j < size; j++){ //iterates through "y"
			visibleBoard[i][j] = '-'; //replaces each x, y with '-'
			arr[i][j] = visibleBoard[i][j]; //sets the array new a new array "visibleboard"
		}
	}
	return arr;
}

/* Function #7 : printVisible
 * This method takes as input a pointer to a matrix (a 2-D function) of Chars and a
 * integer for the size (the length and the width - it's a square). It returns nothing.
 * It should print out the matrix.
 */
void printVisible(int size, char **array){
	for(int i = 0; i < size; i++){  //increments through rows of matrix (chars)
		for(int j = 0; j < size; j++){ //increments through columns of matrix (chars)
			cout <<  array[i][j] << ""; //prints out the element in the character matrix
		}
		cout << endl; //program will go to next line
	}
}

/* Function #8 : chooseSquare
 * This function takes as input parameters the pointer to the board matrix of integers, the pointer to the visible
 * matrix of chars, and the size. It uses "cout" and "cin" to allow the user to choose a square (the x and the y position
 * on the matrix respectively) and then sets the visible matrix at that square to be the value in the board matrix.
 * This function returns a boolean - false if the square chosen was a bomb, and true otherwise.
 */
bool chooseSquare(int **mat,char **visible, int size){
	int x,y; //initializes x,y
	cout << "Enter an X value: " << endl; //asks user to enter a X value
	cin >> x;
	while(x > (size - 1) or x < 0){ //while statement to determine if x is a valid value
		cout << "Enter a valid X value: " << endl; //asks user to enter a new x value
		cin >> x;
	}
	cout << "Enter a Y value: " << endl;  //asks user to enter a Y value
	cin >> y;
	while(y > (size - 1) or y < 0){ //while statement to determine if y is a valid value
		cout << "Enter a valid Y value: " << endl; //asks user to enter a new y value
		cin >> y;
	}
	if(mat[x][y] == 9){ //if mat at x,y is equal to 9 returns false
		return false;
	} else {
		int v =  mat[x][y]; //sets the matrix at [x][y] to v
		char variable = '0' + v; //changes the value to a character
		visible [x][y] = variable; //visible of x,y equals new variable
		return true; //returns true
	}
}

/* Function #9 : checkBox
 * This is a "helper" function for chooseSquare. It makes sure that the 8 surrounding
 * boxes of the selected box is a valid space and is not off the board. It takes in the board,
 * the rows and columns, and the size to validate that information.
 */

int checkBox(int row, int column, int size, int **mat){
	int count = 0;  //initializes count
	if(row - 1 >= 0){
		if(mat[row - 1][column] == 9){ //checks if there is a bomb to the left of the current place
			count++;
		}
	}
	if(row + 1 < size){
		if(mat[row + 1][column] == 9){ //checks if there is a bomb to the right of the current place
			count++;
		}
	}
	if(column - 1 >= 0){
		if(mat[row][column - 1] == 9){ //checks if there is a bomb below the current place
			count++;
		}
	}
	if(column + 1 < size){
		if(mat[row][column + 1] == 9){ //checks if there is a bomb below the current place
			count++;
		}
	}
	if(row - 1 >= 0 && column + 1 < size){ //checks NorthWest box for bomb
		if(mat[row - 1][column + 1] == 9){
			count++;
		}
	}
	if(row + 1 < size && column - 1 >= 0){
		if(mat[row + 1][column - 1] == 9){ //checks SouthEast box for bomb
			count++;
		}
	}
	if(row - 1 >= 0 && column - 1 >= 0){
		if(mat[row - 1][column - 1] == 9){ //checks SouthWest box for bomb
			count++;
		}
	}
	if(row + 1 < size && column + 1 >= 0){
		if(mat[row + 1][column + 1] == 9){ //checks NorthEast box for bomb
			count++;
		}
	}
	return count; //return final count
}

/* Function #10 : addBomb
 * This function takes as input parameters the pointer to the visible matrix of chars, the size integer, and a
 * pointer to the number of bombs found. It returns a boolean value (true if the number of bombs found is equal
 * to size + 1, false otherwise. This function is allowing the user to choose a square where they think a bomb is
 * and mark it as bomb in the visible matrix.
 */
bool addBomb(char **visible, int size, int *bombsFound){
	bool bomb = false; //initializes bomb to false
	int x,y; //initializes x and y
	cout << "Enter an X value to place your flag: " << endl; //asks user to enter X position of flag
	cin >> x;
	while(x > size or x < 0){ //  statement to determine if X input is valid
		cout << "Enter a valid X value: " << endl;  // if a invalid value is entered, asks user to input a valid number
		cin >> x;
	}
	cout << "Enter a Y value to place your flag: " << endl;  //asks user to enter Y position of flag
	cin >> y;
	while(y > size or y < 0){ //while statement to determine if X input is valid
		cout << "Enter a valid Y value: " << endl; //if a invalid value is entered, asks user to input a valid number
		cin >> y;
	}
	if (visible[x][y] != 'X'){ //if the index is not equal to "X"
		visible[x][y] = 'X'; //set the index to "X"
		*bombsFound = *bombsFound + 1; //add one to the number of bombs found
		cout << *bombsFound << endl; //print the amount of bombs found
	}
	if (*bombsFound == size + 1){ //if bombs found equal to the max amount return true
		bomb = true; //set bomb to true
	} else {
		bomb = false; //set bomb to false
	}
	return bomb; //return the boolean value of bomb
}

/* Function #11 : removeBomb
 * This function takes as input parameters the pointer to the visible matrix of chars, the size integer, and a
 * pointer to the number of bombs found. It returns nothing. This function is allowing the user to choose a
 * square where they previously placed a bomb and un-mark the square.
 */
void removeBomb(char **visible, int size, int *bombsFound){
	int x,y;
	cout << "Enter an X value to remove your flag: " << endl; //asks user to enter X position of flag
	cin >> x;
	while(x > size or x < 0){ //while statement to determine if X input is valid
		cout << "Enter a valid X value: " << endl; //if a invalid value is entered, asks user to input a valid number
		cin >> x;
	}
	cout<< "Enter a Y value to remove your flag: " << endl; //asks user to enter Y position of flag
	cin >> y;
	while(y > size or y<0){ //while statement to determine if Y input is valid
		cout<< "Enter a valid Y value: " << endl; //if a invalid value is entered, asks user to input a valid number
		cin >> y;
	}
	if (visible[x][y] == 'X'){ //if the index is equal to "X"
		visible [x][y] = '-'; //removes the bomb at x,y and replaces it with a blank space
		*bombsFound = *bombsFound - 1; //decrements the number of bombs found by 1
	}
	printVisible(size, visible); //print the visible board
}

/* Function #12 : checkForWin
 * This function takes as input the pointer to the board matrix of integers, the pointer to the visible matrix
 * of characters, and the integer size. It checks to make sure that each bomb in the board matrix has been marked
 * as a bomb on the visible matrix. It returns a boolean value - true if all the bombs have been found, and false otherwise.
 */
bool checkForWin(int **mat,char **visible  , int size){
	bool bomb = false; //sets bomb to false
	int bombsFound = size +1; //maximum number is "bombsfound" or size +1
	int checkBombs = 0; //sets "checkedbombs" to 0 to count up on
	for(int i = 0; i < size; i++){ //iterates through row
		for(int j = 0; j < size; j ++){  //iterates through column
			if (visible[i][j] == 'X' && mat[i][j] == 9){ //if statement to check if the new indexes match up
				checkBombs++; //counts up on "checkedbombs"
			}
		}
	}
	if(bombsFound == checkBombs){ //when checkedbombs = bombsfound set bombs to true
		bomb = true;
	}
	return bomb;
}

/* Function #13 : removeBoard
 * This function takes as input parameters the pointer to the 2-D integer matrix that is the board, along with the
 * size integer, and removes the matrix from the heap. It returns nothing.
 */
void removeBoard(int **mat, int size){
	for (int i = 0; i < size; i++){ //for all the rows
		delete [] mat[i]; //freeing up the space in the matrix
	}
	delete mat; //deletes the empty matrix
}

/* Function #14 : removeVisible
 * This function takes as input parameters the pointer to the 2-D integer matrix that is the board, along with the
 * size integer, and removes the matrix from the heap. It returns nothing.
 */
void removeVisible(char **visible, int size){
	for (int i = 0; i < size; i++){ //for all the rows
		delete [] visible[i]; //freeing up the space in the matrix
	}
	delete visible; //deletes the empty matrix
}





































