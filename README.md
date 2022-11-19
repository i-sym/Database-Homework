
## We'll need it later

'''

    //Execute query
    // res = PQexec(conn, "SELECT * FROM student LIMIT 10;");
    
    // //Check query result status
    // if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    //     printf("We did not get any data!\n");
    //     PQfinish(conn);
    //     return 0;
    // }
    
    // //records count
    // rec_count = PQntuples(res);
    
    // printf("We received %d records.\n", rec_count);

    // printf("==========================\n");
    
    // //Print received records
    // for (row=0; row<rec_count; row++) {
    //     for (col=0; col<4; col++) {
    //         printf("%-10s\t", PQgetvalue(res, row, col));
    //     }
    //     printf("\n"); 
    // }
    
    // printf("==========================\n");
    
    // //Free PGresult handle 
    // PQclear(res);
'''