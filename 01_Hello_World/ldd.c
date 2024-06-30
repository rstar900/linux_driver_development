#include <linux/init.h>
#include <linux/module.h>

// Macros for module info (can be seen using modinfo ldd.ko)
MODULE_LICENSE("GPL"); // Without this the kernel won't even accept the module
MODULE_AUTHOR("RG - Rachit Garg");
MODULE_DESCRIPTION("My first dynamically loadable kernel module 😎");

// Constructor
static int rg_kmod_init(void)
{
    printk("RG says Hello Linux Kernel 😇\n");
    return 0;
}

// Destructor
static void rg_kmod_exit(void)
{
    printk("RG says Goodbye! 🫡\n");
}

// Macros for telling compiler, constructors and destructors for our kernel module
module_init(rg_kmod_init);
module_exit(rg_kmod_exit);
