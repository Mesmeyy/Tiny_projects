/*************************************************************************
	> File Name: 11.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月24日 星期三 08时44分55秒
 ************************************************************************/

#include<stdio.h>
int main(int argc,char **argv)
{
    int nums[5] = {2,4,6,8,10};
    int *ptr = (&nums + 1);
    printf("%d , %d \n",*(nums + 1),*(ptr - 1));
    return 0;
}
