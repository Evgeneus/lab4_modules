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

#define OPERAND1 0
#define OPERAND2 1
#define OPERATION 2

static char * wtOperand1 = "nothing";
static char * wtOperand2 = "nothing";
static char * wtOperation = "nothing";
static int operand1 = 0;
static int operand2 = 0;
static int result = 0;



module_param (wtOperand1, charp, 0000);
module_param (wtOperand2, charp, 0000);
module_param (wtOperation, charp, 0000);

MODULE_PARM_DESC (wtOperand1, "Way to the Operand1 file");
MODULE_PARM_DESC (wtOperand2, "Way to the Operand2 file");
MODULE_PARM_DESC (wtOperation, "Way to the Operation file");

static int fRead (char * f_to_read, int action)
{
        struct file *f;
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

// choice the action
        if (action == 0) {
                operand1 = (int)simple_strtol(buff, NULL, 10);
                printk(KERN_ALERT "operand1 : %i\n", operand1);
        } else
        if (action == 1) {
                operand2 = (int)simple_strtol(buff, NULL, 10);
                printk(KERN_ALERT "operand2 : %i\n", operand2);
        } else
        if (action == 2) {
                switch (*buff) {
                        case '/' : 
                                result = operand1 / operand2;
                                printk (KERN_ALERT "operand1 / operand2 = %i\n", result);
                                break;
                        case '*' : 
                                result = operand1 * operand2;
                                printk (KERN_ALERT "operand1 * operand2 = %i\n", result);
                                break;
                        case '+' : 
                                result = operand1 + operand2;
                                printk (KERN_ALERT "operand1 + operand2 = %i\n", result);
                                break;
                        case '-' : 
                                result = operand1 - operand2;
                                printk (KERN_ALERT "operand1 - operand2 = %i\n", result);
                                break;
                        default : 
                                printk (KERN_ALERT "OPERAND ERROR!\n");
                                return 1;
                }
        } else return 1;


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
        printk (KERN_ALERT "Hello, I'm a calculator module!");
        if(fRead (wtOperand1, OPERAND1)) return 1;
        if (fRead (wtOperand2, OPERAND2)) return 1;
        if (fRead (wtOperation, OPERATION)) return 1;

        return 0;
}

static void __exit modExit (void)
{
        printk (KERN_ALERT "Goodbye, world!\n");
}

module_init (modInit);
module_exit (modExit);