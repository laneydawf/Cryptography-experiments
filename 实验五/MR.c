#include <stdio.h>
#include <stdlib.h>
int FastExponent(int a, int m, int n) {
	int d = 1;
	int binaryM[16] = {0};
	int i = 0;
	
	while (m > 0) {
		binaryM[i] = m % 2;
		m = m / 2;
		i++;
	}
	
	for (int j = i - 1; j >= 0; j--) {
		d = (d * d) % n;
		if (binaryM[j] == 1) {
			d = (d * a) % n;
		}
	}
	return d;
}

int WITNESS(int a,int n) {
	if (n <= 1) 
		return 0; 
	
	if (n == 2 || n == 3)
		return 1;
	
	if (n % 2 == 0)
		return 0; 
	
	int d = n-1;
	int k = 0;
	
	while (d % 2 == 0) {
		d = d / 2;
		k++;
	}
	
	int x, witness;
	for (int i = 0; i < a; i++) {
		witness = (rand() % (n - 3)) + 2; 
		x = FastExponent(witness, d, n);

		if (x == 1 || x == n - 1) {
			continue;  
		}
		
		for (int j = 0; j < k - 1; j++) {
			x = FastExponent(x, 2, n);
			
			if (x == n - 1) {
				break;  
			}
			
			if (x == 1) {
				return 0; 
			}
		}
		
		if (x != n - 1) {
			return 0;
		}
	}
	
	return 1;
}

int main() {
	int n;
	printf("输入需要验证的数字：");
	scanf("%d",&n);
	if (WITNESS (10, n)) {
		printf("%d 有很大可能是素数\n", n);
	}else{
		printf("%d 不是素数\n", n);
	}
	
	return 0;
}
