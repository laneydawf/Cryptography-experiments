#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gcd(int a, int b) {
	while (b != 0) {
		int t = b;
		b = a % b;
		a = t;
	}
	return a;
}

int extended_gcd(int a, int b, int *x, int *y) {
	if (b == 0) {
		*x = 1;
		*y = 0;
		return a;
	}
	int x1, y1;
	int gcd = extended_gcd(b, a % b, &x1, &y1);
	*x = y1;
	*y = x1 - (a / b) * y1;
	return gcd;
}

int inverse(int a, int n) {
	int x, y;
	int gcd = extended_gcd(a, n, &x, &y);
	if (gcd != 1) {
		return -1; // 没有逆元
	} else {
		return (x % n + n) % n;
	}
}

int mod_pow(int a, int b, int n) {
	int r = 1;
	while (b > 0) {
		if (b & 1) {
			r = ((long long)r * a) % n;
		}
		a = ((long long)a * a) % n;
		b >>= 1;
	}
	return r;
}

int is_prime(int n) {
	if (n <= 1) {
		return 0;
	}
	if (n <= 3) {
		return 1;
	}
	if (n % 2 == 0 || n % 3 == 0) {
		return 0;
	}
	for (int i = 5; i * i <= n; i += 6) {
		if (n % i == 0 || n % (i + 2) == 0) {
			return 0;
		}
	}
	return 1;
}

long int gen_prime(long int bits) {
	int p, count = 0;
	do {
		p = rand() % (1 << bits) + (1 << (bits - 1));
		if (p % 2 == 0) { // 保证素数是奇数
			p++;
		}
		count++;
	} while (!is_prime(p) && count < 100);
	return p;
}

void gen_key_pair(long int bits,long int *e,long int *d,long int *N) {
	srand(time(NULL));
	printf("生成p，q...\n");
	// 生成两个大素数p和q
	long int p = gen_prime(bits / 2);
	long int q = gen_prime(bits / 2);
	while (p == q) { // 确保p和q不相等
		q = gen_prime(bits);
	}
	printf("p=%ld,q=%ld\n",p,q);
	long int phiN = (p - 1) * (q - 1);
	
	// 选择公钥e，满足1 < e < phi(N)且e与phi(N)互质
	*e = 65537;
	printf("计算公钥（N，e）...\n");
	// 计算模数N
	*N = p * q;
	
	
	// 计算私钥d
	*d = inverse(*e, phiN);
	
	
}

int encrypt(long int m,long int e,long int N) {
	return mod_pow(m, e, N);
}

int decrypt(long int c,long int d,long int N) {
	return mod_pow(c, d, N);
}

int main() {
	int bits = 32;
	long int e, d, N;
	
	gen_key_pair(bits, &e, &d, &N);
	printf("公钥:（N，e）=（%ld, %ld）\n", N, e);
	
	printf("计算私钥d...\n");
	printf("私钥: d = %ld\n", d);
	
	int m = rand() % N;
	int c = encrypt(m, e, N);
	int decrypted = decrypt(c, d, N);
	
	printf("明文m = %d, 密文c = %d\n解密后的明文 = %d\n", m, c, decrypted);
	
	return 0;
}

