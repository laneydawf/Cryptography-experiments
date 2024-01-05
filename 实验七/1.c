#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
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
	return 0;
}

int get_gcd(int x, int y) {
	if (y == 0) {
		return x;
	} else {
		return get_gcd(y, x % y);
	}
}

Point point_addition(int a, int b, int p, Point Q, Point P) {
	Point R;
	int x1 = Q.x, y1 = Q.y, x2 = P.x, y2 = P.y;
	int member, denominator, gcd_value, inverse_value, k;
	
	if (x1 == 0 && y1 == 0) {
		return P;
	}
	if (x2 == 0 && y2 == 0) {
		return Q;
	}
	
	
	if (x1 == x2 && y1 == y2) {
		member = 3 * (x1 * x1) + a;
		denominator = 2 * y1;
	} else {
		member = y2 - y1;
		denominator = x2 - x1;
		
		if (member * denominator < 0) {
			member = abs(member);
			denominator = abs(denominator);
			member=denominator*p-member;
		}
	}
	
	gcd_value = get_gcd(member, denominator);
	member = member / gcd_value;
	denominator = denominator / gcd_value;
	
	inverse_value = mod_inverse(denominator, p);
	k = (member * inverse_value) % p;
	
	R.x = (k * k - x1 - x2 + p) % p;
	R.y = (k * (x1 - R.x) - y1 + p) % p;
	
	return R;
}

Point scalar_multiply(int d, int a, int b, int p, Point P) {
	Point Q = {0, 0};
	Point temp = P;
	
	while (d != 1) {
		Q = point_addition(a, b, p, temp, P);	
		temp = Q;
		d -= 1;
	}
	
	if(Q.x<0){
		Q.x=(Q.x+p)%p;
	}
	if(Q.y<0){
		Q.y=(Q.y+p)%p;
	}
	
	return Q;
}

int main() {
	// 系统参数
	int p = 7;
	int a = 0;
	int b = 3;
	Point G = {1, 2};
	int n = 13;
	
	// 生成私钥 d
	int private_key_d = 4;
	
	// 生成公钥 Q
	Point public_key_Q = scalar_multiply(private_key_d, a, b, p, G);
	//printf("%d %d",public_key_Q.x,public_key_Q.y);
	// 明文
	Point plaintext = {3, 4};
	
	// 加密
	srand(time(0));
	int k = rand()%7+1;
	Point C0 = scalar_multiply(k, a, b, p, G);
	//printf("C0=(%d %d)\n",C0.x,C0.y);
	Point KP=scalar_multiply(k,a,b,p,public_key_Q);
	//printf("KP=%d %d\n",KP.x,KP.y);
	
	Point ciphertext;
	ciphertext.x = (KP.x*plaintext.x)%p;
	ciphertext.y = (plaintext.y * KP.y) % p;
	//printf("%d %d\n",ciphertext.x,ciphertext.y);
	
	// 解密
	Point dC0 = scalar_multiply(private_key_d, a, b, p, C0);
	//Point dC0 = {1,5};
	//printf("dC0=(%d %d)\n",dC0.x,dC0.y);
	Point decrypted_text;
	//decrypted_text.x = ciphertext.x;
	
	//printf("%d %d \n",dC0.x,mod_inverse(dC0.x,p));
	decrypted_text.x = (ciphertext.x * mod_inverse(dC0.x,p)) % p;
	if (decrypted_text.x < 0) {
		decrypted_text.x += p;
	}
	
	decrypted_text.y = (ciphertext.y*mod_inverse(dC0.y,p)) % p;
	if (decrypted_text.y < 0) {
		decrypted_text.y += p;
	}
	
	// 输出结果
	printf("素数域 (p): %d\n", p);
	printf("曲线参数 (a, b): %d, %d\n", a, b);
	printf("基点 (P): (%d, %d)\n", G.x, G.y);
	printf("基点阶数 (n): %d\n", n);
	printf("私钥 (d): %d\n", private_key_d);
	printf("公钥 (Q): (%d, %d)\n", public_key_Q.x, public_key_Q.y);
	printf("明文: (%d, %d)\n", plaintext.x, plaintext.y);
	printf("随机数：%d\n",k);
	printf("密文: ( (%d,%d), %d, %d )\n",C0.x,C0.y, ciphertext.x, ciphertext.y);
	printf("解密后的文本: (%d, %d)\n", decrypted_text.x, decrypted_text.y);
	
	return 0;
}

