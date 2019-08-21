#... 含义

__VA_ARGS__ 宏用来表示可变参数的内容，简单来说就是将左边宏中 … 的内容原样抄写在右边__VA_ARGS__ 所在的位置。如下例代码：

#include <stdio.h>
#define debug(...) printf(__VA_ARGS__)
int main(void)
{
    int year = 2018；
    debug("this year is %d\n", year);  //效果同printf("this year is %d\n", year);
}
