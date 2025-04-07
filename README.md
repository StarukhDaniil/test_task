# Communication manager

## Just plug in the controller to the USB-port and the program will identify the correct port itself.
## I also added operating all tasks in another thread, so ui is not blocked when waiting for the response from the controller.
## If program fails to find the port, it will just write "Failed to find the port" in the output QListWidget