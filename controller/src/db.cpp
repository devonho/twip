#include "db.h"

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

namespace twip 
{

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    return 0;
}

DBWriter::DBWriter(std::string filename) {
    _filename = filename;
}

void DBWriter::writedb() {
    char* zErrMsg = 0;
    int res = 0;
    res = sqlite3_open("./data/data.db", &_db); 
    res = sqlite3_exec(_db, "INSERT INTO runs VALUES (1, 2, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0)", callback, 0, &zErrMsg);
    res = sqlite3_close(_db);
}

}