#include <stdio.h>
void encryption(){
	int key;
	printf("��������Կ��");
	scanf("%d",&key);
	getchar();
	char word[100];
	char passwd[100];
	for(int i=0;i<100;i++){
		word[i]='\0';
		passwd[i]='\0';
	}
	int num=0;
	char a;
	printf("���������ģ�");
	while((a=getchar())!='\n'){
		word[num]=a;//��������
		if(word[num]<='z'&&word[num]>='a'){//��������ֻת����ĸ
			passwd[num]='a'+(a+key-'a'+26)%26;
		}else if(word[num]<='Z'&&word[num]>='A'){
			passwd[num]='A'+(a+key-'A'+26)%26;
		}else{
			passwd[num]=word[num];
		}	
		num++;
	}	
	printf("���ܺ���ı���%s\n",passwd);
	printf("\n");
}

void decryption(){
	char word[100];
	char passwd[100];
	for(int i=0;i<30;i++){
		word[i]='\0';
		passwd[i]='\0';
	}
	int num=0;
	printf("���������ģ�");
	char a;
	getchar();
	while((a=getchar())!='\n'){
		passwd[num]=a;
		num++;
	}
	num=0;
	for(int i=1;i<26;i++){
		while(passwd[num]!='\0'){
			if(passwd[num]<='z'&&passwd[num]>='a'){
				word[num]='a'+(passwd[num]+i-'a'+26)%26;
			}else if(passwd[num]<='Z'&&passwd[num]>='A'){
				word[num]='A'+(passwd[num]+i-'A'+26)%26;
			}else{
				word[num]=passwd[num];
			}	
			num++;
		}
		printf("��%d�ν����ı���%s\n",i,word);
		num=0;
	}
	printf("\n");
}
int main()
{
	int x;
	printf("��������\n��������������1\n��������������2\n�˳�����������3\n");
	scanf("%d",&x);
	while(x!=3){
		if(x==1){
			encryption();//����
		}else{
			decryption();//����
		}
		printf("��������\n��������������1\n��������������2\n�˳�����������3\n");
		scanf("%d",&x);
	}
	
	return 0;
 } 
