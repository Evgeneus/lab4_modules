obj-m += lab4_module.o

#make -C /usr/src/linux-headers-3.11.0-26-generic SUBDIRS=$PWD modules
#sudo insmod lab4_module.ko wtOperand1="/home/evgeny/operand1" wtOperand2="/home/evgeny/operand2" wtOperation="/home/evgeny/operation"

clean: 
	rm -f *.mod.c
	rm -f *.mod.o
	rm -f *.order
	rm -f *.symvers
	rm -f *.o
	rm -f *.ko
