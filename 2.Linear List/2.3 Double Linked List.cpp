#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

template <typename T> 
struct DNode {       //双链表结点
    T data;          //数据域
    DNode<T> *prior; //前驱指针
    DNode<T> *next;  //后继指针
};
template <typename T> 
class DoubleLinkList {
  public:
    DoubleLinkList();                              //无参构造函数，初始化表
    DoubleLinkList(T data[], int len);             //有参构造函数，链表建立
    ~DoubleLinkList();                             //析构函数，链表销毁
    int getLen();                                  //求表长
    bool empty();                                  //判空
    void print();                                  //输出
    DNode<T> *getNodeByValue(T elem);              //按值查找
    DNode<T> *getNodeByLocate(int pos);            //按位查找
    bool insertNextNode(DNode<T> *p, T elem);      //后插，用于按位插入
    bool insertPreNode(DNode<T> *p, T elem);       //前插，用于按位插入
    bool insertNode(int pos, T elem);              //按位插入
    bool deleteNodeByLocate(DNode<T> *p, T &elem); //删除指定结点p
    void headInsert(T data[], int len);            //头插法
    void tailInsert(T data[], int len);            //尾插法
  private:
    DNode<T> *first;                               //头指针
};
template <typename T>
DoubleLinkList<T>::DoubleLinkList() {             //无参构造函数，初始化
    first = (DNode<T> *)malloc(sizeof(DNode<T>)); //分配一头结点
    first->prior = NULL;                          //头结点的前驱永远指向NULL
    first->next = NULL;                           //空表
}
template <typename T>
DoubleLinkList<T>::DoubleLinkList(T data[], int len) { //有参构造函数，链表建立
    first = (DNode<T> *)malloc(sizeof(DNode<T>));      //分配一头结点
    first->prior = NULL;                               //头结点的前驱永远指向NULL
    first->next = NULL;                                //空表

    this->headInsert(data, len);                       //头插法
    // this->tailInsert(data, len);                    //尾插法
}
template <typename T>
DoubleLinkList<T>::~DoubleLinkList() { //析构函数，链表销毁
    while (first != NULL) {
        DNode<T> *p = first;          //暂存要被释放的结点
        first = first->next;          //头指针指向要被释放的结点的下一个结点
        free(p);                      //释放空间
    }
}
template <typename T> 
int DoubleLinkList<T>::getLen() { //求表长
    int len = 0;
    DNode<T> *p = first;          //为保证头指针指向不变，建立临时指针变量进行枚举
    while (p->next != NULL) {     //判断下一结点是否为 NULL
        p = p->next;
        len++;
    }
    return len;
}
template <typename T> 
bool DoubleLinkList<T>::empty() { //判空
    if (first->next == NULL)
        return true;
    return false;
}
template <typename T> 
void DoubleLinkList<T>::print() { //输出
    DNode<T> *p = first->next;    //指向第1个结点
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
template <typename T>
DNode<T> *DoubleLinkList<T>::getNodeByValue(T elem) { //按值查找
    DNode<T> *p = first->next;                        //从头结点开始
    while (p != NULL && p->data != elem)
        p = p->next;
    return p;
}
template <typename T>
DNode<T> *DoubleLinkList<T>::getNodeByLocate(int pos) { //按位查找
    if (pos < 0)                                        //越界判断
        return NULL;
    if (pos == 0)                                      //返回头结点
        return first;

    DNode<T> *p;     //扫描器，当前扫描到的工作结点
    p = first;       //扫描器从头结点开始，头结点是第0个结点
    int now_pos = 0; //累加器，记录p指向的第几个结点

    while (p != NULL && now_pos < pos) { //查找第pos个结点
        p = p->next;
        now_pos++;
    }
    return p;
}
template <typename T>
bool DoubleLinkList<T>::insertNextNode(DNode<T> *p, T elem) { //后插，用于按位插入
    if (p == NULL)
        return false;

    DNode<T> *s = (DNode<T> *)malloc(sizeof(DNode<T>)); //申请新结点

    //对新结点s操作
    s->data = elem;         //存数据
    s->next = p->next;      //新结点s的后继指针指向p的后继
    s->prior = p;           //新结点s的前驱指针指向p

    //对工作结点p操作
    p->next = s;            //工作结点p的后继指针指向新结点

    //对新结点s的后继结点操作
    if (s->next != NULL)    //如果新结点s的后继结点存在
        s->next->prior = s; //新节点s的后继结点的前驱指针指向新结点s

    return true;
}
template <typename T>
bool DoubleLinkList<T>::insertPreNode(DNode<T> *p, T elem) { //前插，用于按位插入
    if (p == NULL)
        return false;

    DNode<T> *s = (DNode<T> *)malloc(sizeof(DNode<T>)); //申请新结点

    //对新结点s操作
    s->data = elem;         //存数据
    s->prior = p->prior;    //新结点s的前驱指向p的前驱
    s->next = p;            //新结点s的后继指针指向p

    //对新结点s的前驱结点操作
    s->prior->next = s; //新节点s的前驱结点的后继指针指向新结点s

    //对工作结点p操作
    p->prior = s;            //工作结点p的后继指针指向新结点

    return true;
}
template <typename T> 
bool DoubleLinkList<T>::insertNode(int pos, T elem) { //按位插入
    if (pos < 1)                                //越界判断
        return false;

    //后插
    DNode<T> *p = getNodeByLocate(pos - 1);     //找到第pos-1个位置
    if (p == NULL)                              //插入位置异常
        return false;
    return insertNextNode(p, elem);             //在pos-1个位置后插入元素

    //前插
    // DNode<T> *p = getNodeByLocate(pos);      //找到第pos个位置
    // if (p == NULL)                           //插入位置异常
    //     return false;
    // return insertPreNode(p, elem);           //在pos个位置前插入元素
}
template <typename T>
bool DoubleLinkList<T>::deleteNodeByLocate(DNode<T> *p, T &elem) { //删除指定结点p
    if (p == NULL)
        return false;
    elem = p->data;                //存储数据
    if (p->next == NULL)           //p为表尾元素
        p->prior->next = NULL;     //p的前驱结点的后继指针指向NULL
    else {                         //p为非表尾元素
        p->next->prior = p->prior; //p的后继结点的前驱指针指向p的前驱结点
        p->prior->next = p->next;  //p的前驱结点的后继指针指向p的后继结点
    }
    free(p);
    return true;
}
template <typename T> 
void DoubleLinkList<T>::headInsert(T data[], int len) { //头插法
    for (int i = 0; i < len; i++)                       //每一次对头结点进行后插操作
        insertNextNode(first, data[i]);
}
template <typename T> 
void DoubleLinkList<T>::tailInsert(T data[], int len) { //尾插法
    DNode<T> *tail = first;                             //尾指针
    for (int i = 0; i < len; i++) {
        DNode<T> *p = (DNode<T> *)malloc(sizeof(DNode<T>)); //申请新结点
        p->data = data[i];                                  //填充数据域
        tail->next = p;                                     //建立后继关系
        p->prior = tail;                                    //建立前驱关系
        tail = p;                                           //更改尾指针为新结点p地址
    }
    tail->next = NULL;                                      //建立完毕，尾指针指针域置空
}

int main() {
    int a[5] = {1, 2, 3, 4, 5};
    DoubleLinkList<int> link_list(a, 5);
    link_list.print();

    DNode<int> *p = link_list.getNodeByLocate(1);
    link_list.insertPreNode(p, 4);
    link_list.print();

    cout << link_list.getLen() << endl;

    int elem = -1;
    link_list.deleteNodeByLocate(link_list.getNodeByValue(4), elem);
    cout << elem << endl;
    link_list.print();

    link_list.insertNode(1, 2);
    link_list.insertNode(2, 2);
    link_list.print();

    system("pause");
    return 0;
}
