/* udev_example2.c
 *
 * this example will enumerate all devices belonging
 * to 'block' subsystem and omit all those which devtype
 * is 'partition' or sysname start with 'loop'.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libudev.h>

#define BLOCK_SIZE 512

int main()
{
	struct udev *udev;
	struct udev_device *dev;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices, *dev_list_entry;

	/* create udev object */
	udev = udev_new();
	if (!udev) {
		fprintf(stderr, "Cannot create udev context.\n");
		return -1;
	}

	/* create enumerate object */
	enumerate = udev_enumerate_new(udev);
	if (!enumerate) {
		fprintf(stderr, "Cannot create enumerate context.\n");
		return -1;
	}

	udev_enumerate_add_match_subsystem(enumerate, "block");
	udev_enumerate_scan_devices(enumerate);
	devices = udev_enumerate_get_list_entry(enumerate);

	udev_list_entry_foreach(dev_list_entry, devices) {
		const char *path, *tmp;
		unsigned long long disk_size = 0;

		path = udev_list_entry_get_name(dev_list_entry);
		dev = udev_device_new_from_syspath(udev, path);

		/* skip if device/disk is a partition or loop device */
		if (strncmp(udev_device_get_devtype(dev), "partition", 9) != 0 &&
		    strncmp(udev_device_get_sysname(dev), "loop", 4) != 0) {
			printf("DEVNODE: %s\n", udev_device_get_devnode(dev));
			printf("DEVPATH: /sys%s\n", udev_device_get_devpath(dev));
			printf("DEVTYPE: %s\n", udev_device_get_devtype(dev));

			tmp = udev_device_get_sysattr_value(dev, "size");
			if (tmp) {
				/* skip size if devices is a CD/DVD */
				if (strncmp(udev_device_get_sysname(dev), "sr", 2) != 0)
					disk_size = strtoull(tmp, NULL, 10);

				printf("DEVSIZE: %lld GB\n", (disk_size * BLOCK_SIZE) / 1000000000);
			}
		}
		/* free dev */
		udev_device_unref(dev);
	}
	/* free enumerate */
	udev_enumerate_unref(enumerate);
	/* free udev */
	udev_unref(udev);

	return 0;
}
