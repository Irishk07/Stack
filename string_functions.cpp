#include "string_functions.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_puts(const char *str) {
    assert(str != NULL);

    for ( ; *str != '\0'; ++str) {
        if (putchar(*str) == EOF) {
            return EOF;
        }
    }

    return 0;
}

const char * my_strchr(const char *str, int c) {
    assert(str != NULL);

    do {
        if (*str == c) {
            return str;
        }
    } while (*str++ != '\0');

    return NULL;
}

size_t my_strlen(const char *str) {
    assert(str != NULL);

    size_t size = 0;

    for ( ; *str != '\0'; ++str) {
        ++size;
    }

    return size;
}

char *my_strcpy(char * dst, const char * src) {
    assert(dst != NULL);
    assert(src != NULL);

    char * temp = dst;

    do {
        *dst++ = *src;
    } while (*src++ != '\0');

    return temp;
}

char *my_strncpy(char * dst, const char * src, size_t n) {
    assert(dst != NULL);
    assert(src != NULL);

    char * temp = dst;

    size_t i = 0;
    do {
        *dst++ = *src++;
    } while (*src != '\0' && i++ < n);

    while (i < n) {
        *dst++ = '\0';
        ++i;
    }

    return temp;
}

char *my_strcat(char * dst, const char * src) {
    assert(dst != NULL);
    assert(src != NULL);

    char * temp = dst;

    while (*dst++ != '\0') {
    }

    do {
        *dst++ = *src;
    } while (*src++ != '\0');

    return temp;
}

char *my_strncat(char * dst, const char * src, size_t ssize) {
    assert(dst != NULL);
    assert(src != NULL);

    char * temp = dst;

    while (*dst++ != '\0') {
    }

    size_t i = 0;
    do {
        *dst++ = *src++;
    } while (*src != '\0' && i++ < ssize);
    
    if (i < ssize) {
        *dst = '\0';
    }

    return temp;
}

char *my_fgets(char *str, int n, FILE *stream) {
    assert(str != NULL);

    int ch = getc(stream);
    if (ch == EOF) {
        return NULL;
    }

    int cnt = 0;
    while (ch != EOF && ch != '\n' && cnt++ != (n - 1)) {
        *str++ = (char)ch;
        ch = getc(stream);
    }
    *str = '\0';

    if (ferror(stream) != 0) {
        return NULL;
    }

    return str;
}

char *my_strdup(const char *s) {
    assert(s != NULL);

    char *point_on_s = (char*)calloc(my_strlen(s) + 1, sizeof(char));

    if (point_on_s == NULL) {
        return NULL;
    }

    point_on_s = my_strcpy(point_on_s, s);

    return point_on_s;
}

 void *my_recalloc(void *ptr, size_t new_size, size_t old_size) {
    char *point = (char*)realloc(ptr, new_size);

    if (new_size <= old_size) {
        return point;
    }

    if (point == NULL) {
        return NULL;
    }

    return memset(point + old_size, ZERO, new_size - old_size);
 }

ssize_t my_getline(char ** const lineptr, size_t * n, FILE * stream) {
    if (n == NULL || lineptr == NULL) {
        return -1;
    }
    
    if (*lineptr == NULL) {
        *n = 0;
    }

    int ch = 0;
    size_t size = 0;
    while ((ch = getc(stream)) != '\n' && ch != EOF) {
        if (*n < size + 1) {
            char * temp = (char*)my_recalloc(*lineptr, (*n == 0) ? SIZE_OF_BUF : 2 * (*n), *n);
            if (temp == NULL) {
                return -1;
            }

            *n = (*n == 0) ? SIZE_OF_BUF : 2 * (*n);
            *lineptr = temp;
        }

        *((*lineptr)++) = (char)ch;
        size++;
    }

    **lineptr = '\0';

    if (ferror(stream) != 0) {
        return -1;
    }

    return (ssize_t)size;
}

int my_strcmp(const char *s1, const char *s2) {
    while(*s1 != '\0' && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

int my_strncmp(const char *s1, const char *s2, size_t n) {
    if (n == 0) {
        return 0;
    }

    while(--n > 0 && *s1 != '\0' && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

const char * my_strstr(const char *haystack, const char *needle) {
    assert(haystack != NULL);
    assert(needle != NULL);

    if (*needle == '\0') {
        return haystack;
    }

    int cnt_same = 1;
    for (int k = 0; needle[k] != '\0'; ++k) {
        if (needle[k] == needle[k + 1]) {
            cnt_same++;
        }
        else {
            break;
        }
    }

    for (int i = 0; haystack[i] != '\0'; ++i) {
        for (int j = 0; haystack[i + j] != '\0'; ++j) {

            if (haystack[i + j] != needle[j]) {

                if (haystack[i + j] == '\0') {
                    return NULL;
                }

                if (haystack[i + j] != needle[0]) {
                    i += cnt_same - 1;
                }
                break;
            } 

            if (needle[j + 1] == '\0') {
                return haystack + i;
            }
        }
    }

    return NULL;
}

const char * my_strstr_mur(const char *haystack, const char *needle) {
    assert(haystack != NULL);
    assert(needle != NULL);

    if (*needle == '\0') {
        return haystack;
    }

    const char * temp = needle;

    size_t size_needle = my_strlen(needle);
    size_t jump_table [CNT_SYMBOLS] = {};
    for (int i = 0; i < CNT_SYMBOLS; ++i) {
        jump_table[i] = size_needle;
    }

    for (size_t i = 0; needle[i] != '\0'; ++i) {
        jump_table[(int)needle[i]] = size_needle - i - 1;
    } 

    size_t size_haystack = my_strlen(haystack);

    needle = temp;
    for (size_t i = size_needle - 1; haystack[i] != '\0'; ++i) {
        while (i < size_haystack && jump_table[(int)haystack[i]] != 0) {
            i += jump_table[(int)haystack[i]];
        }

        if (i >= size_haystack) {
            break;
        }

        if (my_strncmp(haystack + i - (size_needle - 1), needle, size_needle) == 0) {
            return haystack + i - (size_needle - 1);
        }
    }

    return NULL;
}

int my_atoi(const char *nptr) {
    assert(nptr != NULL);

    while(isspace(*nptr)) {
        nptr++;
    }

    int sign = 1;
    if (*nptr == '-') {
        sign = -1;
        nptr++;
    }
    else if (*nptr == '+') {
        nptr++;
    }

    int num = 0;
    for ( ; *nptr != '\0'; ++nptr) {
        if (!('0' <= *nptr && *nptr <= '9')) {
            return 0;
        }

        num = (num * 10) + *nptr - '0';
    }

    return sign * num;
}

char *my_strtok(char * str, const char * delim) {
    assert(delim != NULL);

    static char * string = NULL;

    if (str != NULL) {
        string = str;
    }

    int cnt_delim [CNT_SYMBOLS] = {};
    for ( ; *delim != '\0'; ++delim) {
        cnt_delim[(int)*delim] = 1;
    }

    if (*string == '\0') {
        return NULL;
    }

    char * temp = string;
    for ( ; *string != '\0'; ++string) {
        if (cnt_delim[(int)*string]) {
            *(string++) = '\0';

            break;
        }
    }

    return temp;
}