#include "lists.h"

void printStudentRow(PGresult *, int);
void printGradeRow(PGresult *, int);
void printSubjectRow(PGresult *, int);

void printStudentHeader();
void printGradeHeader();
void printSubjectHeader();



void printStudentTable(PGresult *res, int rows) {
    int row;
    printf("Found %d records: \n\n", rows);
    printStudentHeader();
    for (row = 0; row < rows; row++) {
        printStudentRow(res, row);
    }
    printf("\n");

}
void printStudentHeader() {
    printf("\n");
    printf("| %-6s ", "Code"); 
    printf("| %-10s ", "Name");
    printf("| %-10s ", "Surname");
    printf("| %-10s ", "Birthdate");
    printf("| %-4s ", "Avg");
    printf("|\n");
    printf("|--------|------------|------------|------------|------|\n");

}
void printStudentRow(PGresult *res,  int row) {
    // Number alinged to the right and empty spaces filled with zeros
    printf("| %06d ", atoi(PQgetvalue(res, row, 0)));
    printf("| %-10s ", PQgetvalue(res, row, 1));
    printf("| %-10s ", PQgetvalue(res, row, 2));
    printf("| %10s ", PQgetvalue(res, row, 3));
    printf("| %4s ", PQgetvalue(res, row, 4));
    printf("|\n");
}

void printGradeTable(PGresult *res, int rows) {
    int row;
    printf("Found %d records: \n\n", rows);
    printGradeHeader();
    for (row = 0; row < rows; row++) {
        printGradeRow(res, row);
    }
    printf("\n");
}
void printGradeHeader() {
    
    printf("\n");
    printf("| %-6s ", "ID");
    printf("| %-7s ", "Subject");
    printf("| %-6s ", "Student");
    printf("| %-4s ", "Grade");
    printf("|\n");
    printf("|--------|---------|---------|-------|\n");
}
void printGradeRow(PGresult *res, int row) {
    printf("| %6d ", atoi(PQgetvalue(res, row, 0)));
    printf("| %-7s ", PQgetvalue(res, row, 1));
    printf("| %07d ", atoi(PQgetvalue(res, row, 2)));
    printf("| %5s ", PQgetvalue(res, row, 3));
    printf("|\n");
}

void printSubjectTable(PGresult *res, int rows) {
    int row;
    printf("Found %d records: \n\n", rows);
    printSubjectHeader();
    for (row = 0; row < rows; row++) {
        printSubjectRow(res, row);
    }
    printf("\n");
}
void printSubjectHeader() {
    printf("\n");
    printf("| %-6s ", "ID");
    printf("| %-3s ", "EAP");
    printf("| %-7s ", "Code");
    printf("| %-32s\t ", "Name");
    printf("| %-32s ", "Teacher");
    printf("|\n");
    printf("|--------|-----|---------|---------------------------------------|----------------------------------|\n");
}
void printSubjectRow(PGresult *res, int row) {
        printf("| %6d ", atoi(PQgetvalue(res, row, 0)));
    printf("| %3s ", PQgetvalue(res, row, 1));
    printf("| %-7s ", PQgetvalue(res, row, 2));
    printf("| %-32s\t ", PQgetvalue(res, row, 3));
    printf("| %-32s ", PQgetvalue(res, row, 4));
    printf("|\n");
}