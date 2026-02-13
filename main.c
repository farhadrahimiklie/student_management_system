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
    int count = 0;

    printf("\n");
    printf("====================================================================================================\n");
    printf("%-10s %-20s %-10s %-10s %-8s %-15s\n",
           "ID", "NAME", "Gender", "Marks", "Age", "Course");
    printf("====================================================================================================\n");


    while (fread(student, sizeof(students), 1, ptr) == 1)
    {
        printf("%-10d %-15s %-10s %-10.2f %-8d %-20s\n",
               student->studentId,
               student->studentName,
               student->studentGender,
               student->studentMarks,
               student->studentAge,
               student->studentCourse);
        count++;
    }
    printf("====================================================================================================\n");
    printf("Total Students: %d\n", count);
    fclose(ptr);
}

void Update_Student_By_Name(char name[])
{
    FILE *ptr = fopen("data.bin", "rb+");
    if (ptr == NULL)
    {
        perror("Cannot Open File...");
        return;
    }

    students student;
    int found = 0;

    while (fread(&student, sizeof(students), 1, ptr) == 1)
    {
        if (strcmp(student.studentName, name) == 0)
        {
            printf("\nStudent Found! Enter New Details:\n");

            getchar(); // clear buffer

            printf("New Name: ");
            fgets(student.studentName, sizeof(student.studentName), stdin);
            student.studentName[strcspn(student.studentName, "\n")] = '\0';

            printf("New Course: ");
            fgets(student.studentCourse, sizeof(student.studentCourse), stdin);
            student.studentCourse[strcspn(student.studentCourse, "\n")] = '\0';

            printf("New Gender: ");
            fgets(student.studentGender, sizeof(student.studentGender), stdin);
            student.studentGender[strcspn(student.studentGender, "\n")] = '\0';

            printf("New Marks: ");
            scanf("%f", &student.studentMarks);

            printf("New Age: ");
            scanf("%d", &student.studentAge);

            printf("New ID: ");
            scanf("%d", &student.studentId);

            fseek(ptr, -sizeof(students), SEEK_CUR);
            fwrite(&student, sizeof(students), 1, ptr);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student with name '%s' not found!\n", name);

    fclose(ptr);
}

void Delete_Student_By_Name(char name[])
{
    FILE *ptr = fopen("data.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");

    if (ptr == NULL || temp == NULL)
    {
        perror("File Error...");
        return;
    }

    students student;
    int found = 0;

    while (fread(&student, sizeof(students), 1, ptr) == 1)
    {
        if (strcmp(student.studentName, name) == 0)
        {
            found = 1;
            continue; // skip this student (delete)
        }

        fwrite(&student, sizeof(students), 1, temp);
    }

    fclose(ptr);
    fclose(temp);

    remove("data.bin");
    rename("temp.bin", "data.bin");

    if (found)
        printf("Student Deleted Successfully!\n");
    else
        printf("Student with name '%s' not found!\n", name);
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

void Sort_Students_By_Marks()
{
    FILE *ptr = fopen("data.bin", "rb");
    if (ptr == NULL)
    {
        perror("Cannot Open File...");
        return;
    }

    students arr[100];
    int count = 0;

    while (fread(&arr[count], sizeof(students), 1, ptr) == 1)
        count++;

    fclose(ptr);

    // Bubble Sort
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (arr[j].studentMarks < arr[j + 1].studentMarks)
            {
                students temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    ptr = fopen("data.bin", "wb");
    for (int i = 0; i < count; i++)
        fwrite(&arr[i], sizeof(students), 1, ptr);

    fclose(ptr);

    printf("Students Sorted By Marks Successfully!\n");
}


void Menu()
{
    printf("\n");
    printf("=================================================\n");
    printf("        STUDENT MANAGEMENT SYSTEM\n");
    printf("=================================================\n");
    printf("1. Add Student\n");
    printf("2. View All Students\n");
    printf("3. Search Student By Name\n");
    printf("4. Update Student By Name\n");
    printf("5. Delete Student By Name\n");
    printf("6. Sort Students By Marks\n");
    printf("0. Exit\n");
    printf("=================================================\n");
    printf("Enter Your Choice: ");
}


int main()
{
    
    int choice;
    students student;
    char name[35];

    do
    {
        Menu();
        scanf("%d", &choice);

        getchar(); // clear buffer

        switch (choice)
        {
        case 1:
            printf("Student Name: ");
            fgets(student.studentName, sizeof(student.studentName), stdin);
            student.studentName[strcspn(student.studentName, "\n")] = '\0';

            printf("Student Course: ");
            fgets(student.studentCourse, sizeof(student.studentCourse), stdin);
            student.studentCourse[strcspn(student.studentCourse, "\n")] = '\0';

            printf("Student Gender: ");
            fgets(student.studentGender, sizeof(student.studentGender), stdin);
            student.studentGender[strcspn(student.studentGender, "\n")] = '\0';

            printf("Student Marks: ");
            scanf("%f", &student.studentMarks);

            printf("Student Age: ");
            scanf("%d", &student.studentAge);

            printf("Student ID: ");
            scanf("%d", &student.studentId);

            Write_Student_to_Binary_File(student);
            printf("Student Added Successfully!\n");
            break;

        case 2:
            Read_Student_from_Binary_File(&student);
            break;

        case 3:
            printf("Enter Name to Search: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            Search_Student_By_Name(&student, name);
            break;

        case 4:
            printf("Enter Name to Update: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            Update_Student_By_Name(name);
            break;

        case 5:
            printf("Enter Name to Delete: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            Delete_Student_By_Name(name);
            break;

        case 6:
            Sort_Students_By_Marks();
            break;

        case 0:
            printf("Exiting Program... Goodbye!\n");
            break;

        default:
            printf("Invalid Choice! Try Again.\n");
        }

    } while (choice != 0);

    return 0;
}
