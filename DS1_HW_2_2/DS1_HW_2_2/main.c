/***************************************
작성일 : 2020.04.12
작성자 : 20194059 김태완
프로그램명 : 연산별 수행 시간 구하기
****************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    char input; //연산을 선택받아 그 연산을 저장 할 변수
    int i; //반복을 위한 변수
    clock_t start,finish; //시간을 재기 위한 변수
    int n=5; //계산할 수
    long long result = 1; // 나누기, 곱하기 연산을 위해 result를 0이 아닌 1로 초기화
    //-연산의 경우 음수도 발생하기 때문에 unsigned long long을 사용하지 않음
    unsigned long long num; //입력받는 변수는 양의 정수중 가장 큰 저장공간을 가진 자료형으로 만듬
    double total; //총 시간을 저장하는 변수
    printf("연산을 선택하시오(+,-,*,/): ");
    scanf("%c",&input); //연산의 종류를 입력받아 input에 저장
    printf("반복횟수를 입력하세요: ");
    scanf("%lld",&num); //반복 횟수를 입력받아 num에 저장
    switch(input)
    {
    case '+': //+연산
        start = clock(); //시간 측정 시작
        for(i=0;i<num;i++)
        {
            result += n;
        }
        finish = clock(); //시간 측정 종료
        break;
    case '-': //-연산
        start = clock(); //시간 측정 시작
        for(i=0;i<num;i++)
        {
            result -= n;
        }
        finish = clock(); //시간 측정 종료
        break;
    case '*': //*연산
        start = clock(); //시간 측정 시작
        for(i=0;i<num;i++)
        {
            result *= n;
        }
        finish = clock(); //시간 측정 종료
        break;
    case '/': //'/'연산
        start = clock(); //시간 측정 시작
        for(i=0;i<num;i++)
        {
            result /= n;
        }
        finish = clock(); //시간 측정 종료
        break;
    default:
        break;
    }
    total = (double)(finish-start)/CLOCKS_PER_SEC; //총 걸린 시간 계산
    printf("\n걸린시간은 %lf 입니다.\n",total);
    return 0;
}
