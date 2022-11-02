#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include "../../shared/configuration.h"

static unsigned int callback_blocker(void *,
                          struct sk_buff *skb,
                          const struct nf_hook_state *);



struct nf_hook_ops HOOK_OPTIONS = {};

Configuration config = {0};

static unsigned int callback_blocker(void *,
                          struct sk_buff *skb,
                          const struct nf_hook_state *)
{
    struct iphdr *iph;   // IP header
    struct tcphdr* tcp_h;
    if(skb == NULL){
        return NF_ACCEPT;
    }
    iph = ip_hdr(skb);
    if(iph == NULL){
        return NF_ACCEPT;
    }
    if(iph->saddr == config.ip_addr){
        printk(KERN_INFO "current ip address is %u\n", iph->saddr);
        if(iph->protocol == IPPROTO_TCP){
            tcp_h = tcp_hdr(skb);
            if(tcp_h == NULL){
                return NF_ACCEPT;
            }
            printk(KERN_INFO "tcp dest port: %d tcp src port: %d\n", cpu_to_be16(tcp_h->dest));
            if(cpu_to_be16(tcp_h->dest) == config._port){
                return NF_DROP;
            }
        }
    }
    return NF_ACCEPT;
}



int network_init(void){
    int result;
    HOOK_OPTIONS.hook = (nf_hookfn*)callback_blocker;
    HOOK_OPTIONS.dev = NULL;
    HOOK_OPTIONS.pf = NFPROTO_IPV4;
    HOOK_OPTIONS.hook_ops_type = NF_HOOK_OP_NF_TABLES;
    HOOK_OPTIONS.hooknum = NF_INET_LOCAL_IN;
    HOOK_OPTIONS.priority = NF_IP_PRI_FIRST;
    result = nf_register_net_hook(&init_net, &HOOK_OPTIONS);
    result == 0 ? printk(KERN_INFO "Connection worked!\n") :
    printk(KERN_INFO "nf_register_net_hook failed, result: %d \n", result);     
    return result;
}

void setBlock(const Configuration* block_config){
    config.ip_addr = block_config->ip_addr;
    config._outgoing = block_config->_outgoing;
    config._port = block_config->_port;
}

void network_exit(void){
    nf_unregister_net_hook(&init_net, &HOOK_OPTIONS);
    printk(KERN_INFO "module removed!\n");
}