/* udev_example1.c
 *
 * this example will get basic information about
 * a specified network device
 *
 */

#include <stdio.h>
#include <libudev.h>

#define DEVICE_PATH "/sys/class/net/eth0"

int main()
{
	struct udev *udev;
	struct udev_device *dev;

	/* create udev object */
	udev = udev_new();
	if (!udev) {
		printf("Cannot create udev context.\n");
		return -1;
	}

	/* get device based on path */
	dev = udev_device_new_from_syspath(udev, DEVICE_PATH);
	if (!dev) {
		printf("Failed to get device.\n");
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
