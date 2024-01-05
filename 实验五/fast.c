#include<stdio.h>

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

int main(){
	int a,m,n;
	printf("输入a,m,n\n");
	scanf("%d %d %d",&a,&m,&n);
	int d=FastExponent(a,m,n);
	printf("a^m %% n = %d",d);
	
	
	return 0;
}
