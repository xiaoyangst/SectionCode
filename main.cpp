#include <iostream>
#include <cstring>
using namespace std;
#include "XString.h"

int main() {

    char src[] = "xiaoyang";
    char det[10];
    STRCPY(det, strlen(det),src);
    cout<<det<<endl;
    return 0;
}

