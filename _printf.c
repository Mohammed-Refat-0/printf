#include "main.h"
#include <unistd.h>
#include <stdarg.h>
/**
 * _printf - a custom build printf function
 * @ format: string to print with format specifier
 * Return: number of chars printed
 */
int _printf(const char *format, ...)
{
	int count = 0;
	va_list arguments;
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
