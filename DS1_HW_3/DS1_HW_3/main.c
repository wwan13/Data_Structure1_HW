/*********************************************
작성자 : 20194059 김태완
작성일 : 2020.05.03
프로그램명 : 두 희소행렬을 연산하는 프로그램
**********************************************/

#define _CTR_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int** creat_memory(int rows,int cols); //2차원 메모리를 동적으로 받아주는 함수
int scan_data(int **arr, FILE *fp, int rows, int cols); //파일에서 데이터를 읽어오는 함수
void get_sparse_matrix(int **arr, int **sparse_matrix,int rows, int cols); //희소행렬을 압축하는 함수
void print_arr(int **arr,int rows,int cols); //행렬을 출력하는 함수
void print_arr2(int **arr,int rows,int cols); //희소행렬을 일반행렬로 출력해주는 함수
int arr_add(int **arr1,int **arr2, int **sum, int rows1,int cols1,int rows2, int cols2, int len1, int len2); //행렬의 덧셈을 실행하는 함수
int arr_sub(int **arr1,int **arr2, int **sub, int rows1,int cols1,int rows2, int cols2, int len1, int len2); //행렬의 뺄셈을 실행하는 함수
int arr_mul(int **arr1,int **arr2, int **mul, int rows1,int cols1,int rows2, int cols2, int len1, int len2); //행렬의 곱셈을 실행하는 함수
void delete_memory(int **arr, int rows); //2차원 메모리를 해재하는 함수

int main()
{
    FILE *fp;
    int cols1,rows1,cols2,rows2,len1,len2; //일반 행렬의 크기와 희소행렬의 크기를 저장해주는 변수들
    int **arr1 = NULL, **arr2 = NULL; //일반 행렬을 저장하고 있는 동적 이중배열
    int **s_matrix1 = NULL, **s_matrix2 = NULL; //희소행렬을 저장하고있는 동적 이중배열
    int **sum = NULL, **sub = NULL, **mul = NULL; //연산의 결과를 저장하고 있는 동적 이중배열
    int sizeof_sum, sizeof_sub, sizeof_mul; //희소행렬의 크기를 갖고 있는 변수
    int i,j,max; //반복, 최대값을 저장하는 변수

    fp = fopen("data.txt","r"); //파일 오픈
    if(fp == NULL) //파일 오류시 오류 출력
    {
        printf("파일을 열 수 없습니다.");
        return 0;
    }

    fscanf(fp,"%d %d",&rows1,&cols1); //행렬의 크기를 읽어온다
    arr1 = creat_memory(rows1,cols1); //행렬의 크기만큼 메모리를 할당한다
    len1 = scan_data(arr1,fp,rows1,cols1); //할당한 메모리에 파일에서 읽어온 데이터를 저장하고 0이 아닌 데이터의 갯수를 len1에 저장한다.
    s_matrix1 = creat_memory(len1,3); //0이 아닌 데이터의 갯수 만큼 메모리를 할당한다.
    get_sparse_matrix(arr1,s_matrix1,rows1,cols1); //파일에서 읽어온 데이터로 희소행렬을 만든다.
    
    fscanf(fp,"%d %d",&rows2,&cols2); //행렬의 크기를 읽어온다
    arr2 = creat_memory(rows2,cols2); //행렬의 크기만큼 메모리를 할당한다
    len2 = scan_data(arr2,fp,rows2,cols2); //할당한 메모리에 파일에서 읽어온 데이터를 저장하고 0이 아닌 데이터의 갯수를 len2에 저장한다.
    s_matrix2 = creat_memory(len2,3); //0이 아닌 데이터의 갯수 만큼 메모리를 할당한다.
    get_sparse_matrix(arr2,s_matrix2,rows2,cols2); //파일에서 읽어온 데이터로 희소행렬을 만든다.

    if(len1>=len2) max = len1;
    else max = len2; //더 큰 길이를 max에 저장

    printf(" <<첫번째 행렬(ver.일반행렬)>>\n\n");
    print_arr(arr1,rows1,cols1); //첫번째 배열 출력
    printf("\n\n <<첫번째 행렬(ver.희소행렬)>>\n\n");
    print_arr(s_matrix1,len1,3); //첫번째 배열(희소행렬) 출력
    printf("\n\n <<두번째 행렬(ver.일반행렬)>>\n\n");
    print_arr(arr2,rows2,cols2); //두번째 배열 출력
    printf("\n\n <<두번째 행렬(ver.희소행렬)>>\n\n");
    print_arr(s_matrix2,len2,3); //두번째 배열(희소행렬) 출력
    
    sum = creat_memory(max,3); //더 큰 크기를 기준으로 메모리 할당
    sizeof_sum = arr_add(s_matrix1,s_matrix2,sum,rows1,cols1,rows2,cols2,len1,len2);
    //행렬의 덧셈 연산을 진행하고, 반환된 행렬의 크기를 저장한다.
    printf("\n\n <<두 행렬의 합(ver.일반행렬)>>\n\n");
    print_arr2(sum,rows1,cols1); //합한 행렬을 출력한다.
    printf("\n\n <<두 행렬의 합(ver.희소행렬)>>\n\n");
    print_arr(sum,max,3); //합한 행렬을 출력한다.


    sub = creat_memory(max,3); //더 큰 크기를 기준으로 메모리 할당
    sizeof_sub = arr_sub(s_matrix1,s_matrix2,sub,rows1,cols1,rows2,cols2,len1,len2);
    //행렬의 뺄셈 연산을 진행하고, 반환된 행렬의 크기를 저장한다.
    printf("\n\n <<두 행렬의 차(ver.일반행렬)>>\n\n");
    print_arr2(sub,rows1,rows2); //뺀 행렬을 출력한다.
    printf("\n\n <<두 행렬의 차(ver.희소행렬)>>\n\n");
    print_arr(sub,max,3); //합한 행렬을 출력한다.

    mul = creat_memory(rows1 * cols2,3); //곱셈 결과 나올 수 있는 최대 크기로 메모리 할당
    sizeof_mul = arr_mul(s_matrix1,s_matrix2,mul,rows1,cols1,rows2,cols2,len1,len2);
    //행렬의 곱셈 연산을 진행하고, 반환된 행렬의 크기를 저장한다.
    printf("\n\n <<두 행렬의 곱(ver.일반행렬)>>\n\n");
    print_arr2(mul,rows1,cols2); //곱해진 행렬을 출력한다.
    printf("\n\n <<두 행렬의 곱(ver.희소행렬)>>\n\n");
    print_arr(mul,rows1*cols2,3); //합한 행렬을 출력한다.

    fclose(fp); //파일 닫기
    delete_memory(arr1,rows1);
    delete_memory(arr2,rows2);
    delete_memory(s_matrix1,len1);
    delete_memory(s_matrix2,len2);
    delete_memory(sum,max);
    delete_memory(sub,max);
    delete_memory(mul,rows1); //메모리 반납
    return 0;
}

int** creat_memory(int rows,int cols) //2차원 메모리를 동적으로 할당해주는 함수
{
    int **arr;
    int i;
    arr = (int **)calloc(rows, sizeof(int)); //메모리 할당과 동시에 0으로 초기화 해주기 위해 calloc 함수 사용
    for(i=0;i<rows;i++)
    {
        arr[i] = (int *)calloc(cols, sizeof(int));
    }
    return arr;
}

int scan_data(int **arr, FILE *fp, int rows, int cols) //파일로부터 데이터를 읽어오고 행렬의 크기를 반환하는 함수
{
    int i,j,count=0;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
            fscanf(fp,"%d",&arr[i][j]);
            if(arr[i][j]!=0)
                count++;
        }
    }
    return count;
}
 
void get_sparse_matrix(int **arr, int **sparse_matrix,int rows, int cols) //일반행렬을 희소행렬로 바꿔주는 함수
{
    int i,j,count=0;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
            if(arr[i][j]!=0) //0이 아니면
            {
                sparse_matrix[count][0] = i; //count행의 0열에 i
                sparse_matrix[count][1] = j; //count행의 1열에 j
                sparse_matrix[count][2] = arr[i][j]; ////count행의 2열에 값을 대입 해준다
                count++;
            }
        }
    }
}


void print_arr(int **arr,int rows,int cols) //행렬을 출력하는 함수
{
    int i,j;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
            printf("%3d ",arr[i][j]);
        }
        printf("\n");
    }
}

void print_arr2(int **arr,int rows,int cols) //희소행렬을 일반함수로 출력하는 함수
{
    int i,j,count=0;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
            if(i==arr[count][0]&&j==arr[count][1]) //인덱스 번호와 희소행렬에 저장된 행렬의 값이 같으면 값 출력
            {
                printf("%3d",arr[count][2]);
                count++;
            }
            else //아니면 0 출력
            {
                printf("%3d",0);
            }
        }
        printf("\n");
    }
}


int arr_add(int **arr1,int **arr2, int **sum, int rows1,int cols1,int rows2, int cols2, int len1, int len2)
{
    int i,j,idx;
    int count=0,max;
    int **buf;
    if(cols1!=cols2 || rows1 != rows2) //행렬의 덧셈을 할 수 없는 경우 오류 메세지 출력
    {
        printf("행렬의 크기가 같지 않아 행렬의 덧셈 연산을 수행 할 수 없습니다.\n");
        return;
    }

    if(len1>=len2) max = len1;
    else max = len2; //두개의 길이 중 더 큰 길이 저장

    buf = creat_memory(max,3); //임시 저장을 위한 메모리 생성
    for(i=0;i<len1;i++)
    {
        idx = arr1[i][0] * cols1 + arr1[i][1];
        buf[idx][0] += arr1[i][0];
        buf[idx][1] += arr1[i][1];
        buf[idx][2] = arr1[i][2];
    } //arr1을 buf메모리의 각 자리에 대입
    for(i=0;i<len2;i++)
    {
        idx = arr2[i][0] * cols2 + arr2[i][1];
        buf[idx][2] += arr2[i][2];
    } //arr1이 더해져있는 buf에 arr2도 마찬가지로 각 자리에 더해준다
    for(i=0;i<max;i++)
    {
        if(buf[i][2]!=0)
        {
            sum[count][0] = buf[i][0];
            sum[count][1] = buf[i][1];
            sum[count][2] = buf[i][2];
            count++;
        }
    } //buf 전체중 0이 아닌값을 찾아서 sum에 대입
    delete_memory(buf,max); //메모리 반환
    return count;
}

int arr_sub(int **arr1,int **arr2, int **sub, int rows1,int cols1,int rows2, int cols2, int len1, int len2)
{
    int i,j,idx;
    int count=0,max;
    int **buf;
    if(cols1!=cols2 || rows1 != rows2) //행렬의 뺄셈을 할 수 없는 경우 오류 메세지 출력
    {
        printf("행렬의 크기가 같지 않아 행렬의 뺼셈 연산을 수행 할 수 없습니다.\n");
        return;
    }

    if(len1>=len2) max = len1; //두개의 길이 중 더 큰 길이 저장
    else max = len2;

    buf = creat_memory(max,3); //임시 저장을 위한 메모리 생성
    for(i=0;i<len1;i++)
    {
        idx = arr1[i][0] * cols1 + arr1[i][1];
        buf[idx][0] += arr1[i][0];
        buf[idx][1] += arr1[i][1];
        buf[idx][2] = arr1[i][2];
    } //arr1을 buf메모리의 각 자리에 대입
    for(i=0;i<len2;i++)
    {
        idx = arr2[i][0] * cols2 + arr2[i][1];
        buf[idx][2] -= arr2[i][2];
    } //arr1이 더해져있는 buf에 arr2는 각 자리에 빼준다
    for(i=0;i<max;i++)
    {
        if(buf[i][2]!=0)
        {
            sub[count][0] = buf[i][0];
            sub[count][1] = buf[i][1];
            sub[count][2] = buf[i][2];
            count++;
        }
    } //buf 전체중 0이 아닌값을 찾아서 sum에 대입
    delete_memory(buf,max); //메모리 반환
    return count;
}

int arr_mul(int **arr1,int **arr2, int **mul, int rows1,int cols1,int rows2, int cols2, int len1, int len2)
{
    int i,j,k;
    int n,count=0,idx;
    int **buf1,**buf2;
    if(rows1!=cols2)
    {
        printf("행렬의 크기가 같지 않아 행렬의 곱셈 연산을 수행 할 수 없습니다.\n");
        return;
    }
    buf1 = creat_memory(rows1*cols1,3);
    buf2 = creat_memory(rows2*cols2,3);
    for(i=0;i<rows1*cols1;i++)
    {
        idx = arr1[i][0] * cols1 + arr1[i][1];
        buf1[idx][0] += arr1[i][0];
        buf1[idx][1] += arr1[i][1];
        buf1[idx][2] = arr1[i][2];
    } //arr1을 buf1메모리의 각 자리에 대입
    for(i=0;i<rows2*cols2;i++)
    {
        idx = arr1[i][0] * cols1 + arr1[i][1];
        buf2[idx][0] += arr2[i][0];
        buf2[idx][1] += arr2[i][1];
        buf2[idx][2] = arr2[i][2];
    } //arr2을 buf2메모리의 각 자리에 대입
    for(i=0;i<rows1;i++)
    {
        for(j=0;j<cols2;j++)
        {
            n=0;
            for(k=0;k<cols2;k++)
            {
                if(n==0) //처음에만 행,열값 대입
                {
                    mul[count][0] = i;
                    mul[count][1] = j;
                    n++;
                }
                mul[count][2] += buf1[rows1*i+k][2] * buf2[rows2*k+j][2]; //곱해진 값을 더해주면서 대입
            }
            count++;
        }
    }
    delete_memory(buf1,rows1*cols1);
    delete_memory(buf2,rows2*cols2);
    return count;
}

void delete_memory(int **arr, int rows) //동적으로 할당된 메모리를 반납하는 함수
{
    int i;
    for(i=0;i<rows;i++)
        free(arr[i]);
    free(arr);
}
