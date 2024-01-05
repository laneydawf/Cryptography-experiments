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
	printf("加密后的文本：%s\n",passwd);
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
	printf("请输入密文：");
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
		printf("第%d次解密文本：%s\n",i,word);
		num=0;
	}
	printf("\n");
}
int main()
{
	int x;
	printf("凯撒密码\n加密请输入数字1\n解密请输入数字2\n退出请输入数字3\n");
	scanf("%d",&x);
	while(x!=3){
		if(x==1){
			encryption();//加密
		}else{
			decryption();//解密
		}
		printf("凯撒密码\n加密请输入数字1\n解密请输入数字2\n退出请输入数字3\n");
		scanf("%d",&x);
	}
	
	return 0;
 } 
