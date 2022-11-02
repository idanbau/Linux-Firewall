#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/icmp.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Idan Baumer");
MODULE_DESCRIPTION("An example of linux firewall.");
MODULE_VERSION("1.00");

/**
 * @brief callback to check if packet is of ping type, if it is - drop it 
 * 
 * @param skb holds packet data
 * @return unsigned int action to do of current packet, accept or drop
 */
static unsigned int ping_callback_blocker(void *,
                                          struct sk_buff *skb,
                                          const struct nf_hook_state *);

/**
 * @brief init module with appropriate settings and callback function
 * 
 * @return int result of integration in kernal 
 */
static int __init firewall_module_init(void);

/**
 * @brief disconnect kernal module
 * 
 */
static void __exit firewall_module_exit(void);

struct nf_hook_ops HOOK_OPTIONS = {0};

module_init(firewall_module_init);
module_exit(firewall_module_exit);


static unsigned int ping_callback_blocker(void *,
                          struct sk_buff *skb,
                          const struct nf_hook_state *)
{
    struct iphdr *iph;   // IP header
    struct icmphdr *icmph; // icmp packet information
    if(skb == NULL){
        return NF_ACCEPT;
    }
    iph = ip_hdr(skb);
    if(iph->protocol == IPPROTO_ICMP){
        icmph = icmp_hdr(skb);
        if(icmph->type == ICMP_ECHO)
        {
            printk(KERN_INFO "Ping Dropped from %pI4\n", &iph->saddr);
            return NF_DROP;
        }
    }
    return NF_ACCEPT;
}


static int __init firewall_module_init(void) 
{
    int result;
    HOOK_OPTIONS.hook = (nf_hookfn*)ping_callback_blocker;
    HOOK_OPTIONS.dev = NULL;
    HOOK_OPTIONS.pf = NFPROTO_IPV4;
    HOOK_OPTIONS.hook_ops_type = NF_HOOK_OP_NF_TABLES;
    HOOK_OPTIONS.hooknum = NF_INET_LOCAL_IN;
    HOOK_OPTIONS.priority = NF_IP_PRI_FIRST;
    result = nf_register_net_hook(&init_net, &HOOK_OPTIONS);
    result == 0 ? printk(KERN_INFO "Kernal loaded successfuly!\n") :
     printk(KERN_INFO "nf_register_net_hook failed, result: %d \n", result);     
    return result;
}

//close module and finish
static void __exit firewall_module_exit(void) 
{
    nf_unregister_net_hook(&init_net, &HOOK_OPTIONS);
    printk(KERN_INFO "module removed!\n");
}
