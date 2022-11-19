#ifndef TYPES_H
#define TYPES_H

typedef struct Student {
    int studentCode;
    char firstName[33];
    char lastName[33];
    char birthdate[11];
    int averageGrade;
} Student;

typedef struct Grade {
    int id;
    int studentCode;
    int subjectId;
    int grade;
} Grade;

typedef struct Subject {
    int id;
    char courseCode[8];
    char name[33];
    char teacher[33];
    int credits;
} Subject;

typedef enum {
    STUDENT,
    GRADE,
    SUBJECT
} DataType;

typedef enum Action {
    INSERT,
    UPDATE,
    DELETE,
    LIST
} Action; 

typedef enum FieldMode {
    CREATE,
    EDIT
} FieldMode;



#endif // TYPES_H