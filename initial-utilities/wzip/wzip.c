#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    int sum = 0;
    for(int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        char *str = NULL;
        size_t sz = 0;
        ssize_t len = 0;
        while ((len = getline(&str, &sz, fp)) != -1) {
            sum += strlen(str);
        }
        fclose(fp);
    }

    char *str = malloc(sizeof(char)*sum);
    int idx = 0;

    for(int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        char *s = NULL;
        size_t sz = 0;
        ssize_t len = 0;
        while ((len = getline(&s, &sz, fp)) != -1) {
            for(int i = 0; i < strlen(s); i++) {
                str[idx]=s[i];
                idx++;
            }
        }
        fclose(fp);
    }
    for(int i = 0; i < sum;) {
        int x = 1;
        if (i==strlen(str)-1) {
            fwrite(&x, sizeof(int), 1, stdout);
            printf("%c", str[i]);
            break;
        }
        int tmp = i+1;
        while (str[tmp]==str[i]) {
            x++;
            tmp++;
        }
        fwrite(&x, sizeof(int), 1, stdout);
        printf("%c", str[i]);
        i=tmp;
    }
    free(str);

    return 0;
}
