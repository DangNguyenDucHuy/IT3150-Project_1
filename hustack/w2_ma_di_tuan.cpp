#include<bits/stdc++.h>
using namespace std;

const int MN = 12;

int n;
int r, c;
int g[MN][MN];
bool visited[MN][MN];
int res = INT_MIN;

int directions[8][2] = {
    { 2, 1 },
    { 2, -1 },
    { 1, 2 },
    { 1, -2 },
    { -1, 2 },
    { -1, -2 },
    { -2, 1 },
    { -2, -1 }
};

void performMove(int &row, int &col, int directionId) {
    row += directions[directionId][0];
    col += directions[directionId][1];
}

bool validateMove(int row, int col, int directionId) {
    int newRow = row, newCol = col;
    performMove(newRow, newCol, directionId);

    if (visited[newRow][newCol]) return false;
    if (newRow < 1 || newRow > n || newCol < 1 || newCol > n) return false;
    return true;
}

void backtrack(int row, int col, int total) {
    res = max(res, total);

    for (int d = 0; d < 8; d++) {
        if (!validateMove(row, col, d)) continue;

        performMove(row, col, d);
        visited[row][col] = true;

        backtrack(row, col, total + g[row][col]);

        visited[row][col] = false;
        performMove(row, col, 7 - d);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> r >> c;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }

    backtrack(r, c, g[r][c]);
    cout << res;

    return 0;
}
