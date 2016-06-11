#include <stdio.h>
#include <string.h>
int main(void){
	char a[50],b[50],c[50],d[50],e[100],f[100];
	int i,size=0;
	int k=0;
	int num=0;
	for(i=0;i<50;i++){// 0으로 초기화
		c[i]='0';
		d[i]='0';
	}
	scanf("%s",a);//입력
	scanf("%s",b);

	if(a[0]=='-'){//위의 값이 음수일 때

		if(strlen(a)>strlen(b)){//위의 자리수가 더 클 때

			for(i=0;i<strlen(a)-1;i++)
				c[i]=a[strlen(a)-(i+1)];
			for(i=0;i<strlen(b);i++)
				d[i]=b[strlen(b)-(i+1)];
			for(i=0;i<strlen(a)-1;i++){
				e[i]=(c[i]-48)+(d[i]-48)+48+k;
				if(e[i]>=58){
					e[i]=e[i]-10;
					if(i==strlen(a)-2)
						k=2;
					else
						k=1;
				}
				else
					k=0;
				size++;
			}
			f[0]='-';
			if(k==2){
				f[1]=49;
				for(i=2;i<size+2;i++)
					f[i]=e[size-i+1];
				for(i=0;i<size+2;i++)
					printf("%c",f[i]);
			}
			else{
				for(i=1;i<size+1;i++)
					f[i]=e[size-i];

				for(i=0;i<size+1;i++)
					printf("%c",f[i]);
			}
		}

		if(strlen(a)<=strlen(b)){//아래의 자리수가 더 클 때

			for(i=0;i<strlen(a)-1;i++)
				c[i]=a[strlen(a)-(i+1)];
			for(i=0;i<strlen(b);i++)
				d[i]=b[strlen(b)-(i+1)];

			for(i=0;i<strlen(b);i++){
				e[i]=(c[i]-48)+(d[i]-48)+48+k;
				if(e[i]>=58){
					e[i]=e[i]-10;
					k=1;
				}
				else
					k=0;
				size++;
			}
			f[0]='-';
			for(i=1;i<size+2;i++)
				f[i]=e[size-i+1];
			for(i=0;i<size+2;i++)
				printf("%c",f[i]);
		}
	}

	else{//위의 값이 양수일 때

		if(strlen(a)==strlen(b)){
			for(i=0;i<strlen(a);i++){
				if(a[i]>b[i]){
					num=1;
					break;}
				if(a[i]<b[i]){
					num=2;
					break;}
				if(i!=strlen(a)-1 && a[i]==b[i]){
					continue;}
				else
					printf("%c",48);
			}
		}

		for(i=0;i<strlen(a);i++)
			c[i]=a[strlen(a)-(i+1)];

		for(i=0;i<strlen(b);i++)
			d[i]=b[strlen(b)-(i+1)];

		if(strlen(a)>strlen(b) || num==1){//위의 자리수가 더 클 때
			for(i=0;i<strlen(a);i++){
				e[i]=(c[i]-48)-(d[i]-48)+48-k;
				if(e[i]<48){
					e[i]=e[i]+10;
					k=1;
				}
				else
					k=0;
				size++;
			}

			for(i=0;i<size;i++)
				f[i]=e[size-(i+1)];

			for(i=0;i<size;i++){
				if(f[i]>=48 && f[i]<=57){
					if(i==0 && f[i]==48){
						for(i=0;f[i]==48 && i!=size-1;i++)
							continue;
						printf("%c",f[i]);
					}
					else
						printf("%c",f[i]);}
			}
		}

		if(strlen(a)<strlen(b) || num==2){//아래의 자리수가 더 클 때
			for(i=0;i<strlen(b);i++){
				e[i]=(d[i]-48)-(c[i]-48)+48-k;
				if(e[i]<48){
					e[i]=e[i]+10;
					k=1;
				}
				else
					k=0;
				size++;
			}

			for(i=0;i<size;i++)
				f[i]=e[size-(i+1)];

			printf("-");
			for(i=0;i<size;i++){
				if(f[i]>=48 && f[i]<=57){
					if(i==0 && f[i]==48){
						for(i=0;f[i]==48 && i!=size-1;i++)
							continue;
						printf("%c",f[i]);
					}
					else
						printf("%c",f[i]);}
			}
		}
	}

	return 0;
}
