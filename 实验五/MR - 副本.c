#include <stdio.h>
#include <stdlib.h>
long long modular_exponentiation(long long base, long long exponent, long long modulus) {
	long long result = 1;
	base = base % modulus;
	
	while (exponent > 0) {
		if (exponent % 2 == 1) {
			result = (result * base) % modulus;
		}
		base = (base * base) % modulus;
		exponent = exponent / 2;
	}
	
	return result;
}

int miller_rabin_test(long long a, long long n) {
	if (n <= 1) {
		return 0;  // 不是素数
	}
	if (n == 2 || n == 3) {
		return 1;  // 是素数
	}
	if (n % 2 == 0) {
		return 0;  // 偶数不是素数
	}
	
	long long d = n - 1;
	int k = 0;
	
	while (d % 2 == 0) {
		d = d / 2;
		k++;
	}
	
	long long x, witness;
	for (int i = 0; i < a; i++) {
		witness = (rand() % (n - 3)) + 2;  // 随机选取一个见证数
		x = modular_exponentiation(witness, d, n);
		
		if (x == 1 || x == n - 1) {
			continue;  // 通过了第一个条件
		}
		
		for (int j = 0; j < k - 1; j++) {
			x = modular_exponentiation(x, 2, n);
			
			if (x == n - 1) {
				break;  // 通过了第二个条件
			}
			
			if (x == 1) {
				return 0;  // 不是素数
			}
		}
		
		if (x != n - 1) {
			return 0;  // 不是素数
		}
	}
	
	return 1;  // 是素数
}

int main() {
	int n;  // 需要判断的数
	printf("输入需要验证的数字：");
	scanf("%d",&n);
	if (miller_rabin_test(10, n)) {
		printf("%d 有很大可能是素数\n", n);
	} else {
		printf("%d 不是素数\n", n);
	}
	
	return 0;
}
