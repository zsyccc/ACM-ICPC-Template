// 计算模n下a的逆。如果不存在逆，返回-1
ll inv(ll a, ll n) {
    ll d, x, y;
    ex_gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n : -1;
}