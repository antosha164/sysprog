#include <iostream>
#include <openssl/md5.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

unsigned char result[256];
void error(const char *msg)
{
        perror(msg);
        exit(1);
}
int checksum (char* buffer,unsigned  char* result)
{
        int i;
        MD5_CTX md5handler;
        unsigned char md5digest[MD5_DIGEST_LENGTH];
        string str;
        str = (string)buffer;
        int size = str.length();
        MD5_Init(&md5handler);
        const void *data;
        data = str.c_str();
        MD5_Update(&md5handler,data,size);
        MD5_Final(md5digest,&md5handler);
        for (i=0;i<MD5_DIGEST_LENGTH;i++) {
                result[i] =  md5digest[i];
        };
        return MD5_DIGEST_LENGTH;
}
int main(int argc, char *argv[])
{
int sockfd, newsockfd, portno;
socklen_t clilen;
char buffer[256];
struct sockaddr_in serv_addr, cli_addr;
int n, size;
if (argc < 2)
{
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
}
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0)
        error("ERROR opening socket");
bzero((char *) &serv_addr, sizeof(serv_addr));
portno = atoi(argv[1]);
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);
if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
                error("ERROR on binding");
listen(sockfd,5);
clilen = sizeof(cli_addr);
newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
if (newsockfd < 0)
        error("ERROR on accept");
bzero(buffer,256);
n=recv(newsockfd,buffer,255, 0);
size = checksum(buffer,result);
if (n < 0) error("ERROR reading from socket");
printf("Recieved data: %s\n",buffer);
n=send(newsockfd, result, size, 0);
cout<<"MD5 checksum is already send!"<<endl;
if (n < 0) error("ERROR writing to socket");
close(newsockfd);
close(sockfd);
return 0;
}