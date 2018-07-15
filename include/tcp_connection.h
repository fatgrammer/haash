#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>

#include <cstring>
#include <cassert>

#include <functional>
#include <string>
#include <futils.h>

class TcpServer {
public:
  TcpServer(int port = 9090):listen_fd_(0) {
    bzero(&servaddr_, sizeof(servaddr_));
    servaddr_.sin_family = AF_INET;
    servaddr_.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr_.sin_port = htons(port);
    //init 
    listen_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    assert(listen_fd_ > 0);
    bind(listen_fd_, (sockaddr *) &servaddr_, sizeof(servaddr_));
    listen(listen_fd_, 1024);
  }
  void run(std::function<void(int)> func) {
    for (;;) {
      int tfd = accept(listen_fd_, static_cast<sockaddr *>(nullptr), NULL);
      print("accept suc");
      assert(tfd > 0);
      func(tfd);
      close(tfd);
    }
  }
  void echo(int fd){
    int n;
    char recvline[1024];
    while ( (n = read(fd, recvline, 1024)) > 0) {
    print("echo");
      recvline[n] = 0;
      //assert( fputs(recvline, stdout) == EOF && "fputs error");
      if (fputs(recvline, stdout) == EOF) {
        assert(0 && "fputs error");
      }
      write(fd, recvline, n);
    }
    
  }
private:
  int listen_fd_;
  sockaddr_in servaddr_;
};


