/*************************************************************************
	> File Name: 11.2.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月24日 星期三 08时50分58秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int nums[5] = {2,4,6,8,10};
    int *ptr = (int *)(&nums + 1);
    for(int i = 0;i < 5;i++){
        printf("%p ",nums + i);
    }
    printf("\n");
    printf("ptr = %p\n",ptr);
}
