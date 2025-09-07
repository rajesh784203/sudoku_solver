#include <bits/stdc++.h>
using namespace std;

#define N 9

class SudokuSolver {
private:
    int board[N][N];
    int originalBoard[N][N];

    bool isValid(int row, int col, int num) {
        for (int i = 0; i < N; i++)
            if (board[row][i] == num || board[i][col] == num)
                return false;

        int startRow = row - row % 3, startCol = col - col % 3;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[startRow + i][startCol + j] == num)
                    return false;
            }
        }
        return true;
    }

    pair<int, int> findMRVCell() {
        int minOptions = N + 1;
        pair<int, int> bestCell = { -1, -1 };

        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (board[row][col] == 0) {
                    int options = 0;
                    for (int num = 1; num <= N; num++) {
                        if (isValid(row, col, num))
                            options++;
                    }
                    if (options > 0 && options < minOptions) {
                        minOptions = options;
                        bestCell = { row, col };
                    }
                }
            }
        }
        return bestCell;
    }

    bool solve() {
        pair<int, int> cell = findMRVCell();
        int row = cell.first, col = cell.second;

        if (row == -1 && col == -1)
            return true;

        for (int num = 1; num <= N; num++) {
            if (isValid(row, col, num)) {
                board[row][col] = num;
                if (solve()) return true;
                board[row][col] = 0;
            }
        }
        return false;
    }

public:
    SudokuSolver(int inputBoard[N][N]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                board[i][j] = inputBoard[i][j];
		originalBoard[i][j] = inputBoard[i][j];
            }
        }
    }

    void solveAndDisplay() {
        if (solve()) {
            display();
        } else {
            cout << "No solution exists" << endl;
        }
    }

  void display() {
        cout << "Unsolved Board           ||       Solved Board" << endl;
        cout << "---------------------    ||   ---------------------" << endl;
        for (int row = 0; row < N; row++) {
            if (row % 3 == 0 && row != 0) {
                cout << "---------------------    ||   ---------------------" << endl;
            }
            for (int col = 0; col < N; col++) {
                if (col % 3 == 0 && col != 0) cout << "| ";
                cout << originalBoard[row][col] << " ";
            }
            cout << "   ||   ";
            for (int col = 0; col < N; col++) {
                if (col % 3 == 0 && col != 0) cout << "| ";
                cout << board[row][col] << " ";
            }
            cout << endl;
        }
    }};

int main() {
    int initialBoard[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    SudokuSolver solver(initialBoard);
    solver.solveAndDisplay();

    return 0;
}
