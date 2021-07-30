
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

template <typename T> 
struct LNode {      //单链表结点
    T data;         //数据域
    LNode<T> *next; //指针域
};
template <typename T> 
class LinkStack {
  public:
    LinkStack();          //初始化栈
    int getLen();         //求栈长
    bool empty();         //判空
    bool pop(T &elem);    //出栈
    bool push(T elem);    //入栈
    bool getTop(T &elem); //取栈顶
    void print();         //输出
  private:
    LNode<T> *first;     //头指针
};

template <typename T> 
LinkStack<T>::LinkStack() { //初始化栈
    first = NULL;
}
template <typename T> 
int LinkStack<T>::getLen() { //求栈长
    LNode<T> *p = first;
    int len = 0;
    while (p != NULL) {
        len++;
        p = p->next;
    }
    return len;
}
template <typename T>
bool LinkStack<T>::empty() { //判空
    if (first == NULL)
        return true;
    return false;
}
template <typename T> 
bool LinkStack<T>::pop(T &elem) { //出栈
    if (empty()) //下溢判断
        return false;
    LNode<T> *p = first;
    elem = p->data;
    first = first->next;
    free(p);
    return true;
}
template <typename T> 
bool LinkStack<T>::push(T elem) { //入栈
    LNode<T> *p = (LNode<T> *)malloc(sizeof(LNode<T>));
    if (p == NULL) //空间分配失败
        return false;
    p->data = elem;
    p->next = first;
    first = p;
    return true;
}
template <typename T> 
bool LinkStack<T>::getTop(T &elem) { //取栈顶
    if (empty()) //下溢判断
        return false;
    elem = first->data;
    return true;
}
template <typename T> 
void LinkStack<T>::print() { //输出
    int elem;
    while (!empty()) { //将所有元素依次出栈进行输出
        pop(elem);
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    LinkStack<int> link_stack;
    link_stack.push(1);
    link_stack.push(2);
    link_stack.push(3);
    link_stack.push(4);

    link_stack.print();
    cout << endl;

    link_stack.push(1);
    link_stack.push(2);
    link_stack.push(3);
    link_stack.push(4);
    cout << link_stack.getLen() << endl;
    cout << endl;

    int elem = 0;
    link_stack.pop(elem);
    cout << elem << endl;
    link_stack.pop(elem);
    cout << elem << endl;

    cout << endl;
    link_stack.print();


    system("pause");
    return 0;
}
