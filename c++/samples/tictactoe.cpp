#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int ROWS = 3;
const int COLS = 3;

void runGame();
void initializeGameBoard(string gameBoard[ROWS][COLS]);
void printCurrentgameBoard(string gameBoard[ROWS][COLS]);
void getUserInput(bool xTurn, string gameBoard[ROWS][COLS]);
bool cellAlreadyOccupied(int row, int col, string gameBoard[ROWS][COLS]);
string getWinner(string gameBoard[ROWS][COLS]);
bool isgameBoardFull(string gameBoard[ROWS][COLS]);

int main()
{
    runGame();

    return 0;
}

void runGame()
{
    string winner = "";
    string gameBoard[ROWS][COLS];
    initializeGameBoard(gameBoard);
    printCurrentgameBoard(gameBoard);
    // bool value 0 is player 1, value 1 is player 2 turn
    bool xTurn = 0;
    //if (winner == "X") { cout << "winner found" << winner << endl; }
    while (winner != "X" && winner != "O" && winner != "C")
    {
        getUserInput(xTurn, gameBoard);
        printCurrentgameBoard(gameBoard);
        winner = getWinner(gameBoard);
        // setting to cats game if gameboard full
        if (winner == "" && isgameBoardFull(gameBoard) == true)
        {
            winner = "C";
            cout << "Cat's game" << endl;
            break;
        }
        // xor to rotate turn
        xTurn ^= 1;
    }
    cout << "The Winner is " << winner << endl;
}

void initializeGameBoard(string gameBoard[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
        {
            gameBoard[i][j] = " ";
        }
}

void printCurrentgameBoard(string gameBoard[ROWS][COLS]) {

    //Render Game gameBoard LAYOUT


    cout << "PLAYER - 1 [X]\t PLAYER - 2 [O]\n\n";
    cout << "\t\t     |     |     \n";
    cout << "\t\t  " << gameBoard[0][0] << "  |  " << gameBoard[0][1] << "  |  " << gameBoard[0][2] << " \n";
    cout << "\t\t_____|_____|_____\n";
    cout << "\t\t     |     |     \n";
    cout << "\t\t  " << gameBoard[1][0] << "  |  " << gameBoard[1][1] << "  |  " << gameBoard[1][2] << " \n";
    cout << "\t\t_____|_____|_____\n";
    cout << "\t\t     |     |     \n";
    cout << "\t\t  " << gameBoard[2][0] << "  |  " << gameBoard[2][1] << "  |  " << gameBoard[2][2] << " \n";
    cout << "\t\t     |     |     \n";
}

void getUserInput(bool xTurn, string gameBoard[ROWS][COLS])
{
    int row, col;
    // not needed char gamePiece;
    // 0 to 1 bool used so xTurn+1 prints out correct player number
    cout << "It is Player" << xTurn+1 << "'s Turn" << endl;
    cout << "Specify the row you would like to place your game piece at " << endl;
    cin >> row;
    row -= 1;
    // since it's an array assuming it will always have a 0 so user input has - 1 
    // Checks if row is below 0 or more than const ROWS value
    // if so keep prompting user to select a row to use. other while loop does same thing for col
    while (row < 0 || row >= ROWS)
    {
        cout << "Wrong row specify again make sure it is between 1 and 3: " << endl;
        cin >> row;
        row -= 1;
    }
    cout << "Specify the col you would like to place your game piece at " << endl;
    cin >> col;
    col -= 1;
    while (col < 0 || col >= COLS)
    {
        cout << "Wrong col specify again make sure it is between 1 and 3: " << endl;
        cin >> col;
        col -= 1;
    }
    // check if cell is free or not. if free add to it, if not keep asking
    bool cellCheck = cellAlreadyOccupied(row, col, gameBoard);
    if (cellCheck == false)
    {
        // use xTurn value to either put a X or O on gameboard
        (xTurn == 0) ? gameBoard[row][col] = "X" : gameBoard[row][col] = "O";
    }
    else if (cellCheck == true)
    {
        // fix this with maybe a nested while loop or multiple ?
        cout << "That area is already occupied please try again" << endl;
        // if cell is occupied use recursion to call function again until un-occupied area is chosen
        getUserInput(xTurn, gameBoard);
    }
}

// return false if not occupied, else return true if occupied. last else is to catch error codes and print custom error in catch
bool cellAlreadyOccupied(int row, int col, string gameBoard[ROWS][COLS])
{
    try {
        if (gameBoard[row][col] == " ")
        {
            return false;
        }
        else if (gameBoard[row][col] == "X" || gameBoard[row][col] == "O")
        {
            return true;
        }
        else
        {
            // only allow one in here. I tried two parameters in throw and it didn't work
            throw invalid_argument("Error Exception checking cell free in gameboard[ROWS][COLS]");
        }
    }
    // -1 in bool results in a bool of 1 which is true
    catch (invalid_argument& e)
    {
        cerr << e.what() << endl << "Exiting game use correct ROWS or COLS";
    }
}

string getWinner(string gameBoard[ROWS][COLS])
{
    // create values array holding game pieces values. initialize iterators v and i.
    // get size of values array and while loop through it checking for winners in gameboard array
    // values array doesn't hold " " because the return and break would end search if an area is found 
    // with all empty spaces
    string values[2] = {"X","O"};
    int v = 0, i = 0;
    // vector to store diagonal values
    vector<string> diagVect;
    while (v < (sizeof(values) / sizeof(values[0]))) {
        // checking rows for winner
        for (i = 0; i < ROWS; i++)
        {
            // is it an x or o
            if (gameBoard[i][0] == values[v] && gameBoard[i][1] == values[v] && gameBoard[i][2] == values[v])
            {
                return values[v];
                break;
            } 
        }
        // checking cols for winner
        for (i = 0; i < COLS; i++)
        {
            // is it an x or o
            if (gameBoard[0][i] == values[v] && gameBoard[1][i] == values[v] && gameBoard[2][i] == values[v])
            {
                return values[v];
                break;
            } 
        }
        /*
        code to find corners
        // left top corner
        gameBoard[0][0];
        // right top corner
        gameBoard[0][COLS-1];
        // left bottom corner
        gameBoard[ROWS-1][0];
        // right bottom corner
        gameBoard[ROWS-1][COLS-1];
        */

        // checking both diagonals for a winner
        // clearing vector
        diagVect.clear();
        for (i = 1; i <= ROWS; i++)
        {
            // start going diagonally from bottom left corner
            // ROWS - i and i - 1 incrementally to get to top right corner
            // if value is in there add to diagVect vector
            // && gameBoard[ROWS - i][i - 1] == gameBoard[0][COLS - 1] removed due to issue
            // where it would end early because there was already a value at the end of diagonal area

            if (gameBoard[ROWS - i][i-1] == values[v] )
            {
                diagVect.push_back(gameBoard[ROWS - i][i - 1]);
            }
        // If items in vector equal to ROWS return winner string
        // clear out diagVect vector
        if(diagVect.size() == ROWS)
        {
            return values[v];
            break;
        }
        }
        // ROWS will always equal COLS amount in tic tac toe game so either COLS or ROWS will work here
        // clearing vector
        diagVect.clear();
        for (i = 1; i <= ROWS; i++)
        {
            // start going diagonaly from bottom right corner
            // ROWS - i and COLS - i incrementally up to top left corner
            // check if there is still the v value if so add to diagVector
            if (gameBoard[ROWS - i][COLS - i] == values[v])
            {
                diagVect.push_back(gameBoard[ROWS - i][COLS - i]);
            }
        // If items in vector equal to ROWS return winner string
        if (diagVect.size() == ROWS)
        {
            return values[v];
            break;
        }
        }
        v++;
    }
    // return an empty string since no winner has been found
    return "";
}

bool isgameBoardFull(string gameBoard[ROWS][COLS])
{
    // counter to track how many are occupied already 
    int check = 0;
    // loop through ROWS and COLS and check if area is occupied. If so add to check and at the end check if gameboard is full or not and return bool
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
        {
            if (cellAlreadyOccupied(i, j, gameBoard) == true)
            {
                check++;
            }   
        }
    // ROWS * COLS gets you all areas available on the gameboard
    return check == (ROWS * COLS);
}
