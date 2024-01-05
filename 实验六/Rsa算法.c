#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// 求最大公约数
int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

// 计算模反元素
int mod_inverse(int a, int m) {
	int m0 = m, t, q;
	int x0 = 0, x1 = 1;
	
	if (m == 1) {
		return 0;
	}
	
	while (a > 1) {
		q = a / m;
		t = m;
		
		m = a % m;
		a = t;
		
		t = x0;
		x0 = x1 - q * x0;
		x1 = t;
	}
	
	if (x1 < 0) {
		x1 += m0;
	}
	
	return x1;
}

// 判断一个数是否为素数
int is_prime(int n) {
	if (n < 2) {
		return 0;
	}
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			return 0;
		}
	}
	return 1;
}

// 随机生成一个大素数
int random_prime() {
	int p;
	while (1) {
		p = rand() % (1 << 16) + (1 << 15);
		if (is_prime(p)) {
			return p;
		}
	}
}

// 生成 RSA 密钥对
void generate_key_pair(int* public_key, int* private_key) {
	int p, q, n, phi, e, d;
	
	// 选择两个大素数 p 和 q
	p = random_prime();
	q = random_prime();
	
	n = p * q;  // 计算 n
	phi = (p - 1) * (q - 1);  // 计算 φ(n)
	
	// 选择公钥指数 e
	e = rand() % (phi - 2) + 2;
	while (gcd(e, phi) != 1) {
		e = rand() % (phi - 2) + 2;
	}
	
	// 计算私钥指数 d
	d = mod_inverse(e, phi);
	
	public_key[0] = n;
	public_key[1] = e;
	private_key[0] = n;
	private_key[1] = d;
}

// 加密消息
int encrypt(int message, int* public_key) {
	int n = public_key[0];
	int e = public_key[1];
	int cipher = 1;
	
	for (int i = 0; i < e; i++) {
		cipher = (cipher * message) % n;
	}
	
	return cipher;
}

// 解密密文
int decrypt(int cipher, int* private_key) {
	int n = private_key[0];
	int d = private_key[1];
	int message = 1;
	
	for (int i = 0; i < d; i++) {
		message = (message * cipher) % n;
	}
	
	return message;
}

int main() {
	int message = 12345678;
	int public_key[2], private_key[2];
	int cipher, decrypted_message;
	
	srand(time(NULL));
	
	generate_key_pair(public_key, private_key);
	cipher = encrypt(message, public_key);
	decrypted_message = decrypt(cipher, private_key);
	
	printf("原消息: %d\n", message);
	printf("加密后的密文: %d\n", cipher);
	printf("解密后的消息: %d\n", decrypted_message);
	
	return 0;
}
