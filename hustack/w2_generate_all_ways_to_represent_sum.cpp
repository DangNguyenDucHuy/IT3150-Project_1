#include<bits/stdc++.h>
using namespace std;

int n;

void recursive(int target, vector<int> current) {
    if (target == 0) {
        for (int num : current) cout << num << " ";
        cout << "\n";
        return;
    }

    int last = 1;
    if (!current.empty()) {
        last = current.back();
        if (last > target) return;
    }

    for (int i = last; i <= target; i++) {
        current.push_back(i);
        recursive(target - i, current);
        current.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    vector<int> current;
    recursive(n, current);

    return 0;
}
