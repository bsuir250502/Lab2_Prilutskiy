#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    int unionType;
    char Name[20];
    union medical
    {
        struct v1
        {
            char Weight[20];
            char Height[20];
        }v1;
        struct v2
        {
            char Weight[20];
            char Height[20];
            char Puls[20];
            char Pressure[20];
        }v2;
    } Medical;
} Student;


void Help()
{
    puts("Usage");
    puts("Press 1 to add students, according to selected type of input. Press 2 to print all, 0 to exit program");
}

void GetString(char* string)
{
    fgets(string,20,stdin);
}

int GetInt(int * number)
{
    char buffer[20];
    fgets(buffer,20,stdin);
    *number = atoi(buffer);
    return (strlen(buffer) > 4)?0:1;
}

void AddStudent(Student * source, int count)
{
    char * buffer = (char *) malloc(20 * sizeof(char));
    puts("Name");
    GetString(buffer);
    strcpy(source[count].Name,buffer);

    while (1)
    {
        puts("Input type [1/2]:");
        if (!GetInt(&source[count].unionType))
        {
            puts("Input error. Try again");
            continue;
        }
        if (source[count].unionType == 1)
        {
            puts("Weight:");
            GetString(buffer);
            strcpy(source[count].Medical.v1.Weight, buffer);
            puts("Height:");
            GetString(buffer);
            strcpy(source[count].Medical.v1.Height, buffer);
        }
        if (source[count].unionType == 2)
        {
            puts("Weight:");
            GetString(buffer);
            strcpy(source[count].Medical.v2.Weight, buffer);
            puts("Height:");
            GetString(buffer);
            strcpy(source[count].Medical.v2.Height, buffer);
            puts("Puls:");
            GetString(buffer);
            strcpy(source[count].Medical.v2.Puls, buffer);
            puts("Pressure");
            GetString(buffer);
            strcpy(source[count].Medical.v2.Pressure, buffer);
        }
        if (source[count].unionType != 1 && source[count].unionType != 2)
        {
            puts("Input error. Try again");
            continue;
        }
        free(buffer);
        break;
    }

}

void PrintAll(Student * source, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("=============================%d==============================\n", i+1);
        puts("Name:"); 
        puts(source[i].Name);
        puts("Input type"); printf("%d\n", source[i].unionType);
        if (source[i].unionType == 1)
        {
            puts("Weight:"); puts(source[i].Medical.v1.Weight);
            puts("Height:"); puts(source[i].Medical.v1.Height);
        }
        if (source[i].unionType == 2)
        {
            puts("Weight:"); puts(source[i].Medical.v2.Weight);
            puts("Height:"); puts(source[i].Medical.v2.Height);
            puts("Puls:"); puts(source[i].Medical.v2.Puls);
            puts("Pressure:"); puts(source[i].Medical.v2.Pressure);
        }
    }
}

int main (int argc, char * argv[])
{
    if (argc>1) 
    {
        if (strcmp(argv[1],"-h")==0)
        {
            Help();
            return 0;
        }
        else 
        {
            puts("Error. Improper parameter.");
            return 0;
        }
    }

    int n;
    while (1)
    {
        puts("Type in max amount of students");
        
        if (!GetInt(&n))
        {
            puts("Input error. Try again");
            continue;
        }
        break;
    }

    Student * All = (Student *)malloc(n * sizeof(Student));
    int count = 0;
    while (1)
    {
        puts("1. Add student\n2. Print student list\n0. Exit");
        int inp; 
        if (!GetInt(&inp)) 
        {
            puts("Input error. Try again");
            continue;
        }
        switch(inp)
        {
            default: 
            puts("Input error. Try again");
            break;
            case 1:
            {                
                AddStudent(All, count);
                count++;
                break;
            }
            case 2:
            PrintAll(All, count);
            break;
            case 0:
            free(All);
            return EXIT_SUCCESS;
        }
    }
    free(All);
    return EXIT_SUCCESS;
}