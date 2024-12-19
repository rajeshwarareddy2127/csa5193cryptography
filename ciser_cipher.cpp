#include <stdio.h>
#include <string.h>

void encryption(char s[], char res[], int k,int n) {
    int index = 0;

    for (int i = 0; i < n; i++) {
        int num = (int)s[i] + k;  
        res[index++] = (char)num; 
    }

    res[index] = '\0'; 
    printf("Encrypted string: %s\n", res);
}


void decryption(char res[], int k,int n) {
    char s1[20];
    int index = 0;

    for (int i = 0; res[i] != '\0'; i++) {
        int num = (int)res[i] - k; 
        s1[index++] = (char)num;  
    }

    s1[index] = '\0'; 
    printf("Decrypted string: %s\n", s1);
}

int main() {
    char str[20], encrypted[20];
    int k,n;
    printf("enter the n value:");
    scanf("%d",&n);
    printf("Enter the k value: ");
    scanf("%d", &k);

    
    printf("Enter the string (3 characters): ");
    for (int i = 0; i < n; i++) {
        scanf(" %c", &str[i]);
    }
    str[n] = '\0'; 


    encryption(str, encrypted, k,n);

    decryption(encrypted, k,n);

    return 0;
}

