#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <exception>
#include "../shared/configuration.h"

void send_data(int fd, std::string ip_addr, std::string port){
    int convert_result;
    Configuration config = {};
    config._outgoing = 0;
    config._port = std::stoi(port);
    convert_result = inet_pton(AF_INET, ip_addr.c_str(), &(config.ip_addr));
    if(convert_result != 1){
        throw std::invalid_argument("invalid ip address");
    }
    if (ioctl(fd, MY_IOCTL_IN, &config) == -1){
        throw std::runtime_error("send data error at ioctl");
    }
}

int main(int argc, char** argv){
    const char *file_name = "/dev/my_firewall_device"; //used by ioctl
    int fd;
    if(argc != 4){
        throw std::runtime_error("ip address is missing");
    }
    fd = open(file_name, O_RDWR);
    if(fd == -1){
        throw std::runtime_error("Failed to open ioctl");
    }
    if(std::string(argv[1]) == "1")
        send_data(fd, argv[2], argv[3]);
    close (fd);
    return 0;
}