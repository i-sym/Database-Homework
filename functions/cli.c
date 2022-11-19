#include "cli.h"

void printHint();

void generateConnectionString(char *connString) {
    sprintf(connString, "dbname=%s host=%s port=%s user=%s password=%s", 
        DB_NAME, 
        DB_HOST,
        DB_PORT, 
        DB_USER, 
        DB_PASS);
}

int checkConnectionError(PGconn *conn) {
    if (PQstatus(conn) == CONNECTION_BAD) {
        printf("Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return 1;
    }
    return 0;
}

void startCLI(PGconn *conn) {
    printf("Welcome to the command line interface of the database.\n");
    printHint();
    while (1) {
        char command[100];
        char token[100] = "";
        char param[100] = "";
        printf("> ");
        fgets(command, 100, stdin);
        sscanf(command, "%s %s", token, param);


        if (strcmp(token, "list") == 0) {
            if (strcmp(param, "student") == 0) {
                executeListQuery(conn, STUDENT);
            }
            else if (strcmp(param, "grade") == 0) {
                executeListQuery(conn, GRADE);
            }
            else if (strcmp(param, "subject") == 0) {
                executeListQuery(conn, SUBJECT);
            }
            else {
                printf("Invalid parameter. Type 'list [student|grade|subject]'\n");
            }
        } 

        else if (strcmp(token, "create") == 0) {
            if (strcmp(param, "student") == 0) {
                doInsertion(conn, STUDENT);
            }
            else if (strcmp(param, "grade") == 0) {
                doInsertion(conn, GRADE);
            }
            else if (strcmp(param, "subject") == 0) {
                doInsertion(conn, SUBJECT);
            }
            else {
                printf("Invalid parameter. Type 'create [student|grade|subject]'\n");
            }
        }
        
        else if (strcmp(token, "update") == 0) {
            if (strcmp(param, "student") == 0) {
                doUpdate(conn, STUDENT);
            }
            else if (strcmp(param, "grade") == 0) {
                doUpdate(conn, GRADE);
            }
            else if (strcmp(param, "subject") == 0) {
                doUpdate(conn, SUBJECT);
            }
            else {
                printf("Invalid parameter. Type 'update [student|grade|subject]'\n");
            }
        }
        else if (strcmp(token, "delete") == 0) {
            if (strcmp(param, "student") == 0) {
                doDelete(conn, STUDENT);
            }
            else if (strcmp(param, "grade") == 0) {
                doDelete(conn, GRADE);
            }
            else if (strcmp(param, "subject") == 0) {
                doDelete(conn, SUBJECT);
            }
            else {
                printf("Invalid parameter. Type 'delete [student|grade|subject]'\n");
            }
        }
        else if(strcmp(token, "ranking") == 0){
            doRanking(conn);
        }
        else if (strcmp(token, "exit") == 0) {
            break;
        } else if( strcmp(token, "help") == 0) {
            printHint();
        }
        
        else if (strcmp(token, "") == 0) {
            continue;
        } else {
            printf("Invalid command '%s'. Type 'help' for a list of available commands.\n", token);
        }
    }
    printf("Thank you for using the command line interface of the database.\n");
    return;
}

void printHint() {
    printf("The available commands are:\n");
    printf("_______________________________________________\n");
    printf("help\n");
    printf("ranking\n");
    printf("list student   | list grade   | list subject\n");
    printf("create student | create grade | create subject\n");
    printf("update student | update grade | update subject\n");
    printf("delete student | delete grade | delete subject\n");
    printf("exit\n");
    printf("_______________________________________________\n");

    printf("\n");
}


