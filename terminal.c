/*
 * terminal.c
 *
 * Created: 14.10.2018 20:11:24
 *  Author: Dawid Grzybowski
 */ 

 #include <stdio.h>
 #include <string.h>	// temp

 #include "../usart/usart.h"
 
  static int transmitChar(char character, FILE *stream)
  {
	USART_Transmit((unsigned char)character);

	return 0;
  }	

  static int receiveChar(FILE *stream)
  {	
	int data = (int)USART_Receive();

	if(data == '\r' || data == '\n' || data<0)	return _FDEV_EOF;
	else	return data;

/*
	if(data)	return data;
	else		return _FDEV_EOF;*/

	// TODO: _FDEV_ERR handler needed
  }

 FILE uart_str = FDEV_SETUP_STREAM(transmitChar, receiveChar, _FDEV_SETUP_RW);

 void terminal_init()
 {
	stdin = stdout = &uart_str;
 }

/**
	This Line Feed example prints:

		Characters: a A
		Decimals: 1977 650000
		Preceding with blanks:       1977
		Preceding with zeros: 0000001977
		Some different radices: 100 64 144 0x64 0144
		A string
*/
void terminal_example_printf_LF()
{
	printf ("This is Line Feed example:\n");
	printf ("Characters: %c %c\n", 'a', 65);
	printf ("Decimals: %d %ld\n", 1977, 650000L);
	printf ("Preceding with blanks: %10d\n", 1977);
	printf ("Preceding with zeros: %010d\n", 1977);
	printf ("Some different radices: %d %x %o %#x %#o\n", 100, 100, 100, 100, 100);
	//printf ("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);		// no flats in uC version
	//printf ("Width trick: %*d \n", 5, 10);							// something is wrong here
	printf ("%s\n", "A string");
}

void terminal_example_printf_CR()
{
	printf ("This is Carriage Return example:\r");
	printf ("Characters: %c %c\r", 'a', 65);
	printf ("Decimals: %d %ld\r", 1977, 650000L);
	printf ("Preceding with blanks: %10d\r", 1977);
	printf ("Preceding with zeros: %010d\r", 1977);
	printf ("Some different radices: %d %x %o %#x %#o\r", 100, 100, 100, 100, 100);
	//printf ("floats: %4.2f %+.0e %E", 3.1416, 3.1416, 3.1416);		// no flats in uC version
	//printf ("Width trick: %*d", 5, 10);								// something is wrong here
	printf ("%s\r", "A string");
}

void terminal_example_printf_CRLF()
{
	printf ("This is Carriage Return + Line Feed example:\r\n");
	printf ("Characters: %c %c\r\n", 'a', 65);
	printf ("Decimals: %d %ld\r\n", 1977, 650000L);
	printf ("Preceding with blanks: %10d\r\n", 1977);
	printf ("Preceding with zeros: %010d\r\n", 1977);
	printf ("Some different radices: %d %x %o %#x %#o\r\n", 100, 100, 100, 100, 100);
	//printf ("floats: %4.2f %+.0e %E", 3.1416, 3.1416, 3.1416);		// no flats in uC version
	//printf ("Width trick: %*d", 5, 10);								// something is wrong here
	printf ("%s\r\n", "A string");
}

/**
	Clears terminal output window
*/
void terminal_example_printf_ESCAPE()
{
	printf("\e");		// ASCII decimal 27
}

void terminal_example_scanf()
{
	char str [80];
	int i;

	printf ("Enter your family name:\r\n");
	scanf ("%79s",str);
//	printf("\e");
	printf ("Enter your age:\r\n");
	scanf ("%d",&i);
//	printf("\e");
	printf ("Mr. %s , %d years old.\r\n",str,i);
	printf ("Enter a hexadecimal number:\r\n");
	scanf ("%x",&i);
//	printf("\e");	
	printf ("Your number is: %#x (%d).\r\n",i,i);

/*
	char x[32];
	int y = 0;
	double z = 0.0;

	printf("What's your name? ");
	// note the use of fgets instead of scanf("%s",...)
	// to prevent buffer overflows by specifying a maximum length!
	fgets(x, 32, stdin);

	// remove newline
	x[strlen(x)-1] = '\0';

	printf("Hi, %s!  How old are you? ", x);
	scanf("%d", &y);

	printf("What's your favorite number? ");
	scanf("%lf", &z);

	printf("Nice to meet you, %s!  You are %d years old and like the number %f.\n", x, y, z);*/
}