obj-m += enable-ccr.o

all:
	make -C /lib/modules/3.10-3-rpi/build M=$(PWD) modules

clean:
	make -C /lib/modules/3.10-3-rpi/build M=$(PWD) clean
