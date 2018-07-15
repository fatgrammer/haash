#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/select.h>
#include <sys/time.h>

#include <unistd.h>
#include <futils.h>

int main(int argc, char **argv) {
  int c;
  while ( (c = getopt(argc, argv, "c") ) != -1) {
    print(c);
  }
  
}
