//
// Created by Administrator on 2018/6/1.
//

#include "string.hpp"
#include "malloc.h"

int strassign(Str &str, char *ch) {
    int i = 0;
    char *c = ch;
    int len = 0;
    while (*c) {
        ++ c;
        ++ len;
    }
    if (len == 0) {
        str.ch = NULL;
        str.length = 0;
        return 1;
    }

    str.ch = (char *) malloc(sizeof(char) * (len + 1));
    if (str.ch == NULL) {
        return 0;
    }
    for(i = 0; i < len; ++ i) {
        str.ch[i] = ch[i];
    }
    str.length = len;
    str.ch[str.length] = '\0';
    return 1;
}

int strlength(Str str) {
    return str.length;
}

int strcompare(Str str1, Str str2) {
    int i = 0;
    for (i = 0; i < str1.length && i < str2.length; ++ i) {
        if (str1.ch[i] != str2.ch[i]) {
            return str1.ch[i] - str2.ch[i];
        }
    }
    return str1.length - str2.length;
}

int concat(Str &str, Str str1, Str str2) {
    if (str1.length == 0 && str2.length == 0) {
        str.ch = NULL;
        str.length = 0;
        return 1;
    }

    if (str.ch) { //释放原空间
        free(str.ch);
        str.ch = NULL;
    }

    str.ch = (char *) malloc(sizeof(char) * (str1.length + str2.length + 1));
    if (str.ch == NULL) {
        return 0;
    }
    int i;
    for(i = 0; i < str1.length; ++ i) {
        str.ch[i] = str1.ch[i];
    }

    for(int j = 0; j <= str2.length; ++j) {
        str.ch[i + j] = str2.ch[j];
    }

    str.length = str1.length + str2.length;
    return 1;
}

int substring(Str &substr, Str str, int pos, int len) {
    if (str.length == 0 || pos < 0 || pos >= str.length || len <= 0 || len > str.length - pos) {
        return 0;
    }

    if (substr.ch) {
        free(substr.ch);
        substr.ch = NULL;
    }
    substr.ch = (char *) malloc(sizeof(char) * (len + 1));
    if (substr.ch == NULL) {
        return 0;
    }
    for(int i = pos; i < pos + len; ++ i) {
        substr.ch[i - pos] = str.ch[i];
    }
    substr.ch[len] = '\0';
    substr.length = len;
    return 1;
}

int clearStr(Str &str) {
    if (str.ch) {
        free(str.ch);
        str.ch = NULL;
    }
    str.length = 0;
    return 1;
}

int index(Str str, Str subStr) {
    int i, j ,k;
    k = -1;
    j = 0;
    if (str.length == 0 || subStr.length == 0 || subStr.length > str.length) {
        return k;
    }

    for(i = 0; i < str.length; ++ i) {
        if (subStr.ch[j] == str.ch[i]) {
            if (k == -1) {
                k = i;
            }
            if (j == subStr.length - 1) {
                break;
            } else {
                ++ j;
            }
        } else {
            k = -1;
            j = 0;
        }
    }
    return k;
}

void getnext(Str subStr, int next[]) {
    next[0] = 0;
    int i, j = 0;
    for (i = 1; i < subStr.length; ++ i) {
        while (j > 0 && subStr.ch[i] != subStr.ch[j]) {
            j = next[j - 1];
        }

        if(subStr.ch[i] == subStr.ch[j]) {
            ++ j;
        }

        next[i] = j;
    }
}

void getnextval(Str subStr, int nextval[]) {
    nextval[0] = 0;
    int i, j = 0;
    for (i = 1; i < subStr.length; ++ i) {
        while (j > 0 && subStr.ch[i] != subStr.ch[j]) {
            j = nextval[j - 1];
        }
        if(j == 0 || subStr.ch[i] == subStr.ch[j]) {
            ++j;
            if (subStr.ch[i] != subStr.ch[j]) {
                nextval[i] = j - 1;
            } else {
                nextval[i] = nextval[j - 1];
            }
        }
    }
}

int KMP(Str str, Str substr, int next[]) {
    int i, j = 0;
    for (i = 0; i < str.length; ++i) {
        while (j > 0 && str.ch[i] != substr.ch[j]) {
            j = next[j - 1];
        }

        if (str.ch[i] == substr.ch[j]) {
            ++ j;
        }

        if (j == substr.length) {
            break;
        }
    }

    if (j == substr.length) {
        return i - j + 1;
    } else {
        return -1;
    }
}