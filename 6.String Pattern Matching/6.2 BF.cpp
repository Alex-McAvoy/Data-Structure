#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
#define N 50

int BF(char *T, char *P) { //BF算法
    int tLen = strlen(T);  //文本串长度
    int pLen = strlen(P);  //模式串长度
    int i = 0;             //文本串的当前位置
    int j = 0;             //模式串的当前位置

    while (i < tLen && j < pLen) {
        if (i > tLen - pLen + 1)
            break;
        if (T[i] == P[j]) { //T的第i个与P的第j个字符相等时
            i++;
            j++;
        } else {            //T的第i个与P的第j个字符不等时
            i = i - j + 1;  //i从上一开始的匹配点后移一位
            j = 0;
        }
    }

    if (j == pLen)    //模式串位置与模式串长度相同说明匹配成功
        return i - j; //返回匹配位置
    return -1;        //匹配失败
}

int main(){
    char T[N] = "ababcabcacbab";
    char P[N] = "abc";
    cout<<BF(T,P)<<endl;
    system("pause");
    return 0;
}