#include <iostream>

char board[3][3] = {{' ', ' ', ' '},
                    {' ', ' ', ' '},
                    {' ', ' ', ' '}};

void clearScreen(){
     #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

bool isBoardFilled(){
    int isFilled = 0 ; 
    for (int i = 0 ; i < 3 ; i ++){
        for (int j = 0 ; j < 3 ; j++){
            if (board[i][j] != ' ')
            {
                isFilled++;
            }
        }
    }
    return (isFilled == 9) ? true : false;
}


std::string getSpace(char sign, const int times, char preSign = ' ', char postSign = ' ')
{
    std::string space;
    // Adding the precharacater here
    space += preSign;
    // Filling the rest with symbol in string
    for (int i = 0; i < times; i++)
    {
        space += sign;
    }
    // Adding the postcahracter here
    space += postSign;
    return space;
}

void printBoad()
{

    std::cout << getSpace(' ', 13) << "TIC TAC TOE\n\n";
    std::cout <<  getSpace('-', 13) << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << " | " << board[i][j];
        }
        std::cout << " | " << std::endl
                  << getSpace('-', 13) << std::endl;
    }
}

void printWinner(char won){
    
     if (won == 'X')
    {
        std::cout << "X won this Game !!" << std::endl;
    }
    else if (won == 'O')
    {
        std::cout << "O won this Game !!" << std::endl;
    }
    else if(isBoardFilled()){
        std::cout<<"This Game is Tied (= "<<std::endl; 
    }
}

bool updateboard(const char swap_symbol, const char* println)
{
    struct Pos{int x,y;} pos;

    // TODO: Fix the out of bound later 
    do
    {
        std::cout << println;
        std::cin >> pos.x >> pos.y;
        if(board[pos.x - 1][pos.y - 1] == 'X' || board[pos.x - 1][pos.y - 1] == 'O')
            std::cout<<"invaild input !!\n\n";

    } while((board[pos.x-1][pos.y-1] == 'X' || board[pos.x-1][pos.y-1] == 'O'));

    board[pos.x - 1][pos.y - 1] = swap_symbol;

    return ((pos.x > 0 && pos.x < 4) && (pos.y > 0 && pos.y < 4)) ? true : false;
}

char checkWinner()
{
    // Diagonal check for winner
    const int boardSize = 3; 
    struct Winner{int x,o;}  winnerCount{};
    for (int i = 0; i < boardSize; i++)
    {
        // For O
        int hCount = 0;
        // horizontal
        for (int j = 0; j < 3; j++) if (board[i][j] == 'X' || board[j][boardSize - 1 - j] == 'X') hCount++;
        if (board[i][i] == 'X' || board[i][boardSize - i - 1] == 'X') winnerCount.x++;
        winnerCount.x = winnerCount.x <= hCount ? hCount : winnerCount.x;
        
        // For X 
        hCount = 0;
        for (int j = 0; j < 3; j++) if (board[i][j] == 'O' || board[j][boardSize - 1 - j] == 'O') hCount++;
        if (board[i][i] == 'O' || board[i][boardSize - i - 1] == 'O') winnerCount.o++;
        winnerCount.o = winnerCount.o <= hCount ? hCount : winnerCount.o;

        // For Debug in future  
        // std::cout << "X: " << winnerCount.x << ", O: " << winnerCount.o  << std::endl;
    }
    if (winnerCount.x == boardSize) return 'X';

    if (winnerCount.o == boardSize) return 'O';

    return '!';
}

int main()
{
    clearScreen();
    std::cout << "Welcome to My own Tic-Tac-Toe Game !!\n"
              << "\n Press Enter to continue ->";
    std::cin.get();
    clearScreen();

    bool runningLoop = true;
    char Winner = '!';
    while (runningLoop)
    {
        clearScreen();
        printBoad();
        runningLoop = updateboard('O',"Enter the position of O: ");        
        printBoad();
        clearScreen();
        Winner = checkWinner();
        if (Winner == 'O' || Winner == 'X' || isBoardFilled() || !runningLoop)
        {
            break;
        }

        clearScreen();
        printBoad();
        runningLoop = updateboard('X',"Enter the position of X: ");
        clearScreen();
        printBoad();
        Winner = checkWinner();
        if (Winner == 'O' || Winner == 'X' || isBoardFilled() || !runningLoop)
        {
            break;
        }
    }
    printWinner(Winner);
    std::cout<<"Thanks for playing this game!!";
    std::cin.get();
    std::cin.get();
    return 0;
}
