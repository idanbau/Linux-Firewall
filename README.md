# Linux-Firewall - drop any ping request
# installation:
# 1.make
# 2.sudo insmod ping_blocker.ko
# 3.check for any dropped ping requests: sudo dmesg -c
# 
# removal:
# sudo rmmod ping_blocker.ko