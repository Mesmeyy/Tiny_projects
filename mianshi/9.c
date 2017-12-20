/*************************************************************************
	> File Name: 9.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月23日 星期二 22时13分35秒
 ************************************************************************/

#include<stdio.h>
int main(int argc,char **argv)
{
    int a,b = 2,c = 5;
    for(a = 1;a < 4;a++){
        switch(a){
            //b = 99;
            //printf("Hello world\n");
            case 2 :printf("c is %d\n",c);
                    break;
            printf("Hello world!\n");
            default:printf("a is %d\n",a);
            case 1 :printf("b is %d\n",b);
                    break;
        }
    }
    return 0;
}
