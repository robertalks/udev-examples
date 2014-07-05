/* udev_example3.c
 * 
 * this example monitors udev events for 'net' subsystem 
 * using libudev's API
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <libudev.h>

int main (void)
{
	struct udev *udev;
	struct udev_device *dev;
   	struct udev_monitor *mon;
	int fd;
	
	/* create udev object */
	udev = udev_new();
	if (!udev) {
		printf("Can't create udev\n");
		exit(1);
	}

	mon = udev_monitor_new_from_netlink(udev, "udev");
	udev_monitor_filter_add_match_subsystem_devtype(mon, "net", NULL);
	udev_monitor_enable_receiving(mon);
	fd = udev_monitor_get_fd(mon);

	while (1) {
		fd_set fds;
		struct timeval tv;
		int ret;
		
		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		
		ret = select(fd+1, &fds, NULL, NULL, &tv);
		
		if (ret > 0 && FD_ISSET(fd, &fds)) {
			
			dev = udev_monitor_receive_device(mon);
			if (dev) {
				printf("DEVNAME: %s\n", udev_device_get_sysname(dev));
				printf("DEVPATH: /sys%s\n", udev_device_get_devpath(dev));
				printf("MACADDR: %s\n", udev_device_get_sysattr_value(dev, "address"));
				printf("ACTION: %s\n", udev_device_get_action(dev));

				/* free dev */
				udev_device_unref(dev);
			}
			else {
				printf("No Device from receive_device(). An error occured.\n");
			}					
		}

		/* 500 milliseconds */
		usleep(500*1000);
		printf(".");
		fflush(stdout);
	}

	/* free udev */
	udev_unref(udev);

	return 0;
}

