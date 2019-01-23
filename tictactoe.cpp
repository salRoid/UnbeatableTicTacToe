#include<bits/stdc++.h> 

using namespace std;

typedef vector<bool> VB;
typedef vector<int> VI;
#define IFOR(i) for (int i = 1; i <= 9; i++)
#define SFOR(i) for (int i = 0; i < 3; i++)
#define isEmpty(i, filledSpots) if (filledSpots[i] == false)
#define isBlank(i,j) if (arr[i][j] == ' ')
#define isValidMoves(place) place > 9 || place < 1
#define DFOR(i, j) for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)

// Placing the values on BOARD
void placeFlag (char arr[3][3], int place, char move) {
	switch(place) {
		case 1: arr[0][0] = move; break;
		case 2: arr[0][1] = move; break;
		case 3: arr[0][2] = move; break;
		case 4: arr[1][0] = move; break;
		case 5: arr[1][1] = move; break;
		case 6: arr[1][2] = move; break;
		case 7: arr[2][0] = move; break;
		case 8: arr[2][1] = move; break;
		case 9: arr[2][2] = move; break;   
	}
}

// Check if any more moves are left on the board
bool isMovesLeft(const char arr[3][3]) { 
	DFOR(i,j) {
    	isBlank(i,j){ 
    		return true; 
    	}
    }
    return false; 
}

// Random Move Selection based on highest score available.
int movePicker(const char arr[3][3], const int searchValue, const int weights[10]) {
	VI validValues;
	int wins = INT_MIN;
	IFOR(i) {
		if (weights[i] == searchValue) {
			validValues.push_back(i); 
		}
	}
	cout << endl;
	srand (time(NULL));
	int randomIndex = validValues[rand() % validValues.size()] ;
	return randomIndex;
}

void printBoard(const char arr[3][3]) {
	SFOR(i) {
		SFOR(j) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

// Evaluation of current state of the game.
int evaluate (const char arr[3][3], const char &humanChar, const char &beastChar) {
	// ROWS WIN SCORE
	SFOR(i) { 
        if (arr[i][0] == arr [i][1] && arr[i][1] == arr[i][2]) { 
            if (arr[i][0] == beastChar) {
                return +10; 
            } else if (arr[i][0] == humanChar) {
            	return -10; 
            }
        } 
    }   
    //COLS WIN SCORE
    SFOR(j) {
        if (arr[0][j] == arr[1][j] && arr[1][j] == arr[2][j]) { 
            if (arr[0][j] == beastChar) {
                return +10; 
            } else if (arr[0][j] == humanChar) {
                return -10; 
            }
        } 
    } 
    // RIGHT DIAG WIN SCORE
    if (arr[0][0] == arr[1][1] && arr[1][1]== arr[2][2]) { 
        if (arr[0][0] == beastChar) {
            return +10; 
        } else if (arr[0][0] == humanChar) {
            return -10; 
        }
    } 
  	// RIGHT DIAG WIN SCORE
    if (arr[0][2] == arr [1][1] && arr[1][1] == arr[2][0]) { 
        if (arr[0][2] == beastChar) {
            return +10; 
        } else if (arr[0][2] == humanChar) {
            return -10; 
        }
    } 
    return 0; 
}

int minmax (char arr[3][3], const char &humanChar, const char &beastChar, int depth, bool isMax) {
	int score = evaluate(arr, humanChar, beastChar); 
    if (score == 10) 
        return score - depth; 
    if (score == -10)
    	return score + depth;

    if (isMovesLeft(arr) == false) 
        return 0; 
    
    if (isMax) { 
    	//Choosing Best Move for the beast.
        int best = INT_MIN; 
        SFOR(i) { 
            SFOR(j) {  
                isBlank(i, j) { 
                    arr[i][j] = beastChar;  
                    best = max(best, minmax(arr, humanChar, beastChar, depth + 1, !isMax)); 
                    arr[i][j] = ' '; 
                } 
            } 
        } 
        return best; 
    } else { 
    	//Choosing/Assuming Human always play the worst move.
        int best = INT_MAX; 
        SFOR(i) { 
            SFOR(j) {  
                isBlank(i, j) { 
                    arr[i][j] = humanChar;  
                    best = min(best, minmax(arr, humanChar, beastChar, depth + 1, !isMax));  
                    arr[i][j] = ' '; 
                } 
            } 
        } 
        return best; 
    } 
}

int beastMove (char arr[3][3], const VB &filledSpots, const char &humanChar, const char &beastChar) {
	int place = INT_MIN;
	int moveWeights[9];
	IFOR(i)
		moveWeights[i] = INT_MAX;
	IFOR(i) { 
		 isEmpty(i, filledSpots){
			placeFlag(arr, i, beastChar);
			int moveVal = minmax(arr, humanChar, beastChar, 0, false);
			moveWeights[i] = moveVal;
			placeFlag (arr, i, ' ');
			if (moveVal > place) {
				place = moveVal;
			}
		}
	}
  	int index = movePicker(arr, place, moveWeights);
	cout << "Beast Plays the move at:";
	return index;
}

int main () {
	char arr[3][3] = {};
	DFOR(i, j) {
    	arr[i][j] = ' ';
    }
	char humanChar, beastChar;
	bool humanFlag = false;
	cout << "Choose your Move X or O (X Plays First): ";
	cin >> humanChar;
	if ((humanChar == 'X') || (humanChar == 'x')) {
		beastChar = 'O';
		humanFlag = true;
	} else {
		if ((humanChar != 'O') && (humanChar != 'o')) {
			cout << "You chose an unknown move, Now you play second !!." << endl;
		}
		humanChar = 'O';
		beastChar = 'X';
	}
	cout << "Human : " << humanChar << endl;
	cout << "Beast : " << beastChar << endl;
	VB filledSpots(9, false);
	int boardFillCount = 9;
	bool moveTracker = true;
	bool result = false;
	int place;

	while (boardFillCount--) {
		if (moveTracker == humanFlag ) {
			cout << "Please Give Your Input: ";
			cin >> place;
			while ( isValidMoves(place) || filledSpots[place] == true ) {
				if (isValidMoves(place)) 
					cout << "Given Place "<< place <<" is not Valid." << endl;
				else 
					cout << "Given Place "<< place <<" is Already taken." << endl;
				cout << "Plase Choose Again from the valid moves: " << endl;
				IFOR(i) {
					isEmpty(i, filledSpots)
						cout << i << " ";
				}
				cout << endl;
				cin >> place;
			}
			placeFlag(arr,place,humanChar);
		} else {
			place = beastMove(arr, filledSpots, humanChar, beastChar);
			cout << place << endl;
			placeFlag(arr,place,beastChar);
		}
		filledSpots[place] = true;
		printBoard(arr);
		if (evaluate(arr, humanChar, beastChar) == 10) {
			result = true;
			cout << "Beast WINS" << endl;
			exit (0);
		} else if (evaluate(arr, humanChar, beastChar) == -10)  {
			result = false;
			cout << "Player WINS" << endl;
			exit (0);
		} 
		/*else {
			int moveVal = minmax(arr, humanChar, beastChar, 0, !moveTracker);
			if (moveVal == 0 && boardFillCount <= 3) {
				result = true;
				cout << "Match Drawn" << endl; 
				exit(0);
			}
		}*/
		moveTracker = !moveTracker;
	}
	if (!result) 
		cout << "Match Drawn" << endl; 
	return 0;
}