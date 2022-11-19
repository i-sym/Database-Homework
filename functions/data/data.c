#include "data.h"

int executeQuery(PGconn *, char *, char *, char *);
Student parseStudentData(PGresult *, int);
Grade parseGradeData(PGresult *, int);
Subject parseSubjectData(PGresult *, int);
void updateAverage(PGconn *, int);

void executeListQuery(PGconn *conn, DataType dataType) {
    PGresult *res;
    int numRecords;


    switch (dataType) {
        case STUDENT:
            res = PQexec(conn, "SELECT * FROM student ORDER BY student_code");
            break;
        case GRADE:
            res = PQexec(conn, "SELECT grade.id_grade, subject.subject_code, grade.student_code, grade.grade FROM grade LEFT JOIN subject ON grade.id_subject=subject.id_subject");
            break;
        case SUBJECT:
            res = PQexec(conn, "SELECT * FROM subject");
            break;
    }
    
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("No data retrieved from database");
        PQclear(res);
        return;
    }

    numRecords = PQntuples(res);

    switch(dataType) {
        case STUDENT:
            printStudentTable(res, numRecords);
            break;
        case GRADE:
            printGradeTable(res, numRecords);
            break;
        case SUBJECT:
            printSubjectTable(res, numRecords);
            break;
    }

    PQclear(res);

    return;

}

void doInsertion(PGconn *conn, DataType dataType) {
    char query[300];

    switch (dataType) {
        case STUDENT:
            Student student;
            studentForm(&student, CREATE);
            sprintf(query, "INSERT INTO student(student_code, first_name, last_name, birthdate) VALUES (((select max(student_code) from student) + 1),'%s', '%s', '%s')", student.firstName, student.lastName, student.birthdate);
            executeQuery(conn, query, "Student created successfully", "Error creating student");
            break;

        case GRADE:
            Grade grade;
            gradeForm(&grade, CREATE);
            sprintf(query, "INSERT INTO grade(id_subject, student_code, grade) VALUES (%d, %d, %d)", grade.subjectId, grade.studentCode, grade.grade);
            executeQuery(conn, query, "Grade created successfully", "Error creating grade");
            updateAverage(conn, grade.studentCode);
            break;
        case SUBJECT:
            Subject subject;
            subjectForm(&subject, CREATE);
            sprintf(query, "INSERT INTO subject (id_subject, credits, subject_code, name, teacher) VALUES (((select max(id_subject) from subject) + 1), %d, '%s', '%s', '%s')", subject.credits, subject.courseCode, subject.name, subject.teacher);
            executeQuery(conn, query, "Subject created successfully", "Creation failed");
            break;
    }
}

void doUpdate(PGconn *conn, DataType dataType) {
    PGresult *res;

    char query[300];

    switch (dataType) {
        case STUDENT:
            Student student;

            printf("Enter student code: ");
            scanf("%d", &student.studentCode);
            getchar();
            sprintf(query, "SELECT * FROM student WHERE student_code = %d", student.studentCode);
            res = PQexec(conn, query);
            if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                printf("Error retrieving student data");
                PQclear(res);
                return;
            }
            if (PQntuples(res) == 0) {
                printf("Student not found\n");
                PQclear(res);
                return;
            }

            student = parseStudentData(res, 0);
            PQclear(res);

            studentForm(&student, EDIT);
            sprintf(query, "UPDATE student SET first_name = '%s', last_name = '%s', birthdate = '%s' WHERE student_code = %d", student.firstName, student.lastName, student.birthdate, student.studentCode);
            executeQuery(conn, query, "Student updated successfully", "Error updating student");
            break;

        case GRADE:
            Grade grade;

            printf("Enter grade id: ");
            scanf("%d", &grade.id);
            getchar();
            sprintf(query, "SELECT id_grade, id_subject, student_code, grade FROM grade WHERE id_grade = %d", grade.id);
            res = PQexec(conn, query);
            if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                printf("Error retrieving grade data");
                PQclear(res);
                return;
            }
            if (PQntuples(res) == 0) {
                printf("Grade not found\n");
                PQclear(res);
                return;
            }

            grade = parseGradeData(res, 0);
            PQclear(res);

            gradeForm(&grade, EDIT);
            sprintf(query, "UPDATE grade SET id_subject = %d, student_code = %d, grade = %d WHERE id_grade = %d", grade.subjectId, grade.studentCode, grade.grade, grade.id);
            executeQuery(conn, query, "Grade updated successfully", "Error updating grade");

            updateAverage(conn, grade.studentCode);


            break;
        case SUBJECT:
            Subject subject;

            printf("Enter subject id: ");
            scanf("%d", &subject.id);
            getchar();

            sprintf(query, "SELECT id_subject, credits, subject_code, teacher, name FROM subject WHERE id_subject = %d", subject.id);
            res = PQexec(conn, query);
            if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                printf("Error retrieving subject data");
                PQclear(res);
                return;
            }

            if (PQntuples(res) == 0) {
                printf("Subject not found\n");
                PQclear(res);
                return;
            }
            subject = parseSubjectData(res, 0);
            PQclear(res);

            subjectForm(&subject, EDIT);
            sprintf(query, "UPDATE subject SET credits = %d, subject_code = '%s', name = '%s', teacher = '%s' WHERE id_subject = %d", subject.credits, subject.courseCode, subject.name, subject.teacher, subject.id);
            executeQuery(conn, query, "Subject updated successfully", "Error updating subject");
            break;
    }
    

}

void doDelete(PGconn *conn, DataType dataType) {
    char query[300];

    switch (dataType) {
        case STUDENT:
            int studentCode;
            printf("Enter student code: ");
            scanf("%d", &studentCode);
            getchar();
            sprintf(query, "DELETE FROM student WHERE student_code = %d", studentCode);
            executeQuery(conn, query, "Student deleted successfully", "Error deleting student");
            break;

        case GRADE:
            int gradeId;
            printf("Enter grade id: ");
            scanf("%d", &gradeId);
            getchar();
            sprintf(query, "DELETE FROM grade WHERE id_grade = %d", gradeId);
            executeQuery(conn, query, "Grade deleted successfully", "Error deleting grade");
            break;
        case SUBJECT:
            int subjectId;
            printf("Enter subject id: ");
            scanf("%d", &subjectId);
            getchar();
            sprintf(query, "DELETE FROM subject WHERE id_subject = %d", subjectId);
            executeQuery(conn, query, "Subject deleted successfully", "Error deleting subject");
            break;
    }
}

void doRanking(PGconn *conn){
    PGresult *res;
    char query[300];
    // Ask user for minimum grade
    float minGrade;
    printf("Enter minimum grade: ");
    
    scanf("%f", &minGrade);
    getchar();
    // Query database for students with average_grade >= minGrade, and order by grade. Preform join with student table to get student name
    sprintf(query, "SELECT * FROM student WHERE average_grade >= %f ORDER BY average_grade DESC", minGrade);

    res = PQexec(conn, query);

    if(PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("Error retrieving data from database: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    // Number of rows returned
    int nRows = PQntuples(res);

    // Print results using parseStudentTable
    printStudentTable(res, nRows);
    PQclear(res);


    
}

int executeQuery(PGconn *conn, char * query, char * successMessage, char * errorMessage) {
    PGresult *res;
    res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("%s: %s\n", errorMessage, PQerrorMessage(conn));
        PQclear(res);
            return 0;
    }

    printf("%s\n", successMessage);

    return 1;
}


void updateAverage(PGconn *conn, int studentCode) {
    PGresult *res;
    char query[400];
    sprintf(query, "UPDATE student SET average_grade = (SELECT (SUM(grade.grade * subject.credits) / SUM(subject.credits)) FROM grade INNER JOIN subject ON grade.id_subject = subject.id_subject WHERE student_code=%d) WHERE student_code=%d", studentCode, studentCode);
    executeQuery(conn, query, "Average grade updated successfully", "Error updating average grade");

}


Student parseStudentData(PGresult * res, int row){
    Student student;
    student.studentCode = atoi(PQgetvalue(res, 0, 0));
    strcpy(student.firstName, PQgetvalue(res, 0, 1));
    strcpy(student.lastName, PQgetvalue(res, 0, 2));
    strcpy(student.birthdate, PQgetvalue(res, 0, 3));
    printf("Student ( %06d | %s %s | %10s )\n", student.studentCode, student.firstName, student.lastName, student.birthdate);
    return student;
}

Subject parseSubjectData(PGresult * res, int row){
    Subject subject;
    subject.id = atoi(PQgetvalue(res, 0, 0));
    subject.credits = atoi(PQgetvalue(res, 0, 1));
    strcpy(subject.courseCode, PQgetvalue(res, 0, 2));
    strcpy(subject.teacher, PQgetvalue(res, 0, 3));
    strcpy(subject.name, PQgetvalue(res, 0, 4));

    printf("\n");
    printf("Subject ( ID: %d | Code: %s | Name: %s | Teacher: %s | %d ects )\n", subject.id, subject.courseCode, subject.name, subject.teacher, subject.credits);
    return subject;
}

Grade parseGradeData(PGresult * res, int row){
    Grade grade;
    grade.id = atoi(PQgetvalue(res, 0, 0));
    grade.subjectId = atoi(PQgetvalue(res, 0, 1));
    grade.studentCode = atoi(PQgetvalue(res, 0, 2));
    grade.grade = atoi(PQgetvalue(res, 0, 3));
    printf("\n");
    printf("Grade ( ID: %d | Subject: %d | Student: %06d | %d pnt )\n", grade.id, grade.subjectId, grade.studentCode, grade.grade);
    return grade;
}