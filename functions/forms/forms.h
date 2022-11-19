#ifndef FORMS_H
#define FORMS_H

#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../types.h"

void studentForm(Student * , FieldMode);
void subjectForm(Subject * , FieldMode);
void gradeForm(Grade * , FieldMode);

#endif // DATA_H