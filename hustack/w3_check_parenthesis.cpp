#include<bits/stdc++.h>
using namespace std;

string s;

int parenthesis = 0;
int squareBracket = 0;
int curlyBracket = 0;

bool checkCorrectExpression() {
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        if (c == '(') parenthesis++;
            else if (c == ')') parenthesis--;
        if (parenthesis < 0) return false;

        if (c == '[') squareBracket++;
            else if (c == ']') squareBracket--;
        if (squareBracket < 0) return false;

        if (c == '{') curlyBracket++;
            else if (c == '}') curlyBracket--;
        if (curlyBracket < 0) return false;
    }
    return (parenthesis == 0 && squareBracket == 0 && curlyBracket == 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s;
    cout << checkCorrectExpression();

    return 0;
}
