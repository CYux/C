#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct detail{
    int year;
    int month;
    int day;
    char type[10];
    char category[20];
    double amount;
    struct detail *nxt;
}detail;


detail * readFile(void);
void destroy(detail *head);
void printer(detail *head);
/*case 1*/
void periord(){
    detail *temp= readFile();
    detail *head = temp;
    int d1,d2,m1,m2,y1,y2;
    printf("plx input the start time in day month year\n");
    scanf("%d%d%d",&d1,&m1,&y1);
    printf("plx input the end time in day month year\n");
    scanf("%d%d%d",&d2,&m2,&y2);
    
    if(head==NULL)
    {
        printf("Empty file!");
    }
    else
        printf("type..amount..category..day.month.year\n");
    do{
        if(head->year>y1 && head->year<y2)
            printf("%s %lf %s %d %d %d\n",head->type,head->amount,head->category,head->day,head->month,head->year);
        else if(head->year==y1){
            if(head->month>m1)
                printer(head);
            else if(head->month==m1){
                if(head->day>=m1)printer(head);
            }
        }
        else if(head->year==y2){
            if(head->month<m2)
                printer(head);
            else if(head->month==m2){
                if(head->day<=m2)printer(head);
            }
        }
            head=head->nxt;
    }while(head!=NULL);
    destroy(temp);
}
void printer(detail *head){
    printf("%s %lf %s %d %d %d\n",head->type,head->amount,head->category,head->day,head->month,head->year);
}
/*case 2*/
void creatNew(void){
    FILE *fpWrite=fopen("/Users/chan/Desktop/data.txt","a");
    if(fpWrite==NULL)
    {
        return;
    }
    detail * newDetail;
    while(1){
        newDetail = (detail*)malloc(sizeof(detail));
        printf("Please enter the income or expense \n");
        scanf("%s",newDetail->type);
        printf("Please enter the amount in Eur \n");
        scanf("%lf",&newDetail->amount);
        printf("Please enter the category \n");
        scanf("%s",newDetail->category);
        printf("Please enter the date in this order: day month year \n");
        scanf("%d%d%d",&newDetail->day,&newDetail->month,&newDetail->year);
        
        if(*newDetail->type == '0'){
            free(newDetail);
            fclose(fpWrite);
            break;
        }
        fprintf(fpWrite,"%s %lf %s %d %d %d\n",newDetail->type,newDetail->amount,newDetail->category,newDetail->day,newDetail->month,newDetail->year);
        printf("Great successful!\n");
    }
    fclose(fpWrite);
}

/*print all data*/

/*case 3*/
void exCate(){
    detail *temp= readFile();
    detail *head = temp;
    char category[10][20];
    double sumAmount[10]={0};
    int max;
    int i=0,j=0;
    if(head==NULL)
    {
        printf("Empty file!");
    }
    else{
        do{
        LOOP:for(i=0;i<10;i++)                       //遍历整个 Category 数组
            if(!strcmp(category[i], head->category)){//如果 当前Category  和 当前指针指向的 category相同
                head=head->nxt;                       //指针指向下一个指针
                sumAmount[i]+=head->amount;           //把category对应的 amount 加起来 存到sumAmount 数组中
                goto LOOP;                             //跳出
            }
                                                       //如果 所有category 和 当前指针指向的 category不相同
            strcpy(category[j],head->category);        //复制当前当前指针指向的 category 到一个 Category 数组中
            sumAmount[j++]+=head->amount;             //把category对应的 amount 加起来 存到sumAmount 数组中
            head=head->nxt;                           //指针指向下一个指针
        }while(head!=NULL);                            //遍历整个 指针
    }
    for(max=0,i=0;i<10;i++)
        if(sumAmount[max]<sumAmount[i]){
            max=i;
        }
    printf("most expensive category is %s\nthe amount is %lf\n",category[max],sumAmount[max]);
    destroy(temp);
}

/*case 4*/
void display_total(){
    detail *temp= readFile();
    detail *head = temp;
    double total_income=0;
    double total_expense=0;
    if(head==NULL)
    {
        printf("Empty file!");
    }
    else
    {
        while(head!=NULL){
            if (!strcmp(head->type,"income")){
                total_income+=head->amount;
                head=head->nxt;
            }
            else{
                total_expense+=head->amount;
                head=head->nxt;
            }}
        printf("total income: %lf\ntotal expense: %lf\n total balance: %lf\n",total_income,total_expense,total_income-total_expense);
    }
            destroy(temp);
}

/*case 5*/
void display(){
    detail *head = readFile();
    detail *temp=head;
    
    if(head==NULL)
    {
        printf("Empty file!");
    }
    else
    {
        printf("type..amount..category..day.month.year\n");
        do
        {
            printf("%s %lf %s %d %d %d\n",head->type,head->amount,head->category,head->day,head->month,head->year);
            head=head->nxt;
        }while(head!=NULL);
    }
        destroy(temp);
}

detail * readFile(){
    FILE *fpReader;
    detail *head, *p1, *p2;
    head = p1 = p2 = NULL;
    fpReader = fopen("/Users/chan/Desktop/data.txt", "r");
    if (fpReader == NULL)
    {
        printf("Can't open the file\n");
        exit(0);
    }
    while(!feof(fpReader))
    {
        p1 = (detail*)malloc(sizeof(detail));
        fscanf(fpReader, "%s %lf %s %d %d %d\n",p1->type,&p1->amount,p1->category,&p1->day,&p1->month,&p1->year);
        if (head == NULL)
        {
            head = p1;
            p2 = head;
        }
        else
        {
            p2->nxt = p1;
        }
        p2 = p1;
        p2->nxt = NULL;
    }
    fclose(fpReader);
    return head;
}

void destroy(detail *head) {
    while (head != NULL) {
        detail *tmp = head;
        head = head->nxt;
        free(tmp);
    }
}



int main()
{
    
    char num;
        /*the start menu*/
        printf(" --------------------------------------------------\n");
        printf(" |1.select the time period                         |\n");
        printf(" |2.add new income/expense                         |\n");
        printf(" |3.the most expensive category                    |\n");
        printf(" |4.display the total income and expense and       |\n");
        printf(" |  the overall balance                            |\n");
        printf(" |5.print all data                                 |\n");
        printf(" |0.exit                                           |\n");
        printf(" --------------------------------------------------\n");
        
        
        scanf("plx input an number %c",&num);
        while((num=getchar())!=EOF)
        switch(num)
        {
            case '1':
                periord();
                break;
            case '2':
                creatNew();
                break;
            case '3':
                exCate();
                break;
            case '4':
                display_total();
                break;
            case '5':
                display();
                break;
            case '0':
                exit(1);
            default:
                printf("plx input an number!\n");
                break;
        }
    return 0;
}
