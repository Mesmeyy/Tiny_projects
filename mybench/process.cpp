/*************************************************************************
	> File Name: process.cpp
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年12月17日 星期日 21时46分30秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<sys/param.h>
#include<rpc/types.h>
#include<getopt.h>
#include<cstring>
#include<pthread.h>
#include<string>
#include<time.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<exception>
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"process.h"
using namespace std;
using std::string;
pthread_mutex_t mutex2;//用于clients变化时候的保护
pthread_mutex_t mutex3;//failed
pthread_mutex_t mutex4;//speed
void* sondo(void* p);//子线程函数
PROCESS process;

static const struct option long_options[] = {
    {"force",no_argument,&process.force,1},
    {"reload",no_argument,&process.force_reload,1},
    {"time",required_argument,NULL,'t'},
    {"help",no_argument,NULL,'?'},
    {"http09",no_argument,NULL,'9'},
    {"http10",no_argument,NULL,'1'},
    {"http11",no_argument,NULL,'2'},
    {"get",no_argument,&process.method,METHOD_GET},
    {"head",no_argument,&process.method,METHOD_HEAD},
    {"version",no_argument,NULL,'V'},
    {"proxy",required_argument,NULL,'p'},
    {"clients",required_argument,NULL,'c'},
    {NULL,0,NULL,0}
};
static void signalhandle(int signal)
{
    process.timerecpired = 1;
}

LOCK::LOCK(PROCESS& process,TTTHREAD& th)
{
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_lock(&mutex);
    FILE *fp = fdopen(process.mypipe[1],"wa+");
    fprintf(fp,"%d %d %d\n",th.speed,th.fail,th.bytes);
    fclose(fp);
}
PROCESS::PROCESS()
{
    timerecpired = 0;
    allspeed = 0;
    allfailed = 0;
    allbytes = 0;
    method = METHOD_GET;
    clients = 1;
    force = 0;
    force_reload = 0;
    proxyhost = "";
    proxyport = 0;
    benchtime = 30;
    host = "";
    request = "";
}
int PROCESS::start(int argc,char** argv)
{
    int opt=0;
    int options_index=0;
    char *tmp=NULL;
    int index;
    string  tempport;
    if(argc==1)
    {
        usage();
        return 2;
    } 
    while((opt=getopt_long(argc,argv,"912Vfrt:p:c:?h",long_options,&options_index))!=EOF )
    {
        switch(opt){
        case  0 : break;
        case 'f': force=1;break;
        case 'r': force_reload=1;break; 
        case '9': httpv=0;break;
        case '1': httpv=1;break;
        case '2': httpv=2;break;
        case 'V': printf(PROGRAM_VERSION"\n");exit(0);
        case 't': benchtime=atoi(optarg);break;	     
        case 'p': 
	        proxyhost = optarg;
            index = proxyhost.rfind(':',proxyhost.length() - 1);//找到最后一个:
            if(index == string::npos) break;
	        if(index == 0){
		        fprintf(stderr,"Error in option --proxy %s: Missing hostname.\n",optarg);
		        return 2;
	        }
	        if(index == proxyhost.length() - 1){
		        fprintf(stderr,"Error in option --proxy %s Port number is missing.\n",optarg);
		        return 2;
	        }
            proxyhost = proxyhost.substr(0,index);
	        tempport = proxyhost.substr(index+ 1,proxyhost.length()-index-1);
            proxyport = atoi(tempport.c_str());
            cout << "proxyhost:proxyport = " << proxyhost << " : " << proxyport<<endl;
            if(proxyhost.length()  > MAXHOSTSIZE) return 2;
            if(proxyport > MAXPORT) return 2;
            break;
        case ':':
        case 'h':
        case '?': usage();return 2;break;
        case 'c': clients=atoi(optarg);break;
        }
    }
 
    if(optind==argc) {
        fprintf(stderr,"webbench: Missing URL!\n");
	    usage();
	    return 2;
    }
    if(clients==0) clients=1;
    if(benchtime==0) benchtime=60;
    fprintf(stderr,"Webbench - Simple Web Benchmark "PROGRAM_VERSION"\n"
	 "Copyright (c) Radim Kolar 1997-2004, GPL Open Source Software.\n"
	);
    build_request(argv[optind]);

    switch(method){
	case METHOD_GET:
	default:
		 printf("GET");break;
	case METHOD_HEAD:
		 printf("HEAD");break;
    }
    printf(" %s",argv[optind]);
    switch(httpv){
    case 0: printf(" (using HTTP/0.9)");break;
	case 2: printf(" (using HTTP/1.1)");break;
    }
    printf("\n");
    if(clients==1) printf("1 client");
    else
    printf("%d clients",clients);

    printf(", running %d sec", benchtime);
    if(force) printf(", early socket close");
    if(proxyhost !="") printf(", via proxy server %s:%d",proxyhost.c_str(),proxyport);
    if(force_reload) printf(", forcing reload");
    printf(".\n");
    pthread_mutex_init(&mutex2, NULL);
    pthread_mutex_init(&mutex3,NULL);
    pthread_mutex_init(&mutex4,NULL);
    return bench();
}

void PROCESS::build_request(char *url)
{
    string surl = url;
    char tmp[10];
    int i;


    if(force_reload && proxyhost != "" && httpv<1) httpv=1;
    
    
    if(method== METHOD_GET) httpv = 1;
    if(method==METHOD_HEAD && httpv<1) httpv=1;

    //zzy:构建http包的请求类型
    switch(method){
	  default:
	  case METHOD_GET: request +="GET";break;
	  case METHOD_HEAD:request += "HEAD";break;
    }
    //zzy:根据http包的格式,此处应有空格,然后才能追加url
    request +=" ";

    //以下两个if语句监测url是否规范
    if(surl.length() > MAXHOSTSIZE) exit(2);
    if(surl.compare(0,7,"http://") != 0) exit(2);
    
    if(proxyhost=="")
    //url头必须是http://开头
        if (0 != surl.compare(0,7,"http://")) 
	    { fprintf(stderr,"\nOnly HTTP protocol is directly supported, set --proxy for others.\n");
             exit(2);
        }
    i=strstr(url,"://")-url+3;

    if(surl.find('/',i) <= i) {
        fprintf(stderr,"\nInvalid URL syntax - hostname don't ends with '/'.\n");
        exit(2);
    }

    if(proxyhost=="")
    {
        if(index(url+i,':')!=NULL &&index(url+i,':')<index(url+i,'/'))
        {
	        host = host.assign(url+i,strchr(url+i,':')-url-i);
	        bzero(tmp,10);
	        strncpy(tmp,index(url+i,':')+1,strchr(url+i,'/')-index(url+i,':')-1);
	        proxyport=atoi(tmp);
	        if(proxyport==0) proxyport=80;
        }
        else
        {
            host = host.assign(url+i,strcspn(url+i,"/"));
        }
        request += url+i+strcspn(url+i,"/");
    }
    else
    {
        request += url;
    }
	request +=" HTTP/1.0\r\n";
    
    if(httpv>0)  request += "User-Agent: WebBench "PROGRAM_VERSION"\r\n";
    if(proxyhost =="" && httpv>0)
    {
	    request += "Host: ";
	    request += host;
	    request +="\r\n";
    }
    if(force_reload && proxyhost !="")
    {
	    request += "Pragma: no-cache\r\n";
    }
    request += "Connection:close\r\n";
    request += "\r\n";  
}


bool PROCESS::bench(void)
{
    int tempspeed,tempfail,tempbytes;	
    pid_t pid=0;
    FILE *f;
    int fd; 

    fd=mysocket(proxyhost==""?host:proxyhost,proxyport);
    if(fd<0) { 
	    fprintf(stderr,"\nConnect to server failed. Aborting benchmark.\n");
        return 1;
    }
    close(fd);
    if(pipe(mypipe))
    {
	    perror("pipe failed.");
	    return 3;
    }
    int i = 0;
    PROCESS *tempprocess;
    tempprocess = &process;
    for(i=0;i<clients;i++)
    {
        pthread_t thid;
        pthread_create(&thid,NULL,sondo,NULL);
    }
	allspeed=0;
    allfailed=0;
    allbytes=0;
allcheck:
    if(clients != 0) {
        sleep(3);
        goto allcheck;
    }
    f=fdopen(mypipe[0],"r");
	if(f==NULL) 
	{
	    perror("open pipe for reading failed.");
        return 3;
	}
	setvbuf(f,NULL,_IONBF,0);
    
    
    while(pid=fscanf(f,"%d %d %d",&tempspeed,&tempfail,&tempbytes)!= EOF)
    {
        allspeed  +=tempspeed;
        allfailed +=tempfail;
        allbytes  +=tempbytes;
	}
	fclose(f);

  printf("\nSpeed=%d pages/min, %d bytes/sec.\nRequests: %d susceed, %d failed.\n",
		  (int)((allspeed+allfailed)/(benchtime/60.0f)),
		  (int)(allbytes/(float)benchtime),
		  allspeed,
		  allfailed);
  
  return true;
}



//子线程的执行函数
void* sondo(void* p)
{
    //PROCESS process = *(PROCESS*)p;
    FILE *fp;
    int speed = 0;
    int fail = 0;
    int bytes = 0;
    TTTHREAD temp(speed,fail,bytes);
    if(process.proxyhost == "")
        process.benchcore(temp);
    else
        process.benchcore(temp);
    try
    {
        LOCK alock(process,temp);
    }catch(exception& e){
        cout << e.what()<<endl;
    }
    pthread_mutex_lock(&mutex2);
    process.clients --;
    pthread_mutex_unlock(&mutex2);
}

void PROCESS::benchcore(TTTHREAD& t)
{
    int rlen;
    char buf[1500];
    int fd,i;
    struct sigaction sa;

    sa.sa_handler = signalhandle;
    sa.sa_flags=0;
    if(sigaction(SIGALRM,&sa,NULL)) exit(3);
    alarm(benchtime);
    rlen=request.length();
nexttry:
    while(1)
    {
        //zzy:如果超时,就不给那个网站发数据了,也就是本分支的测试任务已经完成
        if(timerecpired)
        {
           if(allfailed>0)
            {
                pthread_mutex_lock(&mutex3);
                allfailed--;
                pthread_mutex_unlock(&mutex3);
            }
            return;
        }
        fd = mysocket(host,proxyport);                          
        
        //zzy:以下是各种发送出错情况
        if(fd<0) { 
            pthread_mutex_lock(&mutex3);
            allfailed++;
            pthread_mutex_unlock(&mutex3);
            continue;
        }
        if(rlen!=write(fd,request.c_str(),rlen)) {
            pthread_mutex_lock(&mutex3);
            allfailed++;
            pthread_mutex_unlock(&mutex3);
            close(fd);
            continue;
        }
        if(httpv==0) 
	        if(shutdown(fd,1)) {
                pthread_mutex_lock(&mutex3);
                allfailed++;
                pthread_mutex_unlock(&mutex3);
                close(fd);
                continue;
            }
       
        if(force==0) 
        {
	        while(1)
	        {
                if(timerecpired) break; 
	            i=read(fd,buf,1500);
	            if(i<0) 
                { 
                    pthread_mutex_lock(&mutex3);
                    allfailed++;
                    pthread_mutex_unlock(&mutex3);
                    close(fd);
                    //zzy:读失败了无所谓,进行下一次压力发送即可
                    goto nexttry;
                }
	            else if(i==0) break;
                //zzy:这里的bytes代表本分支一共接收到的bytes数量
                else t.bytes+=i;

	        }
        }
        close(fd);
       
        t.speed++;
    }
}


int mysocket(string host,int port)
{
    int connfd;
    struct sockaddr_in ser_addr;
    bzero(&ser_addr,sizeof(struct sockaddr_in));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(port);
    inet_aton(host.c_str(),&ser_addr.sin_addr);

    if((connfd = socket(AF_INET,SOCK_STREAM,0)) <= 0) return -1;
    if(connect(connfd,(struct sockaddr*)&ser_addr,sizeof(struct sockaddr)) < 0) return -2;
    return connfd;
}


void PROCESS::usage(void)
{
   fprintf(stderr,
	"webbench [option]... URL\n"
	"  -f|--force               Don't wait for reply from server.\n"
	"  -r|--reload              Send reload request - Pragma: no-cache.\n"
	"  -t|--time <sec>          Run benchmark for <sec> seconds. Default 30.\n"
	"  -p|--proxy <server:port> Use proxy server for request.\n"
	"  -c|--clients <n>         Run <n> HTTP clients at once. Default one.\n"
	"  -9|--http09              Use HTTP/0.9 style requests.\n"
	"  -1|--http10              Use HTTP/1.0 protocol.\n"
	"  -2|--http11              Use HTTP/1.1 protocol.\n"
	"  --get                    Use GET request method.\n"
	"  --head                   Use HEAD request method.\n"
	"  --options                Use OPTIONS request method.\n"
	"  --trace                  Use TRACE request method.\n"
	"  -?|-h|--help             This information.\n"
	"  -V|--version             Display program version.\n"
	);
};

