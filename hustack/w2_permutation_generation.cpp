#include<bits/stdc++.h>
using namespace std;

int n;

void backtrack(vector<int> current, vector<bool> isSelected) {
    if (current.size() == n) {
        for (int num : current) cout << num << " ";
        cout << "\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (isSelected[i]) continue;

        current.push_back(i);
        isSelected[i] = true;

        backtrack(current, isSelected);

        current.pop_back();
        isSelected[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    vector<bool> isSelected(n+1);
    vector<int> current;

    backtrack(current, isSelected);

    return 0;
}
