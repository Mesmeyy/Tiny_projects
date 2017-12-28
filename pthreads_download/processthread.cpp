/*************************************************************************
	> File Name: processthread.cpp
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年12月28日 星期四 09时43分34秒
 ************************************************************************/

#include<iostream>
#include<pthread.h>
#include<vector>
#include<sys/socket.h>
#include<netinet/in.h>
#include<apra/inet.h>
#include<stdlib.h>
#include"configure.h"
#include"processthread.h"

using namespace std;
PROCESSTHREAD::PROCESSTHREAD()
{
    clients = CLIENTS;
    url = "";
    host = "";
    port = 0;
}
void PROCESSTHREAD::set_clients(int number)
{
    clients = number;
}
void PROCESSTHREAD::set_para(char* a)
{
    int index = 0;
    string para2 = a;
    if(para2.compare("http://") != 0){
        show_error("Format is error.");
    }
    if((index = para2.rfind('/',para2.length() - 1)) != string::npos)
    {
        host = para2.assign(para2,7,index-7);
        url  = para2.assign(para2,index,para2.length()-index);
        int index = url.find(':',0);
        if((index = url.find(':',0)) == string::npos) port = 80;
        string thisport = url.assign(url,index,url.length()-1-index); 
        port = atoi(thisport.c_str());
        return ;
    }
    show_error("No file to request.");
}
void PROCESSTHREAD::start()
{
    int i = 0;
    vector<pthread_t> vec;
    if(clients<= 0) clients = CLIENTS;
    for(;i < clients;i++){
        pthread_t thid;
        pthread_create(&thid,NULL,sondo,NULL);
        vec.push_back(thid);
    }

    for(auto &t : vec)
    {
        pthread_join(thr,NULL);
    }
}
void* sondo(void *)
{
    int fd = set_socket();   
    
}

int  PROCESSTHREAD::set_socket()
{
    int sock;
    unsigned long inaddr;
    struct sockaddr_in ad;
    struct hostent *hp;

    memset(&ad,0,sizeof(ad));
    ad.sin_family = AF_INET;
    
    string ip = url.assign(url,0,url.find(':',0));
    inaddr = inet_addr(ip.c_str());
    if(inaddr != INADDR_NONE)
        memcpy(&ad.sin_addr,&inaddr,sizeof(inaddr));
    else {
        hp = gethostbyname(ip.c_str());
        if(hp = NULL) return -1;
        memcpy(&ad.sin_addr,hp -> h_addr,hp->h_length);
    }
    ad.sin_port = htons(port);

    sock = socket(AF_INET,SOCKER_STREAM,0);
    if(sock < 0) return sock;
    if(connect(sock,(struct sockaddr*)&ad,sizeof(ad)) < 0 ) return -1;
    return sock;
}
