#include <pthread.h>
#include <mutex>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <iostream>
#include <openssl/md5.h>
#include <fstream>

using namespace std;

mutex mut;

struct thread_data
{
	char* in;
};

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

void *cntrlsum(void *threadarg)
{
	int i;
	struct thread_data *my_data;
	my_data = (struct thread_data *) threadarg;
	ifstream file;
	file.open(my_data->in);
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
	{
	const lock_guard<mutex> lock(mut);
	cout<<"PID: "<<getpid()<<endl;
	cout<<"TID: "<<pthread_self()<<endl;
	cout<<"MD5 checksum " << my_data->in <<": ";
	for (i=0;i<MD5_DIGEST_LENGTH;i++) {printf("%02x",md5digest[i]);};
	cout<<"\n"<<endl;
	}
	pthread_exit(NULL);
}

int main()
{
    int i;
    void *status;
    cout<<"\t\nThis programm calculate checksum for files in current directory: "<<endl;
    string dir = string(".");
    vector<string> files = vector<string>();
    getdir(dir,files);
    for (i = 0;i < files.size();++i) {
	if((files[i] == ".") || (files[i] == "..") )
		files.erase(files.begin() + i);
    }
    cout<<"\nFiles: "<<endl;
    for (i = 0;i < files.size();++i) {
        cout << files[i] << endl;
    }
    i = 0;
    int size_v = files.size();
    cout<<"\nNumber of files: "<<size_v<<"\n"<<endl;
    pthread_t threads[size_v];
    for (i=0; i<size_v;++i) {pthread_create(&threads[i],NULL,cntrlsum,(void*)&files[i]);}
    for (i=0;i<size_v;++i) {pthread_join(threads[i],&status);}
    return 0;
}

