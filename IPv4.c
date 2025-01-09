#include <stdio.h>
#include <string.h>

int isDigit(char c) {
    return c >= '0' && c <= '9';
}

int parse(char *buffer, int itr) {
    if (itr == 0) return -1;
    if (itr > 1 && buffer[0] == '0') return -1;

    int num = 0;
    for (int i = 0; i < itr; i++) {
        int diff = buffer[i] - '0';
        if (diff >= 0 && diff < 10) {
            num = (num * 10) + diff;
        } else {
            return -1;
        }
    }
    if (num >= 0 && num < 256)
        return num;
    else
        return -1;
}

void validateIP(char *input) {
    int len = strlen(input);

    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len < 7 || len > 15) {
        printf("Invalid\n");
        return;
    }

    char buffer[4];
    int isValid = 1;
    char *ptr = input;
    int itr = 0;
    int dots = 0;

    for (; *ptr != '\0' && isValid; ptr++) {
        if (*ptr == '.') {
            if (itr == 0) {
                isValid = 0;
                break;
            }
            buffer[itr] = '\0';
            int num = parse(buffer, itr);
            if (num == -1) {
                isValid = 0;
                break;
            }
            dots++;
            itr = 0;
            if (dots > 3) {
                isValid = 0;
                break;
            }
            continue;
        }
        if (!isDigit(*ptr)) {
            isValid = 0;
            break;
        }
        if (itr >= 3) {
            isValid = 0;
            break;
        }
        buffer[itr++] = *ptr;
    }

    if (isValid && dots == 3 && itr > 0) {
        buffer[itr] = '\0';
        isValid = parse(buffer, itr) != -1;
    } else {
        isValid = 0;
    }
    if(isValid)
        printf("Valid");
    else
        printf("Invalid");
}

int main() {
    char input[16];
    while(1){
        printf("\nEnter IP address (or exit): ");
        fgets(input, 16, stdin);
        if (strncmp(input, "exit", 4) == 0 && (input[4] == '\n' || input[4] == '\0')) 
            break;
        validateIP(input);
    }
    return 0;
}
