#include<stdio.h>
#include<stdboll.h>
#include<stdlib.h>
#include<string.h>

// ***************** Error Code ***************** //
enum
{
     ERRCODE_OK = 0xFFFFFF,
     ERRCODE_UNKNOWN_CHAR = 0xFFFFFE,
     ERRCODE_INTEGER_OVERFLOW = 0xFFFFFD,
     ERRCODE_DECIMAL_OVERFLOW = 0xFFFFFC,
     ERRCODE_OPERATOR_OPERAND = 0xFFFFFB
 
  };
 
  // =========================================== //
 
 
  // ***************** Function ***************** //
 
  /*
      DoubleToStr()
      설명 :
      문자열과 실수를 매개변수로 입력받아,
      실수를 문자형 데이터로 변환 후 문자열에 넣어줌.
 
      반환값 :
      오류 코드 반환
 
      */
  int DoubleToStr(char cNumber[], double dNum);
 
  /*
      PrintNumber()
      설명 :
      문자열을 입력 받아 출력함.
      단, 정수 부분일 경우 ',' 를 세자리 마다 출력
 
      반환값 :
      오류 코드 반환
      */
  int PrintNumber(char cNumber[]);
 
  /*
      PrintErrorMsg()
     설명 :
      에러 코드를 입력 받아,
      해당되는 에러 메시지를 화면에 출력
 
      반환값 :
      없음
      */
  void PrintErrorMsg(const int iErrCode);
 
  /*
      get_string()
      설명 :
      엔터를 치기 전까지 문자열을 입력받음
      */
  void get_string(char[]);
  // =========================================== //
 
 
 
  int main()
  {
      // ***************** Variable  ***************** //
 
      bool bIsStart;
      bool bHasVAR;
      bool bHasEqual;
      bool bIsError;
      char cOperator;
      int i, j;
      int iErrCode;
      int iStrInx;
      int iEndInx;
      int iNumOperand;
      int iNumOperator;
      int iNumOfVAR;
      int iIsNegative;
      int iOperatorLocation;
      double dOperandLeft;
      double dOperandRight;
      double dResult;
      char cInput[1024];
      char cInputOperand[10][50 + 9];
      char cInputOperator[9];
      char cVarName[10];
      char cVarValue[10][50 + 9];
      char cBuffer[50 + 9];
 
     FILE *pFile;
 
      // =========================================== //
 
      iNumOfVAR = 0;
     // 1차원 배열인 cVarName[]를 초기화
     memset(cVarName, '\0', sizeof(cVarName));

     for (i = 0; i < 10; ++i) {

         // 2차원 배열인 cVarValue[][]를 초기화
         memset(cVarValue[i], '\0', sizeof(cVarValue[i]));

     }

     printf("Start...\n");

     while (true) {  // 반복적으로 수식 입력을 받기 위한 while문

         // ***************** Initialize ***************** //

         // 변수 및 배열을 초기화 해줍니다.

         bIsStart = true;
         bHasVAR = false;
         bHasEqual = false;
         bIsError = false;

         cOperator = '\0';
         iErrCode = 0;
         iStrInx = 0;
         iEndInx = 0;
         iNumOperand = 0;
         iNumOperator = 0;
         iIsNegative = 0;
         iOperatorLocation = 0;
         dOperandLeft = 0.0;
         dOperandRight = 0.0;
         dResult = 0.0;


         memset(cInput, '\0', sizeof(cInput));

         for (i = 0; i < 10; ++i) {

             memset(cInputOperand[i], '\0', sizeof(cInputOperand[i]));

         }

         memset(cInputOperator, '\0', sizeof(cInputOperator));

         memset(cBuffer, '\0', sizeof(cBuffer));

         // =========================================== //

         printf("(Input) ");
         get_string(cInput);         // Enter가 눌릴 때까지 공백을 포>    함한 입력스트림의 모든 문자를 배열에 저장합니다.

         // 입력 받은 문자열을 strcmp로 비교. 각, 명령어에 대한 실행을
     해줍니다.
         // 화면 지우기
         if (0 == strcmp(cInput, "clear")) {

             system("clear");

         }
         // 저장된 모든 변수 출력
         else if (0 == strcmp(cInput, "VAR")){

             if (0 != iNumOfVAR){

                 for (i = 0; i < iNumOfVAR; ++i) {

                     printf("%c = ", cVarName[i]);
