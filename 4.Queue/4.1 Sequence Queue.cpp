
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define N 50 + 5 //申请空间个数
template <typename T> 
class SeqQueue {
  public:
    SeqQueue();           //初始化队
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
SeqQueue<T>::SeqQueue() { //初始化队列
    head = 0;
    tail = 0;
}
template <typename T> 
int SeqQueue<T>::getLen() { //求队长
    return tail-head;
}
template <typename T> 
bool SeqQueue<T>::empty() { //判空
    if (head == tail)
        return true;
    return false;
}
template <typename T> 
bool SeqQueue<T>::full() { //判满
    if (tail == N)
        return true;
    return false;
}
template <typename T> 
bool SeqQueue<T>::pop(T &elem) { //出队
    if (empty()) //下溢判断
        return false;
    elem = data[head++];
    return true;
}
template <typename T> 
bool SeqQueue<T>::push(T elem) { //入队
    if (full()) //上溢判断
        return false;
    data[tail++] = elem;
    return true;
}
template <typename T> 
bool SeqQueue<T>::getTop(T &elem) { //取队首
    if (empty()) //下溢判断
        return false;
    elem = data[head];
    return true;
}
template <typename T> 
void SeqQueue<T>::print() { //输出
    int elem;
    while (!empty()) { //将所有元素依次出队进行输出
        pop(elem);
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    SeqQueue<int> seq_queue;
    seq_queue.push(1);
    seq_queue.push(2);
    seq_queue.push(3);
    seq_queue.push(4);

    seq_queue.print();
    cout << endl;

    seq_queue.push(1);
    seq_queue.push(2);
    seq_queue.push(3);
    seq_queue.push(4);
    cout << seq_queue.getLen() << endl;
    cout << endl;

    int elem = 0;
    seq_queue.pop(elem);
    cout << elem << endl;
    seq_queue.pop(elem);
    cout << elem << endl;

    cout << endl;
    seq_queue.print();

    system("pause");
    return 0;
}
