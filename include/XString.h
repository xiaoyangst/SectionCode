//
// 封装字符串操作函数
//

#ifndef STUDYLIBRARY_XSTRING_H
#define STUDYLIBRARY_XSTRING_H

#include <iostream>
using namespace std;

    char *STRCPY(char* dest, const size_t destlen, const char* src);
    char *STRNCPY(char* dest,const size_t destlen,const char* src,size_t n);
    char *STRCAT(char* dest, const size_t destlen, const char* src);
    char *STRNCAT(char* dest,const size_t destlen,const char* src,size_t n);
    int SPRINTF(char *dest,const size_t destlen,const char *fmt,...);
    int SNPRINTF(char *dest,const size_t destlen,size_t n,const char *fmt,...);
    void DeleteLChar(char *str, const char chr);
    void DeleteRChar(char *str,const char chr);
    void DeleteLRChar(char *str,const char chr);
    void ToUpper(char *str);
    void ToUpper(string &str);
    void ToLower(char *str);
    void ToLower(string &str);
    void UpdateStr(char *str,const char *str1,const char *str2,const bool bloop=true);
    void PickNumber(const char *src,char *dest,const bool bsigned,const bool bdot);
    bool MatchStr(const string &str,const string &rules);


#endif //STUDYLIBRARY_XSTRING_H
