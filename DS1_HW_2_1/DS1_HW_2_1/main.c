/*******************************************************
작성일 : 2020.04.12
작성자 : 20194059 김태완
프로그램명 : 각 알고리즘의 실행 시간을 비교하는 프로그램
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long algorithm1(unsigned long long num);
unsigned long long algorithm2(unsigned long long num);
unsigned long long algorithm3(unsigned long long num);

int main()
{
    int input,i,j; // 알고리즘의 종류를 입력받을 input, 반복문을 위한 i,j
    unsigned long long sum=0,num; // 0이상의 정수의 자료형중 가장 큰 저장 용량을 가진 unsigned long long 자료형 사용
    clock_t start,finish; //측정 시작 시간, 측정 마감 시간을 저장 할 변수
    double time; // 총 걸린 시간을 계산하여 저장 하는 변수
    printf("알고리즘을 선택하세요(1,2,3): ");
    scanf("%d",&input); // 알고리즘의 종류를 입력받는다.
    printf("숫자를 입력하세요: ");
    scanf("%llu",&num); // 알고리즘 작동에 필요한 정수를 입력받는다
    switch(input)
    {
    case 1: //1번 알고리즘
        start = clock(); // 시간 측정 시작
        algorithm1(num);
        //sum = num * num;
        finish = clock(); // 시간 측정 종료
        break;
    case 2: //2번 알고리즘
        start = clock(); // 시간 측정 시작
        algorithm2(num);
        //for(i=0;i<num;i++)
        //{
        //    sum += num;
        //}
        finish = clock(); // 시간 측정 종료
        break;
    case 3: //3번 알고리즘
        start = clock(); // 시간 측정 시작
        algorithm3(num);
        //for(i=0;i<num;i++)
        //{
        //    for(j=0;j<num;j++)
        //    {
        //        sum += 1;
        //    }
        //}
        finish = clock(); // 시간 측정 종료
        break;
    default: // 예외처리
        break;
    }
    time = (double)(finish - start) / CLOCKS_PER_SEC; // 총 걸린 시간 계산
    printf("\n걸린시간은 %lf입니다.\n",time); // 걸린 시간 출력
    return 0;
}
unsigned long long algorithm1(unsigned long long num) // 1번 알고리즘
{
    unsigned long long sum=0; // 0 이상의 정수 중 가장 큰 자료형 unsigned long long
    sum = num * num;
    return sum;
}
unsigned long long algorithm2(unsigned long long num) // 2번 알고리즘
{
    int i;
    unsigned long long sum=0; // 0 이상의 정수 중 가장 큰 자료형 unsigned long long
    for(i=0;i<num;i++)
    {
        sum += num;
    }
    return sum;
}
unsigned long long algorithm3(unsigned long long num) // 3번 알고리즘
{
    int i,j;
    unsigned long long sum=0; // 0 이상의 정수 중 가장 큰 자료형 unsigned long long
    for(i=0;i<num;i++)
    {
        for(j=0;j<num;j++)
        {
            sum += 1;
        }
    }
    return sum;
}

