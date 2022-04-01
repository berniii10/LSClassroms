#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 50
#define MAX_STRING_LENGTH 70

typedef struct {
    char name[MAX_STRING_LENGTH];
    char login[MAX_STRING_LENGTH];
} Student;

typedef struct {
    char name[MAX_STRING_LENGTH];
    int max_capacity;
    int current_capacity;
    Student *students;
} Classroom;

typedef struct {
    char name[MAX_STRING_LENGTH];
    int num_classrooms;
    Classroom *classrooms;
} Degree;

typedef struct {
    int num_degrees;
    Degree * elements;
} Degrees;

int menu(){
    int opcio;
    printf("1. Summary | 2. Show degree students | 3. Move student | 4. Exit\n");
    printf("Select option: ");
    scanf("%d", &opcio);

    while (opcio < 1 || opcio > 4){
        printf("ERROR: Opcio incorrecte\n");
        printf("1. Summary | 2. Show degree students | 3. Move student | 4. Exit\n");
        printf("Select option: ");
        scanf("%d", &opcio);
    }

    return opcio;
}

void readFileClassrooms(char file_cl[MAX_LEN], Degrees * degrees){
    int open = 0;
    char trash;
    FILE *f;
    f = fopen(file_cl, "r");
    if(f == NULL){
        while(!open){
            printf("\nERROR: Can't open file '%s'\n\n", file_cl);
            printf("Type the name of the 'classrooms file:");       //FICAR ESPAI
            fgets(file_cl, MAX_LEN, stdin);
            file_cl[strlen(file_cl) - 1] = '\0';

            printf("Fila name: %s\n", file_cl);

            f = fopen(file_cl, "r");
            if(f != NULL) open = 1;
        }
    }

    fscanf(f, "%d", &degrees->num_degrees);
    degrees->elements = (Degree *)malloc(sizeof (Degree) * degrees->num_degrees);
    printf("Num degrees: %d\n", degrees->num_degrees);
    for (int i = 0; i < degrees->num_degrees; i++) {
        fscanf(f, "%d", &degrees->elements[i].num_classrooms);
        fscanf(f, "%c", &trash);
        fgets(degrees->elements[i].name, MAX_STRING_LENGTH, f);
        degrees->elements[i].name[strlen(degrees->elements[i].name) - 1] = '\0';

        printf("Num class: %d - Name: %s\n", degrees->elements[i].num_classrooms, degrees->elements[i].name);
    }

}

void readFileStudents(char file_st[MAX_LEN]){
    int open = 0;
    FILE *f;
    f = fopen(file_st, "r");
    if(f == NULL) {
        while (!open) {
            printf("\nERROR: Can't open file '%s'\n\n", file_st);
            printf("Type the name of the 'classrooms file:");       //FICAR ESPAI
            fgets(file_st, MAX_LEN, stdin);
            file_st[strlen(file_st) - 1] = '\0';

            printf("Fila name: %s\n", file_st);

            f = fopen(file_st, "r");
            if (f != NULL) open = 1;
        }
    }



}

int main() {
    int opcio;
    char file_st[MAX_LEN], file_cl[MAX_LEN];
    //Degrees * degrees = (Degrees *) malloc(sizeof (Degrees));
    Degrees degrees;

    printf("Welcome!\n\n");

    printf("Type the name of the 'classrooms' file:");      //FICAR ESPAI!!!
    fgets(file_cl, MAX_LEN, stdin);
    file_cl[strlen(file_cl) - 1] = '\0';
    readFileClassrooms(file_cl, &degrees);

    printf("\nType the name of the 'students' file: ");
    fgets(file_st, MAX_LEN, stdin);
    file_cl[strlen(file_cl) - 1] = '\0';
    //readFileStudents(file_st);

    printf("\n\n");
    opcio = menu();

}
