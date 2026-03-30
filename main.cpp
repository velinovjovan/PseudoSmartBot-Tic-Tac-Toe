#include<iostream>
#include<cstdlib>
#include<string>

constexpr unsigned short BOARD_SIZE = 9;
constexpr char EMPTY = ' ';
constexpr char PLAYER = 'X';
constexpr char BOT = 'O';

char boardState[BOARD_SIZE];
bool gameOver = false;
char gameResult = EMPTY; 

void initializeBoard();
void clearScreen();
void displayBoard();
void displayGameStatus();
bool isValidMove(unsigned short position);
bool checkWin(char player);
bool checkDraw();
unsigned short getBotMove();
unsigned short getSmartBotMove();
void playerMove();
void botTurn();

void playGame() {
    initializeBoard();

    std::cout << "\n=== Welcome to Tic Tac Toe! ===" << std::endl;
    std::cout << "You are X, Bot is O" << std::endl;
    std::cout << "Position numbering:" << std::endl;
    std::cout << " 1 | 2 | 3" << std::endl;
    std::cout << " 4 | 5 | 6" << std::endl;
    std::cout << " 7 | 8 | 9" << std::endl;

    while (!gameOver) {
        clearScreen();
        displayBoard();

        // Player turn
        playerMove();

        if (checkWin(PLAYER)) {
            gameResult = PLAYER;
            gameOver = true;
            break;
        }

        if (checkDraw()) {
            gameResult = 'D';
            gameOver = true;
            break;
        }

        clearScreen();
        displayBoard();

        // Bot turn
        std::cout << "Bot is thinking..." << std::endl;
        botTurn();

        if (checkWin(BOT)) {
            gameResult = BOT;
            gameOver = true;
            break;
        }

        if (checkDraw()) {
            gameResult = 'D';
            gameOver = true;
            break;
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }

    // Board and result
    clearScreen();
    displayBoard();
    displayGameStatus();
}

int main() {
    playGame();
    return 0;
}


void initializeBoard() {
    for (unsigned short i = 0; i < BOARD_SIZE; ++i) {
        boardState[i] = '1' + i;
    }
}
void clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}
void displayBoard() {
    std::cout << std::endl;
    std::cout << "        Tic Tac Toe C++" << std::endl;
    std::cout << std::endl;
    std::cout << "  _________________________" << std::endl;
    std::cout << "  |       |       |       |" << std::endl;
    std::cout << "  |   " << boardState[0] << "   |   " << boardState[1] << "   |   " << boardState[2] << "   |" << std::endl;
    std::cout << "  |_______|_______|_______|" << std::endl;
    std::cout << "  |       |       |       |" << std::endl;
    std::cout << "  |   " << boardState[3] << "   |   " << boardState[4] << "   |   " << boardState[5] << "   |" << std::endl;
    std::cout << "  |_______|_______|_______|" << std::endl;
    std::cout << "  |       |       |       |" << std::endl;
    std::cout << "  |   " << boardState[6] << "   |   " << boardState[7] << "   |   " << boardState[8] << "   |" << std::endl;
    std::cout << "  |_______|_______|_______|" << std::endl;
    std::cout << std::endl;
}
void displayGameStatus() {
    if (gameResult == PLAYER) {
        std::cout << ">>> You WIN! Congratulations! <<<" << std::endl;
    } else if (gameResult == BOT) {
        std::cout << ">>> Bot WINS! Better luck next time! <<<" << std::endl;
    } else if (gameResult == 'D') {
        std::cout << ">>> It's a DRAW! Well played! <<<" << std::endl;
    }
}
bool isValidMove(unsigned short position) {
    return position >= 1 && position <= BOARD_SIZE &&
           boardState[position - 1] != PLAYER &&
           boardState[position - 1] != BOT;
}
bool checkWin(char player) {
    const unsigned short winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // columns
        {0, 4, 8}, {2, 4, 6}              // diagonals
    };

    for (const auto& pattern : winPatterns) {
        if (boardState[pattern[0]] == player &&
            boardState[pattern[1]] == player &&
            boardState[pattern[2]] == player) {
            return true;
        }
    }
    return false;
}
bool checkDraw() {
    for (unsigned short i = 0; i < BOARD_SIZE; ++i) {
        if (boardState[i] != PLAYER && boardState[i] != BOT) {
            return false;
        }
    }
    return true;
}
unsigned short getSmartBotMove() {

    for (unsigned short i = 0; i < BOARD_SIZE; ++i) {
        if (boardState[i] != PLAYER && boardState[i] != BOT) {
            boardState[i] = BOT;
            if (checkWin(BOT)) {
                boardState[i] = '1' + i;
                return i;
            }
            boardState[i] = '1' + i;
        }
    }

    for (unsigned short i = 0; i < BOARD_SIZE; ++i) {
        if (boardState[i] != PLAYER && boardState[i] != BOT) {
            boardState[i] = PLAYER;
            if (checkWin(PLAYER)) {
                boardState[i] = BOT;
                return i;
            }
            boardState[i] = '1' + i;
        }
    }

    if (boardState[4] != PLAYER && boardState[4] != BOT) {
        return 4;
    }

    unsigned short corners[] = {0, 2, 6, 8};
    for (unsigned short corner : corners) {
        if (boardState[corner] != PLAYER && boardState[corner] != BOT) {
            return corner;
        }
    }

    for (unsigned short i = 0; i < BOARD_SIZE; ++i) {
        if (boardState[i] != PLAYER && boardState[i] != BOT) {
            return i;
        }
    }

    return 0;  // (shouldn't happen)
}
void playerMove() {
    unsigned short playerChoice;
    bool validInput = false;

    while (!validInput) {
        std::cout << "Your move (1-9, or 0 to EXIT): ";
        std::cin >> playerChoice;

        if (playerChoice == 0) {
            std::cout << "Game exited. Thanks for playing!" << std::endl;
            exit(0);
        }

        if (isValidMove(playerChoice)) {
            boardState[playerChoice - 1] = PLAYER;
            validInput = true;
        } else {
            std::cout << "Invalid move! Choose an empty position from 1-9." << std::endl;
        }
    }
}
void botTurn() {
    unsigned short botMove = getSmartBotMove();
    boardState[botMove] = BOT;
    std::cout << "Bot played: " << (botMove + 1) << std::endl;
}