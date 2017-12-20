/*************************************************************************
	> File Name: 6.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月23日 星期二 21时27分10秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
int main(int argc,char **argv)
{
    
    int a[][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
    for(int i= 0;i <= 2;i++){
        printf("%d\n",a[i][i]);
        //printf("%p ",&a[i][i]);
    }
   /*
    for(int i = 0;i < 4;i++ ){
        for(int j = 0;j < 2;j++){
            printf("%p ",&a[i][j]);
        }
        printf("\n");
    }
    */
    return 0;
}
