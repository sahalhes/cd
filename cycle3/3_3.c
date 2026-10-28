/*
Write a program to convert NFA with epsilon transition to NFA without epsilon transition.
*/

#include <stdio.h>
#include <string.h>

#define MAX 20

int n;
char trans[MAX][MAX][10];
int closure[MAX][MAX];

void computeClosure() {
    int queue[100];
    int front, rear, current;

    for (int start = 0; start < n; start++) {
        front = 0;
        rear = 0;

        closure[start][start] = 1;
        queue[rear++] = start;

        while (front < rear) {
            current = queue[front++];

            for (int next = 0; next < n; next++) {
                if (strchr(trans[current][next], 'e') != NULL) {
                    if (closure[start][next] == 0) {
                        closure[start][next] = 1;
                        queue[rear++] = next;
                    }
                }
            }
        }
    }
}

void printClosure() {
    int first;

    printf("\n--- Epsilon Closures ---\n");
    for (int i = 0; i < n; i++) {
        printf("e-closure(q%d) = { ", i);
        first = 1;
        for (int j = 0; j < n; j++) {
            if (closure[i][j]) {
                if (!first) printf(", ");
                printf("q%d", j);
                first = 0;
            }
        }
        printf(" }\n");
    }
}

void printNFATransitions(void) {
    int edge[MAX][MAX][128] = {0};
    printf("\n--- NFA Without Epsilon Transitions ---\n");
    /* closure(move(closure(state), symbol)) */
    for (int i = 0; i < n; i++)
        for (int c = 0; c < n; c++) if (closure[i][c])
            for (int j = 0; j < n; j++)
                for (int k = 0; trans[c][j][k]; k++) {
                    unsigned char sym = trans[c][j][k];
                    if (sym == 'e' || sym == '-' || sym >= 128) continue;
                    for (int d = 0; d < n; d++)
                        if (closure[j][d]) edge[i][d][sym] = 1;
                }
    for (int i = 0; i < n; i++)
        for (int d = 0; d < n; d++)
            for (int sym = 0; sym < 128; sym++)
                if (edge[i][d][sym]) printf("q%d on '%c' -> q%d\n", i, sym, d);
}

int main() {
    printf("Enter number of states: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) return 1;

    printf("\nEnter transitions ('e' for epsilon, '-' for none):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("q%d to q%d: ", i, j);
            if (scanf("%9s", trans[i][j]) != 1) return 1;
        }
    }

    computeClosure();
    printClosure();
    printNFATransitions();

    int count, f, finals[MAX] = {0};
    printf("Enter number of final states: ");
    if (scanf("%d", &count) != 1 || count < 0 || count > n) return 1;
    printf("Enter final states: ");
    for (int i = 0; i < count; i++) {
        if (scanf("%d", &f) != 1 || f < 0 || f >= n) return 1;
        finals[f] = 1;
    }
    printf("New final states: ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (closure[i][j] && finals[j]) {
            printf("q%d ", i); break;
        }
    }
    printf("\nStart state: q0\n");
    return 0;
}
