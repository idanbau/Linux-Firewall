#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "include/communication.c"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Idan Baumer");
MODULE_DESCRIPTION("An example of linux firewall.");
MODULE_VERSION("1.00");

static int __init firewall_module_init(void);
static void __exit firewall_module_exit(void);

module_init(firewall_module_init);
module_exit(firewall_module_exit);

static int __init firewall_module_init(void) 
{
    printk(KERN_INFO "Starting firewall_module_init\n");
    
    printk(KERN_INFO "Char: device class created correctly\n"); // Made it! device was initialized
    return user_communication_init();
}

//close module and finish
static void __exit firewall_module_exit(void) 
{
   user_communication_exit();
   printk(KERN_INFO "char: Goodbye from the LKM!\n");
}
