#include "network.c"
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/icmp.h>


#include "../../shared/configuration.h"
#include <linux/fs.h>
#include <linux/cdev.h>


#define MY_MAJOR       42
#define MY_MAX_MINORS  5
#define DEVICE_NAME "my_firewall_device"
#define CLASS_NAME "my_firewall_class"

static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
int user_communication_init(void);
void user_communication_exit(void);


struct class* charClass;
int majorNumber;

const struct file_operations my_fops = {
    .owner = THIS_MODULE,
    // .open = my_open,
    // .read = my_read,
    // .write = my_write,
    // .release = my_release,
    .unlocked_ioctl = my_ioctl
};

struct my_device_data {
    struct cdev cdev;
    Configuration Configuration;
    //...
};

struct my_device_data devs[MY_MAX_MINORS];




static long my_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
    printk(KERN_INFO "in my_ioctl\n");
    printk(KERN_INFO "cmd %u\n", cmd);
    struct my_device_data *my_data =
         (struct my_device_data*) file->private_data;
    Configuration config;

    switch(cmd) {
    case MY_IOCTL_IN:
        printk(KERN_INFO "in MY_IOCTL_IN\n");
        unsigned bytes_not_copied = copy_from_user(&config, (Configuration*) arg,
                           sizeof(Configuration));
        if (bytes_not_copied != 0)
        {
            printk(KERN_INFO "failed_to_copy from user %x\n", bytes_not_copied);
            return -EFAULT;
        }
        /* process data and execute command */
        setBlock(&config);
        break;
    default:
        printk(KERN_INFO "case default failed to reciveve from user\n");
        return -ENOTTY;
    }
    printk(KERN_INFO "My ioctl success");
    return 0;
}

int user_communication_init(void){
    int network_status = network_init();
    if(network_status != 0){
        printk("Error in loading the network: %d\n", network_status);
        return network_status;
    }
    majorNumber = register_chrdev(0, DEVICE_NAME, &my_fops);
    if (majorNumber < 0)
    {
        printk(KERN_ALERT "failed to register a major number\n");
        return majorNumber;
    }
    printk(KERN_INFO "Char: registered correctly with major number %d\n", majorNumber);

   // Register the device class
    charClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(charClass))
    {                // Check for error and clean up if there is
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(charClass);          // Correct way to return an error on a pointer
}
   printk(KERN_INFO "Char: device class registered correctly\n");

   // Register the device driver
   struct device* charDevice = device_create(charClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
   if (IS_ERR(charDevice)){               // Clean up if there is an error
      class_destroy(charClass);           // Repeated code but the alternative is goto statements
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to create the device\n");
      return PTR_ERR(charDevice);
   }
    return 0;
}

void user_communication_exit(void){
    device_destroy(charClass, MKDEV(majorNumber, 0));     // remove the device
    class_unregister(charClass);                          // unregister the device class
    class_destroy(charClass);                             // remove the device class
    unregister_chrdev(majorNumber, DEVICE_NAME);             // unregister the major number
    network_exit();
}