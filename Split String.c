#include <stdio.h>
#include <string.h>

size_t mystrlen(const char *s) {
    
    size_t i = 0;
    while (*s != '\0') {
        s++;
        i++;
    }

    return i;

}

char *simple_split(char *s, char delim) {
    if (s == NULL || *s == '\0') {
        return NULL;
    }

    char *ptr = s;
    
 while (*ptr != '\0') {
        if (*ptr == delim) {
            *ptr = '\0'; 
            return ptr + 1; 
        }
        ptr++;
    }

    return NULL;
}




int main() {
    const char *string = "Hello World";
    int x = mystrlen(string);
    printf("Size: %d\n", x);

    char *s = strdup("can all aardvarks quaff?");
    char *bit = simple_split(s, 'a');
    puts(s);
    puts(bit);
    free(s);

}