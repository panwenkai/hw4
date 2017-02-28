#!/bin/bash
# Part 1

version="$1"
UNI="$2"

make -j8
make modules_install
cp -v arch/x86/boot/bzImage "/boot/vmlinuz-$version-$UNI"
mkinitcpio -k "$version-$UNI" -g "/boot/initramf-$version-$UNI.img"
cp System.map "/boot/System.map-$version-$UNI"
ln -sf "/boot/System.map-$version-$UNI" "/boot/Ststem.map"
dkms remove vboxguest/5.1.14_OSE -k "$version-$UNI"
dkms install vboxguest/5.1.14_OSE -k "$version-$UNI"
