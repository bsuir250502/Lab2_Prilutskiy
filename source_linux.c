#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>

typedef struct student
{
    int unionType;
    struct person
    {
        char firstName[100];
        char lastName[100];
        char secondName[100];
    } personal;

    union     
    {
        struct
        {
            double height;
            double weight;
        }heightWeight;
        struct 
        {
            double _height;
            double _weight;
            int _puls;
            char _bloodPressure[10];
        }heightWeightPulsPressure;
    }medical;
}student;

int studentCount = 0;
void studentAdd(student * source);
void studentShow(student * source);
void studentDelete(student * source);
student * customRealloc(student * source, int sizeNew);

int main()
{
    student * allStudents = (student*)calloc(1,sizeof(student));
    while(1)
    {
        puts("Menu:");
        puts("\n0 - Exit\n1 - Add student\n2 - Remove student\n3 - Output data");
        int inpCommand = 0; __fpurge(stdin);
        if (!scanf("%d",&inpCommand)) {puts("Input Error"); continue;}
        switch(inpCommand)
        {
        default: 
            puts("Input Error"); continue;
        case 0: return;
        case 1:
            studentAdd(allStudents);
            break;
        case 2:
            studentDelete(allStudents);
        case 3:
            studentShow(allStudents);
            break;
        }
    }
    return 0;
}

void medicalInputv1 (student * source)
{
    while (1)
    {
        printf("Height: "); __fpurge(stdin);
        if(!scanf("%lf",&source[studentCount].medical.heightWeight.height)) {puts("Input Error"); continue;}
        printf("Weight: "); __fpurge(stdin);
        if(!scanf("%lf",&source[studentCount].medical.heightWeight.weight)) {puts("Input Error"); continue;}
        break;
    }
}

void medicalInputv2 (student * source)
{
    while (1)
    {
        printf("Height: "); __fpurge(stdin);
        if(!scanf("%lf",&source[studentCount].medical.heightWeightPulsPressure._height)) {puts("Input Error"); continue;}
        printf("Weight: "); __fpurge(stdin);
        if(!scanf("%lf",&source[studentCount].medical.heightWeightPulsPressure._weight)) {puts("Input Error"); continue;}
        printf("Puls: "); __fpurge(stdin);
        if(!scanf("%d",&source[studentCount].medical.heightWeightPulsPressure._puls)) {puts("Input Error"); continue;}
        printf("Blood pressure: ");
        if(!scanf("%s",&source[studentCount].medical.heightWeightPulsPressure._bloodPressure)) {puts("Input Error"); continue;}
        break;
    }
}

void studentAdd(student * source)
{
    puts("-------------------------Personal Info------------------------------");
    printf("First name: "); __fpurge(stdin);
    scanf("%s",&source[studentCount].personal.firstName);
    printf("Last name: "); __fpurge(stdin);
    scanf("%s",&source[studentCount].personal.lastName);
    printf("Second name: "); __fpurge(stdin);
    scanf("%s",&source[studentCount].personal.secondName);
    puts("-------------------------Medical data------------------------------");
    while (1) 
    {
    puts("Choose input type:\n1 - Height & weight only\n2 - Height, weight, puls and blood pressure\n");
    __fpurge(stdin); if (!scanf("%d", &source[studentCount].unionType)) {puts("Input Error"); continue;}
    if (source[studentCount].unionType!= 1 && source[studentCount].unionType!=2) {puts("Input Error"); continue;}
    printf("uniontupe value is %d\n",source[studentCount].unionType);
    break;//if we riched here - evryth is ok, proceeding
    }
    switch(source[studentCount].unionType)
    {
    case 1:
        medicalInputv1(source);
        break;
    case 2:
        medicalInputv2(source);
        break;
    }
    studentCount++;//indicates how many students have been added
    source = customRealloc(source,studentCount+1);    
}

void studentShow(student * source)
{
    for (int i=0; i<studentCount; i++)
    {
        printf("uniontupe value is %d\n",source[i].unionType);
        printf("Name: %s %s %s\n",source[i].personal.firstName,source[i].personal.lastName,source[i].personal.secondName);
        if (source[i].unionType==1)
            printf("Height: %lf\nWeight: %lf\n\n",source[i].medical.heightWeight.height,source[i].medical.heightWeight.weight);
        else 
        {
            printf("Height: %lf\nWeight: %lf\nPuls: %d\nBlood pressure: %s\n\n",source[i].medical.heightWeightPulsPressure._height,
            source[i].medical.heightWeightPulsPressure._weight,source[i].medical.heightWeightPulsPressure._puls,
            source[i].medical.heightWeightPulsPressure._bloodPressure);
        }

    }
}

void studentDelete(student * source)
{
    puts("Choose the student you want to remove from the list");
    for (int i=0; i<studentCount; i++)
        printf("%d - %s %s %s\n\n",i+1,source[i].personal.firstName,source[i].personal.secondName,source[i].personal.lastName);
    int inp;
    while(1)
    {
    printf("Your choise: ");
    __fpurge(stdin);
    if (!scanf("%d",&inp)) { puts("Input Error"); continue; }
    if (inp<1 || inp >=studentCount) { puts("Input Error"); continue; }
    break;
    }
    int validIndex = inp-1;
    for (int i = validIndex; i<=studentCount; i++)
        source[i]=source[i+1];
    studentCount--;
}

student * customRealloc(student * source, int sizeNew)
{
    student * result = (student*)calloc(sizeNew,sizeof(student));
    result = source;
    return result;
} 
