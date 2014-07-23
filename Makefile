obj-m += lab4_module.o

#make -C /usr/src/linux-headers-3.11.0-26-generic SUBDIRS=$PWD modules

clean: 
	rm -f *.mod.c
	rm -f *.mod.o
	rm -f *.order
	rm -f *.symvers
	rm -f *.o
