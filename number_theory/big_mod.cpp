// b>0
ll big_mod(const char* a, ll b) {
    int st = 0;
    if (a[0] == '-') st = 1;
    int len = strlen(a);
    if (b < 0) b = -b;
    long long ans = 0;
    for (int i = st; i < len; i++) {
        ans = (ans * 10 + a[i] - '0') % b;
    }
    return ans;
}