#include<bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
int PROGRAM_STATUS = 0;
string expressionString;



class Utils {
public:
    // Check matched chars
    bool isNum(char c) { return (c >= '0' && c <= '9'); }
    bool isAdd(char c) { return (c == '+'); }
    bool isMul(char c) { return (c == '*'); }
    bool isOpen(char c) { return (c == '('); }
    bool isClose(char c) { return (c == ')'); }

    // Check matched chars (extended)
    bool isSpace(char c) { return (c == ' '); }
    bool isOperator(char c) { return (isAdd(c) || isMul(c)); }
    bool isFullNumber(string s) {
        if (s == "") return false;
        for (char c : s) {
            if (!isNum(c)) return false;
        }
        return true;
    }

    // Compute operations
    string computeAdd(string a, string b) { return to_string((stoll(a) + stoll(b)) % MOD); }
    string computeMul(string a, string b) { return to_string((stoll(a) * stoll(b)) % MOD); }

    // Pure utils
    string charToString(char c) { return string(1, c); }
};
Utils utils;



class ExprNode {
public:
    string val;
    ExprNode* left;
    ExprNode* right;

    ExprNode(string val) {
        this->val = val;
        this->left = NULL;
        this->right = NULL;
    }

    string computeTotal() {
        if (this->val != "") {
            if (utils.isFullNumber(this->val)) return this->val;
            if (utils.isAdd(this->val[0])) return utils.computeAdd(this->left->computeTotal(), this->right->computeTotal());
            if (utils.isMul(this->val[0])) return utils.computeMul(this->left->computeTotal(), this->right->computeTotal());
        }

        // Reason: Some term has no operators, e.g. (5) -> curNode val and right may be NULL -> take only left
        if (this->left != NULL) return this->left->computeTotal();

        PROGRAM_STATUS = 1;
        return "";
    }
};



ExprNode* root = new ExprNode("");
ExprNode* curNode = root;  // Use to traversal
stack<ExprNode*> lastNodes;  // Use for terms in parenthesis
stack<ExprNode*> firstMulNodes;  // Use for sequence of multipication



void initNode(ExprNode*& currentNode, string val = "") {
    currentNode->val = val;

    // Full number is leaf node -> no children
    if (utils.isFullNumber(val)) {
        currentNode->left = NULL;
        currentNode->right = NULL;
        return;
    }

    if (currentNode->left == NULL) currentNode->left = new ExprNode("");
    if (currentNode->right == NULL) currentNode->right = new ExprNode("");
}



void convertToExpressionTree(string s) {
    char prevChar = '+';  // placeholder to trigger isOperator = true
    string fullNumber = "";  // consecutive number char -> number string

    // Init node
    initNode(curNode);


    for (char c : s) {
        // Skip
        if (utils.isSpace(c)) continue;

        // Open parenthesis: (
        if (utils.isOpen(c)) {
            if (!utils.isOperator(prevChar) && !utils.isOpen(prevChar)) {
                PROGRAM_STATUS = 1;
                return;
            }

            lastNodes.push(curNode);
            initNode(curNode->left);
            curNode = curNode->left;

            firstMulNodes.push(NULL);
        }

        // Close parenthesis: )
        if (utils.isClose(c)) {
            if (utils.isOperator(prevChar) || lastNodes.empty()) {
                PROGRAM_STATUS = 1;
                return;
            }

            initNode(curNode, fullNumber);
            curNode = lastNodes.top();
            lastNodes.pop();

            fullNumber = "";
            firstMulNodes.pop();
        }

        // Add: +
        if (utils.isAdd(c)) {
            if (utils.isOperator(prevChar)) {
                PROGRAM_STATUS = 1;
                return;
            }

            if (firstMulNodes.top() != NULL) {
                // End the multiplication sequence
                if (fullNumber != "") initNode(curNode, fullNumber);
                curNode = firstMulNodes.top();
                initNode(curNode, utils.charToString(c));

                firstMulNodes.pop();
                firstMulNodes.push(NULL);

            } else {
                initNode(curNode, utils.charToString(c));
                if (fullNumber != "") initNode(curNode->left, fullNumber);
            }

            initNode(curNode->right);
            curNode = curNode->right;

            fullNumber = "";
        }

        // Mul: *
        if (utils.isMul(c)) {
            if (utils.isOperator(prevChar)) {
                PROGRAM_STATUS = 1;
                return;
            }

            // First number of multiplication sequence
            if (firstMulNodes.top() == NULL) {
                initNode(curNode);

                firstMulNodes.pop();
                firstMulNodes.push(curNode);

                if (curNode->left->val != "") {
                    ExprNode* tmp = new ExprNode("");
                    initNode(tmp, utils.charToString(c));
                    tmp->left = curNode->left;
                    curNode->left = tmp;

                    initNode(tmp->right, utils.charToString(c));
                    curNode = tmp->right;

                    initNode(curNode->left, "1");  // default value (num * 1 = num)
                } else {
                    initNode(curNode->left, utils.charToString(c));
                    curNode = curNode->left;
                }

            } else {
                initNode(curNode, utils.charToString(c));
            }

            if (fullNumber != "") initNode(curNode->left, fullNumber);
            initNode(curNode->right);
            curNode = curNode->right;

            fullNumber = "";
        }

        // Number: 0-9
        if (utils.isNum(c)) {
            if (utils.isClose(prevChar)) {
                PROGRAM_STATUS = 1;
                return;
            }
            fullNumber += c;
        }

        prevChar = c;
    }

    if (!lastNodes.empty()) PROGRAM_STATUS = 1;
}



// Draw Mermaid flow to debug, not used in code
int debugMermaidIdx = 0;
map<ExprNode*, int> mapDebugMermaidIds;

void debugMermaidDrawCurrentNode(ExprNode* cur, int& id) {
    string val = cur->val;
    if (val == "") val = "?";
    cout << id << "((\"" << val << "\"))\n";
    int curId = id;

    if (cur->left != NULL) {
        int leftId = id+1;
        debugMermaidDrawCurrentNode(cur->left, ++id);
        cout << curId << " --> " << leftId << "\n";
    }

    if (cur->right != NULL) {
        int rightId = id+1;
        debugMermaidDrawCurrentNode(cur->right, ++id);
        cout << curId << " --> " << rightId << "\n";
    }
}

void debugMermaidDrawFlow() {
    cout << "\n\n";
    cout << "%% " << expressionString << "\n";
    cout << "graph TD\n";
    int id = 1;
    ExprNode* cur = root;
    debugMermaidDrawCurrentNode(cur, id);
    cout << "\n\n";
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getline(cin, expressionString);

    // Assume: expression = (expression)
    expressionString = "(" + expressionString + ")";
    convertToExpressionTree(expressionString);

    if (PROGRAM_STATUS == 0) cout << root->computeTotal();
    else if (PROGRAM_STATUS == 1) cout << "NOT_CORRECT\n";

//    debugMermaidDrawFlow();

    return 0;
}
