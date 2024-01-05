#include<stdio.h>
int candp(long long base, long long exponent, long long modulus) {  
    long long result = 1;  
    base %= modulus;   
    while (exponent > 0) {   
        if (exponent & 1) {   
            result = (result * base) % modulus;  
        }  
        exponent >>= 1;  
        base = (base * base) % modulus;   
    }  
    return result;  
}  
int fun(int x,int y){
	int t;
	while(y){
		t = x;
		x = y;
		y = t % y;
		
	}
	if(x==1)
		return 0;
	else
		return 1;
}
bool sushu(int s){
	for(int i=2;i<s;i++){
		if(s%i==0) 
		return 1;
	}
	return 0;
}


long long int pow(long long int a, long long int k, long long int c)
{
    long long int ans = 1;
    while(k)
    {
        if(k % 2) ans *= a;
        a = (a * a) % c;
        k /= 2;
        ans %= c;
    }
    return ans;
}



int  main(){
	int p,q,e,d,m,n,t,c,r;
	printf("�������һ������p:");
	scanf("%d",&p);
	if(sushu(p)){
		printf("p������Ҫ������������:");
		scanf("%d",&p);
	}	 
	printf("������ڶ�������q:");
	scanf("%d",&q);
	if(sushu(q)){
		printf("q������Ҫ������������:");
		scanf("%d",&q);
	}	 
	n = p*q;
	printf("������nΪ%3d\n",n);
	t = (p-1)*(q-1);
	printf("������tΪ%3d\n",t);
	printf("�����빫ԿeΪ:");
	scanf("%d",&e);
	if(e<1||e>t||fun(e,t)){
		printf("e������Ҫ������������:");
		scanf("%d",&e);
	}
	d = 1;
	while(((e*d)%t)!=1){
		d++;
	}
	printf("������dΪ%d\n",d);
	while(1){
		printf("��*****************��\n");
		printf("��ѡ����ִ�еĲ���:\n");
		printf("1.����\n");
		printf("2.����\n");
		printf("3.�˳�\n");
		scanf("%d",&r);
		switch(r){
		case 1:
			printf("����������m:");
			scanf("%d",&m);
			c = pow(m,e,n);
			printf("����Ϊ%d\n",c);
			break;
		case 2:
			printf("����������c:");
			scanf("%d",&c);
			m = pow(c,d,n);
			printf("����Ϊ%d\n",m);
			break;
		case 3:
			return 0;
		default:
			printf("�����������������:\n");
		
	}
}
}
