#include "main.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
/**
 * _printf - a custom build printf function
 * @format: string to print with format specifier
 * Return: number of chars printed
 */
int _printf(const char *format, ...)
{
	int size = 0;
	int number;
	int holder;
	int temp;
	int length = 0;
	int specifier = 0;
	int i;
	int count = 0;
	char *ptr;
	va_list arguments;
	if (!format)
	{
		return (0);
	}
	for (i = 0; format[i] != '\0'; i++)
	{
		length++;
		if (format[i] == 37 && (format[i + 1]) != 37  && (format[i + 1] == 'c'  || format[i + 1] == 's' || 
				format[i + 1] == 'i' || format[i + 1] == 'd'))
		{
			specifier++;
		}
	}
	va_start(arguments, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c')
			{
				char c =(char) va_arg(arguments, int);
				count = count + (write(1, &c, 1));
				format++;
			}
			else if (*format == '%')
			{
				count = count + (write(1,format,1));
				format++;
			}
			else if (*format == 's')
			{
				char *string = va_arg(arguments, char *);
				while (*string)
				{
				count = count + (write(1, string, 1));
				string++;
				}
				format++;
			}
			else if (*format == 'd' || *format == 'i')
			{
				size = 0;
				number = va_arg(arguments, int);
				if (number >= 0)
				{
					temp = number;
					while( temp >= 1)
					{
						temp = temp / 10;
						size++;
					}
					ptr = malloc((size + 1) * sizeof(char));
					if (!ptr)
					{
						return (1);
					}
					ptr[size] = '\0';
					for (i = (size - 1); i >= 0; i--)
					{
						holder = number % 10;
						number = number / 10;
						ptr[i] = holder + '0';
					}
					while (*ptr)
					{
						count = count + (write(1, ptr, 1));
						ptr++;
					}
				}
				else
				{
					number = -number;
					temp = number;
					while (temp >= 1)
					{
						temp = temp / 10;
						size++;
					}
					ptr = malloc((size + 2) * sizeof(char));
					if (!ptr)
					{
						return (1);
					}
					ptr[size + 1] = '\0';
					ptr[0] = '-';
					for ( i = size; i > 0; i--)
					{
						holder = number % 10;
						number = number / 10;
						ptr[i] = holder + '0';
					}
					while (*ptr)
					{
						count = count + (write(1, ptr, 1));
						ptr++;
					}
				}
				format++;
			}
		}
		else
		{
			count = count + (write(1, format,1));
			format++;
		}
	}
	va_end(arguments);
	return count;
}
