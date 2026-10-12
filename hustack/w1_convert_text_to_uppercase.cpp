#include<bits/stdc++.h>
using namespace std;

int D = 'A' - 'a';

bool isNormalCase(char c) {
    return (c >= 'a' && c <= 'z');
}

char convertToUppercase(char c) {
    if (!isNormalCase(c)) return c;
    return (c + D);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    while (getline(cin, s)) {
        string r = "";
        for (char c : s) {
            r += convertToUppercase(c);
        }
        cout << r << "\n";
    }

    return 0;
}
