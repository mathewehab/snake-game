#include "UART.h"
#include "bsp.h"

void print_all(unsigned n){
    int count = 0;
    print("DEC: ");
    count = print_idec(n);
    print("COUNT: ");
    print_idec(count);
    print("HEX: ");
    print_ihex(n);
    print("BIN: ");
    print_ibin(n);
}

void print(const char *myString)
{
    for (int i = 0; i < strlen(myString); i++)
    {
        if (*(myString + i) == NEWLINE)
        {
            uart0_putchar(CARRIAGE_RETURN);
        }
        uart0_putchar(*(myString + i)); 
    }
}

char* my_itoa(unsigned int val, int base){
	static char buf[30] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}

int print_idec(int n){
    if(n > 0 && (unsigned)n > 2147483647) 
    {
        print("Out of range\n");
        return 0;
    }
    if(n < 0){
        uart0_putchar('-');
        print(my_itoa(n*-1, 10));
        print("\n"); 
        return log10((-1*(unsigned)n))+2;
    }else if (n > 0){
        print(my_itoa(n, 10));
        print("\n"); 
        return log10(n)+1;
    }else{
        uart0_putchar('0');
        print("\n");
        return 1;
    }
}

void print_ihex(unsigned n)
{
    char hexaDeciNum[8];
    int i = 0, tmp;
    while (n != 0) {
        tmp = n % 16;
        hexaDeciNum[i++] = (tmp < 10)? (tmp + 48): (tmp + 55);
        n = n / 16;
    }
    tmp = i;
    print("0x");    
    while(tmp++ < 8) uart0_putchar('0');
    for (tmp = i - 1; tmp >= 0; tmp--) uart0_putchar(hexaDeciNum[tmp]);
    print("\n"); 
}

void print_ibin(unsigned n){
    char arr[32] = {0};
    for(int j=0; n>0; j++, n/=2) arr[31-j] = n%2;
    print("0b"); 
    for(int i=0; i<32; i++) uart0_putchar(arr[i] + 48);
    print("\n"); 
}
