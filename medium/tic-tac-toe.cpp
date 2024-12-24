#include <iostream>
#include <vector>

using namespace std;

class TicTacToe {
private:
    vector<vector<char> > board; // 3x3 game board
    int currentPlayer; // 1 for Player 1, 2 for Player 2

public:
    TicTacToe()
    {
        board = vector<vector<char> >(3,
                                      vector<char>(3, ' '));
        currentPlayer = 1;
    }

    void printBoard()
    {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j];
                if (j < 2) {
                    cout << " | ";
                }
            }
            cout << endl;
            if (i < 2) {
                cout << "---------" << endl;
            }
        }
    }

    bool isBoardFull()
    {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    bool makeMove(int row, int column)
    {
        if (row < 0 || row >= 3 || column < 0 || column >= 3
            || board[row][column] != ' ') {
            return false; // Invalid move
        }
        board[row][column]
            = (currentPlayer == 1) ? 'X' : 'O';
        currentPlayer
            = 3 - currentPlayer; // Switch player (1 to 2 or
                                 // 2 to 1)
        return true;
    }

    bool checkWinner()
    {
        // Check rows, columns, and diagonals for a win
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] != ' '
                && board[i][0] == board[i][1]
                && board[i][1] == board[i][2]) {
                return true; // Row win
            }
            if (board[0][i] != ' '
                && board[0][i] == board[1][i]
                && board[1][i] == board[2][i]) {
                return true; // Column win
            }
        }
        if (board[0][0] != ' ' && board[0][0] == board[1][1]
            && board[1][1] == board[2][2]) {
            return true; // Diagonal win
        }
        if (board[0][2] != ' ' && board[0][2] == board[1][1]
            && board[1][1] == board[2][0]) {
            return true; // Diagonal win
        }
        return false;
    }
    int getCurrentPlayer() {
        return currentPlayer;
    }
  
  
};

int main()
{
    TicTacToe game;
    int row, column;

    while (!game.isBoardFull() && !game.checkWinner()) {
        game.printBoard();

        cout << "Player " << game.getCurrentPlayer()
             << ", enter your move (row and column): ";
        cin >> row >> column;

        if (game.makeMove(row, column)) {
            cout << "Move successful!" << endl;
        }
        else {
            cout << "Invalid move. Try again." << endl;
        }
    }

    game.printBoard();

    if (game.checkWinner()) {
        cout << "Player " << (3 - game.getCurrentPlayer())
             << " wins!" << endl;
    }
    else {
        cout << "It's a draw!" << endl;
    }

    return 0;
}
