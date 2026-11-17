#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int find(char **w, int n, char *s) {
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (strcmp(w[m], s) < 0) l = m + 1;
        else r = m;
    }
    return l < n && !strcmp(w[l], s) ? l : -1;
}

int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {

    int n = strlen(s), m = wordsSize, k = strlen(words[0]);
    int *ans = malloc((n + 1) * sizeof(int));
    *returnSize = 0;
    if (n < m * k) return ans;

    char **w = malloc(m * sizeof(char*));
    memcpy(w, words, m * sizeof(char*));
    qsort(w, m, sizeof(char*), cmp);

    int need[m], seen[m], stamp[m];
    memset(stamp, 0, sizeof(stamp));

    for (int i = 0; i < m;) {
        int j = i + 1;
        while (j < m && !strcmp(w[i], w[j])) j++;
        need[i] = j - i;
        i = j;
    }

    int epoch = 0;
    char token[31];

    for (int i = 0; i < k; i++) {
        int left = i, count = 0;
        epoch++;

        for (int right = i; right + k <= n; right += k) {
            memcpy(token, s + right, k);
            token[k] = '\0';
            int id = find(w, m, token);

            if (id == -1) {
                count = 0;
                left = right + k;
                epoch++;
                continue;
            }

            if (stamp[id] != epoch)
                seen[id] = 0, stamp[id] = epoch;

            seen[id]++;
            count++;

            while (seen[id] > need[id]) {
                memcpy(token, s + left, k);
                token[k] = '\0';
                int x = find(w, m, token);
                seen[x]--;
                count--;
                left += k;
            }

            if (count == m)
                ans[(*returnSize)++] = left;
        }
    }

    free(w);
    return ans;
    
}