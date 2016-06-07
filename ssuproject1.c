#include<stdio.h>
#include<string.h>
#include<stlib.h>

void comma(char);
void plus(char);
int main(void){
	int i;
}
}
void plus(char)
{
	char num1[100]={0},num2[100]={0},ans[100]={0};
	int input,i,j,leng1,leng2,leng,tmp1,tmp2,tmp3;
	leng1=0,leng2=0,i=0,j=0;

	printf("입력\n");


	while((input=getchar())!='\n'){
			num1[i]=input;
			i++;
			}

	while((input=getchar())!='\n'){
			num2[j]=input;
			j++;
			}

	for(i=0; num1[i]!='\0'; i++){
		leng1++;
	}
	for(i=0; num2[i]!='\0'; i++){
		leng2++;
	}
	if(leng1<leng2)
		leng=leng2;
	else
		leng=leng1;

	for(i=0; i<leng1; i++){
		tmp1=num1[i];
		num1[i+1]=tmp1;
	}
	for(i=0; i<leng2; i++){
		tmp2=num2[i];
		num2[i+1]=tmp2;
	}	

	for(i=0; i<leng; i++){
		ans[leng-i]=num1[leng1-i]+num2[leng2-i];
		if(ans[leng-i]>=10){
			tmp3=num1[leng-i-1];
			num1[leng-i-1]=tmp3+1;
		}
	}

	if(ans[0]!=0){
		printf("%c",ans[0]);
	}

	for(i=1; i<=leng; i++){
		printf("%c",ans[i]);
	}

	return 0;
}

void comma(char)
{
	int i;

	for(i=0; tmp[i]!='\0'; i++){//tmp는 입력의 임시로 나타낸 거
		printf("%c",str[i]);
	 	if((i%3==0)&&(tmp[i+1]!='\0'))
			printf(",");
	}

	return 0;
}

