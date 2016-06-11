#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// ***************** Define ***************** //

const int MAX_INPUT = 1024;
const int MAX_INPUT_OPERAND = 20;
const int MAX_INPUT_OPERATOR = MAX_INPUT_OPERAND - 1;

const int MAX_INTEGER_PLACE = 50;
const int MAX_DECIAML_PLACE = 9;

// =========================================== //


// ***************** Error Code ***************** //

const int ERRCODE_OK = 0xFFFFFFFF;
const int ERRCODE_UNKNOWN_CHAR = 0xFFFFFFFE;
const int ERRCODE_INTEGER_OVERFLOW = 0xFFFFFFFE;
const int ERRCODE_DECIMAL_OVERFLOW = 0xFFFFFFFD;

// =========================================== //



// ***************** Function ***************** //

void PrintErrorMsg(const int iErrCode);
int DoubleToStr(char cNumber[], double dNum);

// =========================================== //



int main()
{
    // ***************** Variable  ***************** //
    
    bool bIsStart;
    int i, j;
    int iStrInx;
    int iEndInx;
    int iNumOperand;
    int iNumOperator;
    int iNumOfVAR;
    double dOperandLeft;
    double dOperandRight;
    char cInput[MAX_INPUT];
    char cInputOperand[MAX_INPUT_OPERAND][MAX_INTEGER_PLACE + MAX_DECIAML_PLACE];
    char cInputOperator[MAX_INPUT_OPERATOR];
    char cOutputResult[MAX_INTEGER_PLACE + MAX_DECIAML_PLACE + 1];
    char cVarName[10][1];
    char cVarValue[10][MAX_INTEGER_PLACE + MAX_DECIAML_PLACE];
    
    // =========================================== //
    
    
    
    // ***************** Initialize ***************** //
    
    bIsStart = true;
    iNumOfVAR = 0;
    iStrInx = 0;
    iEndInx = 0;
    iNumOperand = 0;
    iNumOperator = 0;
    dOperandLeft = 0.0;
    dOperandRight = 0.0;
    
    
    memset(cInput, '\0', sizeof(cInput));
    
    for (i = 0; i<MAX_INPUT_OPERAND; ++i) {
        
        memset(cInputOperand[i], '\0', sizeof(cInputOperand[i]));
        
    }
    
    memset(cInputOperator, '\0', sizeof(cInputOperator));
    
    memset(cOutputResult, '\0', sizeof(cOutputResult));
    
    // =========================================== //
    
    
    
    
    //while (true) {
    
    gets(cInput);
    
    if (0 == strcmp(cInput, "claer")) {
        
        system("clear");
        
    }else if(0 == strcmp(cInput, "VAR")){
        
        for (i=0; i < iNumOfVAR; ++i) {
            
            printf("%c = %s", cVarName[i][0], cVarValue[i]);
            
        }
        
    }else if(0 == strcmp(cInput, "save")){
        
        
    }else if(0 == strcmp(cInput, "load")){
        
        
    }else{
        
        for (i = 0; i<strlen(cInput); ++i) {
            
            if (('0' <= cInput[i] && cInput[i] <= '9') || '.' == cInput[i]) {
                
                if (bIsStart) {
                    
                    iStrInx = i;
                    bIsStart = false;
                    
                }
                
                ++iEndInx;
                
            }else if ((' ' == cInput[i] && !('0' <= cInput[i+1] && cInput[i+1] <= '9'))) {
                
                for (j = 0; j<iEndInx; ++j) {
                    
                    cInputOperand[iNumOperand][j] = cInput[iStrInx + j];
                    
                }
                
                bIsStart = true;
                ++iNumOperand;
                
            }else if('+' == cInput[i] || '-' == cInput[i] || '*' == cInput[i] || '/' == cInput[i] || '%'== cInput[i]){
            
                cInputOperator[iNumOperator++] = cInput[i];
                ++i;
                
            }else{
            
                PrintErrorMsg(ERRCODE_UNKNOWN_CHAR);
                return 0;
            
            }
            
        }
        
        for (j = 0; j<iEndInx; ++j) {
            
            cInputOperand[iNumOperand][j] = cInput[iStrInx + j];
            
        }
        
        ++iNumOperand;
        
        // 연산
        for (i = 0; i<iNumOperator; ++i) {
            
            switch (cInputOperator[i]) {
                case '*':
                    dOperandLeft = atof(cInputOperand[i]);
                    dOperandRight = atof(cInputOperand[i+1]);
                    
                    break;
                case '/':
                    
                    break;
                    
                case '%':
                    break;
                    
                    
                default:
                    break;
            }
        }
        
        
    }
    
    // }
    
    return 0;
    
}
int DoubleToStr(char cNumber[], double dNum)
{
    bool bHasPoint;
    int i;
    int i10Division;
    int d10Division;
    int iDecimalCnt;
    
    bHasPoint = false;
    i10Division = 1;
    d10Division = 0.1;
    iDecimalCnt = 0;
    
    for (i = 0;; ++i) {
        
        if (i > MAX_INTEGER_PLACE) {
            
            return ERRCODE_INTEGER_OVERFLOW;
            
        }
        
        if(0 == (int)dNum / i10Division){
            
            break;
            
        }
        
        i10Division *= 10;
        
    }
    
    i = 0;
    
    if (dNum < 1.0) {
        
        cNumber[0] = '0';
        i++;
        
    }
    
    
    for (; i<MAX_INTEGER_PLACE + MAX_DECIAML_PLACE; ++i) {
        
        
        if (1 == i10Division && dNum > 0.0 && !bHasPoint) {
            
            bHasPoint = true;
            cNumber[i] = '.';
            continue;
            
        }
        
        if (!bHasPoint) {
            
            i10Division /= 10;
            cNumber[i] = ((int)dNum / i10Division) + '0';
            dNum -= ((int)dNum / i10Division) * i10Division;
            
        }else{
            
            dNum *= 10;
            cNumber[i] = ((int)dNum % 10) + '0';
            iDecimalCnt++;
            
            if (iDecimalCnt > MAX_DECIAML_PLACE-1) {
                
                break;
                
            }
            
            if (dNum - (int)dNum < 0.0000000001) {
                
                break;
                
            }
            
        }
        
    }
    
    
    return ERRCODE_OK;
    
}

void PrintErrorMsg(const int iErrCode)
{
    printf("error : ");
    switch (iErrCode) {
            
        case ERRCODE_UNKNOWN_CHAR:
            
            printf("숫자나 연산자 외의 문자가 입력 되었습니다.\n");
            
            break;
            
        default:
            
            printf("정의 되지 않은 오류입니다.\n");
            
            break;
            
    }
}








