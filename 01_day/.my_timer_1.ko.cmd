cmd_/root/kernel/01_day/my_timer_1.ko := arm-linux-gnueabihf-ld -EL -r  -T ./scripts/module-common.lds --build-id  -o /root/kernel/01_day/my_timer_1.ko /root/kernel/01_day/my_timer_1.o /root/kernel/01_day/my_timer_1.mod.o ;  true