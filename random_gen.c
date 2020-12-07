#include <linux/module.h>  
#include <linux/kernel.h>
#include <linux/fs.h>	   
#include <linux/random.h>  
#include <linux/device.h>  
#include <linux/slab.h>	   
#include <linux/uaccess.h> 
#include <linux/cdev.h>

#define DEVICE_NAME "random_number_device"
#define CLASS_NAME "random_number_class"

static int random_number_open(struct inode*, struct file*);
static int random_number_release(struct inode*, struct file*);
static ssize_t random_number_read(struct file* , char* , size_t , loff_t* );

static dev_t first; // Global variable for <major,minor> of a device
static struct class* random_number_class = NULL; // Globle variable to take returned value of class_create
static struct cdev c_dev; // Global variable for the character device structure 


static struct file_operations fops =
{
	.open = random_number_open,
	.release = random_number_release,
	.read = random_number_read
};



static int __init random_number_init(void)
{
	printk(KERN_INFO "Initializing module...\n");
	
    // Register major and minor number for device
    if (alloc_chrdev_region(&first, 0, 1, DEVICE_NAME) < 0)
    {
        // Failed
    	printk(KERN_ALERT "ERROR: Can not register number for device!\n");
        return -1;
    }
    // Successful
	printk(KERN_INFO  "Register number for device successfully: <major,minor> - <%d,%d> \n", MAJOR(first),MINOR(first));
	
    /*__________________________________________________________________________________________________________________*/

	// Register a device class
	random_number_class = class_create(THIS_MODULE, CLASS_NAME);
	if(IS_ERR(random_number_class))
	{
        // Failed
		printk(KERN_ALERT "ERROR: Can not register device class\n");
		unregister_chrdev_region(first, 1); // unregister number
		return -1;
	}
    // Successful
	printk(KERN_INFO "Device class registered\n");

    /*__________________________________________________________________________________________________________________*/


	//  Register a device driver
	if(IS_ERR(device_create(random_number_class, NULL, first, NULL, DEVICE_NAME))) 
	{
        // Failed
    	printk(KERN_ALERT "ERROR: Can not register the device!\n");
		class_destroy(random_number_class);	
		unregister_chrdev_region(first, 1);
		return -1;
	}
    // Successful
	printk(KERN_INFO "Device created \n");

    /*__________________________________________________________________________________________________________________*/


    cdev_init(&c_dev, &fops);
    // Add a character device to the system
    if (cdev_add(&c_dev, first, 1) == -1)
    {
        // Failed
        printk(KERN_ALERT "ERROR: Can not add character device to the system!\n");
        device_destroy(random_number_class, first);
        class_destroy(random_number_class);
        unregister_chrdev_region(first, 1);
        return -1;
    }
    // Successful
	printk(KERN_INFO "Add character device to the system. \n");
	return 0;
}

static void __exit random_number_exit(void)
{
    	cdev_del(&c_dev);
	device_destroy(random_number_class, first);
	class_unregister(random_number_class);
	class_destroy(random_number_class);
    	unregister_chrdev_region(first, 1);
	printk(KERN_INFO "Unregister %s.\n",DEVICE_NAME);
}


static int random_number_open(struct inode* inode, struct file* filp)
{
	printk(KERN_INFO "Device opened. \n");
	return 0;
}	


static int random_number_release(struct inode* inode, struct file* filp)
{
	printk(KERN_INFO "Device released.\n");
	return 0;
}

static ssize_t random_number_read(struct file* filp, char* buffer, size_t len, loff_t* offset)
{
	
	// get len bytes randomly
    char *temp = kmalloc(len, GFP_KERNEL);
	if (temp == NULL)
    {
            printf("Allocation failed\n");
            return -1;
    }
	get_random_bytes(temp, len);
	
    // send 'len' bytes  from temp to buffer 
    
	if(copy_to_user(buffer,temp,len) == 0)
	{
        // Success
		printk(KERN_INFO "Send random number to user.\n");
		kfree(temp);
		return 0;
	}
	else
	{
        // Failed
		printk(KERN_INFO "ERROR: Can not send random number to user!\n");
		kfree(temp);
		return -EFAULT;
	}
}

module_init(random_number_init);
module_exit(random_number_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Loc - Tue - Phuc");
MODULE_DESCRIPTION("Module Random Number Generator");
MODULE_VERSION("1.0");
