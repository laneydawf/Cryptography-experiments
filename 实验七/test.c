#include <stdio.h>
#include <stdlib.h>

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
	return (m - 1);
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
	
	for (int i = 1; i < d; i++) {
		Q = point_addition(a, b, p, temp, P);
		temp = Q;
	}
	
	if (Q.x < 0) {
		Q.x = (Q.x + p) % p;
	}
	
	if (Q.y < 0) {
		Q.y = (Q.y + p) % p;
	}
	
	return Q;
}
#include <time.h>

int main() {
//	Point P = {2, 2};
//	Point R = scalar_multiply(2, 0, 3, 7, P);
//
//	printf("%d %d\n", R.x, R.y);
srand(time(0));
	int a= rand();
	int b=a%7+1;
	printf("%d %d",a,b);
	
	return 0;
}
