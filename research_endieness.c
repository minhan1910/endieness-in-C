#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASII_ZERO 48
#define BUFF_SIZE 10

/**
*
Suppose we are on a 32-bit machine.

If it is little endian, the x in the memory will be something like:

       higher memory
          ----->
    +----+----+----+----+
    |0x01|0x00|0x00|0x00|
    +----+----+----+----+
    A
    |
   &x
so (char*)(&x) == 1, and *y+48 == '1'. (48 is the ascii code of '0')

If it is big endian, it will be:

    +----+----+----+----+
    |0x00|0x00|0x00|0x01|
    +----+----+----+----+
    A
    |
   &x
so this one will be '0'.
*/
int is_little_endien_system() {
    int x = 1;
    return (*(unsigned char *)(&x) + ASII_ZERO) == (ASII_ZERO + 1);
}

void reverse_bytes(char* bytes, size_t nbytes) {
    for (size_t i = 0; i < nbytes / 2; ++i) {
        char temp = bytes[i];
        bytes[i] = bytes[nbytes - i - 1];
        bytes[nbytes - i - 1] = temp;
    }     
}

int main() {

    int arr[BUFF_SIZE + 1];
    arr[0] = 65; 
    // arr[0] = 255 + 255 + 1;     

    printf("In decimal format of a[0]: 0x%02x\n", arr[0]); // 0x41 in hexadecimal = 65 in decimal

    unsigned char *p = (unsigned char *)&arr[0];

    if (is_little_endien_system()) {        
        printf("Memory representaion of arr[0] in litte-endien system:\n");
        for (int i = 0; i < sizeof(int); ++i) {
            printf("Byte %d: 0x%02x\n", i, p[i]);
        }
        // In Little endien system
        // arr[0] has 0x41 0x00 0x00 0x00 
        // Output
        // Byte 0: 0x41
        // Byte 1: 0x00
        // Byte 2: 0x00
        // Byte 3: 0x00
    } else {
        // stimulate big endien in this case we have array of little endien for
        char pArrZeroth[] = { 0x41, 0x00, 0x00, 0x00 };

        size_t nArrZeroth = sizeof(pArrZeroth) / sizeof(char);
        
        // reserve bytes and print it
        reverse_bytes(pArrZeroth, nArrZeroth);

        for (int i = 0; i < nArrZeroth; ++i) {            
            printf("Bytes %d: 0x%02x\n", i, pArrZeroth[i]);
        }

        // In Big endien system (0x41 at higher memory)
        // arr[0] has 0x00 0x00 0x00 0x41
        // Output
        // Byte 0: 0x00
        // Byte 1: 0x00
        // Byte 2: 0x00
        // Byte 3: 0x41
    }


    // check is little endien system
    // printf("hexa of '1': %x\n", '1');
    // int x = 1;
    // char *px = (char *)&x;
    // printf("%c\n", *px + ASII_ZERO);

    return 0;
}