/* udev_example1.c
 *
 * Copyright (C) 2014 Robert Milasan <rmilasan@suse.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This example will get basic information about a specified network
 * device using libudev API.
 *
 */

#include <stdio.h>
#include <libudev.h>

#define SYSPATH "/sys/class/net"

int main(int argc, char *argv[])
{
	struct udev *udev;
	struct udev_device *dev, *dev_parent;
	char device[128]; 

	/* verify that we have an argument, like eth0, otherwise fail */
	if (!argv[1]) {
		fprintf(stderr, "Missing network interface name.\nexample: %s eth0\n", argv[0]);
		return 1;
	}

	/* build device path out of SYSPATH macro and argv[1] */
	snprintf(device, sizeof(device), "%s/%s", SYSPATH, argv[1]);
	
	/* create udev object */
	udev = udev_new();
	if (!udev) {
		fprintf(stderr, "Cannot create udev context.\n");
		return 1;
	}

	/* get device based on path */
	dev = udev_device_new_from_syspath(udev, device);
	if (!dev) {
		fprintf(stderr, "Failed to get device.\n");
		return 1;
	}
	
	printf("I: DEVNAME=%s\n", udev_device_get_sysname(dev));
	printf("I: DEVPATH=%s\n", udev_device_get_devpath(dev));
	printf("I: MACADDR=%s\n", udev_device_get_sysattr_value(dev, "address"));

	dev_parent = udev_device_get_parent(dev);
	if (dev_parent)
		printf("I: DRIVER=%s\n", udev_device_get_driver(dev_parent));

	/* free dev */
	udev_device_unref(dev);

	/* free udev */
	udev_unref(udev);

	return 0;
}
