#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Idan Baumer");
MODULE_DESCRIPTION("An example of linux firewall.");
MODULE_VERSION("1.00");

struct nf_hook_ops HOOK_OPTIONS = {0};

unsigned int my_firewall(void *priv,
                          struct sk_buff *skb,
                          const struct nf_hook_state *state)
{
    printk(KERN_INFO "Packet Recieved\n");
    return NF_ACCEPT;
}


static int __init lkm_example_init(void) 
{
    printk(KERN_INFO "Hello, World!\n");     

    HOOK_OPTIONS.hook = (nf_hookfn*)my_firewall;
    HOOK_OPTIONS.dev = NULL;
    HOOK_OPTIONS.pf = NFPROTO_IPV4;
    HOOK_OPTIONS.hook_ops_type = NF_HOOK_OP_NF_TABLES;
    HOOK_OPTIONS.hooknum = NF_INET_LOCAL_IN;
    HOOK_OPTIONS.priority = NF_IP_PRI_FIRST;
    int result = nf_register_net_hook(&init_net, &HOOK_OPTIONS);

    printk(KERN_INFO "nf_register_net_hook Result: %d \n", result);
    return 0;
}

static void __exit lkm_example_exit(void) 
{
    printk(KERN_INFO "Goodbye, World!\n");
    nf_unregister_net_hook(&init_net, &HOOK_OPTIONS);
}


module_init(lkm_example_init);
module_exit(lkm_example_exit);
