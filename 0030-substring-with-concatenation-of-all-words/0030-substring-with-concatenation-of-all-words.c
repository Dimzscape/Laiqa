
#include <stdlib.h>
#include <string.h>

unsigned long long hash(const char *s, int k) {
    unsigned long long h = 14695981039346656037ULL;
    while (k--)
        h = (h ^ (unsigned char)*s++) * 1099511628211ULL;
    return h;
}

int lookup(char *s, char **words, int *table, int mask, int k) {
    int h = hash(s, k) & mask;
    while (table[h]) {
        int id = table[h] - 1;
        if (!memcmp(s, words[id], k)) return id;
        h = (h + 1) & mask;
    }
    return -1;
}

int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    int n = strlen(s), m = wordsSize, k = strlen(words[0]);
    int *ans = malloc((n + 1) * sizeof(int));
    *returnSize = 0;
    if (n < m * k) return ans;

    int cap = 1;
    while (cap < 4 * m) cap *= 2;

    int *table = calloc(cap, sizeof(int));
    int *need = calloc(m, sizeof(int));
    int *seen = calloc(m, sizeof(int));
    int *ids = malloc(n * sizeof(int));

    for (int i = 0; i < m; i++) {
        int h = hash(words[i], k) & (cap - 1);
        while (table[h] && strcmp(words[table[h]-1], words[i]))
            h = (h + 1) & (cap - 1);

        if (!table[h]) table[h] = i + 1;
        need[table[h] - 1]++;
    }

    for (int i = 0; i < k; i++) {
        memset(seen, 0, m * sizeof(int));
        int left = i, count = 0;

        for (int right = i; right + k <= n; right += k) {
            int id = lookup(s + right, words, table, cap - 1, k);
            ids[right] = id;

            if (id == -1) {
                while (left < right) {
                    seen[ids[left]]--;
                    left += k;
                }
                left = right + k;
                count = 0;
                continue;
            }

            seen[id]++;
            count++;

            while (seen[id] > need[id]) {
                seen[ids[left]]--;
                left += k;
                count--;
            }

            if (count == m) {
                ans[(*returnSize)++] = left;
                seen[ids[left]]--;
                left += k;
                count--;
            }
        }
    }

    free(table);
    free(need);
    free(seen);
    free(ids);
    return ans;
}
