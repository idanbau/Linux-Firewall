#ifndef CONFIGURATION_H
#define CONFIGURATION_H

typedef struct {
    int _outgoing;
    unsigned int ip_addr;
    unsigned short _port;
} Configuration;

#define MY_IOCTL_IN _IOC(_IOC_WRITE, 'k', 1, sizeof(Configuration))

#endif
