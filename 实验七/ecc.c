#include <stdio.h>

struct Point {
	int x;
	int y;
};

// 椭圆曲线参数
int p = 7;    // 素数p
int a = 0;
int b = 3;
struct Point P = {1, 2};    // 生成元P

// 计算两点相加的结果
struct Point pointAdd(struct Point P, struct Point Q) {
	struct Point result;
	if (P.x == 0 && P.y == 0)
		return Q;
	else if (Q.x == 0 && Q.y == 0)
		return P;
	else if (P.x == Q.x && P.y != Q.y)
		result.x = result.y = 0;    // O点
	else if (P.x == Q.x && P.y == Q.y) {
		int lambda = (3 * P.x * P.x + a) % p;    // 斜率
		int inverse = 1;
		for (int i = 1; i <= p-2; i++) {    // 求逆元
			inverse = (inverse * lambda) % p;
		}
		lambda = (2 * P.y * inverse) % p;
		result.x = (lambda * lambda - 2 * P.x) % p;
		result.y = (lambda * (P.x - result.x) - P.y) % p;
	}
	else {
		int lambda = (Q.y - P.y) % p;
		int inverse = 1;
		for (int i = 1; i <= p-2; i++) {    // 求逆元
			inverse = (inverse * (Q.x - P.x)) % p;
		}
		lambda = (lambda * inverse) % p;
		result.x = (lambda * lambda - P.x - Q.x) % p;
		result.y = (lambda * (P.x - result.x) - P.y) % p;
	}
	return result;
}

// 加密明文
struct Point encrypt(struct Point P, struct Point publicKey, struct Point plaintext) {
	int k = 3;    // 随机整数k
	struct Point C1 = pointAdd(P, P);    // C1 = kP
	struct Point C2 = pointAdd(publicKey, publicKey);    // C2 = kQ
	struct Point ciphertext;
	ciphertext.x = plaintext.x ^ C2.x;    // C = (C0, C1, C2)
	ciphertext.y = plaintext.y ^ C2.y;
	return ciphertext;
}

// 解密密文
struct Point decrypt(struct Point P, int privateKey, struct Point ciphertext) {
	struct Point C1 = pointAdd(P, P);    // C1 = dP
	struct Point C2 = pointAdd(C1, C1);    // C2 = 2C1 = 2dP
	struct Point decryptedtext;
	decryptedtext.x = ciphertext.x ^ C2.x;    // m = C ^ 2dP
	decryptedtext.y = ciphertext.y ^ C2.y;
	return decryptedtext;
}

int main() {
	// 输出系统参数
	printf("p = %d\n", p);
	printf("椭圆曲线：E: y^2 = x^3 + %dx + %d\n", a, b);
	printf("生成元P: (%d, %d)\n", P.x, P.y);
	
	// 选取私钥d
	int privateKey = 4;
	printf("私钥d: %d\n", privateKey);
	
	// 计算公钥Q = dP
	struct Point publicKey = pointAdd(P, P);    // Q = P + P
	for (int i = 2; i < privateKey; i++) {
		publicKey = pointAdd(publicKey, P);    // Q = Q + P
	}
	printf("公钥Q: (%d, %d)\n", publicKey.x, publicKey.y);
	
	// 随机生成明文并加密
	struct Point plaintext = {5, 6};
	printf("明文: (%d, %d)\n", plaintext.x, plaintext.y);
	struct Point ciphertext = encrypt(P, publicKey, plaintext);
	printf("密文: (%d, %d)\n", ciphertext.x, ciphertext.y);
	
	// 解密密文
	struct Point decryptedtext = decrypt(P, privateKey, ciphertext);
	printf("解密后的明文: (%d, %d)\n", decryptedtext.x, decryptedtext.y);
	
	return 0;
}

