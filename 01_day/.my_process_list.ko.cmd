cmd_/root/kernel/01_day/my_process_list.ko := arm-linux-gnueabihf-ld -EL -r  -T ./scripts/module-common.lds --build-id  -o /root/kernel/01_day/my_process_list.ko /root/kernel/01_day/my_process_list.o /root/kernel/01_day/my_process_list.mod.o ;  true