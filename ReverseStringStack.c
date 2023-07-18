#include <stdio.h>
#include <string.h>
#define MAX 100

char stack[MAX];
int top = -1;

// menambahkan karakter ke dalam stack
void push(char c) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = c;
}

// mengambil karakter dari stack
char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[top--];
}

// membalikkan string menggunakan stack
void reverse(char str[]) {
    int len = strlen(str);

    // menambahkan setiap karakter pada string ke dalam stack
    for (int i = 0; i < len; i++) {
        push(str[i]);
    }

    // mengambil setiap karakter dari stack untuk membentuk string terbalik
    for (int i = 0; i < len; i++) {
        str[i] = pop();
    }
}

int main() {
    char str[MAX];
    printf("Input string: ");
    fgets(str, MAX, stdin);

    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    // memanggil fungsi reverse untuk membalikkan string
    reverse(str);
    printf("Result: %s", str);
    return 0;
}