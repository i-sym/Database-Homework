#include "forms.h"

void formStringField(char *, char*, FieldMode);
void formIntField(char *, int*, FieldMode);

void studentForm(Student * student, FieldMode mode) {

    printf("Enter information about student: \n");
    formStringField("First name", student->firstName, mode);
    formStringField("Last name", student->lastName, mode);
    formStringField("Birthdate", student->birthdate, mode);    
}
void subjectForm(Subject * subject, FieldMode mode) {

    printf("Enter information about subject: \n");
    formStringField("Code", subject->courseCode, mode);
    formStringField("Name", subject->name, mode);
    formStringField("Teacher", subject->teacher, mode);
    formIntField("Credits", &subject->credits, mode);

}
void gradeForm(Grade * grade, FieldMode mode) {

    printf("Enter information about grade: \n");
    formIntField("Student code", &grade->studentCode, mode);
    formIntField("Subject id number", &grade->subjectId, mode);
    formIntField("Grade", &grade->grade, mode);

}

void formStringField(char * message, char* field, FieldMode mode) {
    char readValue[33] = "";
    
    if(mode == EDIT) {
        printf("%s [%s]: ", message, field);

        // User can either press enter to keep the current value or enter a new value
        fgets(readValue, 32, stdin);
        if(readValue[0] == '\n') {
            return;
        }
        readValue[strlen(readValue) - 1] = '\0';
        strcpy(field, readValue);

    } else {
        do {
            printf("%s: ", message);
            fgets (readValue, 32, stdin);
            readValue[strlen(readValue) - 1] = '\0';
        } while(strlen(readValue) == 0);  
        strcpy(field, readValue);         
    }

}
void formIntField(char * message, int* field, FieldMode mode) {
    char readValue[32] = "";
    
    if(mode == EDIT) {
        printf("%s [%d]: ", message, *field);

        // User can either press enter to keep the current value or enter a new value
        fgets (readValue, 32, stdin);
        if (readValue[0] == '\n') {
            return;
        }
        readValue[strlen(readValue) - 1] = '\0';
        *field = atoi(readValue);

    } else {
        do {
            printf("%s: ", message);
            fgets (readValue, 32, stdin);
            readValue[strlen(readValue) - 1] = '\0';
        } while(strlen(readValue) == 0); 
        *field = atoi(readValue);         
    }

}
