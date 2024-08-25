#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_match(char *str, char *target) {
    int len = strlen(str);
    int f = 0;
    for(int i = 0; i < len; i++) {
        int g = i+strlen(target);
        if (g>=len) {
            break;
        }
        int idx = 0;
        int f2 = 1;
        for(int j = i; j < g; j++) {
            if (target[idx]!=str[j]) {
                f2 = 0;
                break;
            }
            idx++;
        }
        if (f2==1) {
            f=1;
        }
    }
    if (f==1) {
        printf("%s", str);
    }
}

int main(int argc, char *argv[]) {
    char *target = argv[1];
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    if (argc == 2) {
        char *str;
        size_t sz = 0;
        ssize_t len = 0;
        while ((len = getline(&str, &sz, stdin)) != -1) {
            get_match(str, target);
        }
    } else {
        for(int i = 2; i < argc ; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                exit(1);
            }
            char *str = NULL;
            size_t sz = 0;
            ssize_t len = 0;
            while ((len = getline(&str, &sz, fp)) != -1) {
                get_match(str, target);
            }
        }
    }

    return 0;
}
