/* UDP Log server for logging communication to echo.log
   Written by James Speights*/
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <fcntl.h>
void     INThandler(int);
void error(const char *msg) {
     perror(msg);
     exit(1);
}

//waits with no hang to prevent zombie processes
void SigCatcher(int n) {
     wait3(NULL,WNOHANG,NULL);
}

//logs char array to file
void log2file(char buff[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("%d-%d-%d %d:%d:%d\t%s\n",
              tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
              tm.tm_hour, tm.tm_min, tm.tm_sec, buff);
}
void  INThandler(int sig)
{
     char  c;

     signal(sig, SIG_IGN);
     printf("Did you hit Ctrl-C?\n"
            "Do you really want to quit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y')
          exit(0);
     else
          signal(SIGINT, INThandler);
     getchar(); // Get new line character
}

int main(int argc, char *argv[]) {
<<<<<<< HEAD
     int sockfd, portno = 9999;
=======
     signal(SIGINT, INThandler);
     int sockfd, portno;
>>>>>>> bd8b5f77cc937d186d138561db1606732199cdcc
     int buffer_length = 256;
     char buffer[buffer_length];
     struct sockaddr_in serv_addr;
     int n, pid;
     if(argv.length == 3){
	if(argv[1] == '-path';{
     		int portno = atoi(argv[2]);
	}
     }

     //catches SIGCHLD signal (child dies) and calls SigCatcher
     signal(SIGCHLD,SigCatcher);

     //init socket
     sockfd = socket(AF_INET, SOCK_DGRAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");

     //hard-coded port for server -> log_server communication


     //init server details
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
          error("ERROR on binding");

     //changes stdout to output to this file
     int log_fd = open("echo.log", O_RDWR | O_CREAT, S_IRUSR);
     dup2(log_fd, 1);

     int length;

     //loop to accept clients and fork
     while(1) {
          bzero(buffer,buffer_length);
          length = recvfrom(sockfd, buffer,
                      sizeof(buffer) - 1,
                      0, NULL, 0);
          if (length < 0)
               error("ERROR on recv");
          if ((pid = fork()) == 0) { //child process
               buffer[length] = '\0';
               log2file(buffer);
               exit(0);
          }
          length = -1; //parent process
     }
     console.log("echo_s is stopping");
     close(sockfd);
     return 0;
}
