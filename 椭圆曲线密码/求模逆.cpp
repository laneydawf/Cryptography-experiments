#include <iostream>
using namespace std;
void exgcd(int a,int b, int &x, int &y, int &d)
{
	if (!b)
	{
		d = a;
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, x, y, d);
	int temp = x;
	x = y;
	y = temp - (a / b) * y;
}
int main()
{
	while(1){
		int a, b, x, y, d;
		cin >> a >> b;
		exgcd(a, b, x, y, d);
		x = (x % b + b) % b; //防止出现负数
		cout << "a关于模b的逆元为: " << x << endl;
	}
	
	return 0;
}
