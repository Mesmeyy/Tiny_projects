/*************************************************************************
	> File Name: 16.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月24日 星期三 14时42分41秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
int main(int argc,char **argv)
{
    FILE *fp ;
    int fd;
    int count = 0;
    int n = atoi(argv[2]);
    char readline1[1024];

    fp = fopen(argv[1],"a+");
    fd = open("temp.txt",O_RDWR|O_APPEND|O_CREAT,0664);
    
    while(!feof(fp)){
        memset(readline1,1024,0);
        if(fgets(readline1,1024,fp) == NULL) break;
        count ++;
        if(n == count) continue;
        write(fd,readline1,strlen(readline1));
    }
    if(count < n) {
        printf("Line is too big to delete!\n");
        exit(1);
    }
    fclose(fp);
    close(fd);

    //system("rm file.txt");
    system("mv temp.txt file.txt");
    //system("rm temp.txt");
}
