#include<stdio.h>

void Euclid(){
	int a,b;
	printf("������a��b��");
	scanf("%d %d",&a,&b);
	int X,Y,R;
	X=a,Y=b;
	while(1){
		if(Y==0){
			printf("gcd( %d , %d ) = %d",a,b,X);
			return;
		}else if(Y==1){
			printf("gcd( %d , %d ) = %d",a,b,Y);
			return;
		}
		R=X%Y;
		X=Y;
		Y=R;
		}
}

void ExtendedEuclid(){
	int a,b;
	printf("������a��b��");
	scanf("%d %d",&a,&b);
	int x1,x2,x3,y1,y2,y3;
	int t1,t2,t3;
	x1=1,x2=0,x3=a,y1=0,y2=1,y3=b;
	while(1){
		if(y3==0){
			printf("%d mod %d û����Ԫ",a,b);
			return;
		}else if(y3==1){
			printf("%d mod %d ����Ԫ�� %d",b,a,y2);
			return;
		}
		int q=x3/y3;
		t1=x1-q*y1,t2=x2-q*y2,t3=x3-q*y3;
		x1=y1,x2=y2,x3=y3;
		y1=t1,y2=t2,y3=t3;
	}
}


int main(){
	printf("��ѡ�����:\n1.���������\n2.����Ԫ\n");
	int flag;
	scanf("%d",&flag);
	if(flag==1){
		Euclid();
	}else{
		ExtendedEuclid();
	}
	return 0;
} 
