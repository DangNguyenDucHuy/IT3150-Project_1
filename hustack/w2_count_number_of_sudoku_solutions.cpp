#include<bits/stdc++.h>
using namespace std;

int s[9][9];
bool isChosen[10];

void setup() {
    for (int i = 1; i <= 9; i++) isChosen[i] = false;
}

vector<int> validateChoices(int row, int col) {
    setup();

    vector<int> validatedChoices;

    for (int j = 0; j < 9; j++) isChosen[s[row][j]] = true;
    for (int i = 0; i < 9; i++) isChosen[s[i][col]] = true;

    int si = row - (row % 3);
    int sj = col - (col % 3);
    for (int i = si; i < si + 3; i++) {
        for (int j = sj; j < sj + 3; j++) {
            isChosen[s[i][j]] = true;
        }
    }

    for (int i = 1; i <= 9; i++) {
        if (!isChosen[i]) validatedChoices.push_back(i);
    }

    return validatedChoices;
}

int backtrack(int row, int col) {
    if (row >= 9) return 1;
    if (col >= 9) return backtrack(row+1, 0);
    if (s[row][col]) return backtrack(row, col+1);

    vector<int> valid = validateChoices(row, col);
    int total = 0;

    for (int num : valid) {
        s[row][col] = num;
        total += backtrack(row, col+1);
    }
    s[row][col] = 0;

    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> s[i][j];
        }
    }

    cout << backtrack(0, 0);

    return 0;
}
