#include <stdio.h>
void encryption(){
	int key;
	printf("请输入密钥：");
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
	printf("请输入明文：");
	while((a=getchar())!='\n'){
		word[num]=a;//保存明文
		if(word[num]<='z'&&word[num]>='a'){//凯撒密码只转换字母
			passwd[num]='a'+(a+key-'a'+26)%26;
		}else if(word[num]<='Z'&&word[num]>='A'){
			passwd[num]='A'+(a+key-'A'+26)%26;
		}else{
			passwd[num]=word[num];
		}	
		num++;
	}	
	printf("加密后的文本：%s",passwd);
}

void decryption(){
	char word[100];
	char passwd[100];
	for(int i=0;i<100;i++){
		word[i]='\0';
		passwd[i]='\0';
	}
	int num=0;
	printf("请输入密文：");
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
		printf("第%d次解密文本：%s\n",i,word);
		num=0;
	}
}
int main()
{
	//encryption();//加密
	decryption();//解密
	return 0;
 } 
