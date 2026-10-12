#include<bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
string s;
vector<string> terms;

bool isNumber(char c) { return (c >= '0' && c <= '9'); }
bool isPlus(char c) { return (c == '+'); }
bool isProduct(char c) { return (c == '*'); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s;

    // First / last char must be a number
    if (!isNumber(s[0]) || !isNumber(s[s.length()-1])) {
        cout << "NOT_CORRECT";
        return 0;    }

    // Extract terms in the string to array (queue)
    string curNumStr = "";
    string lastOperator = "";

    for (char c : s) {
        if (isNumber(c)) {
            if (lastOperator != "") {
                terms.push_back(lastOperator);
                lastOperator = "";
            }
            // n-digit number
            curNumStr += c;

        } else if (isPlus(c) || isProduct(c)) {
            // 2 consecutive operators
            if (lastOperator != "") {
                cout << "NOT_CORRECT";
                return 0;
            }
            lastOperator += c;
            terms.push_back(curNumStr);
            curNumStr = "";

        } else {
            cout << "NOT_CORRECT";
            return 0;
        }
    }

    if (curNumStr != "") {
        terms.push_back(curNumStr);
    }

    // Convert to number and handle products
    stack<long long> numbers;

    for (int i = 0; i < terms.size(); i++) {
        // Numbers
        if (i % 2 == 0) {
            numbers.push(stol(terms[i]));
            continue;
        }

        // Operators
        if (isProduct(terms[i][0])) {
            // Product previous and next term
            long long prevNum = numbers.top();
            numbers.pop();
            // Take (and skip) next number
            long long nextNum = stol(terms[++i]);
            long long prod = prevNum * nextNum;
            numbers.push(prod);
        } else if (isPlus(terms[i][0])) {
            // Literally do nothing to plus
            // Get mod
            long long num = numbers.top();
            numbers.pop();
            num = num % MOD;
            numbers.push(num);
        }
    }


    // Handle plus
    long long total = 0;
    while (!numbers.empty()) {
        long long num = numbers.top();
        numbers.pop();
        total += num;
        if (total > MOD) total -= MOD;
    }

    cout << total;

    return 0;
}
