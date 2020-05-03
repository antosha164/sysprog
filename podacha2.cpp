#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

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

int main()
{
    pid_t v;
    int i;
    int status = 0;
    cout<<"\t\nThis programm calculate checksum for files in current directory: "<<endl;
    const char *argv, *progname="/lab4/cntrlsum2";
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
    cout<<"\nNumber of files: "<<size_v<<endl;
    while (size_v > 0)
	{
		argv = files[i].c_str();
		v = fork();
		switch(v)
		{
			case -1:
				cout<<"Can't fork"<<endl;
			case 0:
				cout<<"The PID of Child is: "<<getpid()<<endl;
				sleep(1);
				cout<<"Checksum of file "<<files[i]<<" is: "<<endl;
				execl("cntrlsum2", progname, argv, NULL);
			default:
				cout<<"\nThe PID of parent is: "<<getpid()<<endl;
				wait(&status);
				cout<<"Exit status is: "<<WEXITSTATUS(status)<<endl;
				if (WEXITSTATUS(status) == 1)
				{
					++i;
					--size_v;
				}
		}
	}
    cout<<"\t\nComplete! "<<i<<" checksums are calculated! "<<endl;
    return 0;
}
