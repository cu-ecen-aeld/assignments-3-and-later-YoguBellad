#include <stdio.h>
#include <string.h>
#include <syslog.h>
int main(int argc, char* argv[]){

    int rc = 0;
    openlog(NULL,0,LOG_USER);
    // printf("argc %i\t argv[0]:%s argv[1]:%s argv[2]:%s",argc, argv[0],argv[1],argv[2]);
    // syslog(LOG_DEBUG,"Writing abdcefg");
    // syslog(LOG_DEBUG,"Writing abdcefg");
    // syslog(LOG_ERR,"Writing abdcefg");
    if(argc == 3){
        char* writefile=argv[1];
        char* writestr=argv[2];

        FILE *fp = fopen(writefile, "w");
        if(fp == NULL){
            rc = 1;
            syslog(LOG_ERR,"Unable to open file");
            return 1;
        }
        else{
            int charCountWritten = fprintf(fp, "%s", writestr);
            if(charCountWritten!=strlen(writestr)){
                rc = 1;
                syslog(LOG_ERR,"Unable to write file");
                return 1;
            }
            syslog(LOG_DEBUG,"Writing %s to %s",writestr,writefile);
        }

    }
    else
        return 1;
    return rc;
}