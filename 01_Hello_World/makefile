obj-m += ldd.o # We are adding ldd.ko to the make build system's list for kernel modules

# -C is used to Change the working directory to a specific one where other makefiles exist (in this: kernel's build tree)
# M=$(PWD) is telling that take and store artifacts from current directory where our makefile is executed from
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
