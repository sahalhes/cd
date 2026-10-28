#include <stdio.h>

#define MAX 20

int n, m;
char sym[MAX];

int nfa[MAX][MAX][MAX];
/* At most 1024 subsets in this simple implementation. */
#define DFA_MAX 1024
int dfa[DFA_MAX][MAX];
int dfa_trans[DFA_MAX][MAX];
int dfa_count = 0;

int same_set(int a[], int b[]) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

int find_dfa_state(int set[]) {
    for (int i = 0; i < dfa_count; i++) {
        if (same_set(dfa[i], set))
            return i;
    }
    return -1;
}

int main() {
    int count, dest, existing, empty;
    int next_set[MAX];

    printf("Enter number of states: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) return 1;

    printf("Enter number of input symbols: ");
    if (scanf("%d", &m) != 1 || m < 1 || m > MAX) return 1;

    printf("Enter input symbols (e.g. a b): ");
    for (int i = 0; i < m; i++)
        scanf(" %c", &sym[i]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < n; k++)
                nfa[i][j][k] = 0;

    printf("\nEnter transitions for each state:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Transitions from q%d on '%c' (count): ", i, sym[j]);
            if (scanf("%d", &count) != 1 || count < 0 || count > n) return 1;

            if (count > 0) {
                printf("  Enter destination states: ");
                for (int c = 0; c < count; c++) {
                    if (scanf("%d", &dest) != 1 || dest < 0 || dest >= n) return 1;
                    nfa[i][j][dest] = 1;
                }
            }
        }
    }

    int finals[MAX] = {0}, f;
    printf("Enter number of final states: ");
    if (scanf("%d", &count) != 1 || count < 0 || count > n) return 1;
    printf("Enter final states: ");
    for (int i = 0; i < count; i++) {
        if (scanf("%d", &f) != 1 || f < 0 || f >= n) return 1;
        finals[f] = 1;
    }
    for (int s = 0; s < n; s++)
        dfa[0][s] = (s == 0);

    dfa_count = 1;

    for (int i = 0; i < dfa_count; i++) {
        for (int j = 0; j < m; j++) {
            for (int s = 0; s < n; s++)
                next_set[s] = 0;

            for (int s = 0; s < n; s++) {
                if (dfa[i][s]) {
                    for (int dest_st = 0; dest_st < n; dest_st++) {
                        if (nfa[s][j][dest_st])
                            next_set[dest_st] = 1;
                    }
                }
            }

            existing = find_dfa_state(next_set);

            if (existing != -1) {
                dfa_trans[i][j] = existing;
            } else {
                if (dfa_count == DFA_MAX) { puts("Too many DFA states"); return 1; }
                for (int s = 0; s < n; s++)
                    dfa[dfa_count][s] = next_set[s];

                dfa_trans[i][j] = dfa_count;
                dfa_count++;
            }
        }
    }

    printf("\n--- Resulting DFA Transition Table ---\n");
    printf("State\tSubset\t\t");

    for (int j = 0; j < m; j++)
        printf("%c\t", sym[j]);

    printf("\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < dfa_count; i++) {
        printf("q%d\t{ ", i);
        empty = 1;

        for (int s = 0; s < n; s++) {
            if (dfa[i][s]) {
                printf("%d ", s);
                empty = 0;
            }
        }

        (void)empty;

        printf("}\t\t");

        for (int j = 0; j < m; j++)
            printf("q%d\t", dfa_trans[i][j]);

        printf("\n");
    }

    printf("Start state: q0\nFinal DFA states: ");
    for (int i = 0; i < dfa_count; i++) {
        for (int j = 0; j < n; j++) if (dfa[i][j] && finals[j]) {
            printf("q%d ", i); break;
        }
    }
    printf("\n");
    return 0;
}
