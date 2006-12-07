CC=/usr/cross/bin/i586-elf-g++
CXX=/usr/cross/bin/i586-elf-g++
CFLAGS= -nostartfiles -nostdlib -fno-rtti -fno-exceptions -Wall -Werror

LINK=/usr/cross/bin/i586-elf-ld
LOPT= -T linker.ld 

AS=/usr/cross/bin/i586-elf-as
AOPT=

#build the kernel

kernel.elf : kmain.o loader.o vgaTextSink.o linker.ld
	$(LINK) -o $@ $(LOPT) $^

kmain.o : kmain.c vgaTextSink.h stdlib.h multiboot.h idt.h
vgaTextSink.o : vgaTextSink.h vgaTextSink.cpp ktypes.h dataMacro.h kPortIO.h
loader.o : loader.s

#copy the kernel to a bootable disk img
.PHONY : boot-disk boot-img 

boot-img :
	cp grub_disk.img ~/boot_disk.img
	sudo losetup /dev/loop/0 ~/boot_disk.img
	mount /dev/loop/0 
	cp kernel.elf /media/img/boot/kernel.elf
	cp menu.cfg /media/img/boot/menu.cfg
	umount /dev/loop/0
	sudo losetup -d /dev/loop/0

boot-disk :
	dd if=grub_disk.img of=/dev/fd0 bs=512 count=2880
	mount /dev/fd0

.PHONY : clean
clean :
	rm *.o
