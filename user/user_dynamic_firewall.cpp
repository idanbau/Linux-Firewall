#include <unistd.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <exception>
#include "../shared/configuration.h"

void send_data(int fd, int option){
    Configuration config = {};
    config._outgoing = 0;
    config._port = 80;
    inet_pton(AF_INET, "10.100.102.74", &(config.ip_addr));
    std::cout << "current ip as number is:" << config.ip_addr << std::endl;
    // config.ip_addr = 3232295169;
    // strncpy(config._ip_addr, "10.0.0.8", 15);
    // struct sockaddr_in sa;
    // std::cout << "please choose 0 for recieving, 1 for sending and 2 for both:" << std::endl;
    // Configuration config;
    // std::cin >> config._outgoing;
    // std::string ip;//to avoid buffer overflow
    // std::getchar();
    // std::cout << "please choose an ip address to block" << std::endl;
    // std::getline(std::cin, ip);
    // strncpy(config._ip_addr, ip.c_str(), sizeof(config._ip_addr));
    // if(inet_pton(AF_INET, config._ip_addr, &(sa.sin_addr)) != 1){
    //     exit(EXIT_FAILURE);
    // }

    // std::cout << "please choose a port to block" << std::endl;
    // std::cin >> config._port;
    // std::getchar();
    // getchar();
    if (ioctl(fd, MY_IOCTL_IN, &config) == -1)
    {
        perror("send data error at ioctl");
    }
}

int main(){
    const char *file_name = "/dev/my_firewall_device"; //used by ioctl
    int fd;
    fd = open(file_name, O_RDWR);
    if(fd == -1){
        throw std::runtime_error("Failed to open ioctl");
    }
    std::cout << "Welcome to firewall app" << std::endl;
    std::cout << "This tool aim to block connections" << std::endl;
    std::cout << "Please choose 1 to add block, 2 to remove block, 3 to exit: " << std::endl;
    int option = 0;
    std::cin >> option;
    while(option != 3){
        if(option == 1)
            send_data(fd, option);
        std::cout << "Please choose 1 to add block, 2 to remove block, 3 to exit: " << std::endl;
        std::cin >> option;
    }
    close (fd);
    return 0;
}