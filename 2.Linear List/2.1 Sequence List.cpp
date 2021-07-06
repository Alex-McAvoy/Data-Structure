#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define N 50 + 5 //最大表长
template <typename T> 
class SeqList {
  public:
    SeqList();                              //无参构造函数，初始化表
    SeqList(T m_data[], int m_len);         //有参构造函数，对表赋初值
    ~SeqList();                             //析构函数，销毁表
    void increaseList(int increaseLen);     //扩充线性表长度
    int getLen();                           //求表长
    bool empty();                           //判空
    bool full();                            //判满
    bool print();                           //输出
    bool insertElement(int pos, T elem);    //第pos个位置插入元素elem
    bool deleteElement(int pos, T &elem);   //删除第pos个元素，通过引用返回元素值
    int getNodeByValue(T elem);             //查找与elem相同的第一个元素位置，不存在返回-1
    bool getNodeByLocate(int pos, T &elem); //查找第pos个元素，通过引用返回元素值
  private:
    T *data;
    int len;    //当前表长
    int maxLen; //最大表长
};
template <typename T> 
SeqList<T>::SeqList() { //无参构造函数，初始化表
    len = 0;                                  //初始长度为0，空表
    maxLen = N;                               //最大表长为N

    // 使用malloc开辟空间
    data = (T *)malloc(maxLen * sizeof(T));   //申请连续的maxLen个存储单元
    // 使用new开辟空间
    // data = new int(maxLen);
}
template <typename T> 
SeqList<T>::SeqList(T m_data[], int m_len) { //有参构造函数，对表赋初值
    data = m_data;
    len = m_len;
}
template <typename T> 
SeqList<T>::~SeqList() { //析构函数，销毁表
    free(data); // 使用free回收malloc分配的空间
    // delete data; // 使用delete回收new分配的空间
}
template <typename T>
void SeqList<T>::increaseList(int increaseLen) { //扩充线性表长度
    maxLen = maxLen + increaseLen;               //表长增加increaseLen

    //使用malloc重新分配空间
    T *p = data;
    data = (T *)malloc(maxLen * sizeof(T));     //重新开辟空间
    for (int i = 0; i < len; i++)               //将原有数据复制到新开辟空间
        data[i] = p[i];
    free(p); //释放原空间

    //使用realloc重新分配空间
    // data = (T *)realloc(data, maxLen * sizeof(T));
}
template <typename T> 
int SeqList<T>::getLen() { //求表长
    return len;
}
template <typename T> 
bool SeqList<T>::empty() { //判空
    if (len == 0)
        return true;
    return false;
}
template <typename T> 
bool SeqList<T>::full() { //判满
    if (len == maxLen)
        return true;
    return false;
}
template <typename T> 
bool SeqList<T>::print() { //输出
    if (empty())                                 //判空
        return false;

    int len = getLen(); //表长
    for (int i = 0; i < len - 1; i++)
        cout << data[i] << " ";
    cout << data[len - 1] << endl;
    return true;
}
template <typename T> 
bool SeqList<T>::insertElement(int pos, T elem) { //第pos个位置插入元素elem
    if (pos < 1 || pos > len + 1)                 //越界判断
        return false;
    if (full())                                   //判满
        return false;

    //从最后一个元素到第pos个元素的所有元素后移
    for (int i = len; i >= pos; i--)
        data[i] = data[i - 1];

    data[pos - 1] = elem;
    len++;

    return true;
}
template <typename T>
bool SeqList<T>::deleteElement(int pos, T &elem) { //删除第pos个元素，通过引用返回元素值
    if (pos < 1 || pos > len)                      //越界判断
        return false;
    if (empty())                                   //判空
        return false;

    elem = data[pos - 1];                         //要删除元素
    for (int i = pos; i < len; i++)               //要删除元素之后元素前移
        data[i - 1] = data[i];
    len--;

    return true;
}
template <typename T>
int SeqList<T>::getNodeByValue(T elem) { //查找与elem相同的第一个元素位置，不存在返回-1
    if (empty())                         //判空
        return -1;

    for (int i = 0; i < len; i++)
        if (data[i] == elem)
            return i + 1;

    return -1;
}
template <typename T>
bool SeqList<T>::getNodeByLocate(int pos, T &elem) { //查找第pos个元素，通过引用返回元素值
    if (pos < 1 || pos > len)                        //越界判断
        return false;
    if (empty())                                     //判空
        return false;
    elem = data[pos - 1];
    return true;
}

int main() {
    int data[5] = {1, 2, 3, 4, 5};
    SeqList<int> seq_list(data, 5);
    seq_list.print();
    cout << seq_list.getLen() << endl;
  
    seq_list.insertElement(5, 132);
    seq_list.print();
  
    int elem = 0;
    seq_list.deleteElement(3, elem);
    cout << elem << endl;
    seq_list.print();
  
    seq_list.getNodeByLocate(5, elem);
    cout << elem << endl;

    int pos = seq_list.getNodeByValue(2);
    cout << pos << endl;

    system("pause");
    return 0;
}
