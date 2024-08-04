#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

// Macros for module info (can be seen using modinfo ldd.ko)
MODULE_LICENSE("GPL"); // Without this the kernel won't even accept the module
MODULE_AUTHOR("RG - Rachit Garg");
MODULE_DESCRIPTION("My dynamically loadable kernel module 😎");

static struct proc_dir_entry *pde = NULL;

// Our implementation of read (right now only in kernel space)
static ssize_t rg_mod_read(struct file *, char __user *, size_t, loff_t *)
{
    printk("rg_mod_read: Enter\n");
    return 0;
}

// We link the proc_read function pointer member variable to our implementation here
struct proc_ops pops = {.proc_read = rg_mod_read}; 

// Constructor
static int rg_kmod_init(void)
{
    printk("rg_kmod_init: Enter\n");

    // Create an entry in /proc directory with the name rg_mod (hence: /proc/rg_mod)
    // The last parameter (proc_ops struct pointer) cannot be left as NULL 
    // as that causes error while inserting the module in kernel
    // leaving it in an unstable state, requiring a reboot to recover
    pde = proc_create("rg_mod", 0, NULL, &pops);

    printk("rg_kmod_init: Exit\n");
    return 0;
}

// Destructor
static void rg_kmod_exit(void)
{
    printk("rg_kmod_exit: Enter\n");

    // Removing the proc entry made in init
    proc_remove(pde);

    printk("rg_kmod_exit: Exit\n");
}

// Macros for telling compiler, constructors and destructors for our kernel module
module_init(rg_kmod_init);
module_exit(rg_kmod_exit);
