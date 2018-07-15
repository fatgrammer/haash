#include <iostream>
#include <string>
#include <algorithm>

#include <cstring>

#include <cassert>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/select.h>
#include <sys/time.h>

#include <futils.h>
#include <tcp_connection.h>


void con();
void serv();
void read_fd(int);
int main(int argc, char **argv) {

  if(argc <= 1) {
    std::cerr << "no args" << std::endl;
    return 0;
  } else if (strcmp("c", argv[1]) == 0) {
    con();
  } else if (strcmp("s", argv[1]) == 0) {
//  serv();
    TcpServer server;
    server.run([&server](int fd){server.echo(fd);});
  } else {
    std::cerr << "sth else" <<std::endl;
  }
}
void str_cli(FILE *fp, int sockfd) {
  constexpr int MAX = 1024;
  int maxfdp1;
  fd_set rset;
  char sendline[MAX], recvline[MAX];
  FD_ZERO(&rset);
  for (;;) {
    FD_SET(fileno(fp), &rset);
    FD_SET(sockfd,&rset);
    maxfdp1 = std::max(fileno(fp), sockfd) + 1;
    print("pre block");
    select(maxfdp1, &rset, NULL, NULL, NULL);
    print("post block");
    if (FD_ISSET(sockfd, &rset)) {
      int n = read(sockfd, recvline, MAX); 
      recvline[n] = 0;
      puts(recvline);
      //FD_CLR(sockfd, &rset);
    }
    if (FD_ISSET(fileno(fp), &rset)) {
      if (fgets(sendline, MAX, fp) == NULL)
        return;
      int n =  write(sockfd, sendline, strlen(sendline));
      assert(n >= 0 && "connection fail");
      //FD_CLR(fileno(fp), &rset);
    }
  }
}
void con(){
  int sfd;
  if ( (sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    assert(0 && "socket error");
  }
  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(9090);
  if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
    assert(0 && "inet_pton error");
  }
  if (connect(sfd, (sockaddr*) &servaddr, sizeof(servaddr)) < 0) { 
    assert(0 && "connect error");
  }
 // std::string ss = "hahahahahaha";
  //write(sfd, ss.c_str(), ss.length());
  constexpr int MAXLINE = 10;
  char recvline[MAXLINE + 1];
  //int n;
 /* 
  while (  fgets(recvline, MAXLINE, stdin) != NULL) {
    //recvline[n] = 0;
    //if (fputs(recvline, stdout) == EOF){
    //  assert(0 && "fputs error");
    //}
    //
    write(sfd, recvline, strlen(recvline));
    int n = read(sfd,recvline, MAXLINE);
    recvline[n] = '\0';
    print("prepare to put");
    puts(recvline);
  }
  */
  str_cli(stdin,sfd);
  print("transfer suc");
  //read_fd(sfd);
 // if (n < 0) {
 //   assert(0 && "read error");
 // }
  close(sfd);
  exit(0);
}
void read_fd(int fd){
  int n;
  constexpr int MAXLINE = 1024;
  char recvline[MAXLINE + 1];
  while ( ( n = read(fd, recvline, MAXLINE)) > 0 ) {
    recvline[n] = 0;
    if (fputs(recvline, stdout) == EOF) {
      assert( 0 && "fputs error");
    }
  }
}
void serv() {
  int lfd;
  lfd = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in servaddr;

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(13);
  bind(lfd, (sockaddr *) &servaddr, sizeof(servaddr));
  listen(lfd, 1023);
  int cfd;
///  time_t ticks;
  char buff[1024+1];
  puts("haha");
  for (;;) {
    cfd = accept(lfd, (sockaddr *) NULL, NULL);
//    ticks = time(NULL);
//    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
    read_fd(lfd);
    write(cfd, buff, strlen(buff));
    close(cfd);
  }
}
