CC=i586-elf-g++
CXX=i586-elf-g++
CXXFLAGS= -nostartfiles -nostdlib -fno-rtti -fno-exceptions -pedantic \
	-Wall -Werror -Wshadow -Wextra -Wpointer-arith \
	-Wcast-align -Wwrite-strings


LINK=i586-elf-ld
LOPT= -T linker.ld 

AS=i586-elf-as
AOPT=

VPATH=. vga

#build the kernel

all : kernel.elf
kernel.elf : kmain.o loader.o textSink.o linker.ld
	$(LINK) -o $@ $(LOPT) $^

kmain.o : kmain.cpp textSink.h stdlib.h multiboot.h
textSink.o :
	cd vga
	$(MAKE)

loader.o : loader.s

#compile the kernel make a disk image and then fire up bochs
.PHONY : test

test : boot-img
	bochs

#copy the kernel to a bootable disk img
.PHONY : boot-disk boot-img 

boot-img : kernel.elf
	cp grub_disk.img ~/boot_disk.img
	sudo losetup /dev/loop/0 ~/boot_disk.img
	mount /dev/loop/0
	cp kernel.elf /mnt/loop/boot/kernel.elf
	cp menu.cfg /mnt/loop/boot/menu.cfg
	umount /dev/loop/0
	sudo losetup -d /dev/loop/0

boot-disk :
	dd if=grub_disk.img of=/dev/fd0 bs=512 count=2880
	mount /dev/fd0

.PHONY : clean
clean :
	rm *.o
