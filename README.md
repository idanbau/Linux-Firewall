# Linux-Firewall - drop any request according to user option (in/ or out ip or port)
## installation:
1.terminal inside new installation:
2.make
3.sudo insmod kernel/kernel_dynamic_firewall.ko
4. "./user_dynamic_firewall {1 or 2 for input / output} {ip_address number} {port}
5.check for any dropped requests: sudo dmesg -c 
# to-do:
enable blocking of output packets, enable udp support (currently just tcp)
#ping blocker module is also included
# removal:
sudo rmmod kernel_dynamic_firewall.ko
