const int maxn=100;
const int MOD=1e9+7;

struct Matrix {
    double a[3][3];
    Matrix inverse() {    //求三阶矩阵的行列式和逆矩阵
        double det = a[0][0] * a[1][1] * a[2][2] + a[0][1] * a[1][2] * a[2][0] + a[0][2] * a[1][0] * a[2][1] - a[0][2] * a[1][1] * a[2][0] -
                     a[0][1] * a[1][0] * a[2][2] - a[0][0] * a[1][2] * a[2][1];
        Matrix ret;
        ret.a[0][0] = a[1][1] * a[2][2] - a[1][2] * a[2][1];
        ret.a[1][0] = (a[1][0] * a[2][2] - a[1][2] * a[2][0]) * (-1);
        ret.a[2][0] = a[1][0] * a[2][1] - a[1][1] * a[2][0];
        ret.a[0][1] = (a[0][1] * a[2][2] - a[0][2] * a[2][1]) * (-1);
        ret.a[0][2] = a[0][1] * a[1][2] - a[0][2] * a[1][1];
        ret.a[1][1] = a[0][0] * a[2][2] - a[0][2] * a[2][0];
        ret.a[2][1] = (a[0][0] * a[2][1] - a[0][1] * a[2][0]) * (-1);
        ret.a[1][2] = (a[0][0] * a[1][2] - a[0][2] * a[1][0]) * (-1);
        ret.a[2][2] = a[0][0] * a[1][1] - a[0][1] * a[1][0];
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++) { ret.a[i][j] /= det; }
        }
        return ret;
    }
};

struct Matrix {
    ll a[maxn][maxn];
};

//若矩阵太大，返回值写在参数里
//中间结果用全局变量保存,最好不要重复使用
Matrix mul(const Matrix& l, const Matrix& r, int len) {       
    Matrix c;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            c.a[i][j] = 0;
            for (int k = 0; k < len; k++) {
                c.a[i][j] = (c.a[i][j] + (l.a[i][k] * r.a[k][j]) % MOD) % MOD;
            }
        }
    }
    return c;
}

Matrix pow_mod(Matrix x, ll n, int len) {
    Matrix ans;
    memset(ans.a, 0, sizeof(ans.a));
    for (int i = 0; i < len; i++) ans.a[i][i] = 1;
    while (n) {
        if (n & 1) ans = mul(ans, x, len);
        x = mul(x, x, len);
        n >>= 1;
    }
    return ans;
}

Matrix add(const Matrix& l, const Matrix& r, int len) {
    Matrix c;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            c.a[i][j] = l.a[i][j] + r.a[i][j];
            c.a[i][j] %= MOD;
        }
    }
    return c;
}

//倍增法求解a^1 + a^2 + ... + a^n
Matrix ad(const Matrix& x, int p) {
    if (p == 1) return x;
    Matrix tmp = ad(x, p / 2);
    Matrix sum = add(tmp, mul(tmp, pow_mod(x, p / 2, N), N), N);
    if (p & 1) sum = add(sum, pow_mod(x, p, N), N);
    return sum;
}