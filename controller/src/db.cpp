#include "db.h"

#include <sstream>
#include <iostream>

// "INSERT INTO runs VALUES (1, 2, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0)"

namespace twip 
{

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    
    return 0;
}

std::string to_csv(std::vector<std::string> v) {
    std::stringstream ss;
    while(true)
    {
        ss << v.back();
        v.pop_back();
        if(v.empty())
        {
            break;
        }
        else
        {
            ss << ",";            
        }
    }
    return ss.str();    
}

DBWriter::DBWriter(std::string filename) {
    _filename = filename;
}

bool DBWriter::open() {
    int res = 0;
    res = sqlite3_open(_filename.c_str(), &_db);
    return res == 0 ? true : false;
}

bool DBWriter::close() {
    int res = 0;
    res = sqlite3_close(_db);
    return res == 0 ? true : false;
}

bool DBWriter::insert(DBObject *obj) {

    std::stringstream ss;
    
    ss << "INSERT INTO [" << obj->name << "] (";
    ss << to_csv(obj->get_columns());
    ss << ") VALUES (";
    ss << to_csv(obj->get_values());
    ss << ");";

    //std::cout << ss.str().c_str() << std::endl;
    return DBWriter::exec(ss.str().c_str());
}

bool DBWriter::create_table(DBObject *obj) {
    std::stringstream ss;

    ss << "CREATE TABLE [" << obj->name << "] (";
    for(int i=0; i<obj->get_columns().size(); i++)
    {
        ss << obj->get_columns()[i] << " ";
        ss << obj->get_column_types()[i];
        if(i+1 < obj->get_columns().size())
            ss << ",";
    }
    ss << ");";
    //std::cout << ss.str().c_str() << std::endl;
    return DBWriter::exec(ss.str().c_str());
}



bool DBWriter::exec(std::string query) {
    char* zErrMsg = 0;
    int res = 0;
    
    res = sqlite3_exec(_db, query.c_str(), callback, 0, &zErrMsg);
    return res == SQLITE_OK ? true : false;
}

};