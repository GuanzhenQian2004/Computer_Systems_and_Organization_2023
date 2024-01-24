#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[]) {

    char type;
    int int1;
    int int2;
    float float1;
    float float2;
    char string1[11];
    char string2[11];

    if (argc == 2) {
        if (strcmp(argv[1], "-i") == 0) {
            type = 'I';
        } else if (strcmp(argv[1], "-f") == 0) {
            type = 'F';
        } else if (strcmp(argv[1], "-s") == 0) {
            type = 'S';
        } else {
            printf("Invalid flag supplied\n");
            return 1;
        }
    } else {
        printf("What types of values do you want to add (I/F/S): ");
        scanf("%c", &type);
    }

    switch (type) {
        case 'I':
            printf("Enter your first value: ");
            scanf("%d", &int1);
            printf("Enter your second value: ");
            scanf("%d", &int2);
            printf("The result is: %d\n", int1 + int2);
            return 0;
        case 'F':
            printf("Enter your first value: ");
            scanf("%f", &float1);
            printf("Enter your second value: ");
            scanf("%f", &float2);
            printf("The result is: %.8g\n", float1 + float2);
            return 0;
        case 'S':
            printf("Enter First String: ");
            scanf("%s", string1);
            printf("Enter Second String: ");
            scanf("%s", string2);
            strcat(string1,string2);
            printf("The result is: %s\n", string1);
            return 0;
        default:
            printf("Invalid type. Please enter I, F, or S.\n");
            return 1;
    }

}
