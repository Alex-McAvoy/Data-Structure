#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
#define N 50

int next[N];
void getNext(char p[]) { //获取字符数组p的next数组
    next[0] = -1;        //初始化

    int len = strlen(p); //模式串长度
    int j = 0;           //模式指针j
    int k = -1;          //位置k

    while (j < len) {
        if (k == -1 || p[j] == p[k]) { //next[j+1]=next[j]+1
            k++; //此前有next[j]=k
            j++; //指针后移
            next[j] = k;
        } else { // k=next[k]
            k = next[k];
        }
    }
}
int MP(char T[], char P[]) { // MP算法
    int tLen = strlen(T);    //文本串长度
    int pLen = strlen(P);    //模式串长度

    int i = 0;  //文本串指针
    int j = 0;  //模式串指针

    getNext(P); //获取MP版本的next数组

    while (i < tLen && j < pLen) {
        if (j == -1 || T[i] == P[j]) { //当j=-1时，要移动的是i，同样j也要归零
            i++;
            j++;
        } else {
            j = next[j]; //j回到指定位置
        }
    }

    if (j == pLen) //匹配成功
        return i - j;
    return -1;
}

int main(){
    char T[N] = "ababcabcacbab";
    char P[N] = "abc";
    cout << MP(T, P) << endl;
    system("pause");
    return 0;
}