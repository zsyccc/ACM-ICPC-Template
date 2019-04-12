void ex_gcd(ll a, ll b, ll& d, ll& x, ll& y) {
    if (!b) {
        d = a;
        x = 1;
        y = 0;
    } else {
        ex_gcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }
}