obj-m = my_ramdisk.o

KERNEL = /root/linux
PWD    = $(shell pwd) 

default : 
	make -C $(KERNEL) SUBDIRS=$(PWD) modules

clean : 
	make -C $(KERNEL) SUBDIRS=$(PWD) clean

install :
	scp $(patsubst %.o,%.ko,$(obj-m)) root@192.168.137.100:/root

app :
	arm-linux-gnueabihf-gcc my_ramdisk_test.c -o myapp
	scp myapp root@192.168.137.100:/root
