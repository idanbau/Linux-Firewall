# Linux-Firewall - drop any ping request - made by Idan Baumer

## Installation:
 1.make
 2.sudo insmod ping_blocker.ko
 3.check for any dropped ping requests: sudo dmesg -c
 
## Removal:
 sudo rmmod ping_blocker.ko
 
## License:
 GNU General Public License v3.0
