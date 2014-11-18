udev-examples
=============

**libudev API examples**

* udev_example1.c:
using libudev API we get basic information for network device 'eth0'.


*example:*

        [user@linux ~]$ ./udev_example1 eth0
        I: DEVNAME=eth0
        I: DEVPATH=/devices/pci0000:00/0000:00:19.0/net/eth0
        I: MACADDR=18:03:73:db:c3:31
        I: DRIVER=e1000


* udev_example2.c:
using libudev API we enumerate all devices under 'block' subsystem that are not 'partitions' or 'loop' devices.

*example:*

        [user@linux ~]$ ./udev_example2
        I: DEVNODE=/dev/sda
        I: KERNEL=sda
        I: DEVPATH=/devices/pci0000:00/0000:00:1f.2/ata1/host0/target0:0:0/0:0:0:0/block/sda
        I: DEVTYPE=disk
        I: DEVSIZE=500 GB
        I: DEVNODE=/dev/sr0
        I: KERNEL=sr0
        I: DEVPATH=/devices/pci0000:00/0000:00:1f.2/ata2/host1/target1:0:0/1:0:0:0/block/sr0
        I: DEVTYPE=disk
        I: DEVSIZE=n/a


* udev_example3.c:
using libudev API we monitor 'net' subsystem for events.

*example:*

        [user@linux ~]$ ./udev_example3
        I: ACTION=remove
        I: DEVNAME=net0
        I: DEVPATH=/devices/pci0000:00/0000:00:19.0/net/net0
        I: MACADDR=(null)
        ---
        I: ACTION=add
        I: DEVNAME=net0
        I: DEVPATH=/devices/pci0000:00/0000:00:19.0/net/net0
        I: MACADDR=d4:be:d9:2b:86:7c
