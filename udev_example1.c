/* udev_example1.c
 *
 * this example will get basic information about
 * a specified network device
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libudev.h>

#define SYSPATH "/sys/class/net"

int main(int argc, char *argv[])
{
	struct udev *udev;
	struct udev_device *dev;
	char *device;

	/* verify that we have an argument, like eth0, otherwise fail */
	if (!argv[1]) {
		fprintf(stderr, "Missing network interface name.\nexample: %s eth0\n", argv[0]);
		return -1;
	}

	/* allocate device based on SYSPATH and argv[1] */
	device = malloc(strlen(SYSPATH) + strlen(argv[1]) + 1);
	if (!device) {
		fprintf(stderr, "Failed to allocate memory for device.");
		return -1;
	}
	
	/* build device path out of SYSPATH macro and argv[1] */
	sprintf(device, "%s/%s", SYSPATH, argv[1]);
	
	/* create udev object */
	udev = udev_new();
	if (!udev) {
		fprintf(stderr, "Cannot create udev context.\n");
		return -1;
	}

	/* get device based on path */
	dev = udev_device_new_from_syspath(udev, device);
	if (!dev) {
		fprintf(stderr, "Failed to get device.\n");
		return -1;
	}
	
	printf("DEVNAME: %s\n", udev_device_get_sysname(dev));
	printf("DEVPATH: /sys%s\n", udev_device_get_devpath(dev));
	printf("MACADDR: %s\n", udev_device_get_sysattr_value(dev, "address"));

	/* free dev */
	udev_device_unref(dev);

	/* free udev */
	udev_unref(udev);

	return 0;
}
