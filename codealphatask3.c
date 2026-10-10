#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

void addStudent() {
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter student ID: ");
    scanf("%d", &s.id);

    printf("Enter student name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student added successfully!\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("\nID: %d\nName: %s\nMarks: %.2f\n",
               s.id, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    struct Student s;
    int id, found = 0;

    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter student ID to search: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.id == id) {
            printf("ID: %d\nName: %s\nMarks: %.2f\n",
                   s.id, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");

    fclose(fp);
}

void updateStudent() {
    struct Student s;
    int id, found = 0;

    FILE *fp = fopen("students.dat", "rb+");

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter student ID to update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.id == id) {
            printf("Enter new name: ");
            scanf(" %49[^\n]", s.name);

            printf("Enter new marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found)
        printf("Student updated successfully!\n");
    else
        printf("Student not found.\n");
}

void deleteStudent() {
    struct Student s;
    int id, found = 0;

    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("File error or no records found.\n");

        if (fp != NULL) fclose(fp);
        if (temp != NULL) fclose(temp);

        return;
    }

    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.id == id) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (remove("students.dat") != 0 ||
        rename("temp.dat", "students.dat") != 0) {
        printf("Error updating the records file.\n");
        return;
    }

    if (found)
        printf("Student deleted successfully!\n");
    else
        printf("Student not found.\n");
}

int main() {
    int choice;

    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}