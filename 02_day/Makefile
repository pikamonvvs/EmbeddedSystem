obj-m = my_process.o

KERNEL=/root/linux
PWD=$(shell pwd) 

default : 
	$(MAKE) -C $(KERNEL)  SUBDIRS=$(PWD) modules 

clean : 
	$(MAKE) -C $(KERNEL)  SUBDIRS=$(PWD) clean 

install : 
	scp  $(patsubst %.o,%.ko, $(obj-m))  root@192.168.137.100: 
