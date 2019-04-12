bool vis[maxn];
int primes[maxn];
int primes_len;

void sieve(int n) {
    int m = (int)sqrt(n + 0.5);
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= m; i++)
        if (!vis[i]) {
            for (int j = i * i; j <= n; j += i) vis[j] = true;
        }
}

int gen_primes(int n) {
    sieve(n);
    int c = 0;
    for (int i = 2; i <= n; i++)
        if (!vis[i]) {
            primes[c++] = i;
        }
    return c;
}