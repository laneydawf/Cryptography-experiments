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
	printf("���ܺ���ı���%s",passwd);
}

void decryption(){
	char word[100];
	char passwd[100];
	for(int i=0;i<100;i++){
		word[i]='\0';
		passwd[i]='\0';
	}
	int num=0;
	printf("���������ģ�");
	char a;
	while((a=getchar())!='\n'){
		passwd[num]=a;
		num++;
	}
	num=0;
	for(int i=1;i<26;i++){
		while(passwd[num]!='\0'){
			if(passwd[num]>='A'&&passwd[num]<='Z')
				word[num]='A'+((passwd[num]-'A'-i+26)%26);
			else if(passwd[num]>='a'&&passwd[num]<='z')
				word[num]='a'+((passwd[num]-'a'-i+26)%26);
			else
				word[num]=passwd[num];
			num++;
		}
		printf("��%d�ν����ı���%s\n",i,word);
		num=0;
	}
}
int main()
{
	//encryption();//����
	decryption();//����
	return 0;
 } 
