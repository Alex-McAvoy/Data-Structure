#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define N 50 + 5 //申请空间个数
template <typename T> 
class ShStack {
  public:
    ShStack();                   //初始化栈
    int getLen(int i);           //求栈长
    bool empty(int i);           //判空
    bool full();                 //判满
    bool pop(int i, T &elem);    //出栈
    bool push(int i, T elem);    //入栈
    bool getTop(int i, T &elem); //取栈顶
    void print(int i);           //输出
  private:
    T data[N];                   //栈空间
    int top1;                    //1号栈指针
    int top2;                    //2号栈指针
};

template <typename T> 
ShStack<T>::ShStack() { //初始化栈
    top1 = -1;          //1号栈栈底为头部
    top2 = N;           //2号栈栈底为尾部
}
template <typename T>
int ShStack<T>::getLen(int i) { //求栈长
    if (i == 1) //判断1号栈
        return top1 + 1;
    else       //判断2号栈
        return N - top2;
}
template <typename T>
bool ShStack<T>::empty(int i) { //判空
    if (i == 1) { //判断1号栈
        if (top1 == -1)
            return true;
        return false;
    } 
    else {       //判断2号栈
        if (top2 == N)
            return true;
        return false;
    }
}
template <typename T> 
bool ShStack<T>::full() { //判满
    if (top1 == top2 - 1)
        return true;
    return false;
}
template <typename T> 
bool ShStack<T>::pop(int i, T &elem) { //出栈
    if (empty(i)) //下溢判断
        return false;
    if (i == 1)   //1号栈出栈
        elem = data[top1--];
    else          //2号栈出栈
        elem = data[top2++];
    return true;
}
template <typename T> 
bool ShStack<T>::push(int i, T elem) { //入栈
    if (full()) //上溢判断
        return false;
    if (i == 1) //1号栈入栈
        data[++top1] = elem;
    else        //2号栈入栈
        data[--top2] = elem;
    return true;
}
template <typename T> 
bool ShStack<T>::getTop(int i, T &elem) { //取栈顶
    if (empty(i)) //下溢判断
        return false;
    if (i == 1)   //取1号栈栈顶
        elem = data[top1];
    else          //取2号栈栈顶
        elem = data[top2];
    return true;
}
template <typename T> 
void ShStack<T>::print(int i) { //输出
    int elem;
    while (!empty(i)) { //将所有元素依次出栈进行输出
        pop(i, elem);
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    ShStack<int> sh_stack;
    sh_stack.push(1,1);
    sh_stack.push(1,2);
    sh_stack.push(1,3);
    sh_stack.push(1,4);
    cout << sh_stack.getLen(1) << endl;

    sh_stack.push(2,5);
    sh_stack.push(2,6);
    sh_stack.push(2,7);
    sh_stack.push(2,8);
    cout << sh_stack.getLen(2) << endl;

    sh_stack.print(2);
    cout << endl;

    int elem = 0;
    sh_stack.pop(1, elem);
    cout << elem << endl;
    sh_stack.pop(1, elem);
    cout << elem << endl;

    cout << endl;
    sh_stack.print(1);

    system("pause");
    return 0;
}
