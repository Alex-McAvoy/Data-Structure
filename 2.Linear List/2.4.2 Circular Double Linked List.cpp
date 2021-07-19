#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

template <typename T> 
struct CDNode {       //双链表结点
    T data;           //数据域
    CDNode<T> *prior; //前驱指针
    CDNode<T> *next;  //后继指针
};
template <typename T> 
class CirDoubleLinkList {
  public:
    CirDoubleLinkList();                            //无参构造函数，初始化表
    CirDoubleLinkList(T data[], int len);           //有参构造函数，链表建立
    ~CirDoubleLinkList();                           //析构函数，链表销毁
    int getLen();                                   //求表长
    bool empty();                                   //判空
    void print();                                   //输出
    CDNode<T> *getNodeByValue(T elem);              //按值查找
    CDNode<T> *getNodeByLocate(int pos);            //按位查找
    bool insertNextNode(CDNode<T> *p, T elem);      //后插，用于按位插入
    bool insertPreNode(CDNode<T> *p, T elem);       //前插，用于按位插入
    bool insertNode(int pos, T elem);               //按位插入
    bool deleteNodeByLocate(CDNode<T> *p, T &elem); //删除指定结点p
    void headInsert(T data[], int len);             //头插法
    void tailInsert(T data[], int len);             //尾插法
  private:
    CDNode<T> *first;                               //头指针
};

template <typename T>
CirDoubleLinkList<T>::CirDoubleLinkList() {         //无参构造函数，初始化
    first = (CDNode<T> *)malloc(sizeof(CDNode<T>)); //分配一头结点
    first->prior = first;                           //指向自己
    first->next = first;                            //指向自己
}
template <typename T>
CirDoubleLinkList<T>::CirDoubleLinkList(T data[], int len) { //有参构造函数，链表建立
    first = (CDNode<T> *)malloc(sizeof(CDNode<T>));          //分配一头结点
    first->prior = first;                                    //头结点的前驱永远指向NULL
    first->next = first;                                     //空表

    this->headInsert(data, len);                             //头插法
    // this->tailInsert(data, len);                          //尾插法
}
template <typename T>
CirDoubleLinkList<T>::~CirDoubleLinkList() { //析构函数，链表销毁
    first->prior->next = NULL; //断掉最后一个结点与头结点的连接
    while (first != NULL) {
        CDNode<T> *p = first;  //暂存要被释放的结点
        first = first->next;   //头指针指向要被释放的结点的下一个结点
        free(p);               //释放空间
    }
}
template <typename T> 
int CirDoubleLinkList<T>::getLen() { //求表长
    int len = 0;
    CDNode<T> *p = first;            //为保证头指针指向不变，建立临时指针变量进行枚举
    while (p->next != first) {       //判断下一结点是否为头结点
        p = p->next;
        len++;
    }
    return len;
}
template <typename T> 
bool CirDoubleLinkList<T>::empty() { //判空
    if (first->next == first) //判断头结点下一结点是否为自身
        return true;
    return false;
}
template <typename T> 
void CirDoubleLinkList<T>::print() { //输出
    CDNode<T> *p = first->next;      //指向第1个结点
    while (p != first) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
template <typename T>
CDNode<T> *CirDoubleLinkList<T>::getNodeByValue(T elem) { //按值查找
    CDNode<T> *p = first->next;                           //从头结点开始
    while (p != first && p->data != elem)
        p = p->next;
    return p;
}
template <typename T>
CDNode<T> *CirDoubleLinkList<T>::getNodeByLocate(int pos) { //按位查找
    if (pos < 0)      //越界判断
        return NULL;
    if (pos == 0)     //返回头结点
        return first;

    CDNode<T> *p;     //扫描器，当前扫描到的工作结点
    p = first->next;  //扫描器从头结点指向的结点开始
    int now_pos = 1;  //累加器，记录p指向的第几个结点

    while (p != first && now_pos < pos) { //查找第pos个结点
        p = p->next;
        now_pos++;
    }
    return p;
}
template <typename T>
bool CirDoubleLinkList<T>::insertNextNode(CDNode<T> *p, T elem) { //后插，用于按位插入
    if (p == NULL)
        return false;

    CDNode<T> *s = (CDNode<T> *)malloc(sizeof(CDNode<T>));

    //对新结点s操作
    s->data = elem;     //存数据
    s->next = p->next;  //新结点s的后继指针指向p的后继
    s->prior = p;       //新结点s的前驱指针指向p

    //对工作结点p操作
    p->next = s;        //工作结点p的后继指针指向新结点

    //对新结点s的后继结点操作
    s->next->prior = s; //新节点s的后继结点的前驱指针指向新结点s

    return true;
}
template <typename T>
bool CirDoubleLinkList<T>::insertPreNode(CDNode<T> *p, T elem) { //前插，用于按位插入
    if (p == NULL)
        return false;

    CDNode<T> *s = (CDNode<T> *)malloc(sizeof(CDNode<T>)); 

    //对新结点s操作
    s->data = elem;      //存数据
    s->prior = p->prior; //新结点s的前驱指向p的前驱
    s->next = p;         //新结点s的后继指针指向p

    //对新结点s的前驱结点操作
    s->prior->next = s;  //新节点s的前驱结点的后继指针指向新结点s

    //对工作结点p操作
    p->prior = s;        //工作结点p的后继指针指向新结点

    return true;
}
template <typename T> 
bool CirDoubleLinkList<T>::insertNode(int pos, T elem) { //按位插入
    if (pos < 1) //越界判断
        return false;

    //后插
    CDNode<T> *p = getNodeByLocate(pos - 1); //找到第pos-1个位置
    if (p == NULL)                           //插入位置异常
        return false;
    return insertNextNode(p, elem);          //在pos-1个位置后插入元素

    //前插
    // CDNode<T> *p = getNodeByLocate(pos);  //找到第pos个位置
    // if (p == NULL)                        //插入位置异常
    //     return false;
    // return insertPreNode(p, elem);        //在pos个位置前插入元素
}
template <typename T>
bool CirDoubleLinkList<T>::deleteNodeByLocate(CDNode<T> *p, T &elem) { //删除指定结点p
    if (p == NULL)
        return false;
    elem = p->data;            //存储数据
    p->next->prior = p->prior; //p的后继结点的前驱指针指向p的前驱结点
    p->prior->next = p->next;  //p的前驱结点的后继指针指向p的后继结点
    free(p);
    return true;
}
template <typename T> 
void CirDoubleLinkList<T>::headInsert(T data[], int len) { //头插法
    for (int i = 0; i < len; i++) //每一次对头结点进行后插操作
        insertNextNode(first, data[i]);
}
template <typename T> 
void CirDoubleLinkList<T>::tailInsert(T data[], int len) { //尾插法
    CDNode<T> *tail = first;                               //尾指针
    for (int i = 0; i < len; i++) {
        CDNode<T> *p = (CDNode<T> *)malloc(sizeof(CDNode<T>));
        p->data = data[i]; //填充数据域
        tail->next = p;    //建立后继关系
        p->prior = tail;   //建立前驱关系
        tail = p;          //更改尾指针为新结点p地址
    }
    tail->next = NULL;     //建立完毕，尾指针指针域置空
}

int main() {
    int a[5] = {1, 2, 3, 4, 5};
    CirDoubleLinkList<int> link_list(a, 5);
    link_list.print();

    CDNode<int> *p = link_list.getNodeByLocate(1);
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
