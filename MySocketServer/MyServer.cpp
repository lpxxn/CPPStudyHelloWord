#include<string>
#include<iostream>
#include<Windows.h>
#include<winsock.h>
//无法解析的外部符号 _socket@12 加上这个
#pragma comment(lib,"ws2_32.lib")
const int SRVER_PORT=8485;
const int MAX_ACCEPT=20;

void main(int argc, char *argv[]) 
{
	 WSADATA wsaDATA;
	 WORD sockVersion  = MAKEWORD(2,2);
	 if(WSAStartup(sockVersion,&wsaDATA)!=0)
	 {
		 std::cout << "Failed to retrive socket version." << std::endl;
		 std::cin.get();
		 exit(1);
	 }
	SOCKET sockfd;
	SOCKET client_fd;

	SOCKADDR_IN my_addr;
	SOCKADDR_IN remote_addr;

	int sin_size = 0;
	char * msg="欢迎登录！";
	if((sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET)
	{
		std::cout<<"socket create error\n"<<std::endl;
		std::cin.get();
		exit(1);
	}

	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(SRVER_PORT);
	my_addr.sin_addr.S_un.S_addr=INADDR_ANY;	
	int bindValue =bind(sockfd,(LPSOCKADDR)&my_addr,sizeof(my_addr));
	if(bindValue==-1)
	{
		std::cout<<"socket bind error\n"<<std::endl;
		std::cin.get();
		exit(1);
	}
	if(listen(sockfd,MAX_ACCEPT)==-1)
	{
		std::cout<<"socket listen error\n"<<std::endl;
		std::cin.get();
		exit(1);
		
	}
	std::cout<<"server runing....."<<std::endl;
	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);
		if((client_fd = accept(sockfd ,(struct sockaddr *)&remote_addr,&sin_size))==-1)
		{
			std::cout<<"socket accept error\n"<<std::endl;
			//std::cin.get();
			continue;
		}
		//send
		if(send(client_fd,msg,strlen(msg),0)==-1)
		{
			std::cout<<"socket accept error\n"<<std::endl;
			//std::cin.get();
			closesocket(client_fd);	
			exit(0);
		}
		closesocket(client_fd);
	}

	 //WSADATA wsaDATA;
	 //WORD sockVersion  = MAKEWORD(2,2);
	 //if(WSAStartup(sockVersion,&wsaDATA)!=0)
	 // std::cin.get();
	/* SOCKET sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	 if(sListen==INVALID_SOCKET)
	 {
		  printf("socket error \n");
		  std::cin.get();
	 }
	 sockaddr_in sin;
	 sin.sin_family = AF_INET;
	 sin.sin_port = htons(3999);
	 sin.sin_addr.S_un.S_addr = INADDR_ANY;
	 if( bind(sListen,(LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	 {
		  DWORD err = GetLastError();
		  printf("bind error:%d\n",err);
		  std::cin.get();
	 }
	  std::cin.get();*/
}