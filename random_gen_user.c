#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int file_device,n;
char * temp = NULL;

int main()
{
	
    // Open file device
    printf("Opening device file...\n");
	file_device = open("/dev/random_number_device", O_RDONLY);
	if(file_device < 0)
	{
		perror("Failed to open the device!!\n");
		return -1;
	}

    // Loop to get random number.
    while (1)
    {
        printf("Type in number of bytes of your random number (1 to 8) - else : quit: ");
        scanf("%d",&n);
        if (n<1 || n>8) break;

	    if (temp != NULL) 
            free(temp);
        temp = malloc(n);
        if (temp == NULL)
        {
            printf("Allocation failed\n");
            return -1;
        }
        printf("Receiving information from device file...\n");
        
        if(read(file_device, temp, n) < 0)
        {
            free(temp);
            close(file_device);
            perror("Failed to read from device!!!\n");
            return -1;
        }
        // Print 
        printf("The random number is: %llu\n",*(unsigned long long*)temp);
    }
    free(temp);
    close(file_device);
	printf("Good bye!\n");
	return 0;
}
