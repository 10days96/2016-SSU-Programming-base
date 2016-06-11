#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


const int MAX_INTEGER_PLACE = 50;
const int MAX_DECIAML_PLACE = 9;

const int ERRCODE_OK = 0xFFFFFFFF;



void PrintErrorMsg(const int iErrCode);


int main()
{
    int i;
		double x[10];
		int iNumOfVAR;
    char cInput[1024];
    char cVarName[10][1];
    char cVarValue[10][MAX_INTEGER_PLACE + MAX_DECIAML_PLACE];
    
		FILE *pFile;
		pFile = fopen("Variable", "wt+");
		
		for(i=0; i<10; ++i){
			fprintf(pFile, "%lf\n", &x[i]);
		}
		while(fscanf(Variable, "%lf\n", x[i])!=EOF){
				fprintf(Variable, "%lf\n", x[i]);
		}
		
		fclose(Variable);
    
    iNumOfVAR = 0;
    
    while (true) {
        
        gets(cInput);
        
        if (strcmp(cInput, "claer")) {
            
            system("clear");
            
        }else if(strcmp(cInput, "VAR")){
            
            for (i=0; i < iNumOfVAR; ++i) {
                
                printf("%c = %s", cVarName[i][0], cVarValue[i]);
                
            }
        
        }else if(strcmp(cInput, "save")){
        
        }else if(strcmp(cInput, "load")){
        
        }else{
        
        }
        
    }
    
    return 0;
}


void PrintErrorMsg(const int iErrCode)
{
    printf("error : ");
    switch (iErrCode) {
            
        default:
            printf("정의 되지 않은 오류입니다.\n");
            break;
    }
}
