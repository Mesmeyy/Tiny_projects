/*************************************************************************
	> File Name: server.cpp
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年08月14日 星期一 13时35分16秒
 ************************************************************************/

#include<iostream>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include"file.h"
#include"threadpool.h"
#include<string.h>
#include<stdlib.h>
#define PORT 37000
using namespace std;

int main()
{
    int optval;
    int ret;

    struct sockaddr_in address,cli_address;
    memset(&address,0,sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    /* ret = inet_aton("127.0.0.1",&address.sin_addr);
    if(ret == 0){
        cout << "ip error"<<endl;
        return -1;
    }*/

    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listen<0){
        cout << "socket error"<<endl;
        return -1;
    }

    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(void*)&optval,4);

    ret = bind(listenfd,(struct sockaddr*)&address,sizeof(struct sockaddr_in));

    if(ret < 0){
        cout << "bind error"<<endl;
        return -1;
    }

    ret = listen(listenfd,5);

    if(ret < 0){
        cout << "listen error"<<endl;
        return -1;
    }

    socklen_t len= sizeof(cli_address);
    cout << "wait for client..."<<endl;
    int connfd = accept(listenfd,(struct sockaddr*)&cli_address,&len);
    if(connfd < 0){
        cout << "accept error"<<endl;
        return -1;
    }
    cout << "open the pool"<<endl;
    threadpool<file> pool(connfd);
}
