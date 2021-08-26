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
class LinkQueue {
  public:
    LinkQueue();          //初始化队
    int getLen();         //求队长
    bool empty();         //判空
    bool pop(T &elem);    //出队
    bool push(T elem);    //入队
    bool getTop(T &elem); //取队首
    void print();         //输出
  private:
    LNode<T> *head;       //队首指针
    LNode<T> *tail;       //队尾指针
    int len;              //队列长度
};

template <typename T> 
LinkQueue<T>::LinkQueue() { //初始化队列
    head = (LNode<T> *)malloc(sizeof(LNode<T>));
    tail = head;
    head->next = NULL;
    len = 0;
}
template <typename T> 
int LinkQueue<T>::getLen() { //求队长
    return len;
}
template <typename T> 
bool LinkQueue<T>::empty() { //判空
    if (head == tail)
        return true;
    return false;
}
template <typename T> 
bool LinkQueue<T>::pop(T &elem) { //出队
    if (empty()) //下溢判断
        return false;
    //队长-1
    len--; 
    //将队首结点断链
    LNode<T> *p = head->next;
    elem = p->data;
    head->next = p->next;
    //最后一个结点
    if (tail == p) 
        tail = head;
    //释放队首结点空间
    free(p);
    return true;
}
template <typename T> 
bool LinkQueue<T>::push(T elem) { //入队
    LNode<T> *p = (LNode<T> *)malloc(sizeof(LNode<T>));
    if (p == NULL) //空间分配失败
        return false;
    //队长+1
    len++;
    //为新结点赋值
    p->data = elem;
    p->next = NULL;
    //连接到队尾
    tail->next = p;
    tail = p;
    return true;
}
template <typename T> 
bool LinkQueue<T>::getTop(T &elem) { //取队首
    if (empty()) //下溢判断
        return false;
    elem = head->next->data;
    return true;
}
template <typename T> 
void LinkQueue<T>::print() { //输出
    int elem;
    while (!empty()) { //将所有元素依次出队进行输出
        pop(elem);
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    LinkQueue<int> link_queue;
    link_queue.push(1);
    link_queue.push(2);
    link_queue.push(3);
    link_queue.push(4);

    link_queue.print();
    cout << endl;

    link_queue.push(1);
    link_queue.push(2);
    link_queue.push(3);
    link_queue.push(4);
    cout << link_queue.getLen() << endl;
    cout << endl;

    int elem = 0;
    link_queue.pop(elem);
    cout << elem << endl;
    link_queue.pop(elem);
    cout << elem << endl;

    cout << endl;
    link_queue.print();

    system("pause");
    return 0;
}

