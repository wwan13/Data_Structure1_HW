/****************************************************************************
작성자: 20194059 김태완
작성일: 2020.06.10
프로그램명: 링크드 리스트를 이용하여 두 다항식의 곱셈 연산을 수행하는 프로그램
*****************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//필요한 데이터의 원소들을 모아둔 구조체
typedef struct Elements
{
    int coef; //계수
    int expon; //지수
}Elements;
//연결리스트 노드
typedef struct ListNode
{
    Elements elements; //필요한 데이터 구조체
    struct ListNode *link; //링크필드
}ListNode;
//연결리스트 헤더
typedef struct ListType
{
    int size; //연결리스트의 크기
    ListNode *head; //헤드노드의 주소
    ListNode *tail; //마지막 노드의 주소
}ListType;

void error(char *message); //오류 출력함수
ListType* creat(); //연결리스트 헤더를 생성하는 함수
ListNode* insert_node(ListNode *pre,Elements value); //pre의 뒤에 새로운 노드 생성
ListNode* insert_head(ListNode *pre,Elements value); //맨 앞에 새로운 노드 생성
void insert_last(ListType* plist,Elements elements); //연결리스트의 노드를 뒤에 삽입하는 함수
void insert_with_sort(ListType *plist,Elements value); //정렬과 동시에 삽입 연산을 해주는 함수
void read_data(FILE *fp,ListType* plist); //파일로부터 데이터를 읽어오는 함수
void poly_mul(ListType* plist1,ListType* plist2,ListType* plist3); //다항식의 곱셈연산을 수행하는 함수
void poly_print(ListType* plist); //다항식을 출력하는 함수

int main()
{
    FILE *fp; //파일포인터
    ListType *list1,*list2,*list3; //리스트헤더를 저장하는 변수
    fp = fopen("data.txt","r"); //data.txt를 읽기 모드로 오픈
    if(fp == NULL) error("파일을 열 수 없습니다."); //파일 오픈 오류시 경고문 출력
    list1 = creat(); //list1 헤더 생성
    list2 = creat(); //list2 헤더 생성
    list3 = creat(); //list3 헤더 생성
    read_data(fp,list1); //list1에 데이터를 읽어 정렬 후 연결리스트에 저장
    read_data(fp,list2); //list1에 데이터를 읽어 정렬 후 연결리스트에 저장
    printf("polynomial A = ");
    poly_print(list1); //list1 출력
    printf("polynomial B = ");
    poly_print(list2); //list2 출력
    poly_mul(list1,list2,list3); //list1과list2의 다항식 곱셈 연산 수행
    printf("polynomial C = ");
    poly_print(list3); //다항식 곱셈 결과 출력
    free(list1); //list1 메모리 반납
    free(list2); //list2 메모리 반납
    free(list3); //list3 메모리 반납
    return 0;
}
//에러 출력 함수
void error(char *message)
{
    fprintf(stderr,"%s\n",message); //매개변수를 받아와 stderr형식으로 출력
    exit(1); //프로그램 종료
}
//연결리스트 헤더를 생성하는 함수
ListType* creat()
{
    ListType *plist = (ListType *)malloc(sizeof(ListType)); //메모리 동적 할당
    plist->size = 0; //크기 0으로 초기화
    plist->head = NULL; //헤드노드를 NULL로 초기화
    plist->tail = NULL; //마지막 노드를 NULL로 초기화
    return plist; //plist를 반환
}
//pre의 뒤에 새로운 노드 생성
ListNode* insert_node(ListNode *pre,Elements value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    if (p==NULL) error("메모리 할당 에러"); //동적할당 오류시 오류문 출력
    p->elements = value;
    p->link = pre->link;
    pre->link = p;
    return p;
}
//맨 앞에 새로운 노드 생성
ListNode* insert_head(ListNode *pre,Elements value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    if (p==NULL) error("메모리 할당 에러"); //동적할당 오류시 오류문 출력
    p->elements = value;
    p->link = pre;
    return p;
}
//연결리스트의 마지막 노드 뒤에 새로운 노드를 생성 후 삽입하는 함수
void insert_last(ListType* plist,Elements elements)
{
    ListNode* temp = (ListNode *)malloc(sizeof(ListNode)); //메모리 동적 할당
    if (temp==NULL) error("메모리 할당 에러"); //동적할당 오류시 오류문 출력
    temp->elements = elements;
    temp->link = NULL;
    if(plist->tail == NULL)
    {
        plist->head = temp;
        plist->tail = temp;
    }
    else
    {
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->size++;
}
//정렬과 동시에 삽입 연산을 해주는 함수
void insert_with_sort(ListType *plist,Elements value)
{
    ListNode *p = plist->head;
    ListNode *temp;
    int n=0;
    if(plist->head==NULL) //연결리스트가 비어있을 경우
    {
        insert_last(plist,value); //헤드노드 생성
        n++;
    }
    for(temp=plist->head;temp;temp=temp->link)
    {
        if(value.expon>temp->elements.expon) //만약 받아온 지수가 원래 저장된 값보다 크다면
        {
            if(temp==plist->head) //그 위치가 헤드노드일 경우
            {
                plist->head = insert_head(temp,value); //새로운 헤드노드를 생성하고 헤드 포인터를 바꾼다
            }
            else //헤드노드가 아닐경우
            {
                insert_node(p,value); //temp의 앞에 새로운 노드 생성
            }
            n++;
        }
        p = temp; //p는 temp의 전 링크를 가르키게 함
    }
    if(n==0) //가장 작을때
    {
        insert_last(plist,value); //맨 뒤에 새로운 노드 생성
    }
}
//파일로부터 데이터를 읽어오는 함수
void read_data(FILE *fp,ListType* plist)
{
    char tmp[20];
    Elements value;
    fscanf(fp,"%s",tmp); //파일 각 줄의 첫번째에 있는 문자열을 읽어온다
    while(fscanf(fp,"%d %d",&value.coef,&value.expon) == 2) //fscanf는 반환값으로 읽어온 데이터의 수를 반환하기 때문에
    {                                                       //계수와 지수를 같이 읽어와 반환값이 2일때만 반복하게 한다
        insert_with_sort(plist,value);
    }
}
//다항식의 곱셈 연산을 수행해주는 함수
void poly_mul(ListType* plist1,ListType* plist2,ListType* plist3)
{
    int n=0;
    ListNode *a = plist1->head;
    ListNode *b = plist2->head;
    ListNode *tmp;
    Elements elements;
    for(a = plist1->head;a;a=a->link)
    {
        for(b = plist2->head;b;b=b->link)
        {
            elements.coef = a->elements.coef * b->elements.coef; //계수끼리는 곱해준다
            elements.expon = a->elements.expon + b->elements.expon; //지수끼리는 더해준다
            n=0;
            for(tmp = plist3->head;tmp;tmp=tmp->link)
            {
                if(tmp->elements.expon==elements.expon) //만약 list3에 지수값이 같은 항이 존재하면
                {
                    tmp->elements.coef += elements.coef; //기존에 저장된 계수에 새로운 계수를 더해준다
                    n++; //새로운 노드에 삽입 할 필요 없다는 것을 알려준다
                }
            }
            if(n==0) //새로운 노드에 삽입해야 하는 경우
            {
                insert_last(plist3,elements);
            }
        }
    }
}
//다항식을 출력해주는 함수
void poly_print(ListType* plist)
{
    ListNode* p = plist->head;
    for(p = plist->head;p;p=p->link)
    {
        printf("%d^%d",p->elements.coef,p->elements.expon);
        if(p->link!=NULL) //맨 마지막에는 *출력을 하면 안된다
        {
            printf(" + ");
        }
    }
    printf("\n");
}
