 #include <sqlite3.h>

sqlite3 *db;

/*

[index] INT,
    [timestamp] INT,
    kp dec,
    ki dec,
    kd dec,
    fposx dec,
    fposy dec,
    fposz dec,
    feulerx dec,
    feulery dec,
    feulerz dec
*/

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    return 0;
}

void writedb() {
    char* zErrMsg = 0;
    int res = 0;
    res = sqlite3_open("./data/data.db", &db); 
    res = sqlite3_exec(db, "INSERT INTO runs VALUES (1, 2, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0)", callback, 0, &zErrMsg);
    res = sqlite3_close(db);
}