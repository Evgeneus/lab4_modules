#include <linux/module.h>     
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("E. O. KRIVOSHEEV");

static char * wtOperand1 = "nothing";
static char * wtOperand2 = "nothing";
static char * wtOperation = "nothing";

module_param (wtOperand1, charp, 0000);
module_param (wtOperand2, charp, 0000);
module_param (wtOperation, charp, 0000);

MODULE_PARM_DESC (wtOperand1, "Way to the Operand1 file");
MODULE_PARM_DESC (wtOperand2, "Way to the Operand2 file");
MODULE_PARM_DESC (wtOperation, "Way to the Operation file");

static int __init modInit(void)
{
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