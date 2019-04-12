const int maxn = 100;

// 求因子个数
int euler_phi(int n) {
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

int phi[maxn];

// 求1~n的欧拉函数值
void phi_table(int n) {
    for (int i = 2; i <= n; i++) phi[i] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        if (!phi[i]) {
            for (int j = i; j <= n; j += i) {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
}

// 求因子的和
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

const int MOD = 1e9 + 7;

// 同时求cnt和sum
// sum取模
void solve(int n, ll& sum, ll& cnt) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ll a = 1;
            ll t = 0;
            while (n % i == 0) {
                n /= i;
                a = a * i % MOD;
                t++;
            }
            cnt *= t + 1;
            sum = sum * ((a * i - 1) / (i - 1) % MOD) % MOD;
        }
    }
    if (n > 1) {
        sum = sum * (1 + n) % MOD;
        cnt *= 2;
    }
}

int primes[maxn];
int primes_len;

// 打素数表，只遍历素数
ll cnt(ll n) {
    ll s = 1;
    for (int i = 0; i < primes_len && primes[i] * primes[i] <= n; ++i) {
        if (n % primes[i] == 0) {
            ll a = 0;
            while (n % primes[i] == 0) {
                n /= primes[i];
                a++;
            }
            s = s * (a + 1);
        }
    }
    if (n > 1) s = s * 2;
    return s;
}