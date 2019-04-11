//求因子个数
int cnt(int n) {
    int s = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int a = 0;
            while (n % i == 0) {
                n /= i;
                a++;
            }
            s = s * (a + 1);
        }
    }
    if (n > 1) s = s * 2;
    return s;
}

//求因子的和
int sum(int n) {
    int s = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int a = 1;
            while (n % i == 0) {
                n /= i;
                a *= i;
            }
            s = s * (a * i - 1) / (i - 1);
        }
    }
    if (n > 1) s = s * (1 + n);
    return s;
}