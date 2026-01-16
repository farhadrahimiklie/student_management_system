#include <stdio.h>
#include <string.h>

typedef struct students
{
    char studentName[35];
    char studentCourse[15];
    char studentGender[7];
    float studentMarks;
    int studentAge;
    int studentId;
} students;

void Write_Student_to_Binary_File(students student)
{
    FILE *ptr = fopen("data.bin", "ab");
    if (ptr == NULL)
    {
        perror("Cannot Open File While Writing... ");
        return;
    }
    fwrite(&student, sizeof(students), 1, ptr);
    fclose(ptr);
}

void Read_Student_from_Binary_File(students *student)
{
    FILE *ptr = fopen("data.bin", "rb");
    if (ptr == NULL)
    {
        perror("Cannot Open File While Reading... ");
        return;
    }
    printf("\t\t\t___________________________________ \n");
    printf("\t\t\t****** Students Full Details ****** \n");
    printf("\t\t\t___________________________________ \n");

    while (fread(student, sizeof(students), 1, ptr) == 1)
    {
        printf("________________________________________________________________________________________ \n");
        printf("Name: %s, Course: %s, Gender: %s, Marks: %.2f, Age: %d, ID: %d \n", student->studentName, student->studentCourse, student->studentGender, student->studentMarks, student->studentAge, student->studentId);
        printf("________________________________________________________________________________________ \n");
    }

    fclose(ptr);
}

void Search_Student_By_Name(students *student, char name[])
{
    FILE *ptr = fopen("data.bin", "rb");
    if (ptr == NULL)
    {
        perror("Cannot Open File While Reading... ");
        return;
    }

    int found = 0;

    while (fread(student, sizeof(students), 1, ptr) == 1)
    {
        if (strcmp(student->studentName, name) == 0)
        {
            printf("\n\t\tStudent Found!\n");
            printf("_________________________________________\n");
            printf("Name   : %s\n", student->studentName);
            printf("Course : %s\n", student->studentCourse);
            printf("Gender : %s\n", student->studentGender);
            printf("Marks  : %.2f\n", student->studentMarks);
            printf("Age    : %d\n", student->studentAge);
            printf("ID     : %d\n", student->studentId);
            printf("_________________________________________\n");

            found = 1;
            break; // remove if you want to find duplicates
    
        }  
    }

    if (!found)
    {
        printf("\nStudent with name '%s' not found!\n", name);
    }

    fclose(ptr);
}

int main()
{
    students student;
    char name[35];
    printf("Enter student name to search: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    Search_Student_By_Name(&student, name);
    // printf("Student Name__ ");
    // fgets(student.studentName, sizeof(student.studentName), stdin);
    // student.studentName[strcspn(student.studentName, "\n")] = '\0';

    // printf("Student Course__ ");
    // fgets(student.studentCourse, sizeof(student.studentCourse), stdin);
    // student.studentCourse[strcspn(student.studentCourse, "\n")] = '\0';

    // printf("Student Gender__ ");
    // fgets(student.studentGender, sizeof(student.studentGender), stdin);
    // student.studentGender[strcspn(student.studentGender, "\n")] = '\0';

    // printf("Student Marks__ ");
    // scanf("%f", &student.studentMarks);

    // printf("Student Age__ ");
    // scanf("%d", &student.studentAge);

    // printf("Student Id__ ");
    // scanf("%d", &student.studentId);

    // Write_Student_to_Binary_File(student);
    // Read_Student_from_Binary_File(&student);
    return 0;
}