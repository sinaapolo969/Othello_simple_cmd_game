#include <iostream>
#include <fstream>
#include <windows.h> // for cls and changing the terminal color.
#include <conio.h> // for getch func.
#include <wchar.h>
#include <iomanip> // for setw func.

using namespace std;


struct GameInfo
{
    string name;
    char character;
    int sizeOfTable;
};


struct point // for moving on table houses.
{
    int x = 3;
    int y = 1;
};


bool TURN = false;
char currentPlayerChar = 'X';

string **head = new string*[7];

void getInfo(GameInfo);
void menu();
void tableMaker(string **board, int row, int col);
void headerMaker();
void movement(string **board, point A, int row , int col, int n, GameInfo game[]);
void update(string **board, point A, int row, int col, int n, GameInfo game[]);
void printer(string **board, point A, int row, int col, int n, GameInfo game[]);
void firstMove(string **board, point A, int row, int col, int n, GameInfo game[]);
void playerTurn(); // this func is for changing thr char.
bool checIsNotFull(string**, point);
void aroundTheHouse(string**, point, int, int, int, GameInfo game[]); // for checking all 8 directions around every houses.
//all change index fuctions are changing the symbols on their direction.
void changeIndex_col1(string**, point, int, int);
void changeIndex_col2(string**, point, int, int);
void changeIndex_row1(string**, point, int, int);
void changeIndex_row2(string**, point, int, int);
void changeIndex_diagonalUR(string**, point, int, int);
void changeIndex_diagonalUL(string**, point, int, int);
void changeIndex_diagonalDR(string**, point, int, int);
void changeIndex_diagonalDL(string**, point, int, int);
bool canPutOrNot(string **board, point A, int row, int col, int n, GameInfo game[]); // this fuction is the complement of possibleHouseFinder function.
bool possibleHouseFinder(string **board, int row, int col, int n, GameInfo game[]); //for finding all possible houses that we can select.
void win(string **board, int row, int col, int n, GameInfo game[]); // for check who is the winner in the last.
void save(string**, int, int, int, GameInfo[]);
void load();
void ranking();
void normal(string**, string[], point, int, int, int, GameInfo[]); // for make the table normal after each move.

int main()
{
    menu();
    return 0;
}

void help()
{
    system("cls");
    cout << "Hello! welcome to OTHELLO :)" << endl;
    cout << "before play this game pay attention to this items: " << endl;
    cout << "1_ the first player plays as character X and the second player plays as O! the game starts with X!" << endl;
    cout << "2_ for moving on the houses of the table and selecting them use the guidline" << endl;
    cout << "3_ if there is no house to select, the turn will be change." << endl;
    cout << "4_ do not enter a long name!" << endl;
    cout << "5_ enjoy playing!!" << endl;
    cout << "press any key for back to menu...";
    getch();
    menu();

}


void getInfo(GameInfo game[])
{
    point A;
    for(int i = 0; i < 2; i++)
    {
        cout << "for back to menu enter EXIT" << endl;
        cout << "player " << i + 1 << endl;
        cout << "please enter your name : " << endl;
        cin >> game[i].name;
        if(game[i].name == "EXIT")
        {
            menu();
            break;
        }
        system("cls");
    }

    game[0].character = 'X';
    game[1].character = 'O';

    cout << "please enter the size of your board game : " << endl;
    cout << "(the size should be an even number in range of 4 to 12)" << endl;

    cin >> game->sizeOfTable;
    int n = game->sizeOfTable;
    int row = 2 * n + 1 , col = 6 * n + 1;
    string **board = new string*[row];
    tableMaker(board, row, col);
    headerMaker();
    firstMove(board, A, row, col, n, game); // the begining of game.


}

void menu()
{
    system("cls");
    system("color 80");
    for(int i = 0; i < 15; i++)
    {
        if(i == 0)
        {
            cout << "\u2554";
        }
        else if(i == 14)
        {
            cout << "\u2557";
        }
        else
        {
            cout << "\u2550";
        }
    }
    cout << endl << "\u2551" << "1_ NEW GAME" << setw(5) << "\u2551" << endl;

    for(int i = 0; i < 15; i++)
    {
        if(i == 0)
        {
            cout << "\u255A";
        }
        else if(i == 14)
        {
            cout << "\u255D";
        }
        else
        {
            cout << "\u2550";
        }
    }
    cout << endl;

    for(int i = 0; i < 15; i++)
    {
        if(i == 0)
        {
            cout << "\u2554";
        }
        else if(i == 14)
        {
            cout << "\u2557";
        }
        else
        {
            cout << "\u2550";
        }
    }

    cout << endl << "\u2551" << "2_ LOAD GAME" << setw(4) << "\u2551" << endl;

    for(int i = 0; i < 15; i++)
    {
        if(i == 0)
        {
            cout << "\u255A";
        }
        else if(i == 14)
        {
            cout << "\u255D";
        }
        else
        {
            cout << "\u2550";
        }
    }
    cout << endl;

    for(int i = 0; i < 15; i++)
    {
        if(i == 0)
        {
            cout << "\u2554";
        }
        else if(i == 14)
        {
            cout << "\u2557";
        }
        else
        {
            cout << "\u2550";
        }
    }

    cout << endl << "\u2551" << "3_ RANKING" << setw(6) << "\u2551" << endl;

    for(int i = 0; i < 15; i++)
    {
        if(i == 0)
        {
            cout << "\u255A";
        }
        else if(i == 14)
        {
            cout << "\u255D";
        }
        else
        {
            cout << "\u2550";
        }
    }

    cout << endl;

    for(int i = 0; i < 15; i++)
    {
        if(i == 0)
        {
            cout << "\u2554";
        }
        else if(i == 14)
        {
            cout << "\u2557";
        }
        else
        {
            cout << "\u2550";
        }
    }

    cout << endl << "\u2551" << "4_ HELP" << setw(9) << "\u2551" << endl;

    for(int i = 0; i < 15; i++)
    {
        if(i == 0)
        {
            cout << "\u255A";
        }
        else if(i == 14)
        {
            cout << "\u255D";
        }
        else
        {
            cout << "\u2550";
        }
    }

    cout << endl;

    for(int i = 0; i < 15; i++)
    {
        if(i == 0)
        {
            cout << "\u2554";
        }
        else if(i == 14)
        {
            cout << "\u2557";
        }
        else
        {
            cout << "\u2550";
        }
    }

    cout << endl << "\u2551" << "5_ EXIT" << setw(9) << "\u2551" << endl;

    for(int i = 0; i < 15; i++)
    {
        if(i == 0)
        {
            cout << "\u255A";
        }
        else if(i == 14)
        {
            cout << "\u255D";
        }
        else
        {
            cout << "\u2550";
        }
    }
    cout << endl << endl;

    cout << "please choose a number..." << endl;
    int number;
    GameInfo game[2];
    cin >> number;

    switch (number)
    {
        case 1:
            system("cls");
            getInfo(game);
            break;
        case 2:
            load();
            break;
        case 3:
            ranking();
            exit(0);
            break;
        case 4:
            help();
            break;
        case 5:
            cout << "Bye Bye :)";
            exit(0);
            break;
        default:
            cout << endl << "wrong number!!";
            menu();
    }

}

void tableMaker(string **board, int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        board[i] = new string[col];
    }
    for(int i = 0; i < row; i += 2)
    {
        for(int j = 0; j < col; j++)
        {
            board[i][j] = "\u2501";
        }
    }

    for(int i = 1; i < row; i += 2)
    {
        for(int j = 0; j < col; j++)
        {
            board[i][j] = " ";
        }
    }

    for(int i = 1; i < row; i += 2)
    {
        for(int j = 0; j < col; j += 6)
        {
            board[i][j] = "\u2503";
        }
    }

    for(int i = 2; i < row - 2; i += 2)
    {
        board[i][0] = "\u2523";
    }

     for(int i = 2; i < row - 2; i += 2)
    {
        board[i][col - 1] = "\u252B";
    }

    for(int j = 0; j < col; j += 6)
    {
        board[0][j] = "\u2533";
        if(j == 0)
        {
            board[0][j] = "\u250F";
        }
        if(j == col - 1)
        {
            board[0][j] = "\u2513";
        }
    }

    for(int i = 2; i < row - 2; i += 2)
    {
        for(int j = 6; j < col - 6; j += 6)
        {
            board[i][j] = "\u254B";
        }
    }

    for(int j = 0; j < col; j += 6)
    {
        board[row - 1][j] = "\u253B";

        if(j == 0)
        {
            board[row - 1][j] = "\u2517";
        }

        if(j == col - 1)
        {
            board[row -1][j] = "\u251B";
        }
    }

    board[(row / 2) - 1][(col / 2) - 3] = 'X';
    board[(row / 2) - 1][(col / 2) + 3] = 'O';
    board[(row / 2) + 1][(col / 2) - 3] = 'O';
    board[(row / 2) + 1][(col / 2) + 3] = 'X';
}

void headerMaker()
{
    for(int i = 0; i < 7; i++)
    {
        head[i] = new string[100];
    }

    for(int i = 0 ; i < 7; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            if(i == 0 | i == 6)
            {
                head[i][j] = "\u2550";
            }
        }
    }

    for(int i = 1 ; i < 6; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            head[i][j] = " ";
        }
    }

    for(int i = 1; i < 6; i++)
    {
        head[i][0] = "\u2551";
        head[i][99] = "\u2551";
    }

    head[0][0] = "\u2554";
    head[0][99] = "\u2557";
    head[6][0] = "\u255A";
    head[6][99] = "\u255D";

    head[3][44] = 'O';
    head[3][46] = 'T';
    head[3][48] = 'H';
    head[3][50] = 'E';
    head[3][52] = 'L';
    head[3][54] = 'L';
    head[3][56] = 'O';
}

void movement(string **board, point A, int row , int col, int n, GameInfo game[])
{
    char moves = getch();
    while(moves != '\r')
    {
        switch(moves)
        {
        case 'w':
            A.y -= 2;
            if(A.y < 0)
            {
                A.y = row - 2;
            }
            break;
        case 's':
            A.y += 2;
            if(A.y > row - 2)
            {
                A.y = 1;
            }
            break;
        case 'a':
            A.x -= 6;
            if(A.x < 0)
            {
                A.x = col - 4;
            }
            break;
        case 'd':
            A.x += 6;
            if(A.x > col - 1)
            {
                A.x = 3;
            }
            break;
        case 'V':
            save(board, row, col, n, game);
            break;
        case 'E':
            cout << endl << endl;
            cout << "if you want to exit press key 1, and for continue press key 2" << endl;
            char exitOrNot = getch();
            if(exitOrNot == '1')
            {
                menu();
            }
            break;
        }

        if(!possibleHouseFinder(board, row, col, n, game))
        {
            playerTurn();
            if(!possibleHouseFinder(board, row, col, n, game))
            {
                win(board, row, col, n, game);
            }
            cout << endl;
            cerr << "THERE IS NO PLACE FOR YOU!\n PRESS ANY KEY TO CHANGE THE TURN";
            getch();
        }

        update(board, A, row, col, n, game);
    }

    bool empty;
    if(moves == '\r')
    {
        empty = checIsNotFull(board, A);
        if(empty)
        {
            aroundTheHouse(board, A, row, col, n, game);
        }

        else
        {
            update(board, A, row, col, n, game);
        }
    }

    update(board, A, row, col, n, game);
}

void update(string **board, point A, int row, int col, int n, GameInfo game[])
{
    string tmp[2] = {" "}; // for keeping the interval position.
    tmp[0] = board[A.y - 1][A.x - 3];
    tmp[1] = board[A.y + 1][A.x + 3];

    board[A.y - 1][A.x - 3] = "\u2554";
    board[A.y + 1][A.x + 3] = "\u255D";

    printer(board, A, row, col, n, game);
    normal(board, tmp, A, row, col, n, game);
}


void printer(string **board, point A, int row, int col, int n, GameInfo game[])
{
    int Xcounter = 0;
    int Ocounter = 0;
    for(int i = 1; i < row; i += 2)
    {
        for(int j = 3; j < col; j += 6)
        {
            if(board[i][j] == "X")
            {
                Xcounter++;
            }
            else if(board[i][j] == "O")
            {
                Ocounter++;
            }
        }
    }
    system("cls");
    system("color 80");
    for(int i = 0; i < 7; i++)
    {
        cout << setw(40);
        for(int j = 0; j < 100; j++)
        {
            cout << head[i][j];
        }
        cout << endl;
    }

    int whiteSpace;
    if(n == 4)
    {
        whiteSpace = 77;
    }
    else if(n == 6)
    {
        whiteSpace = 72;
    }
    else if(n == 8)
    {
        whiteSpace = 67;
    }
    else if(n == 10)
    {
        whiteSpace = 60;
    }
    else if(n == 12)
    {
        whiteSpace = 53;
    }

    int space = (game[0].name).size() - 4;
    cout << setw(53) << "player1's name: " << game[0].name;
    cout << setw(72 - space) << "player2's name: " << game[1].name << endl;
    cout << setw(48) << "character: " << game[0].character;
    cout << setw(75) << "character: " << game[1].character;
    cout << endl << setw(46) << "peicesX: " << Xcounter;
    cout << setw(75) << "peicesO: " << Ocounter;
    cout << endl << endl;
    cout << setw(whiteSpace + col / 2) << "TURN " << currentPlayerChar;

    cout << endl;
    for(int i = 0; i < row; i++)
    {

        cout << setw(whiteSpace);
        for(int j = 0; j < col; j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }

    cout << endl << endl;
    cout << setw(40);
    for(int i = 0; i < 100; i++)
    {
        cout << "\u2550";
    }
    cout << endl;
    cout << setw(42);
    cout << "UP: w" << setw(15) << "DOWN: s" << setw(15) << "RIGHT: d";
    cout << setw(15) << "LEFT: a" << setw(20) << "SELECT: enter" << setw(15) << "SAVE: V";
    cout << setw(15) << "EXIT: E";


}

void normal(string **board, string tmp[], point A, int row, int col, int n, GameInfo game[])
{
    board[A.y - 1][A.x - 3] = tmp[0];
    board[A.y + 1][A.x + 3] = tmp[1];
    movement(board, A, row, col, n, game);
}

void firstMove(string **board, point A, int row, int col, int n, GameInfo game[])
{
    currentPlayerChar = 'X';
    string tmp[2] = {" "};
    tmp[0] = board[A.y - 1][A.x - 3];
    tmp[1] = board[A.y + 1][A.x + 3];

    board[A.y - 1][A.x - 3] = "\u2554";
    board[A.y + 1][A.x + 3] = "\u255D";

    printer(board, A, row, col, n, game);
    normal(board, tmp, A, row, col, n, game);

}

void playerTurn()
{
    if(TURN == true)
    {
        currentPlayerChar = 'X';
        TURN = false;
    }
    else
    {
        currentPlayerChar = 'O';
        TURN = true;
    }

}

bool checIsNotFull(string **board, point A)
{
    if(board[A.y][A.x] == " ")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void aroundTheHouse(string **board, point A, int row, int col, int n, GameInfo game[])
{
    bool currectPlace = false;
    string temp[1];
    temp[0] = currentPlayerChar;
    if(A.y != row - 2)
    {
        if(temp[0] != board[A.y + 2][A.x] & board[A.y + 2][A.x] != " ")
        {
            for(int i = A.y + 2; i <= row - 2; i += 2)
            {
                if(board[i][A.x] == temp[0])
                {
                    currectPlace = true;
                    changeIndex_col1(board, A, row, col);
                    break;
                }
                else if(board[i][A.x] == " ")
                {
                    break;
                }
            }
        }
    }
    if(A.y != 1)
    {
        if(temp[0]  != board[A.y - 2][A.x] & board[A.y - 2][A.x] != " ")
        {
            for(int i = A.y - 2; i >= 1; i -= 2)
            {
                if(board[i][A.x] == temp[0])
                {
                    currectPlace = true;
                    changeIndex_col2(board, A, row, col);
                    break;
                }
                else if(board[i][A.x] == " ")
                {
                    break;
                }
            }
        }
    }
    if(A.x != col - 4)
    {
         if(temp[0]  != board[A.y][A.x + 6] & board[A.y][A.x + 6] != " ")
         {
             for(int i = A.x + 6; i <= col - 4; i += 6)
             {
                 if(board[A.y][i] == temp[0])
                 {
                     currectPlace = true;
                     changeIndex_row1(board, A, row, col);
                     break;

                 }
                 else if(board[A.y][i] == " ")
                 {
                     break;
                 }
             }
         }
    }
    if(A.x != 3)
    {
        if(temp[0]  != board[A.y][A.x - 6] & board[A.y][A.x - 6] != " ")
        {
            for(int i = A.x - 6; i >= 3; i -= 6)
            {
                if(board[A.y][i] == temp[0])
                {
                    currectPlace = true;
                    changeIndex_row2(board, A, row, col);
                    break;
                }
                else if(board[A.y][i] == " ")
                {
                    break;
                }
            }
        }
    }

    if(A.x != col - 4 && A.y != 1)
    {

        if(temp[0] != board[A.y - 2][A.x + 6] && board[A.y - 2][A.x + 6] != " ")
        {
            for(int i = A.y - 2, j = A.x + 6; i >= 1 & j <= col - 4; i -= 2, j += 6)
            {
                if(A.y == 3 | A.x == col - 10)
                {
                    break;
                }
                if(board[i][j] == temp[0])
                {
                    currectPlace = true;
                    changeIndex_diagonalUR(board, A, row, col);
                    break;
                }
                else if(board[i][j] == " ")
                {
                    break;
                }
            }
        }
    }

    if(A.x != 3 && A.y != 1)
    {
        if(temp[0] != board[A.y - 2][A.x - 6] && board[A.y - 2][A.x - 6] != " ")
        {
            for(int i = A.y - 2, j = A.x - 6; i >= 1 & j >= 3; i -= 2, j -= 6)
            {
                if(A.y == 3 | A.x == 6)
                {
                    break;
                }
                if(board[i][j] == temp[0])
                {
                    currectPlace = true;
                    changeIndex_diagonalUL(board, A, row, col);
                    break;
                }
                else if(board[i][j] == " ")
                {
                    break;
                }
            }
        }
    }

    if(A.x != col - 4 && A.y != row - 2)
    {
        if(temp[0] != board[A.y + 2][A.x + 6] && board[A.y + 2][A.x + 6] != " ")
        {
            for(int i = A.y + 2, j = A.x + 6; i <= row - 2 & j <= col - 4; i += 2, j += 6)
            {
                if(A.y == row - 4 | A.x == col - 10)
                {
                    break;
                }
                if(board[i][j] == temp[0])
                {
                    currectPlace = true;
                    changeIndex_diagonalDR(board, A, row, col);
                    break;
                }
                else if(board[i][j] == " ")
                {
                    break;
                }
            }
        }
    }

    if(A.x != 3 && A.y != row - 2)
    {
        if(temp[0] != board[A.y + 2][A.x - 6] && board[A.y + 2][A.x - 6] != " ")
        {
            for(int i = A.y + 2, j = A.x - 6; i <= row - 2 & j >= 3; i += 2, j -= 6)
            {
                if(A.y == row - 4 | A.x == 6)
                {
                    break;
                }
                if(board[i][j] == temp[0])
                {
                    currectPlace = true;
                    changeIndex_diagonalDL(board, A, row, col);
                    break;
                }
                else if(board[i][j] == " ")
                {
                    break;
                }
            }
        }
    }

    if(!currectPlace)
    {
        update(board, A, row, col, n, game);
    }
    else
    {
        board[A.y][A.x] = temp[0];
        playerTurn();
        update(board, A, row, col, n, game);
    }

}


void changeIndex_col1(string **board, point A, int row, int col)
{
    string temp[1];
    temp[0] = currentPlayerChar;
    for(int i = A.y + 2; board[i][A.x] != temp[0]; i += 2)
    {
        board[i][A.x] = temp[0];
    }

}

void changeIndex_col2(string **board, point A, int row, int col)
{
    string temp[1];
    temp[0] = currentPlayerChar;
    for(int i = A.y - 2; board[i][A.x] != temp[0]; i -= 2)
    {
        board[i][A.x] = temp[0];
    }

}

void changeIndex_row1(string **board, point A, int row, int col)
{
    string temp[1];
    temp[0] = currentPlayerChar;
    for(int i = A.x + 6; board[A.y][i] != temp[0]; i += 6)
    {
        board[A.y][i] = temp[0];
    }

}

void changeIndex_row2(string **board, point A, int row, int col)
{
    string temp[1];
    temp[0] = currentPlayerChar;
    for(int i = A.x - 6; board[A.y][i] != temp[0]; i -= 6)
    {
        board[A.y][i] = temp[0];
    }

}

void changeIndex_diagonalUR(string **board, point A, int row, int col)
{
    string temp[1];
    temp[0] = currentPlayerChar;
    for(int i = A.y - 2, j = A.x + 6; board[i][j] != temp[0]; i -= 2, j += 6)
    {
        board[i][j] = temp[0];
    }
}

void changeIndex_diagonalUL(string **board, point A, int row, int col)
{
    string temp[1];
    temp[0] = currentPlayerChar;
    for(int i = A.y - 2, j = A.x - 6; board[i][j] != temp[0]; i -= 2, j -= 6)
    {
        board[i][j] = temp[0];
    }
}

void changeIndex_diagonalDR(string **board, point A, int row, int col)
{
    string temp[1];
    temp[0] = currentPlayerChar;
    for(int i = A.y + 2, j = A.x + 6; board[i][j] != temp[0]; i += 2, j += 6)
    {
        board[i][j] = temp[0];
    }
}

void changeIndex_diagonalDL(string **board, point A, int row, int col)
{
    string temp[1];
    temp[0] = currentPlayerChar;
    for(int i = A.y + 2, j = A.x - 6; board[i][j] != temp[0]; i += 2, j -= 6)
    {
        board[i][j] = temp[0];
    }
}

bool canPutOrNot(string **board, point A, int row, int col, int n, GameInfo game[])
{
    bool currectPlace = false;
    string temp[1];
    temp[0] = currentPlayerChar;
    if(A.y != row - 2)
    {
        if(temp[0] != board[A.y + 2][A.x] & board[A.y + 2][A.x] != " ")
        {
            for(int i = A.y + 2; i <= row - 2; i += 2)
            {
                if(board[i][A.x] == temp[0])
                {
                    currectPlace = true;
                    break;
                }
                else if(board[i][A.x] == " ")
                {
                    break;
                }
            }
        }
    }
    if(A.y != 1)
    {
        if(temp[0]  != board[A.y - 2][A.x] & board[A.y - 2][A.x] != " ")
        {
            for(int i = A.y - 2; i >= 1; i -= 2)
            {
                if(board[i][A.x] == temp[0])
                {
                    currectPlace = true;
                    break;
                }
                else if(board[i][A.x] == " ")
                {
                    break;
                }
            }
        }
    }
    if(A.x != col - 4)
    {
         if(temp[0]  != board[A.y][A.x + 6] & board[A.y][A.x + 6] != " ")
         {
             for(int i = A.x + 6; i <= col - 4; i += 6)
             {
                 if(board[A.y][i] == temp[0])
                 {
                     currectPlace = true;
                     break;

                 }
                 else if(board[A.y][i] == " ")
                 {
                     break;
                 }
             }
         }
    }
    if(A.x != 3)
    {
        if(temp[0]  != board[A.y][A.x - 6] & board[A.y][A.x - 6] != " ")
        {
            for(int i = A.x - 6; i >= 3; i -= 6)
            {
                if(board[A.y][i] == temp[0])
                {
                    currectPlace = true;
                    break;
                }
                else if(board[A.y][i] == " ")
                {
                    break;
                }
            }
        }
    }

    if(A.x != col - 4 && A.y != 1)
    {

        if(temp[0] != board[A.y - 2][A.x + 6] && board[A.y - 2][A.x + 6] != " ")
        {
            for(int i = A.y - 2, j = A.x + 6; i >= 1 & j <= col - 4; i -= 2, j += 6)
            {
                if(A.y == 3 | A.x == col - 10)
                {
                    break;
                }
                if(board[i][j] == temp[0])
                {
                    currectPlace = true;
                    break;
                }
                else if(board[i][j] == " ")
                {
                    break;
                }
            }
        }
    }

    if(A.x != 3 && A.y != 1)
    {
        if(temp[0] != board[A.y - 2][A.x - 6] && board[A.y - 2][A.x - 6] != " ")
        {
            for(int i = A.y - 2, j = A.x - 6; i >= 1 & j >= 3; i -= 2, j -= 6)
            {
                if(A.y == 3 | A.x == 6)
                {
                    break;
                }
                if(board[i][j] == temp[0])
                {
                    currectPlace = true;
                    break;
                }
                else if(board[i][j] == " ")
                {
                    break;
                }
            }
        }
    }

    if(A.x != col - 4 && A.y != row - 2)
    {
        if(temp[0] != board[A.y + 2][A.x + 6] && board[A.y + 2][A.x + 6] != " ")
        {
            for(int i = A.y + 2, j = A.x + 6; i <= row - 2 & j <= col - 4; i += 2, j += 6)
            {
                if(A.y == row - 4 | A.x == col - 10)
                {
                    break;
                }
                if(board[i][j] == temp[0])
                {
                    currectPlace = true;
                    break;
                }
                else if(board[i][j] == " ")
                {
                    break;
                }
            }
        }
    }

    if(A.x != 3 && A.y != row - 2)
    {
        if(temp[0] != board[A.y + 2][A.x - 6] && board[A.y + 2][A.x - 6] != " ")
        {
            for(int i = A.y + 2, j = A.x - 6; i <= row - 2 & j >= 3; i += 2, j -= 6)
            {
                if(A.y == row - 4 | A.x == 6)
                {
                    break;
                }
                if(board[i][j] == temp[0])
                {
                    currectPlace = true;
                    break;
                }
                else if(board[i][j] == " ")
                {
                    break;
                }
            }
        }
    }



    if(!currectPlace)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool possibleHouseFinder(string **board, int row, int col, int n, GameInfo game[])
{
    point A;
    bool empty;
    bool currectPlace;
    for(int i = 1; i < row; i += 2)
    {
        for(int j = 3; j < col; j += 6)
        {
            A.y = i;
            A.x = j;
            empty = checIsNotFull(board, A);
            if(empty)
            {
                currectPlace = canPutOrNot(board, A, row, col, n, game);
                if(currectPlace)
                {
                    return currectPlace;
                }
            }
        }
    }

    return false;
}


void win(string **board, int row, int col, int n, GameInfo game[])
{
    int Xcounter = 0;
    int Ocounter = 0;
    for(int i = 1; i < row; i += 2)
    {
        for(int j = 3; j < col; j += 6)
        {
            if(board[i][j] == "X")
            {
                Xcounter++;
            }
            else if(board[i][j] == "O")
            {
                Ocounter++;
            }
        }
    }

    ofstream saveWinners("winners.txt", ios::out | ios::app);//saving winner's names
    if (Xcounter > Ocounter)
    {
        cout << endl << endl;
        cout << "GAME OVER!!!" << endl;
        cout << game[0].name << " is winner." << endl;
        saveWinners << game[0].name << " ";
        cout << "press any key to exit...";
    }
    if (Xcounter < Ocounter)
    {
        cout << endl << endl;
        cout << "GAME OVER!!!" << endl;
        cout << game[1].name << " is winner." << endl;
        saveWinners << game[1].name << " ";
        cout << "press any key to exit...";
    }

    if (Xcounter == Ocounter)
    {
        cout << endl << endl;
        cout << "GAME OVER!!!" << endl;
        cout << "DRAW!!!" << endl;
        cout << "press any key to exit...";
    }

    for(int i = 0; i < row; i++)
    {
        delete[] board[i];
    }

    delete[] board;

    saveWinners.close();
    getch();
    menu();
}


void ranking()
{
    system("cls");
    cout << "RANKING:" << endl << endl;
    ifstream playerRank("winners.txt", ios::in);
    if(!playerRank)
    {
        cout << "there is no ranking yet!!" << endl;
        cout << "press any key for back to menu...";
        getch();
        menu();
    }
    string names[10000];
    string Name;
    int nameCounter = 0;
    while(!playerRank.eof())
    {
        playerRank >> Name;
        names[nameCounter] = Name;
        nameCounter++;
    }

    nameCounter -= 1;
    int counter = 0;
    int *tekrar = new int[nameCounter];
    cout << "name" << setw(10) << "wins";
    cout << endl;
    for(int i = 0; i < 30; i++)
    {
        cout << "\u2550";
    }
    cout << endl;
    for(int i = 0; i < nameCounter; i++)
    {
        int k = 0;
        counter = 0;
        for(int j = 0; j < nameCounter; j++)
        {
            if(names[i] == names[j])
            {
                tekrar[k] = j;
                k++;
                counter++;
            }
        }
        for(int t = 1; t < k ; t++)
            {
                if(i == tekrar[t])
                {
                    names[i] = "0";
                }
            }
            if(names[i] != "0")
            {
                int space = names[i].size() - 4;
                cout << names[i] << setw(8 - space) << counter << endl;
                for(int p = 0; p < 30; p++)
                {
                    cout << "\u2500";
                }
                cout << endl;
            }
    }
    delete[] tekrar;
    playerRank.close();

    cout << "press any key for back to menu..." << endl;
    getch();
    menu();
}




void save(string **board, int row, int col, int n, GameInfo game[]) // this is for saving the game info.
{
    ofstream saveTable("table.txt", ios::out);//saving important houses im file
    for(int i = 1; i < row; i += 2)
    {
        for(int j = 3; j < col; j += 6)
        {
            saveTable << board[i][j];
        }
    }

    saveTable.close();

    ofstream saveNames("Nameinfo.txt", ios::out);
    for(int i = 0; i < 2; i++)
    {
        saveNames << game[i].name << " ";
    }

    saveNames.close();

    ofstream saveChars("Charinfo.txt", ios::out);
    for(int i = 0; i < 2; i++)
    {
        saveChars << game[i].character;
    }

    saveChars << currentPlayerChar;

    saveChars.close();

    ofstream saveNumbers("number.txt", ios::out);

    saveNumbers << row << " " << col << " " << n;
    saveNumbers.close();

}


void load()// this function load saved informations
{
    system("cls");
    GameInfo game[2];
    point A;
    ifstream Numbers("number.txt", ios::in);//loading row, col, n
    if(!Numbers)
    {
        cout << "there is not any save yet!" << endl;
        cout << "press any key for back to menu..." << endl;
        getch();
        menu();
    }
    int row, col, n;
    while(!Numbers.eof())
    {
        Numbers >> row >> col >> n;
    }

    Numbers.close();

    ifstream table("table.txt", ios::in);//loading important houses in table
    string **indexHolder = new string*[row];
    tableMaker(indexHolder, row, col);
    int m = row * col;
    char temp[m];
    table.get(temp, m);//saving important houses as string in temp

    int x = 0;
    for(int i = 1; i < row; i += 2)
    {
        for(int j = 3; j < col; j += 6)
        {
            indexHolder[i][j] = temp[x];//transfer important houses from temp to indexHolder
            x++;
        }
    }
    table.close();

    ifstream names("Nameinfo.txt", ios::in);//loading names of players
    while(!names.eof())
    {
        names >> game[0].name >> game[1].name;
    }

    names.close();

    ifstream Chars("Charinfo.txt", ios::in);//loading characters of players
    char oldTurn;
    while(!Chars.eof())
    {
        for(int i = 0; i < 2; i++)
        {
            Chars.get(game[i].character);
        }
        Chars >> oldTurn;
    }

    if(oldTurn != currentPlayerChar)
    {
        playerTurn();
    }
    Chars.close();

    update(indexHolder, A, row, col, n, game);//starting the game again

    for(int i = 0; i < row; i++)
    {
        delete[] indexHolder[i];
    }

    delete[] indexHolder;

}
