/**************************************************
작성자 : 20194059 김태완
작성일 : 2020.03.26 (TUE)
프로그램 명 : 파일입출력을 이용한 최대,최소값 출력
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
    FILE *fp = NULL;
    int input,i=0,j=0,line=0,count=0,max=0,min=0,end=0;
    //input : 입력값(데이터 출력 개수)을 저장 하기 위한 변수
    //i,j : 반복문을 위한 변수
    //line : 출력해야 할 줄의 개수를 계산한 결과를 저장할 변수
    //count : data.txt에서 불러온 데이터의 개수를 세는 변수
    //max,min : 최대, 최소값을 저장 하기 위한 변수
    //end : 출력을 중단하기 위해 사용한 변수
    int arr[10000];
    fp = fopen("data.txt","r"); //data.txt 파일 오픈
    if(fp == NULL)
    {
        printf("파일을 열 수 없습니다."); //파일을 열 수 없을 시 오류 출력 후 프로그램 종료
        return 0;
    }
    while(!feof(fp))
    {
        if(count>10000) //데이터의 개수가 10000개 이상일시 오류 출력 후 프로그램 종료
        {
            printf("데이터가 너무 많습니다.\n");
            return 0;
        }
        fscanf(fp,"%d",&arr[count]); //data.txt에서 불러온 데이터를 배열 arr에 저장 후
        count++; //데이터의 개수 카운트
    }
    if(count<50) //데이터의 개수가 50개 미만일시 오류 출력 후 프로그램 종료
        {
            printf("데이터가 너무 적습니다.\n");
            return 0;
        }
    max = arr[0]; //max변수에 초기값 대입
    min = arr[0]; //min변수에 초기값 대입
    for(i=0;i<count;i++)
    {
        if(arr[i]>max) max = arr[i]; //최대값 찾기
        if(arr[i]<min) min = arr[i]; //최소값 찾기
    }
    printf("몇개의 데이터씩 출력할지를 선택해 주세요: ");
    scanf("%d",&input); //출력할 데이터의 개수를 입력받는다
    printf("\n");
    for(i=0;i<input;i++)
    {
        printf("%5d",i+1);
    }
    printf("\n");
    for(i=0;i<input*5+1;i++)
    {
        printf("=");
    }
    printf("\n"); //초기 문장 출력

    line = count/input+1; //출력해야할 줄의 총 개수 == 총 데이터개수 / 한줄에 출력할 데이터의 개수 + 1
    for(i=0;i<line;i++) //위에서 계산한 줄 수 만큼 반복
    {
        for(j=0;j<input;j++) //한 줄에 입력한 수 만큼 반복하여 출력
        {
            printf("%5d",arr[(i*input)+j]); //i번째줄은 (i*input)+1 번 인덱스부터 출력되어야 한다
            end++; //end변수가 count의 값과 같아지면 종료시키기위해 end의 값을 1씩 증가시킨다
            if(end==count) break; //end == count일 시 출력 종료
        }
        printf("\n");
        //if(end==count) break;
        for(j=0;j<input;j++)
        {
            if(arr[i*input+j]==max) printf("최대값"); //윗줄에서 출력한 값이 최대값과 같으면 "최대값" 출력
            else if(arr[i*input+j]==min) printf("최소값"); //윗줄에서 출력한 값이 최소값과 같으면 "최소값" 출력
            else printf("     "); //최대, 최소 모두 아닐시 공백 출력
        }
        printf("\n");
        for(j=0;j<input*5+1;j++)
        {
            printf("-"); //밑의 ------------를 input의 수와 필드폭에 맞춰 출력
        }
        printf("\n");
    }
    //for(j=0;j<input*5+1;j++)
    //    {
    //        printf("-"); //밑의 ------------를 input의 수와 필드폭에 맞춰 출력
    //    }
    //    printf("\n");
    printf("\n");
    fclose(fp); //파일포인터 닫기
    return 0;
}
