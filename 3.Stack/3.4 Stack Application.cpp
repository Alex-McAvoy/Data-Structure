#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
#define N 1000 + 5

void parenthesisMatch() { //括号匹配
    char str[N];
    stack<char> S;

    while (scanf("%s", str) != EOF) {
        int len = strlen(str);
        bool flag = true;
        for (int i = 0; i < len; i++) {
            if (str[i] == '(' || str[i] == '[' || str[i] == '{')
                S.push(str[i]);
            else {
                if (S.empty()) {
                    flag = false;
                    break;
                }

                char top = S.top();
                S.pop();

                if (str[i] == ')' && top != '(') {
                    flag = false;
                    break;
                }
                if (str[i] == ']' && top != '[') {
                    flag = false;
                    break;
                }
                if (str[i] == '}' && top != '{') {
                    flag = false;
                    break;
                }
            }
        }
        stack<char>().swap(S);

        if (flag)
            printf("sucessful\n");
        else
            printf("fail\n");
    }
}
void postfix_of_cal() { //后缀表达式计算
    char postfix[N];
    stack<int> S;

    cin.get(postfix,N);
    int len = strlen(postfix);
    int left_op, right_op;
    for (int i = 0; i < len; i++) { //从前向后遍历
        if (postfix[i] == '+') {
            right_op = S.top(); S.pop(); //右操作数先出栈
            left_op = S.top(); S.pop();
            S.push(left_op + right_op);
        } 
        else if (postfix[i] == '-') {
            right_op = S.top(); S.pop(); //右操作数先出栈
            left_op = S.top(); S.pop();
            S.push(left_op - right_op);
        } 
        else if (postfix[i] == '*') {
            right_op = S.top(); S.pop(); //右操作数先出栈
            left_op = S.top(); S.pop();
            S.push(left_op * right_op);
        } 
        else if (postfix[i] == '/') {
            right_op = S.top(); S.pop(); //右操作数先出栈
            left_op = S.top(); S.pop();
            S.push(left_op / right_op);
        } 
        else {
            if (postfix[i] != ' ') {
                int temp = 0;
                while (postfix[i] != ' ') {
                    temp = temp * 10 + postfix[i] - '0';
                    i++;
                }
                S.push(temp);
            }
        }
    }
    printf("%d\n", S.top());
}
void prefix_of_cal() {  //前缀表达式计算
    char prefix[N];
    stack<int> S;

    cin.get(prefix,N);
    int len = strlen(prefix);
    int left_op, right_op;
    for (int i = len - 1; i >= 0; i--) { //从后向前遍历
        if (prefix[i] == '+') {
            left_op = S.top(); S.pop(); //左操作数先出栈
            right_op = S.top(); S.pop();
            S.push(left_op + right_op);
        } 
        else if (prefix[i] == '-') {
            left_op = S.top(); S.pop(); //左操作数先出栈
            right_op = S.top(); S.pop();
            S.push(left_op - right_op);
        } 
        else if (prefix[i] == '*') {
            left_op = S.top(); S.pop(); //左操作数先出栈
            right_op = S.top(); S.pop();
            S.push(left_op * right_op);
        } 
        else if (prefix[i] == '/') {
            left_op = S.top(); S.pop(); //左操作数先出栈
            right_op = S.top(); S.pop();
            S.push(left_op / right_op);
        } 
        else {
            if (prefix[i] != ' ') {
                int num = 0;
                int pos = 0;
                while (prefix[i] != ' ') {
                    int temp = prefix[i] - '0';
                    temp *= pow(10, pos);
                    num += temp;
                    i--;
                    pos++;
                }
                S.push(num);
            }
        }
    }
    printf("%d\n", S.top());
}
int getLevel(char x) { //算符优先级
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    if (x == '^')
        return 3;
    return 0; // ( 与 ) 的优先级
}
void infix_to_postfix() { //中缀转后缀
    char infix[N];
    char postfix[N];
    stack<char> S;

    cin.get(infix,N);
    int len = strlen(infix);
    memset(postfix, '\0', sizeof(postfix));

    int pos = 0;
    for (int i = 0; i < len; i++) {
        if(infix[i] == ' ')
            continue;

        if (infix[i] == '(') // ( 入栈
            S.push(infix[i]);
        else if (infix[i] == ')') {
            while (!S.empty() && S.top() != '(') { //遇到 ( 为止
                postfix[pos++] = S.top();
                postfix[pos++] = ' ';
                S.pop();
            }
            S.pop(); // ( 出栈
        } 
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' ||
                 infix[i] == '/' || infix[i] == '^') {
            
            //当前算符优先级小于等于栈中运算符优先级
            while (!S.empty() && getLevel(infix[i]) <= getLevel(S.top())) {
                char op = S.top();
                postfix[pos++] = op;
                postfix[pos++] = ' ';
                S.pop();
            }
        
            S.push(infix[i]); //当前操作符入栈
        } 
        else { //数字
            postfix[pos++] = infix[i];
            if (i + 1 == len || infix[i + 1] == ' ')
                postfix[pos++] = ' ';
        }
    }
    while (!S.empty()) { //栈中剩余算符出栈
        postfix[pos++] = S.top();
        postfix[pos++] = ' ';
        S.pop();
    }

    printf("%s\n", postfix);
}
void infix_to_prefix() { //中缀转前缀
    char infix[N];
    char prefix[N];
    stack<char> S;

    cin.get(infix,N);
    int len = strlen(infix);
    memset(prefix, '\0', sizeof(prefix));

    int pos = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (infix[i] == ' ')
            continue;

        if (infix[i] == ')') // ) 入栈
            S.push(infix[i]);
        else if (infix[i] == '(') {
            while (!S.empty() && S.top() != ')') { //遇到 ) 为止
                prefix[pos++] = S.top();
                prefix[pos++] = ' ';
                S.pop();
            }
            S.pop(); // ) 出栈
        } 
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' ||
                 infix[i] == '/' || infix[i] == '^') {
            
            //当前算符优先级小于等于栈中运算符优先级
            while (!S.empty() && getLevel(infix[i]) <= getLevel(S.top())) {
                char op = S.top();
                prefix[pos++] = op;
                prefix[pos++] = ' ';
                S.pop();
            }
        
            S.push(infix[i]); //当前操作符入栈
        } 
        else { //数字
            prefix[pos++] = infix[i];
            if (i == 0 || infix[i - 1] == ' ')
                prefix[pos++] = ' ';
        }
    }
    while (!S.empty()) {
        prefix[pos++] = S.top();
        prefix[pos++] = ' ';
        S.pop();
    }
    reverse(prefix, prefix + pos);

    printf("%s\n", prefix + 1);
}
int main() {
    //括号匹配
    parenthesisMatch(); 
    cout << endl;
    // ())))[])      ---> fail
    // [(}({))]      ---> fail
    // ([[]][])      ---> sucessful
    // [[[(){{]]}}]  ---> fail
    // [[[{{(})}]]]  ---> fail
    
    //后缀表达式计算
    postfix_of_cal();   
    cout << endl;
    // 15 7 1 1 + - / 3 * 2 1 1 + + -    --->   5
    // 16 9 4 3 + * -                    ---> -47

    //前缀表达式计算
    prefix_of_cal();    
    cout << endl;
    // - * / 15 - 7 + 1 1 3 + 2 + 1 1    --->    5
    // - 16 * 9 + 4 3                    --->  -47

  
    //中缀转后缀
    infix_to_postfix(); 
    cout << endl;
    // A + B - C * D / E + F             --->     A B + C D * E / - F +
    // AA + BB * ( CC - DD ) - EE / FF   --->     AA BB CC DD - * + EE FF / -

    //中缀转前缀
    infix_to_prefix();  
    // 16 - 9 * ( 4 + 3 )                --->     - 16 * 9 + 4 3
    // A + B - C * D / E + F             --->     + A - B + * C / D E F
    // AA + BB * ( CC - DD ) - EE / FF   --->     + AA - * BB - CC DD / EE FF
  
    system("pause");
    return 0;
}

