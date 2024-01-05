#include <iostream>

class Point {
public:
	int x;
	int y;
	
	// 默认构造函数，表示无穷远点
	Point() : x(0), y(0) {}
	
	// 构造函数，用于创建具有给定坐标的点
	Point(int x, int y) : x(x), y(y) {}
	
	// 重载+运算符，用于实现椭圆曲线上的点加法
	Point operator+(const Point& other) const {
		Point result;
		int m;
		
		if (x != other.x || y != other.y) {
			m = ((other.y - y) * mod_inverse(other.x - x + p, p)) % p;
		} else {
			m = ((3 * x * x + a) * mod_inverse(2 * y, p)) % p;
		}
		
		result.x = (m * m - x - other.x + p) % p;
		result.y = (m * (x - result.x) - y + p) % p;
		
		return result;
	}
	
	// 重载*运算符，用于实现点的倍乘
	Point operator*(int scalar) const {
		Point result = *this;
		for (int i = 1; i < scalar; i++) {
			result = result + *this;
		}
		return result;
	}
	
private:
	static int mod_inverse(int a, int m) {
		for (int i = 1; i < m; i++) {
			if ((a * i) % m == 1) {
				return i;
			}
		}
		return 0;  // Inverse doesn't exist
	}
	
	static const int p = 23;  // 模数，即素数
	static const int a = 0;   // 椭圆曲线参数 a
	static const int b = 3;   // 椭圆曲线参数 b
};

int main() {
	// 系统参数
	Point P(1, 2);  // 基点 P
	
	// 生成私钥 d
	int private_key_d = 6;
	
	// 生成公钥 Q
	Point public_key_Q = P * private_key_d;
	
	// 明文
	Point plaintext(8, 12);
	
	// 加密
	int k = 5;
	Point C0 = P * k;
	Point ciphertext = C0 + plaintext;
	
	// 解密
	Point dC0 = P * private_key_d;
	Point decrypted_text = ciphertext + (dC0 * -1);  // -1 是为了获取 C0 的逆元
	
	// 输出结果
	std::cout << "基点 (P): (" << P.x << ", " << P.y << ")\n";
	std::cout << "私钥 (d): " << private_key_d << "\n";
	std::cout << "公钥 (Q): (" << public_key_Q.x << ", " << public_key_Q.y << ")\n";
	std::cout << "明文: (" << plaintext.x << ", " << plaintext.y << ")\n";
	std::cout << "密文: (" << ciphertext.x << ", " << ciphertext.y << ")\n";
	std::cout << "解密后的文本: (" << decrypted_text.x << ", " << decrypted_text.y << ")\n";
	
	return 0;
}

