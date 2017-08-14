/*************************************************************************
	> File Name: client.cpp
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年08月14日 星期一 15时51分03秒
 ************************************************************************/

#include<iostream>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<unistd.h>
#include <sstream>
#include<stdio.h>
#include<string.h>
#include<condition_variable>
#include<thread>
#include<vector>
#include"file.h"
using namespace std;
std::vector<std::thread> tv;         //保存线程的情况

std::condition_variable_any m_t;     //条件变量
std::mutex locks;                     //互斥锁
int i = 1;                           //打印机资源 初始为1 表示可用
file f;
string filename;
int per_size;
int connfd;


template <class T>  
string Tostring(const T &t){  
    ostringstream oss;
    oss << t;
    return oss.str();
}  

void subi()
{
    std::lock_guard<std::mutex> locker(locks);
    if(i == 0){
        m_t.wait(locks);
    }
    i--;
}
void addi()
{
    std::lock_guard<std::mutex> locker(locks);
    i++;
    m_t.notify_all();
}

/*线程工作函数*/
void work(int i)
{
    cout << "client threadis the "<< i << "number"<<endl;
    FILE *fp;
    fp = fopen(filename.data(),"r");
    fseek(fp,i*per_size,0);
    char readbuf[512];
    memset(readbuf,0,512);
    fread(readbuf,512,1,fp);
    
    f.url = filename.data();
    f.count = 5;
    f.now_count = Tostring(i);
    f.content = readbuf;
    f.end = "\r\n";
    int fd = fileno(fp);
    subi();
    send(fd,f,,0);
    addi();
}
int main()
{
    file f;
    struct stat st;
    struct sockaddr_in client;

    /*计算每一块的大小*/
    cout << "input filename :";
    cin >> filename;
    stat(filename.data(),&st);
    file.all_size = st.st_size;
    per_size = st.st_size / 5 + 1 ;
 
    memset(&client,0,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(37000);
    inet_aton("127.0.0.1",&client.sin_addr);

    connfd = socket(AF_INET,SOCK_STREAM,0);
    int ret = connect(connfd,(struct sockaddr*)&client,sizeof(client));
    if(ret < 0){
        cout << "connect error"<<endl;
        return -1;
    }
    
    /*创建线程*/
    for(int i = 0;i < 5;i++){
        thread t(work,i);
        tv.push_back(std::move(t));
    }
}
