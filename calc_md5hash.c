#include<stdio.h>
#include<fcntl.h>
#include<openssl/md5.h>

int main(int argc,char **argv){
    
    const int BUFLEN = 1024;
    unsigned char buf[BUFLEN];
    const char *filename = argv[1];
    int fd = -1;

    if(argc != 2){
        printf("Specify filename\n");
        return -1;
    }
    
    fd = open(filename,O_RDONLY);
    if(fd < 0){
        printf("Failed to open file:%s\n",filename);
        return -1;
    }
    
    int bytes = 0;
    unsigned char hashVal[MD5_DIGEST_LENGTH];
    MD5_CTX context;
    MD5_Init(&context);
    while((bytes = read(fd,buf,BUFLEN)) != 0){
        MD5_Update(&context,buf,bytes);
    }
    MD5_Final(hashVal,&context);
    for(int i=0; i < MD5_DIGEST_LENGTH;i++){
        printf("%02x",hashVal[i]);
    }
    printf("\n");
    close(fd);
}
