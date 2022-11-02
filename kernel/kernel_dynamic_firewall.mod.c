#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xc4162456, "module_layout" },
	{ 0xef58c4c6, "class_unregister" },
	{ 0x7ebe1016, "device_destroy" },
	{ 0xdb8c13c, "class_destroy" },
	{ 0x3b1038f3, "device_create" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xe72972aa, "__class_create" },
	{ 0xfd059f5d, "__register_chrdev" },
	{ 0x8f8ae7ea, "nf_unregister_net_hook" },
	{ 0xe1a94e6c, "nf_register_net_hook" },
	{ 0x221cc46f, "init_net" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "0C29BFA2F49C8C5714B926A");
