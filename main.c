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

            printf("File name: %s\n", file_cl);

            f = fopen(file_cl, "r");
            if(f != NULL) open = 1;
        }
    }

    fscanf(f, "%d", &degrees->num_degrees);
    degrees->elements = (Degree *)malloc(sizeof (Degree) * degrees->num_degrees);
    //printf("Num degrees: %d\n", degrees->num_degrees);
    for (int i = 0; i < degrees->num_degrees; i++) {
        fscanf(f, "%d", &degrees->elements[i].num_classrooms);
        fscanf(f, "%c", &trash);
        fgets(degrees->elements[i].name, MAX_STRING_LENGTH, f);
        degrees->elements[i].name[strlen(degrees->elements[i].name) - 1] = '\0';

        degrees->elements[i].classrooms = (Classroom *) malloc(sizeof (Classroom) * degrees->elements[i].num_classrooms);

        //printf("Num class: %d - Name: %s\n", degrees->elements[i].num_classrooms, degrees->elements[i].name);

        for (int j = 0; j < degrees->elements[i].num_classrooms; j++) {
            fscanf(f, "%s", degrees->elements[i].classrooms[j].name);
            fscanf(f, "%d", &degrees->elements[i].classrooms[j].max_capacity);
            degrees->elements[i].classrooms[j].current_capacity = 0;
            //printf("Class name: %s - Max capacity: %d\n", degrees->elements[i].classrooms[j].name, degrees->elements[i].classrooms[j].max_capacity);

            degrees->elements[i].classrooms[j].students = (Student *) malloc(sizeof (Student) * degrees->elements[i].classrooms[j].max_capacity);
        }
    }
}

void readFileStudents(char file_st[MAX_LEN], Degrees * degrees){
    int open = 0;
    char nom_aux[MAX_STRING_LENGTH];
    char grau_aux[MAX_STRING_LENGTH];
    char login_aux[MAX_STRING_LENGTH];
    char trash;
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

    while(fscanf(f, "%s", nom_aux) == 1){

        nom_aux[strlen(nom_aux) -1 ] = '\0';
        fscanf(f, "%c", &trash);

        fgets(grau_aux, MAX_STRING_LENGTH, f);
        grau_aux[strlen(grau_aux) - 1] = '\0';

        fscanf(f, "%s", login_aux);

        //printf("Nom:%s-Grau:%s-Login:%s\n", nom_aux, grau_aux, login_aux);

        for (int i = 0; i < degrees ->num_degrees; i++) {
            if(!strcmp(grau_aux, degrees->elements[i].name)){

                for (int j = 0; j < degrees->elements[i].num_classrooms; ++j) {
                    if(degrees->elements[i].classrooms[j].current_capacity < degrees->elements[i].classrooms[j].max_capacity){
                        strcpy(degrees->elements[i].classrooms[j].students[degrees->elements[i].classrooms[j].current_capacity].name, nom_aux);
                        strcpy(degrees->elements[i].classrooms[j].students[degrees->elements[i].classrooms[j].current_capacity].login, login_aux);
                        degrees->elements[i].classrooms[j].current_capacity++;
                        break;
                    }
                }

            }
        }
    }
}

int main() {
    int opcio;
    char file_st[MAX_LEN], file_cl[MAX_LEN];
    Degrees * degrees = (Degrees *) malloc(sizeof (Degrees));
    //Degrees degrees;

    printf("Welcome!\n\n");

    printf("Type the name of the 'classrooms' file:");      //FICAR ESPAI!!!
    fgets(file_cl, MAX_LEN, stdin);
    file_cl[strlen(file_cl) - 1] = '\0';
    readFileClassrooms(file_cl, degrees);


    printf("\nType the name of the 'students' file:");
    fgets(file_st, MAX_LEN, stdin);
    file_cl[strlen(file_st) - 1] = '\0';
    printf("--%s--", file_st);
    readFileStudents(file_st, degrees);


    for (int i = 0; i < degrees->num_degrees; i++) {
        printf("Num class: %d - Name: %s\n", degrees->elements[i].num_classrooms, degrees->elements[i].name);

        for (int j = 0; j < degrees->elements[i].num_classrooms; j++) {
            printf("Class name: %s - Max capacity: %d - Current capacity: %d\n", degrees->elements[i].classrooms[j].name, degrees->elements[i].classrooms[j].max_capacity, degrees->elements[i].classrooms[j].current_capacity);
            for (int k = 0; k < degrees->elements[i].classrooms[j].current_capacity; ++k) {
                printf("Student name: %s - Student Login: %s\n", degrees->elements[i].classrooms[j].students[k].name, degrees->elements[i].classrooms[j].students[k].login);
            }
        }
        printf("\n");
    }



    printf("\n\n");
    opcio = menu();

    switch (opcio) {
        case 1:
            break;
    }

}
