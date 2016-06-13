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

                   }
  
               }
               else{
  
                   printf("정의된 변수 없음\n");
  
               }
 
          }
          // 저장된 모든 변수를 파일에 저장
          else if (0 == strcmp(cInput, "save")){
 
              pFile = fopen("save.txt", "w");
 
              for (i = 0; i < iNumOfVAR; ++i) {
 
                  fprintf(pFile, "%c = %s\n", cVarName[i], cVarValue[i]);
 
              }
 
              fclose(pFile);
 
          }
          // 파일에 저장된 변수를 변수를 저장하는 배열 공간에 불러옴
          else if (0 == strcmp(cInput, "load")){
 
              pFile = fopen("save.txt", "r");
 
              while (fscanf(pFile, "%c = %s\n", &cVarName[iNumOfVAR], cVarValue[iNumOfVAR]) != EOF){
 
                  iNumOfVAR++;
 
              }
 
              fclose(pFile);
 
          }
          // 프로그램 종료
          else if (0 == strcmp(cInput, "end")){
 
              return 0;
 
          }
          else{
 
              // 변수 저장 여부 확인
              for (i = 0; i < strlen(cInput); i++)
              {
                  if ('=' == cInput[i])       // 입력 받은 문자열에 = 이 있다는 의미는 곧 변수를 저장하겠다는 것으로 봐도 무방
                  {
                      bHasEqual = true;
                               break;
                  }
              }
 
              // 변수 검색 후 출력
              if ((('a' <= cInput[0] && cInput[0] <= 'z') || ('A' <= cInput[0] && cInput[0] <= 'Z')) && 1 == strlen(cInput)){
 
                  for (i = 0; i < 10; i++)
                  {
 
                      // 알파벳의 대소문자를 구별하지 않으므로 소문자일때는 대문자를 대문자일때는 소문자를 한번 더 확인 해주어야 한다.
                      if (cInput[0] == cVarName[i] || ('a' <= cInput[0] && cInput[0] - 32 == cVarName[i]) || ('Z' >= cInput[0] && cInput[0] + 32 == cVarName[i])){
 
                          bHasVAR = true;
                          break;
 
                      }
                  }
 
                  printf("= ");
 
                  if (bHasVAR)    // 변수를 찾았다면
                  {
                      PrintNumber(cVarValue[i]);  // 변수 출력
                  }
                  else{
 
                      printf("undefined.\n");
 
                  }
 
              }
              else{
 
 
                  // 문자열에 입력된 피연산자와 연산자를 각각 다른 배열에 나눈다.
                  for (i = 0; i < strlen(cInput); i++){
 
                      if (('0' <= cInput[i] && cInput[i] <= '9') || ('.' == cInput[i])) {
 
                          if (bIsStart) {
 
                              iStrInx = i;
                              iEndInx = iStrInx;
                              bIsStart = false;
 
                         }

                         ++iEndInx;
         
                         // 다음 칸이 숫자도 아니고 .도 아니라면 하나의 숫자가 끝났다는 것을 의미
                         if (!('0' <= cInput[i + 1] && cInput[i + 1] <= '9') && ('.' != cInput[i + 1]))
                         {

                             if (iIsNegative)
                             {
                                 cInputOperand[iNumOperand][0] = '-';
                             }
                             // 지금 까지 지나온 숫자 한자리 한자리를 피연산자 관리 배열에 저장
                             for (j = 0; j < iEndInx - iStrInx; ++j) {

                                 cInputOperand[iNumOperand][j + iIsNegative] = cInput[iStrInx + j];

                             }

                             iIsNegative = 0;
                             bIsStart = true;
                             ++iNumOperand;

                         }

                     }// 연산자 일경우
                     else if ('+' == cInput[i] || '-' == cInput[i] || '*' == cInput[i] || '/' == cInput[i] || '%' == cInput[i]){

                         // 단항 연산자 - 라면, 연산자 배열에 저장하지 않음
                         if ('-' == cInput[i] && (('0' <= cInput[i + 1] && cInput[i + 1] <= '9')) || ('a' <= cInput[i + 1] && cInput[i + 1] <= 'z') || ('A' <= cInput[i +     1] && cInput[i + 1] <= 'Z'))
                         {

                             iIsNegative = 1;

                         }
                         else{// 이항 연산자라면, 연산자 배열에 저장

                             cInputOperator[iNumOperator++] = cInput[i];

                         }

                     }// 변수가 수식에 있을 경우
                     else if ((('a' <= cInput[i] && cInput[i] <= 'z') || ('A' <= cInput[i] && cInput[i] <= 'Z')))
                     {

                         if ('=' == cInput[i + 1] || '=' == cInput[i + 2]){

                             continue;

                         }
                         for (j = 0; j < 10; j++)
                         {
                             // 대소구분을 안하므로 2중 확인
                             if (cInput[i] == cVarName[j] || ('a' <= cInput[i] && cInput[i] - 32 == cVarName[j]) || ('Z' >= cInput[i] && cInput[i] + 32 == cVarName[j])){

                                 bHasVAR = true;
                                 break;

                             }
                         }

                         // 입력된 변수가 배열에 존재 한다면, 그 값을 피연산자 배열에 복사해서 붙여 넣음
                         if (bHasVAR)
                         {
                             strcpy(cInputOperand[iNumOperand], cVarValue[j]);
                             iNumOperand++;
                         }
                         else{// 변수가 없다면 undefined 출력
                             printf("undefined.\n");

                         }

                     }
                     else if (' ' == cInput[i] || '=' == cInput[i]){// 공백 무시

                         continue;

                     }
                     else{// 이외의 문자가 입력시 에러 코드 출력

                         PrintErrorMsg(ERRCODE_UNKNOWN_CHAR);
                         bIsError = true;

                     }

                 }

                 if (iNumOperator + 1 != iNumOperand && !bIsError){// 모든 입력을 받은 후에 연산자와 피연산자의 개수 차이가 1인지 확인하여 올바른 >    수식여부를 체크함

                     PrintErrorMsg(ERRCODE_OPERATOR_OPERAND);
                     bIsError = true;

                 }

                 // 연산
                 if (!bIsError)
                 {

                     while (iNumOperator)
                     {

                         cOperator = '\0';

                         for (i = 0; i < iNumOperator; i++) // 연산자 우선순위에 따라서 * , / , % 연산자 먼저 탐색함
                         {

                             if ('*' == cInputOperator[i] || '/' == cInputOperator[i] || '%' == cInputOperator[i])
                             {
                                 cOperator = cInputOperator[i];
                                 iOperatorLocation = i;
                                 break;
                             }

                         }

                         if (cOperator == '\0') // 연산자 배열에 * , / , %  가 없다면
                         {
                             for (i = 0; i < iNumOperator; i++)
                             {

                                 if ('+' == cInputOperator[i] || '-' == cInputOperator[i])
                                 {
                                     cOperator = cInputOperator[i];
                                     iOperatorLocation = i;
                                     break;	
                                 }

                             }
                         }

                         // atof 함수를 이용해서 문자열을 double형으로 변환
                         dOperandLeft = atof(cInputOperand[iOperatorLocation]);
                         dOperandRight = atof(cInputOperand[iOperatorLocation + 1]);

                         switch (cOperator)
                         {
                         case '+':
                             dResult = dOperandLeft + dOperandRight;
                             break;

                         case '-':
                             dResult = dOperandLeft - dOperandRight;
                             break;

                         case '*':
                             dResult = dOperandLeft * dOperandRight;
                             break;

                         case '/':
                             dResult = dOperandLeft / dOperandRight;
                             break;

                         case '%':
 dResult = (int)dOperandLeft % (int)dOperandRight;
                             break;

                         default:
                             break;
                         }

                         // 연산 후 연산결과를 다시 double 형에서 문자열 형으로 변환함
                         DoubleToStr(cBuffer, dResult);
                         strcpy(cInputOperand[iOperatorLocation], cBuffer);

                         for (i = iOperatorLocation + 2; i < 10; i++)
                         {

                             strcpy(cInputOperand[i - 1], cInputOperand[i]);

                         }

                         for (i = iOperatorLocation + 1; i < 10; i++)
                         {

                             cInputOperator[i - 1] = cInputOperator[i];

                         }

                         --iNumOperand;
                         --iNumOperator;

                     }

                     // 변수를 배열에 저장
                     if (bHasEqual){

                         j = 0;
                         bIsStart = false;

                         // 입력 받은 문자열에서 가장 첫번째 칸에는 변수명이 기입 되므로
                         cVarName[iNumOfVAR] = cInput[0];

                         strcpy(cVarValue[iNumOfVAR], cInputOperand[0]);

                         printf("= ");
                         PrintNumber(cVarValue[iNumOfVAR]);
                         // 저장된 변수의 개수를 하나 증가 (하나의 변수를 입력 받았으므로...)
                         iNumOfVAR++;

                     }
                     else{

                         printf("= ");
                         PrintNumber(cInputOperand[0]);

                     }
                 }

             }


         }

     }

     return 0;

 }
 int DoubleToStr(char cNumber[], double dNum)
 {

     int i;
     int iDecimal, iSign;
     int iStart;
     char *cBuffer;

     iStart = 0;

    // https://msdn.microsoft.com/ko-kr/library/ehz2dset.aspx 참조
     cBuffer = ecvt(dNum, 50 + 9 - 2, &iDecimal, &iSign);

     if (iSign)
     {

         for (i = strlen(cBuffer) - 1; i != iStart; i--)


