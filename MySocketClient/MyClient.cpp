#include<Windows.h>
#include<winsock.h>
#include<iostream>
#include<string>

#define SERVPORT 8485
#define MAXDATASIZE 100
#pragma comment(lib,"ws2_32.lib")
BOOL InitSocket()
{
	 //¼ÓÔØÌ×½Ó×Ö¿â
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD( 1, 1 );
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) 
    {
        return FALSE;
    }

    if ( LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1 ) 
    {
        WSACleanup( );
        return FALSE;
    }

    return TRUE;
}

void main(int argc,char *argv[])
{
	if(!InitSocket())
	{
		std::cout<<"init socket error "<<std::endl;
	}

	int sockClient ,recvbytes;
	char mybuf[MAXDATASIZE]={0};

	hostent *host;

	sockaddr_in serv_addr;

	/*if(argc<2)
	{
		std::cout<<"please enter the server's hostname!"<<std::endl;
		std::cin.get();
		exit(1);
	}

	if((host=gethostbyname(argv[1]))==NULL)
	{
		std::cout<<"gethostbyname error!"<<std::endl;
		std::cin.get();
		exit(1);
	}*/
	sockClient=socket(AF_INET,SOCK_STREAM,0);
	if(sockClient==-1)
	{
		std::cout<<"create socket error!"<<std::endl;
		std::cin.get();
		exit(1);
	}
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERVPORT);
	serv_addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	if(connect(sockClient,(SOCKADDR*)&serv_addr,sizeof(SOCKADDR))==-1)
	{
		std::cout<<"connect socket error!"<<std::endl;
		std::cin.get();
		exit(1);
	}
	send(sockClient,"hello server",strlen("hello server")+1,0);
	if((recv(sockClient,mybuf,MAXDATASIZE,0))==-1)
	{
		std::cout<<"recv msg error!"<<std::endl;
		std::cin.get();
		exit(1);
	}
	std::cout<<mybuf<<std::endl;
	std::cin.get();
}