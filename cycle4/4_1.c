/* FIRST and FOLLOW using repeated passes. Use e for epsilon.
   Enter each alternative separately, for example A->a and A->e. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[20][40];
int first[26][128], follow[26][128], used[26];
int n, changed;

void add(int set[], int c) {
    if (!set[c]) { set[c] = 1; changed = 1; }
}

/* Add FIRST of a sequence; return 1 if the whole sequence is nullable. */
int sequence(int set[], char *s) {
    for (int i = 0; s[i]; i++) {
        unsigned char c = s[i];
        if (c == 'e') continue;
        if (c < 'A' || c > 'Z') { add(set, c); return 0; }
        for (int t = 0; t < 128; t++)
            if (t != 'e' && first[c-'A'][t]) add(set, t);
        if (!first[c-'A']['e']) return 0;
    }
    return 1;
}

int main(void) {
    printf("Enter the number of productions: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 20) return 1;
    printf("Enter productions (one alternative per line, e for epsilon):\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%39s", prod[i]) != 1 || strlen(prod[i]) < 4 ||
            prod[i][0] < 'A' || prod[i][0] > 'Z' ||
            prod[i][1] != '-' || prod[i][2] != '>') {
            printf("Invalid production\n"); return 1;
        }
        used[prod[i][0]-'A'] = 1;
    }
    do {
        changed = 0;
        for (int i = 0; i < n; i++) {
            int a = prod[i][0]-'A';
            if (sequence(first[a], prod[i]+3)) add(first[a], 'e');
        }
    } while (changed);
    follow[prod[0][0]-'A']['$'] = 1;
    do {
        changed = 0;
        for (int i = 0; i < n; i++) {
            int a = prod[i][0]-'A';
            for (int j = 3; prod[i][j]; j++) {
                char c = prod[i][j];
                if (c < 'A' || c > 'Z') continue;
                int b = c-'A';
                if (sequence(follow[b], prod[i]+j+1))
                    for (int t = 0; t < 128; t++)
                        if (follow[a][t]) add(follow[b], t);
            }
        }
    } while (changed);
    printf("\n--- FIRST and FOLLOW Sets ---\n");
    for (int a = 0; a < 26; a++) if (used[a]) {
        printf("FIRST(%c)  : { ", a+'A');
        for (int t = 0; t < 128; t++) if (first[a][t]) printf("%c ", t);
        printf("}\nFOLLOW(%c) : { ", a+'A');
        for (int t = 0; t < 128; t++) if (follow[a][t]) printf("%c ", t);
        printf("}\n\n");
    }
    return 0;
}
