#include "ros/ros.h"
#include <stdio.h>
#include<iostream>
#include <sys/ioctl.h> // For FIONREAD
#include <termios.h>
#include <stdbool.h>
#include <fstream>
    

int kbhit(void) {
    static bool initflag = false;
    static const int STDIN = 0;

    if (!initflag) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initflag = true;
    }

    int nbbytes;
    ioctl(STDIN, FIONREAD, &nbbytes);  // 0 is STDIN
    return nbbytes;
}


#include <unistd.h>

int main( int argc, char* argv[] )
{
      ros::init(argc, argv, "f_log");
      
       ros::NodeHandle n;
      std::ofstream myfile;
      char c;
      
      myfile.open ("example.csv");
      printf("Press key");
    while (!kbhit()) {
        //printf(".");
        //fflush(stdout);
        std::cout<<"\t"<<int(c)<<std::endl;
        myfile<<c<<"\n";
        sleep(2);
    c=getchar();
    }   
     myfile.close();
      return 0;
}
