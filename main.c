#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

#include "functions/cli.h"

int executeQuery(PGconn *, char * , char * , char * );

int main() {
    PGconn *conn;

    char connString[100];
    generateConnectionString(connString);
    conn = PQconnectdb(connString);


    if (checkConnectionError(conn)) {
        return 1;
    }
    
    startCLI(conn);
    
    PQfinish(conn);
    
    return 0;
}
