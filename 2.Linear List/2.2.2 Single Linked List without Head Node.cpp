
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

template <typename T> 
struct LNode {       //单链表结点
    T data;          //数据域
    LNode<T> *next;  //指针域
};
template <typename T> 
class LinkList {
  public:
    LinkList();                                    //无参构造函数，初始化表
    LinkList(T data[], int len);                   //有参构造函数，链表建立
    ~LinkList();                                   //析构函数，链表销毁
    int getLen();                                  //求表长
    bool empty();                                  //判空
    void print();                                  //输出
    LNode<T> *getNodeByValue(T elem);              //按值查找
    LNode<T> *getNodeByLocate(int pos);            //按位查找
    bool insertNextNode(LNode<T> *p, T elem);      //后插，用于按位插入
    bool insertPreNode(LNode<T> *p, T elem);       //前插，用于按位插入
    bool insertNode(int pos, T elem);              //按位插入
    bool deleteNodeByLocate(LNode<T> *p, T &elem); //删除指定结点p
    bool deleteNodeByElem(T elem);                 //删除所有值为elem的结点
    void headInsert(T data[], int len);            //头插法
    void tailInsert(T data[], int len);            //尾插法
  private:
    LNode<T> *first;                               //头指针
};
template <typename T> 
LinkList<T>::LinkList() {  //无参构造函数，初始化
    first = NULL;          //空表
}
template <typename T>
LinkList<T>::LinkList(T data[], int len) {  //有参构造函数，链表建立
    first = NULL;                           //空表

    this->headInsert(data, len);            //头插法
    // this->tailInsert(data, len);         //尾插法
}
template <typename T> 
LinkList<T>::~LinkList() {   //析构函数，链表销毁
    while (first != NULL) {
        LNode<T> *p = first; //暂存要被释放的结点
        first = first->next; //头指针指向要被释放的结点的下一个结点
        free(p);             //释放空间
    }
}
template <typename T> 
int LinkList<T>::getLen() { //求表长
    int len = 0;
    LNode<T> *p = first;    //为保证头指针指向不变，建立临时指针变量进行枚举
    while (p != NULL) {     //判断当前结点是否为 NULL
        p = p->next;
        len++;
    }
    return len;
}
template <typename T> 
bool LinkList<T>::empty() { //判空
    if (first == NULL)
        return true;
    return false;
}
template <typename T> 
void LinkList<T>::print() { //输出
    LNode<T> *p = first;    //指向第1个结点
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
template <typename T>
LNode<T> *LinkList<T>::getNodeByValue(T elem) { //按值查找
    LNode<T> *p = first;                        //从头指针开始
    while (p != NULL && p->data != elem)
        p = p->next;
    return p;
}
template <typename T>
LNode<T> *LinkList<T>::getNodeByLocate(int pos) { //按位查找
    if (pos <= 0)                                 //越界判断
        return NULL;

    LNode<T> *p;     //扫描器，当前扫描到的工作结点
    p = first;       //扫描器从头指针开始，头指针指向的是第0个结点
    int now_pos = 1; //累加器，记录p指向的第几个结点

    while (p != NULL && now_pos < pos) { //查找第pos个结点
        p = p->next;
        now_pos++;
    }
    return p;
}
template <typename T>
bool LinkList<T>::insertNextNode(LNode<T> *p, T elem) { //后插，用于按位插入
    if (p == NULL)
        return false;

    LNode<T> *s = (LNode<T> *)malloc(sizeof(LNode<T>)); //申请新结点
    s->data = elem;
    s->next = p->next;
    //将s链接至p后
    p->next = s;

    return true;
}
template <typename T>
bool LinkList<T>::insertPreNode(LNode<T> *p, T elem) { //前插，用于按位插入
    if (p == NULL)
        return false;

    LNode<T> *s = (LNode<T> *)malloc(sizeof(LNode<T>)); //申请新结点

    //将新结点s链接到工作结点p后
    s->next = p->next;
    p->next = s;

    //交换数据
    s->data = p->data; //将p结点的数据存入s结点
    p->data = elem;    //将元素elem存入p结点

    return true;
}
template <typename T>
bool LinkList<T>::insertNode(int pos, T elem) { //按位插入
    if (pos < 1)                                //越界判断
        return false;
    
    //第1个结点
    if (pos == 1) {
        LNode<T> *s = (LNode<T> *)malloc(sizeof(LNode<T>));
        s->data = elem;
        s->next = first; //新结点指向头指针所指向的第一个结点
        first = s;       //头指针指向新结点
        return true;
    }
   
    //后插
    LNode<T> *p = getNodeByLocate(pos - 1);     //找到第pos-1个位置
    if (p == NULL)                              //插入位置异常
        return false;
    return insertNextNode(p, elem);             //在pos-1个位置后插入元素

    //前插
    // LNode<T> *p = getNodeByLocate(pos);      //找到第pos个位置
    // if (p == NULL)                           //插入位置异常
    //     return false;
    // return insertPreNode(p, elem);           //在pos个位置前插入元素
}
template <typename T>
bool LinkList<T>::deleteNodeByLocate(LNode<T> *p, T &elem) { //删除指定结点p
    if (p == NULL)
        return false;
    
    //删除非最后一个结点
    if (p->next != NULL) {
        LNode<T> *s = p->next; //指向结点p的下一结点s
        elem = p->data;        //记录数据域，通过引用的方式返回
        p->data = s->data;     //将结点p的下一结点s中的数据存到结点p中
        p->next = s->next;     //断开结点p与其下一结点s的链接关系
        free(s);               //释放p的下一结点的空间
        return true;
    }

    //删除最后一个结点
    if (p->next == NULL) {
        LNode<T> *s = first;       //指向头指针所指向的结点的临时指针
        while (s->next != NULL) {  //从头指针所指向的结点开始遍历
            if (s->next == p) {    //地址相同，即找到链表的最后一个结点
                elem = p->data;    //记录数据域，通过引用的方式返回
                s->next = NULL;    //断开链接关系
                free(p);           //释放p的空间

                return true;
            }
            s = s->next;
        }
    }
}
template <typename T>
bool LinkList<T>::deleteNodeByElem(T elem) { //删除所有值为elem的结点
    LNode<T> *pre = NULL;                    //前驱指针
    LNode<T> *p = first;                     //从头指针指向的结点开始
    if (p == NULL)
        return false;
    while (p != NULL) { 
        if (p->data == elem) { //值相同
            LNode<T> *s = p;   //暂存工作指针p所指向的结点
            p = p->next;       //工作指针p指向下一结点
            pre->next = p;     //p的前驱结点指向p
            free(s);           //释放要删除的结点
        } else {               //值不同
            pre = p;           //前驱指针pre后移
            p = p->next;       //工作指针p后移
        }
    }
}
template <typename T> 
void LinkList<T>::headInsert(T data[], int len) { //头插法
    for (int i = 0; i < len; i++) {
        LNode<T> *p = (LNode<T> *)malloc(sizeof(LNode<T>));
        p->data = data[i]; //填充数据域
        p->next = first;   //将新结点指向头指针所指向的地址
        first = p;         //更改头指针地址为新结点地址
    }
}
template <typename T> 
void LinkList<T>::tailInsert(T data[], int len) { //尾插法
    LNode<T> *tail = first;                       //尾指针
    
    //初始结点
    LNode<T> *p = (LNode<T> *)malloc(sizeof(LNode<T>)); 
    p->data = data[0];  //初始结点数据域
    p->next = first;    //初始结点指向头指针
    first = p;          //更改头指针地址为初始结点地址
    tail = first;       //更改尾指针地址为头指针地址，即初始结点地址

    //初始结点后的len-1个结点
    for (int i = 1; i < len; i++) {
        LNode<T> *p = (LNode<T> *)malloc(sizeof(LNode<T>)); //申请新结点
        p->data = data[i];                                  //填充数据域

        tail->next = p; //建立后继关系
        tail = p;       //更改尾指针为新结点p地址
    }
    tail->next = NULL;  //建立完毕，尾指针指针域置空
}

int main() {
    int a[5] = {1, 2, 3, 4, 5};
    LinkList<int> link_list(a, 5);
    link_list.print();

    LNode<int> *p = link_list.getNodeByLocate(1);
    link_list.insertPreNode(p, 4); //在pos个位置前插入元素
    link_list.print();

    cout << link_list.getLen() << endl;

    int elem = -1;
    link_list.deleteNodeByLocate(link_list.getNodeByValue(4), elem);
    cout << elem << endl;
    link_list.print();

    link_list.insertNode(1, 2);
    link_list.insertNode(2, 2);
    link_list.print();

    link_list.deleteNodeByElem(4);
    link_list.print();

    system("pause");
    return 0;
}
