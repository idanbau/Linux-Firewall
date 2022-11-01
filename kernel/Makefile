
obj-m +=  kernel_dynamic_firewall.o
ccflags-y := -Iinclude
files := communication.c network.c
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
