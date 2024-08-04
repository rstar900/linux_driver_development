#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

// Macros for module info (can be seen using modinfo ldd.ko)
MODULE_LICENSE("GPL"); // Without this the kernel won't even accept the module
MODULE_AUTHOR("RG - Rachit Garg");
MODULE_DESCRIPTION("My dynamically loadable kernel module 😎");

static struct proc_dir_entry *pde = NULL;

// Our implementation of read 
static ssize_t rg_mod_read(struct file * file, char __user *user_data_buffer, size_t, loff_t *offset)
{
    printk("rg_mod_read: Enter\n"); 

    // The string we want to pass when our driver is read from user space
    char* read_string = "RG Mod is Awesome!!!!\n";
    size_t str_len = strlen(read_string); // We don't need string.h for this here

    // Only proceed reading if offset is not equal to string size (if so we have already read the string before)
    if (*offset != str_len)
    {
        size_t bytes_not_read = 0;
        
        // This reurns 0 if all bytes are read, else the number of remaining bytes
        if ((bytes_not_read = copy_to_user(user_data_buffer, read_string + *offset, str_len)) == 0)
        {
            printk("rg_mod_read: Read Complete!!!!\n");
            *offset += str_len;
            return str_len; // In this case we would have read the whole string hence it's length
        }
        else
        {
            // In this case only the bytes read need to be returned
            size_t bytes_read =  str_len - bytes_not_read;
            printk("rg_mod_read: %ld Bytes left to read\n", bytes_read);
            *offset += bytes_read;
            return bytes_read;
        }
    }

    // This will anyways happen if the above condition is false and our read succeeded already
    printk("rg_mod_read: Exit\n");
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
