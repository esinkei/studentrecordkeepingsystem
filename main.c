#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//structure defn
struct record{
    char name[50];
    int roll;
    float math;
    float sci;
    float eng;
    float nep;
    float soci;
};
//function prototypes
void starln();
void blanckln();
void sinlgerecin();
void batchrecin();
void modifyrecord(int x);
void secondmenu();
void deleterecord(int x);
void viewall();
void searchrecord();
void viewrecord(int x);

int main(){
	int choice;
    int numread=0;
    while(1){
        starln();
        blanckln();
        printf("1. Add a record\n2. Add Bulk Records\n3. List Students\n4. Search Student\n5. Quit\n");
        printf("What's your choice? : ");
        fflush(stdin);
        numread = scanf("%d",&choice);
        if (numread!=1)
        {   
            scanf("%*[^\n]");
            printf("\nBye Bye!\n");
        }
        else{
        switch (choice)
        {
        case 1:
            sinlgerecin();
            break;
        case 2:
            batchrecin();
            break;
        case 3:
            viewall();
            break;
        case 4:
            searchrecord();
            break;
        case 5:
            return 0;
            break;
        default:
            
            starln();
            printf("\nBye Bye!\n");
            break;
        }
        }
    }	
}

void starln(){
	printf("***************************************************************************\n");
}
void blanckln(){
	printf("                                                                                  \n");
}

void sinlgerecin(){
    FILE *fp;
    fp = fopen("rex.txt","ab+");
    if (fp == NULL)
    {
        fprintf(stderr, "\nError to open the file\n");
        exit (1);
    }
    struct record stu;
    printf("Enter name: ");
    scanf(" %[^\n]",stu.name);
    printf("Enter roll: ");
    scanf("%d",&stu.roll);
    printf("Enter marks obatained in Maths: ");
    scanf("%f",&stu.math);
    printf("Enter marks obatained in Science: ");
    scanf("%f",&stu.sci);
    printf("Enter marks obatained in English: ");
    scanf("%f",&stu.eng);
    printf("Enter marks obatained in Nepali: ");
    scanf("%f",&stu.nep);
    printf("Enter marks obatained in Social: ");
    scanf("%f",&stu.soci);
    fwrite(&stu,sizeof(struct record),1,fp);
    if(fwrite != 0)
        printf("Contents to file written successfully !\n");
    else
        printf("Error writing file !\n");
    fclose (fp);
}     


void batchrecin(){
	int N;
	printf("How many students?: ");
	scanf("%d",&N);
	FILE *fp;
    fp = fopen("rex.txt","ab+");
    if (fp == NULL)
    {
        fprintf(stderr, "\nError to open the file\n");
        exit (1);
    }
    struct record stu[N];
    for (int i = 0; i < N; i++)
    {
        printf("Enter information for student %d :\n",i+1);
        printf("Enter name: ");
        fflush(stdin);
        scanf(" %[^\n]",stu[i].name); 
        printf("Enter roll: ");
        fflush(stdin);
        scanf("%d",&stu[i].roll);
        printf("Enter marks obatained in Maths: ");
        fflush(stdin);
        scanf("%f",&stu[i].math);
        printf("Enter marks obatained in Science: ");
        fflush(stdin);
        scanf("%f",&stu[i].sci);
        printf("Enter marks obatained in English: ");
        fflush(stdin);
        scanf("%f",&stu[i].eng);
        printf("Enter marks obatained in Nepali: ");
        fflush(stdin);
        scanf("%f",&stu[i].nep);
        printf("Enter marks obatained in Social: ");
        fflush(stdin);
        scanf("%f",&stu[i].soci);
    }
    
    fwrite(&stu,sizeof(struct record),N,fp);

    if(fwrite != 0)
        printf("Contents to file written successfully !\n");
    else
        printf("Error writing file !\n");
    fclose (fp);
}


void secondmenu(){
    starln();
    printf("1. Edit Record\n");
    printf("2. Delete Record\n");
    printf("3. View Marksheet\n");
    printf("4. Quit\n");
    printf("What is your choice?:");
}

void modifyrecord(int x){
    int flag = 1;
    FILE *fm;
    struct record s;
    fm= fopen("rex.txt","rb+");
    if(fm==NULL){
        fprintf(stderr, "\nError to open the file\n");
        exit(1);
    }
    rewind(fm);
    while(fread(&s,sizeof(struct record),1,fm)==1){
        if(x==s.roll){
            printf("Enter new data:\n");
            printf("Enter name: ");
            scanf(" %[^\n]",s.name);   
            printf("Enter marks obatained in Maths: ");
            scanf("%f",&s.math);
            printf("Enter marks obatained in Science: ");
            scanf("%f",&s.sci);
            printf("Enter marks obatained in English: ");
            scanf("%f",&s.eng);
            printf("Enter marks obatained in Nepali: ");
            scanf("%f",&s.nep);
            printf("Enter marks obatained in Social: ");
            scanf("%f",&s.soci);
            fseek(fm,-sizeof(s),1);
            fwrite(&s,sizeof(s),1,fm);
            flag = 0;
            break;
        }

    }
    if (flag==0)
    {
        printf("Record successfully added!\n");
    }else
    {
        printf("\n Record not found\n.");
    }

    fclose(fm);

}

void deleterecord(int x){
    FILE *fp1,*fp2;
    struct record s1;
    fp1 = fopen("rex.txt","rb+");
    fp2 = fopen("copy.txt","ab+");
    if (fp1 ==NULL)
    {
        fprintf(stderr, "\nError to open the file\n");
        exit(1);
    }
    while (fread(&s1,sizeof(struct record),1,fp1))
    {
        if(s1.roll !=x){
            fwrite(&s1,sizeof(struct record),1,fp2);
        }
    }
    
    fclose(fp1);
    fclose(fp2);
    remove("rex.txt");
    rename("copy.txt","rex.txt");
    printf("Record deleted successfully! \n");
}

void viewall(){   
    FILE* fp;
    fp = fopen ("rex.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "\nError to open the file\n");
        exit(1);
    }
   
    struct record e;
    // sets pointer to start
    // of the file
    rewind(fp);
  
    starln();
    printf("Roll\t\t\t\tName\t\t\n");
  
    while (fread(&e, sizeof(struct record), 1, fp) == 1)
        printf("%d\t\t\t\t%s\n",e.roll, e.name);
  
   
 
    fclose(fp);
}

void searchrecord()
{
    int k;
    int rf =0;
    FILE* fp;
    fp = fopen ("rex.txt", "rb");
    if (fp == NULL) {
        fprintf(stderr, "\nError to open the file\n");
        exit (1);
    }
    printf("Enter the roll no:");
    scanf("%d",&k);
    struct record e;
    
    rewind(fp);
    
    while (fread(&e, sizeof(struct record), 1, fp) == 1){
        if (k == e.roll)
        {
            printf("Record Found\n");
            printf("Record name: %s\n",e.name);
            rf=1;
			break;
        }
    }
    
    fclose(fp);
   
    if(rf ==1)
    {
        secondmenu();
        int choice;
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            modifyrecord(k);
            break;
        
            case 2:
            deleterecord(k);
            break;
        
            case 3:
            viewrecord(k);
            break;

            default:
                break;
            }
    }else if(rf == 0)
    {
        printf("Record not found! \n");
    }

}

void viewrecord(int x){
    FILE *fm;
    struct record s;
    fm= fopen("rex.txt","rb+");
    if(fm==NULL){
        fprintf(stderr, "\nError to open the file\n");
        exit(1);
    }
    rewind(fm);
    while(fread(&s,sizeof(struct record),1,fm)==1){
        if(x==s.roll){
            char div[30];
            float pcent = (s.math + s.eng + s.nep + s.sci + s.soci)/5;
            if (pcent>=80 && pcent<=100)
            {
                strcpy(div,"Distinction");   
            }
            else if (pcent >=70)
            {
                strcpy(div,"First");
            }else if (pcent>=60)
            {
                strcpy(div,"Second");
            }else if (pcent>=50)
            {
                strcpy(div,"Third");
            }
            else
            {
                strcpy(div,"No Division");
            }
            
            printf("***************************************************************************\n");
            printf("|\tRoll\t: %-50d      |\n",s.roll);
            printf("|\tName\t: %-50s      |\n",s.name);
            printf("***************************************************************************\n");
            printf("|\tS.N.\t| Subjects                       |\tMarks\t\t  |\n");
            printf("***************************************************************************\n");
            printf("|\t1\t| Mathematics                    |  \t%-5.2f\t\t  |\n",s.math);
            printf("|\t2\t| English                        |  \t%-5.2f\t\t  |\n",s.eng);
            printf("|\t3\t| Nepali                         |  \t%-5.2f\t\t  |\n",s.nep);
            printf("|\t4\t| Science                        |  \t%-5.2f\t\t  |\n",s.sci);
            printf("|\t5\t| Social                         |  \t%-5.2f\t\t  |\n",s.soci);
            printf("***************************************************************************\n");
            printf("|\t \t| Percentage                     |  \t%-5.2f%%\t\t  |\n",pcent);
            printf("|\t \t| Division                       |  \t%-15s\t  |\n",div);
            printf("***************************************************************************\n");
			printf("END OF RESULT!\n");

            break;
        }
    
    }
    fclose(fm);
}
