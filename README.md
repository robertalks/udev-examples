udev-examples
=============

**libudev API examples**

* udev_example1.c:
using libudev API we get basic information for network device 'eth0'.


*example:*

        [user@linux ~]$ ./udev_example1 eth0
        DEVNAME: eth0
        DEVPATH: /sys/devices/pci0000:00/0000:00:19.0/net/eth0
        MACADDR: 18:03:73:db:c3:31


* udev_example2.c:
using libudev API we enumerate all devices under 'block' subsystem that are not 'partitions' or 'loop' devices.

*example:*

        [user@linux ~]$ ./udev_example2
        DEVNODE: /dev/sda
        DEVPATH: /sys/devices/pci0000:00/0000:00:1f.2/ata1/host0/target0:0:0/0:0:0:0/block/sda
        DEVTYPE: disk
        DEVSIZE: 500 GB
        DEVNODE: /dev/sr0
        DEVPATH: /sys/devices/pci0000:00/0000:00:1f.2/ata2/host1/target1:0:0/1:0:0:0/block/sr0
        DEVTYPE: disk
        DEVSIZE: n/a


* udev_example3.c:
using libudev API we monitor 'net' subsystem for events.

*example:*

        [user@linux ~]$ ./udev_example3
        DEVNAME: net0
        DEVPATH: /sys/devices/pci0000:00/0000:00:19.0/net/net0
        MACADDR: (null)
        ACTION: remove
        ---
        DEVNAME: net0
        DEVPATH: /sys/devices/pci0000:00/0000:00:19.0/net/net0
        MACADDR: d4:be:d9:2b:86:7c
        ACTION: add
