// n个方程：x=a[i](mod m[i]) (0<=i<n)
ll china(int n, ll* a, ll* m) {
    ll M = 1, d, y, x = 0;
    for (int i = 0; i < n; i++) M *= m[i];
    for (int i = 0; i < n; i++) {
        ll w = M / m[i];
        ex_gcd(m[i], w, d, d, y);
        x = (x + y * w * a[i]) % M;
    }
    return (x + M) % M;
}

// unused
long long ex_crt(long long a[], long long n[], int num) {
    long long n1 = n[0], a1 = a[0], n2, a2, k1, k2, x0, gcd, c;
    for (int i = 1; i < num; i++) {
        n2 = n[i], a2 = a[i];
        c = a2 - a1;
        gcd = ex_gcd(n1, n2, k1, k2);  //解得：n1*k1+n2*k2=gcd(n1,n2)
        if (c % gcd) {
            flag = 1;
            return 0;  //无解
        }
        x0 = c / gcd * k1;  // n1*x0+n2*(c/gcd*k2)=c  PS:k1/gcd*c错误！
        t = n2 / gcd;
        x0 = (x0 % t + t) % t;  //求n1*x0+n2*y=c的x0的最小解
        a1 += n1 * x0;
        n1 = n2 / gcd * n1;
    }
    return a1;
}