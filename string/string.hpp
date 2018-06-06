//
// Created by Administrator on 2018/6/1.
//

#ifndef DATA_STRUCT2019_STRING_HPP
#define DATA_STRUCT2019_STRING_HPP

#define MAXSIZE 100

typedef struct str {
    char *ch;
    int length;
} Str;

int strassign(Str &str, char *ch); //字符串赋值

int strlength(Str str); //取串长度

int strcompare(Str str1, Str str2); //串比较

int concat(Str &str, Str str1, Str str2); //串连接

int substring(Str &substr, Str str, int pos, int len); //取子串

int clearStr(Str &str); //清空字符串

int index(Str str, Str subStr); //简单匹配

void getnext(Str subStr, int next[]); //获得KMP的next数组

void getnextval(Str subStr, int nextval[]); //获得KMP的nextval数组

int KMP(Str str, Str substr, int next[]); //KMP算法

#endif //DATA_STRUCT2019_STRING_HPP
