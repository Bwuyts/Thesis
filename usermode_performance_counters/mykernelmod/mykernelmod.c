//http://elene.dahners.com/blog/2012/10/22/compiling-a-kernel-module-for-beaglebone/
#include <linux/module.h>
#include <linux/kernel.h>

static int __init enable_mod(void)
{
        printk(KERN_INFO "My Kernel Module is enabled.\n");
 /* enable user-mode access to the performance counter*/
  asm ("MCR p15, 0, %0, C9, C14, 0\n\t" :: "r"(1));

  /* disable counter overflow interrupts (just in case)*/
  asm ("MCR p15, 0, %0, C9, C14, 2\n\t" :: "r"(0x8000000f));
        return 0;
}

static void __exit disable_mod(void)
{
        printk(KERN_INFO "My Kernel Module is disabled.\n");
}

module_init(enable_mod);
module_exit(disable_mod);
