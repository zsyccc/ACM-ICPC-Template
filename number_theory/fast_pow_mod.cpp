ll fast_pow_mod(ll a, ll p, ll n) {
    if (p == 0) return 1;
    a = a % n;
    ll ans = pow_mod(a, p / 2, n) % n;
    ans = (ans * ans) % n;
    if (p % 2 == 1) ans = (ans * a) % n;
    return ans;
}

ll faster_pow_mod(ll a, ll b, ll c) {
    ll ans = 1;
    a = a % c;
    while (b != 0) {
        if (b & 1) ans = (ans * a) % c;
        b >>= 1;
        a = (a * a) % c;
    }
    return ans;
}