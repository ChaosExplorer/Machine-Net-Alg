#include <stack>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    int calculate(string s) {
        std::stack<int> numbers;
        std::stack<char> ops;

        int number_tail = -1;
        for (int i = s.size()-1; i >= 0; --i) {
            if (s[i] >= '0' && s[i] <= '9') {
                if (number_tail < 0)   number_tail = i;  
            }
            else {
                if (number_tail >= 0)   {
                    numbers.push(std::stoi(s.substr(i+1, number_tail - i)));
                    number_tail = -1;
                }

                if (s[i] == ' ')    continue;
                if (s[i] == ')') {
                    --i;
                    // move i, find )
                    int inner = 0, pos = i;
                    for (; i >= 0; --i) {
                        if (s[i] == ')')    ++inner;
                        if (s[i] == '(') {
                            if (inner == 0) {
                                // pair
                                numbers.push(calculate(s.substr(i+1, pos-i)));
                                break;
                            }
                            else {
                                // inner ()
                                --inner;
                            } 
                        } 
                    }
                }

                else if (s[i] == '+' || s[i] == '-') {
                    ops.push(s[i]);
                }
            }  
        }

        if (number_tail >= 0)   {
            numbers.push(std::stoi(s.substr(0, number_tail + 1)));
        }

        // start cal
        if (numbers.size() != ops.size()+1) numbers.push(0);    // + ; -
        int left, right;
        while (!ops.empty()) {
            left = numbers.top(); numbers.pop();
            right = numbers.top(); numbers.pop();

            if (ops.top() == '+') numbers.push(left+right);
            if (ops.top() == '-') numbers.push(left-right);

            ops.pop();
        }

        return numbers.top();
    }
    
};

class Solution2 {
public:
    int calculate(string s) {
        stack<int> numbers;
        stack<char> ops;

        float num_pos = 0.1;
        int num = 0;
        for (int i = s.size()-1; i >= 0; --i) {
            if (s[i] >= '0' && s[i] <= '9') {
                num_pos *= 10;
                num += (s[i]-'0')* (int)num_pos;    // err1 ,2147483647
            }
            else {
                // end of number
                if (num_pos >= 1) {
                    num_pos = 0.1;
                    numbers.push(num);
                    num = 0;
                }

                // op or ' '
                if (s[i] == ' ')    continue;

                if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')  ops.push(s[i]);
            }
        }

        if (num_pos >= 1)    numbers.push(num);

        // cal
        int num1, num2, num3;
        char op, next_op;
        while (!ops.empty()) {
            op = ops.top(); ops.pop();
            num1 = numbers.top();   numbers.pop();
            num2 = numbers.top();   numbers.pop();

            if (op == '+' || op == '-') {       // err 2
                while (!ops.empty() && (ops.top() == '*' || ops.top() == '/'))   {
                    next_op = ops.top();    ops.pop();
                    num3 = numbers.top();   numbers.pop();
                    
                    num2 = (next_op == '*' ? num2*num3 : num2/num3);
                }
            }

            switch (op) {
                case '+':
                    numbers.push(num1+num2);    break;
                case '-':
                    numbers.push(num1-num2);    break;
                case '*':
                    numbers.push(num1*num2);    break;
                case '/':
                    numbers.push(num1/num2);    break;
            }
        }

        return numbers.top();
    }
};

int main() {
    Solution2 s;
    auto ret = s.calculate("3+2*2");

    cout << ret << endl;

    return 0;
}