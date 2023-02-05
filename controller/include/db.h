#ifndef __DB_H__
#define __DB_H__

#include <sqlite3.h>
#include <vector>
#include <string>

namespace twip 
{
    class DBObject 
    {
        virtual std::vector<std::string> get_columns();
    };

    class DBWriter
    {
        DBWriter(std::string filename);
        ~DBWriter() {};

        void writedb();
        private:
        sqlite3 *_db;
        std::string _filename;
    };    
}

#endif // __DB_H__