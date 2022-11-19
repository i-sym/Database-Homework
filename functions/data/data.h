#ifndef DATA_H
#define DATA_H

#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../types.h"
#include "../lists/lists.h"
#include "../forms/forms.h"

void executeListQuery(PGconn *conn, DataType dataType);
void doInsertion(PGconn *conn, DataType dataType);
void doUpdate(PGconn *conn, DataType dataType);
void doDelete(PGconn *conn, DataType dataType);
void doRanking(PGconn *conn);

#endif // DATA_H