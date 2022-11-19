#ifndef LISTS_H
#define LISTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

void printStudentTable(PGresult *, int );
void printGradeTable(PGresult *, int );
void printSubjectTable(PGresult *, int );

#endif // LISTS_H