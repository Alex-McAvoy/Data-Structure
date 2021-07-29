#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define N 50 + 5 //申请空间个数
template <typename T> 
class SeqStack {
  public:
    SeqStack();           //初始化栈
    int getLen();         //求栈长
    bool empty();         //判空
    bool full();          //判满
    bool pop(T &elem);    //出栈
    bool push(T elem);    //入栈
    bool getTop(T &elem); //取栈顶
    void print();         //输出
  private:
    T data[N];            //栈空间
    int top;              //栈指针
};

template <typename T> 
SeqStack<T>::SeqStack() { //初始化栈
    top = -1;
}
template <typename T> 
int SeqStack<T>::getLen() { //求栈长
    return top + 1;
}
template <typename T> 
bool SeqStack<T>::empty() { //判空
    if (top == -1)
        return true;
    return false;
}
template <typename T> 
bool SeqStack<T>::full() { //判满
    if (top == N - 1)
        return true;
    return false;
}
template <typename T> 
bool SeqStack<T>::pop(T &elem) { //出栈
    if (empty()) //下溢判断
        return false;
    elem = data[top--];
    return true;
}
template <typename T> 
bool SeqStack<T>::push(T elem) { //入栈
    if (full()) //上溢判断
        return false;
    data[++top] = elem;
    return true;
}
template <typename T> 
bool SeqStack<T>::getTop(T &elem) { //取栈顶
    if (empty()) //下溢判断
        return false;
    elem = data[top];
    return true;
}
template <typename T> 
void SeqStack<T>::print() { //输出
    int elem;
    while (!empty()) { //将所有元素依次出栈进行输出
        pop(elem);
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    SeqStack<int> seq_stack;
    seq_stack.push(1);
    seq_stack.push(2);
    seq_stack.push(3);
    seq_stack.push(4);

    seq_stack.print();
    cout << endl;

    seq_stack.push(1);
    seq_stack.push(2);
    seq_stack.push(3);
    seq_stack.push(4);
    cout << seq_stack.getLen() << endl;
    cout << endl;

    int elem = 0;
    seq_stack.pop(elem);
    cout << elem << endl;
    seq_stack.pop(elem);
    cout << elem << endl;

    cout << endl;
    seq_stack.print();

    system("pause");
    return 0;
}
