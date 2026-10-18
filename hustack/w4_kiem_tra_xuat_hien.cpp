#include <bits/stdc++.h>
using namespace std;

int n;
map<long, bool> nums;

bool checkNum(int num) {
    if (nums.find(num) != nums.end()) return true;
    nums[num] = true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    int num;
    for (int i = 0; i < n; i++) {
        cin >> num;
        cout << checkNum(num) << "\n";
    }

    return 0;
}
