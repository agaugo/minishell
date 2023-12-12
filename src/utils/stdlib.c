#include "../../includes/minishell.h"

char *ft_strncpy(char *dest, const char *src, size_t n) 
{
    char *dest_start;

	dest_start = dest;
    // Copy at most 'n' characters from 'src' to 'dest'
    while (*src != '\0' && n > 0) {
        *dest++ = *src++;
        n--;
    }
    // Pad 'dest' with null bytes if 'n' is greater than the length of 'src'
    while (n > 0) 
	{
        *dest++ = '\0';
        n--;
    }
    return (dest_start);
}

char *ft_strndup(const char *str, size_t n)
{
	char *result;
	size_t len;

    if (str == NULL)
        return NULL;
    len = ft_strlen(str);
    if (n < len)
        len = n;
    result = (char *)allocate_memory(len + 1); // +1 for the null terminator
    ft_strncpy(result, str, len);
    result[len] = '\0'; // Null-terminate the copied string
    return result;
}
char *ft_strcpy(char *dest, const char *src) 
{
    char *dest_start = dest;

    // Copy characters from src to dest until the null terminator is encountered in src
    while ((*dest++ = *src++) != '\0');

    return dest_start;
}

char *ft_strchr(const char *str, int character) {
    while (*str != '\0') {
        if (*str == character)
            return (char *)str;
        str++;
    }
    return (NULL);
}

char *ft_strcat(char *dest, const char *src) {
    char *dest_start = dest;

    // Move the dest pointer to the end of the destination string
    while (*dest)
        dest++;

    // Copy characters from src to the end of dest
    while ((*dest++ = *src++) != '\0');

    return dest_start;
}
