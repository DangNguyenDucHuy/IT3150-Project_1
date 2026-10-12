#include<bits/stdc++.h>
using namespace std;

string s;

int convertTimeStringToInt(string t) {
    if (t.length() != 2) return -1;
    char c1 = t[0], c2 = t[1];
    if (c1 < '0' || c1 > '9' || c2 < '0' || c2 > '9') return -1;
    int i1 = c1 - '0', i2 = c2 - '0';
    return i1 * 10 + i2;
}

int convertTimeFormat(string t) {
    if (t.length() != 8) return -1;
    if (t[2] != ':' || t[5] != ':') return -1;

    string shh = t.substr(0, 2);
    string smm = t.substr(3, 2);
    string sss = t.substr(6, 2);

    int hh = convertTimeStringToInt(shh);
    int mm = convertTimeStringToInt(smm);
    int ss = convertTimeStringToInt(sss);

    if (hh < 0 || mm < 0 || ss < 0) return -1;

    int totalTime = hh * 3600 + mm * 60 + ss;
    return totalTime;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    int result = convertTimeFormat(s);

    if (result < 0) {
        cout << "INCORRECT";
    } else {
        cout << result;
    }

    return 0;
}
