ll pow_mod(ll a, ll p, ll n) {
    if (p == 0) return 1;
    ll ans = pow_mod(a, p / 2, n);
    ans = ((ans % n) * (ans % n)) % n;
    if (p % 2 == 1) ans = ((ans % n) * (a % n)) % n;
    return ans;
}