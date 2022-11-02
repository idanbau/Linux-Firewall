# Linux-Firewall - drop any request according to user option (in/ or out ip or port)
# installation:
# 1.make
# 2.sudo insmod ping_blocker.ko
# 3. "./user_dynamic_firewall {1 or 2 for input / output} {ip_address number} {port}
# 4.check for any dropped requests: sudo dmesg -c
# 
# removal:
# sudo rmmod ping_blocker.ko