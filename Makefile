KDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=`pwd`
	$(CC) random_gen_user.c -o random_gen_user
clean:
	make -C $(KDIR) M=`pwd` clean
	rm random_gen_user
