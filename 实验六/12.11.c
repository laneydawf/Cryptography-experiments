#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int gcd(long long int a,long long int b) {
	while (b != 0) {
		long long int t = b;
		b = a % b;
		a = t;
	}
	return a;
}

long long int extended_gcd(long long int a,long long int b,long long int *x,long long int *y) {
	if (b == 0) {
		*x = 1;
		*y = 0;
		return a;
	}
	long long int x1, y1;
	long long int gcd = extended_gcd(b, a % b, &x1, &y1);
	*x = y1;
	*y = x1 - (a / b) * y1;
	return gcd;
}

long long int inverse(long long int a,long long int n) {
	long long int x, y;
	long long int gcd = extended_gcd(a, n, &x, &y);
	if (gcd != 1) {
		return -1; // 没有逆元
	} else {
		return (x % n + n) % n;
	}
}

long long int mod_pow(long long int a,long long int b,long long int n) {
	long long int r = 1;
	while (b > 0) {
		if (b & 1) {
			r = ((long long)r * a) % n;
		}
		a = ((long long)a * a) % n;
		b >>= 1;
	}
	return r;
}

long long int is_prime(long long int n) {
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

long long int gen_prime(int bits) {
	long long int p, count = 0;
	do {
		p = rand() % (1 << bits) + (1 << (bits - 1));
		count++;
	} while (!is_prime(p) && count < 1000);
	return p;
}

void gen_key_pair(int bits,long long int *e,long long int *d,long long int *N) {
	srand(time(NULL));
	printf("生成p，q...\n");
	// 生成两个大素数p和q
	long long int p = gen_prime(bits / 2);
	long long int q = gen_prime(bits / 2);
	printf("p=%lld,q=%lld\n",p,q);
	//欧拉函数值
	long long int phiN = (p - 1) * (q - 1);
	
	// 选择公钥e，满足1 < e < phi(N)且e与phi(N)互质
	*e = 65537;
	printf("计算公钥（N，e）...\n");
	// 计算模数N
	*N = p*q;
	
	// 计算私钥d
	*d = inverse(*e, phiN);
}

long long int encrypt(long long int m,long long int e,long long int N) {
	return mod_pow(m, e, N);
}

long long int decrypt(long long int c,long long int d,long long int N) {
	return mod_pow(c, d, N);
}

int main() {
	int bits = 32;
	long long int e, d, N;
	
	gen_key_pair(bits, &e, &d, &N);
	//printf("%d\n",count);
	printf("公钥:（N，e）=（%lld, %lld）\n", N, e);
	
	printf("计算私钥d...\n");
	printf("私钥: d = %lld\n", d);
	
	long long int m = rand() % N;
	long long int c = encrypt(m, e, N);
	long long int decrypted = decrypt(c, d, N);
	printf("明文m = %lld, 密文c = %lld\n解密后的明文(16进制) = %llx\n解密后的明文(十进制) = %lld\n", m, c, decrypted, decrypted);
	
	//printf("明文m = %lld, 密文c = %lld\n解密后的明文 = %lld\n", m, c, decrypted);
	
	return 0;
}
