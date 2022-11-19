#ifndef CLI_H
#define CLI_H

#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

#include "data/data.h"

#define DB_NAME "homework_1"
#define DB_HOST "localhost"
#define DB_PORT "54320"
#define DB_USER "admin"
#define DB_PASS "admin"


void generateConnectionString(char *);
void startCLI(PGconn *);
int checkConnectionError(PGconn *);


#endif // CLI_H