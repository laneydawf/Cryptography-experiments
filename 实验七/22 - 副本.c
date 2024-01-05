#include <stdio.h>

// 定义有限域上的素数和椭圆曲线参数
#define PRIME_P 23
#define COEFF_A 1
#define COEFF_B 0
#define BASE_GX 5
#define BASE_GY 7
#define ORDER_N 17  // 生成元的阶

// 定义椭圆曲线上的点结构体
typedef struct {
	int x;
	int y;
} Point;
// 计算 a 在模 m 下的乘法逆元
int inverseModulo(int a, int m) {
	int m0 = m, t, q;
	int x0 = 0, x1 = 1;
	
	if (m == 1)
		return 0;
	
	// 应用扩展欧几里得算法来找到模逆
	while (a > 1) {
		q = a / m;
		t = m;
		m = a % m, a = t;
		t = x0;
		x0 = x1 - q * x0;
		x1 = t;
	}
	
	// 确保 x1 为正数
	if (x1 < 0)
		x1 += m0;
	
	return x1;
}
// 计算两点之和
Point addPoints(Point P, Point Q) {
	Point result;
	int m;
	
	if (P.x == Q.x && P.y == Q.y) {
		// 计算斜率 m = (3 * x^2 + A) / (2 * y)
		m = ((3 * P.x * P.x + COEFF_A) * inverseModulo(2 * P.y, PRIME_P)) % PRIME_P;
		
		// 计算新点坐标
		result.x = (m * m - 2 * P.x + PRIME_P) % PRIME_P;
		result.y = (m * (P.x - result.x) - P.y + PRIME_P) % PRIME_P;
	} else {
		// 计算斜率 m = (Q.y - P.y) / (Q.x - P.x)
		m = ((Q.y - P.y) * inverseModulo(Q.x - P.x, PRIME_P)) % PRIME_P;
		
		// 计算新点坐标
		result.x = (m * m - P.x - Q.x + PRIME_P) % PRIME_P;
		result.y = (m * (P.x - result.x) - P.y + PRIME_P) % PRIME_P;
	}
	
	return result;
}



// 计算倍点运算
Point multiplyPoint(Point P, int k) {
	Point result = {0, 0};
	
	for (int i = 0; i < k; i++) {
		result = addPoints(result, P);
	}
	
	return result;
}

int main() {
	// 选择私钥
	int privateKey = 3;
	
	// 计算公钥
	Point publicKey = multiplyPoint((Point){BASE_GX, BASE_GY}, privateKey);
	
	// 明文
	Point plaintext = {10, 12};
	
	// 加密
	int k = 6;
	Point ciphertext1 = multiplyPoint((Point){BASE_GX, BASE_GY}, k);
	Point ciphertext2 = addPoints(plaintext, multiplyPoint(publicKey, k));
	
	// 解密
	Point decryptedText = addPoints(ciphertext2, multiplyPoint(ciphertext1, ORDER_N - privateKey));
	
	// 输出结果
	printf("Public Key: (%d, %d)\n", publicKey.x, publicKey.y);
	printf("Ciphertext: ((%d, %d), (%d, %d))\n", ciphertext1.x, ciphertext1.y, ciphertext2.x, ciphertext2.y);
	printf("Decrypted Text: (%d, %d)\n", decryptedText.x, decryptedText.y);
	
	return 0;
}

