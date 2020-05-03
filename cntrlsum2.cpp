#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main(int argc, char* argv[]) {
	ifstream file;
	file.open(argv[1]);
	int i;
	MD5_CTX md5handler;
	unsigned char md5digest[MD5_DIGEST_LENGTH];
	string str;
        getline(file,str);
	int size = str.length();
	MD5_Init(&md5handler);
	const void *data;
	data = str.c_str();
	MD5_Update(&md5handler,data,size);
	MD5_Final(md5digest,&md5handler);
	for (i=0;i<MD5_DIGEST_LENGTH;i++) {
		printf("%02x",md5digest[i]);
	};
	printf("\n");
	exit(1);
}
