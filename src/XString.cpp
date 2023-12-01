#include "XString.h"
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <string>


// dest：目标字符串，不需要初始化，在STRCPY函数中会对它进行初始化
// destlen：目标字符串dest占用内存的大小
// src：原字符串
// 返回值：目标字符串dest的地址
// 注意，超出dest容量的内容将丢弃
char *STRCPY(char *dest, const size_t destlen, const char *src) {
    if (dest == nullptr) return nullptr;    //如果dest为空指针，直接返回
    memset(dest,0,destlen);
    if (src == nullptr) return dest;        //如果src为空指针，返回已清零操作的dest

    if (strlen(src) > destlen - 1){         //如果源字符串长度 > 目的字符串长度 ，需要截取操作，即指定长度复制
        strncpy(dest,src,destlen-1);        //destlen - 1 是为腾出空间作为字符串终止符 '\0'
    } else{
        strcpy(dest,src);                   //如果源字符串长度 < 目的字符串长度，安心复制即可
    }
    return dest;
}

// dest：目标字符串，不需要初始化，在STRNCPY函数中会对它进行初始化
// destlen：目标字符串dest占用内存的大小
// src：原字符串
// n：待复制的字节数
// 返回值：目标字符串dest的地址
// 注意，超出dest容量的内容将丢弃
char *STRNCPY(char *dest, const size_t destlen, const char *src, size_t n) {
    if (dest == nullptr) return nullptr;
    memset(dest,0,destlen);
    if (src == nullptr) return dest;
    if (n > destlen - 1){
        strncpy(dest,src,destlen-1);
    } else{
        strncpy(dest,src,n);
    }
    return dest;
}

// 安全的strcat函数
// dest：目标字符串
// destlen：目标字符串dest占用内存的大小
// src：待追加的字符串
// 返回值：目标字符串dest的地址
// 注意，超出dest容量的内容将丢弃
char *STRCAT(char *dest, const size_t destlen, const char *src) {
    if (dest == nullptr) return nullptr;
    if (src == nullptr) return dest;

    unsigned int left = destlen - 1 - strlen(dest);     //dest有效可用空间
    if (strlen(src) > left){    //需要截断
        strncat(dest,src,left);
        dest[destlen - 1] = 0;
    } else{
        strcat(dest,src);
    }
    return dest;
}

// dest：目标字符串
// destlen：目标字符串dest占用内存的大小
// src：待追加的字符串
// n：待追加的字节数
// 返回值：目标字符串dest的地址
// 注意，超出dest容量的内容将丢弃
char *STRNCAT(char *dest, const size_t destlen, const char *src, size_t n) {
    if (dest == nullptr) return nullptr;
    if (src == nullptr) return dest;

    unsigned int left = destlen - 1 - strlen(dest); //dest有效可用空间
    if (n > left){
        strncat(dest,src,left);
        dest[destlen-1] = 0;
    } else{
        strncat(dest,src,n);
    }
    return dest;
}

// 将可变参数(...)按照fmt描述的格式输出到dest字符串中
// dest：输出字符串，不需要初始化，在SPRINTF函数中会对它进行初始化
// destlen：输出字符串dest占用内存的大小，如果格式化后的字符串长度大于destlen-1，后面的内容将丢弃
// fmt：格式控制描述
// ...：填充到格式控制描述fmt中的参数
// 返回值：格式化后的字符串的长度，程序员一般不关心返回值
int SPRINTF(char *dest, const size_t destlen, const char *fmt, ...) {
    if (dest == nullptr) return -1;
    memset(dest,0,destlen);
    va_list arg;
    va_start(arg,fmt);
    int ret = vsnprintf(dest,destlen,fmt,arg);
    va_end(arg);
    return ret;
}

// 将可变参数(...)按照fmt描述的格式输出到dest字符串中
// dest：输出字符串，不需要初始化，在SNPRINTF函数中会对它进行初始化
// destlen：输出字符串dest占用内存的大小，如果格式化后的字符串长度大于destlen-1，后面的内容将丢弃
// n：把格式化后的字符串截取n-1存放到dest中，如果n>destlen-1，则取destlen-1
// fmt：格式控制描述
// ...：填充到格式控制描述fmt中的参数
// 返回值：格式化后的字符串的长度，程序员一般不关心返回值
// 注意：windows和linux平台下的snprintf函数的第三个参数n的用法略有不同。假设格式化后的字符串的长度
// 超过10,第三个参数n取值是10，那么，在windows平台下dest的长度将是10，linux平台下dest的长度却是9
int SNPRINTF(char *dest, const size_t destlen, size_t n, const char *fmt, ...) {
    if (dest == nullptr) return -1;
    memset(dest,0,destlen);

    size_t len = n;
    if (n > destlen){   //复制到缓冲区长度n > 缓冲区可容纳长度destlen
        len = destlen;
    }
    //处理完长度问题，就该处理参数个数问题
    va_list arg;
    va_start(arg,fmt);
    int ret = vsnprintf(dest,len,fmt,arg);
    va_end(arg);
    return ret;
}

// 删除字符串左边指定的字符。
// str：待处理的字符串
// chr：需要删除的字符
void DeleteLChar(char *str, const char chr) {
    if (str == nullptr) return;
    if (strlen(str) == 0) return;

    char strTemp[strlen(str) + 1];
    int iTemp = 0;

    //临时存储清零操作
    memset(strTemp,0, sizeof(strTemp));
    strcpy(strTemp,str);
    //从左往右匹配chr，一个或多个相同的字符，因此我们这里不只是删除一个字符
    //举例：aaaahajskd
    // 删除左边指定字符a，结果为hajskd
    //
    while (strTemp[iTemp] == chr) iTemp++;
    memset(str,0, strlen(str)+1);
    strcpy(str,strTemp+iTemp);

    return;
}

// 删除字符串右边指定的字符。
// str：待处理的字符串
// chr：需要删除的字符
void DeleteRChar(char *str, const char chr) {
    if (str == nullptr) return;
    if (strlen(str) == 0) return;

    size_t istrlen = strlen(str);

    while (istrlen > 0){
        if (str[istrlen - 1] != chr) break;
        str[istrlen - 1] = 0;
        istrlen--;
    }
}

// 删除字符串左右边指定的字符
// str：待处理的字符串
// chr：需要删除的字符
void DeleteLRChar(char *str, const char chr) {
    DeleteLChar(str,chr);
    DeleteRChar(str,chr);
}

//转换为大写
//支持char[]和string两种类型
//str：待转换的字符串，支持char[]和string两种类型
void ToUpper(char *str) {
    if (str == nullptr) return;
    if (strlen(str) == 0) return;

    size_t istrlen = strlen(str);
    for (int i = 0; i < istrlen; i++) {
        if ((str[i] >= 'a') && (str[i]) <= 'z'){
            str[i] = str[i] - 32;
        }
    }
}

void ToUpper(std::string &str) {
    if (str.empty()) return;
    char strtemp[str.size() + 1];
    STRCPY(strtemp,sizeof(strtemp),str.c_str());
    ToUpper(strtemp);
    str = strtemp;
    return;
}

//转换为小写
//支持char[]和string两种类型
//str：待转换的字符串，支持char[]和string两种类型
void ToLower(char *str) {
    if (str == nullptr) return;

    if (strlen(str) == 0) return;

    size_t istrlen=strlen(str);

    for (int i=0;i<istrlen;i++)
    {
        if ( (str[i] >= 'A') && (str[i] <= 'Z') ) {
            str[i]=str[i] + 32;
        }
    }
}

void ToLower(std::string &str) {
    if (str.empty()) return;

    char strtemp[str.size()+1];

    STRCPY(strtemp,sizeof(strtemp),str.c_str());

    ToLower(strtemp);

    str=strtemp;

    return;
}

// 字符串替换函数
// 在字符串str中，如果存在字符串str1，就替换为字符串str2
// str：待处理的字符串
// str1：旧的内容
// str2：新的内容
// bloop：是否循环执行替换
// 注意：
// 1、如果str2比str1要长，替换后str会变长，所以必须保证str有足够的空间，否则内存会溢出
// 2、如果str2中包含了str1的内容，且bloop为true，这种做法存在逻辑错误，UpdateStr将什么也不做
void UpdateStr(char *str, const char *str1, const char *str2, const bool bloop) {
    if (str == nullptr) return;
    if (strlen(str) == 0) return;
    if ((str1 == nullptr) || (str2 == nullptr)) return;

    // 如果bloop为true并且str2中包函了str1的内容，直接返回，因为会进入死循环，最终导致内存溢出
    if (bloop && (strstr(str2, str1) != nullptr) ) return;

    size_t ilen = strlen(str) * 10;
    if (ilen < 1000) ilen = 1000;

    char strTemp[ilen];
    char *strStart = str;
    char *strPos = NULL;

    while (true){
        if (bloop){
            strPos = strstr(str,str1);
        } else{
            strPos = strstr(strStart,str1);
        }

        if (strPos == NULL) break;

        memset(strTemp,0, sizeof(strTemp));
        STRNCPY(strTemp,sizeof(strTemp),str,strPos-str);
        STRCAT(strTemp,sizeof(strTemp),str2);
        STRCAT(strTemp,sizeof(strTemp),strPos+strlen(str1));
        strcpy(str,strTemp);

        strStart=strPos+strlen(str2);
    }
}

// 从一个字符串中提取出数字、符号和小数点，存放到另一个字符串中
// src：原字符串
// dest：目标字符串
// bsigned：是否包括符号（+和-），true-包括；false-不包括
// bdot：是否包括小数点的圆点符号，true-包括；false-不包括
void PickNumber(const char *src, char *dest, const bool bsigned, const bool bdot) {
    if (dest == nullptr) return;    // 判断空指针。
    if (src == nullptr) { strcpy(dest,""); return; }

    char strtemp[strlen(src)+1];
    memset(strtemp,0,sizeof(strtemp));
    strcpy(strtemp,src);
    DeleteLRChar(strtemp,' ');

    size_t ipossrc,iposdst,ilen;
    ipossrc=iposdst=ilen=0;

    ilen=strlen(strtemp);

    for (ipossrc=0;ipossrc<ilen;ipossrc++)
    {
        if (bsigned && (strtemp[ipossrc] == '+') )
        {
            dest[iposdst++]=strtemp[ipossrc]; continue;
        }

        if (bsigned && (strtemp[ipossrc] == '-') )
        {
            dest[iposdst++]=strtemp[ipossrc]; continue;
        }

        if (bdot && (strtemp[ipossrc] == '.') )
        {
            dest[iposdst++]=strtemp[ipossrc]; continue;
        }

        if (isdigit(strtemp[ipossrc])) dest[iposdst++]=strtemp[ipossrc];
    }

    dest[iposdst]=0;
}

