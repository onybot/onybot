# onybot


# DEBIAN USB
$ ls -la /dev/ttyUSB0 
crw-rw---- 1 root dialout 188, 0 ago  5 12:14 /dev/ttyUSB0

add  user to dialout group and restart
$ sudo usermod -a -G dialout user

