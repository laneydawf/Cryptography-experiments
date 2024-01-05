#include <stdio.h>

typedef struct {
	int x;
	int y;
} Point;

int mod_inverse(int a, int m) {
	for (int i = 1; i < m; i++) {
		if ((a * i) % m == 1) {
			return i;
		}
	}
	return 0;  // Inverse doesn't exist
}

Point point_addition(int a, int b, int p, Point P, Point Q) {
	Point R;
	int m;
	
	if (P.x == 0 && P.y == 0) {  // Point at infinity
		return Q;
	}
	if (Q.x == 0 && Q.y == 0) {  // Point at infinity
		return P;
	}
	
	if (P.x != Q.x || P.y != Q.y) {
		m = ((Q.y - P.y) * mod_inverse(Q.x - P.x + p, p)) % p;  // 修正：确保 y 和 -y 对应相同 x
	} else {
		m = ((3 * P.x * P.x + a) * mod_inverse(2 * P.y, p)) % p;
	}
	
	R.x = (m * m - P.x - Q.x + p) % p;
	R.y = (m * (P.x - R.x) - P.y + p) % p;
	
	return R;
}

Point scalar_multiply(int d, int a, int b, int p, Point P) {
	Point Q = {0, 0};  // Point at infinity
	
	for (int i = 0; i < d; i++) {
		Q = point_addition(a, b, p, Q, P);
	}
	
	return Q;
}

int main() {
	// 系统参数
	int p = 7;
	int a = 0;
	int b = 3;
	Point P = {1, 2};
	int n = 13;  // 基点 P 的阶
	
	// 生成私钥 d
	int private_key_d = 9;
	
	// 生成公钥 Q
	Point public_key_Q = scalar_multiply(private_key_d, a, b, p, P);
	
	// 随机生成明文
	Point plaintext = {3, 1};
	
	// 加密
	int k = 5;  // 随机整数
	Point C0 = scalar_multiply(k, a, b, p, P);
	Point ciphertext;
	ciphertext.x = C0.x;
	ciphertext.y = ((plaintext.y + C0.y) % p + p) % p;  // 修改取模运算
	
	// 解密
	Point dC0 = scalar_multiply(private_key_d, a, b, p, C0);
	Point decrypted_text;
	decrypted_text.x = ciphertext.x;
	decrypted_text.y = (ciphertext.y - dC0.y + p) % p;  // 修正取模运算
	if (dC0.y > ciphertext.y) {
		decrypted_text.y = (p - dC0.y + ciphertext.y) % p;
	} else {
		decrypted_text.y = (ciphertext.y - dC0.y) % p;
	}
	
	// 输出结果
	printf("素数 (p): %d\n", p);
	printf("椭圆曲线: y^2 = x^3 + %d*x + %d\n", a, b);
	printf("中点 (P): (%d, %d)\n", P.x, P.y);
	printf("P的阶数 (n): %d\n", n);
	printf("私钥 (d): %d\n", private_key_d);
	printf("公钥 (Q): (%d, %d)\n", public_key_Q.x, public_key_Q.y);
	printf("明文: (%d, %d)\n", plaintext.x, plaintext.y);
	printf("密文: (%d, %d)\n", ciphertext.x, ciphertext.y);
	printf("解密后的文本: (%d, %d)\n", decrypted_text.x, decrypted_text.y);
	
	return 0;
}

