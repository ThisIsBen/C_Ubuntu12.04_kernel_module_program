obj-m += klhello.o

all: klhello

klhello:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
user_mode:
	 user_mode.c
	 gcc user_mode.c -o procprint

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm procprint
