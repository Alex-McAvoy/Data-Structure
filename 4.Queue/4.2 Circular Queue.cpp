#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define N 55 //申请空间个数
template <typename T> 
class CirQueue {
  public:
    CirQueue();           //初始化队
    int getLen();         //求队长
    bool empty();         //判空
    bool full();          //判满
    bool pop(T &elem);    //出队
    bool push(T elem);    //入队
    bool getTop(T &elem); //取队首
    void print();         //输出
  private:
    T data[N];            //队列空间
    int head;             //队首指针
    int tail;             //队尾指针
};

template <typename T> 
CirQueue<T>::CirQueue() { //初始化队列
    head = 0;
    tail = 0;
}
template <typename T> 
int CirQueue<T>::getLen() { //求队长
    return (tail + N - head) % N;
}
template <typename T> 
bool CirQueue<T>::empty() { //判空
    if (head == tail)
        return true;
    return false;
}
template <typename T> 
bool CirQueue<T>::full() { //判满
    if ((tail + 1) % N == head)
        return true;
    return false;
}
template <typename T> 
bool CirQueue<T>::pop(T &elem) { //出队
    if (empty()) //下溢判断
        return false;
    elem = data[head];
    head = (head + 1) % N;
    return true;
}
template <typename T> 
bool CirQueue<T>::push(T elem) { //入队
    if (full()) //上溢判断
        return false;
    data[tail] = elem;
    tail = (tail + 1) % N;
    return true;
}
template <typename T> 
bool CirQueue<T>::getTop(T &elem) { //取队首
    if (empty()) //下溢判断
        return false;
    elem = data[head];
    return true;
}
template <typename T> 
void CirQueue<T>::print() { //输出
    int elem;
    while (!empty()) { //将所有元素依次出队进行输出
        pop(elem);
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    CirQueue<int> cir_queue;
    cir_queue.push(1);
    cir_queue.push(2);
    cir_queue.push(3);
    cir_queue.push(4);

    cir_queue.print();
    cout << endl;

    cir_queue.push(1);
    cir_queue.push(2);
    cir_queue.push(3);
    cir_queue.push(4);
    cout << cir_queue.getLen() << endl;
    cout << endl;

    int elem = 0;
    cir_queue.pop(elem);
    cout << elem << endl;
    cir_queue.pop(elem);
    cout << elem << endl;

    cout << endl;
    cir_queue.print();

    system("pause");
    return 0;
}
