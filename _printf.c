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
	int length = 0;
	int specifier = 0;
	int i;
	int count = 0;
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
