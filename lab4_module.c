#include <linux/module.h>     
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/proc_fs.h>

#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched.h>

//struct proc_dir_entry *proc_parent; 

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("E. O. KRIVOSHEEV");

#define TRUE 1
#define FALSE 0

static char * wtOperand1 = "nothing";
static char * wtOperand2 = "nothing";
static char * wtOperation = "nothing";


module_param (wtOperand1, charp, 0000);
module_param (wtOperand2, charp, 0000);
module_param (wtOperation, charp, 0000);

MODULE_PARM_DESC (wtOperand1, "Way to the Operand1 file");
MODULE_PARM_DESC (wtOperand2, "Way to the Operand2 file");
MODULE_PARM_DESC (wtOperation, "Way to the Operation file");

static int fRead (char * f_to_read, int flag)
{
	struct file *f;
        int pp;
        //char *endptr;
    	static char buff[256];
    	size_t n;

    	printk (KERN_ALERT "openning file: %s\n", f_to_read);
   	
        f = filp_open (f_to_read, O_RDONLY, 0);
   	
        if (!f) {
                printk(KERN_ALERT "file open failed: %s\n",f_to_read);
     	        return 1;    
   	}

  	n = kernel_read (f, 0, buff, 255);

    	if (kernel_read (f, 0, buff, 255)) {
   	     	buff[n] = 0;
       		printk (KERN_ALERT "read first %d bytes: %s\n", 255, buff);
   	} else {
                printk (KERN_ALERT "kernel_read failed\n");
  	} 

        //if (flag) {
        //        printk (KERN_ALERT "I'm bool flag!\n");
        //}
        //pp = simple_strtol(buff, NULL, 10);
        //kstrtol (buff, 10, &pp);
        //opl++;

        pp = (int)simple_strtol(buff, NULL, 10);
        pp++;

        if (flag) printk (KERN_ALERT "I'm flag!\n");

        printk(KERN_ALERT "int: %i\n", pp);
   	filp_close (f, current->files);
   	return 0;
}




static int __init modInit (void)
{
	/*proc_parent = proc_mkdir("lab4_modules",NULL) ;
	if(!proc_parent)
     	{
    		printk(KERN_INFO "Error creating proc entry");
    		return -ENOMEM;
    	}*/
    	fRead (wtOperand1, FALSE);
        fRead (wtOperand2, TRUE);
        //fRead (wtOperation);
	printk (KERN_ALERT "Hello, I'm a calculator module!");
	printk (KERN_ALERT "Way to the Operand1 file: %s\n", wtOperand1);
	printk (KERN_ALERT "Way to the Operand2 file: %s\n", wtOperand2);
	printk (KERN_ALERT "Way to the Operation file: %s\n", wtOperation);
	return 0;
}

static void __exit modExit (void)
{
	printk (KERN_ALERT "Goodbye, world!\n");
}

module_init (modInit);
module_exit (modExit);