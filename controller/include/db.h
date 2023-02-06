#ifndef __DB_H__
#define __DB_H__

#include <sqlite3.h>
#include <vector>
#include <string>

#include <gz/msgs.hh>

namespace twip 
{
    class DBObject 
    {
        public:
            virtual std::vector<std::string> get_columns() = 0;
            virtual std::vector<std::string> get_values() = 0;
            virtual std::vector<std::string> get_column_types() = 0;
            DBObject(){};
            ~DBObject(){};
            std::string name;
    };

    class PoseDBObject : public DBObject
    {
        public:
            float orientx;
            float orienty;
            float orientz;

            float posx;
            float posy;
            float posz;
            long unsigned int timestamp;

            PoseDBObject();
            PoseDBObject(gz::msgs::Pose pose, long unsigned int timestamp);
            PoseDBObject(float orientx, float orienty, float orientz, float posx, float posy, float posz, long unsigned int timestamp);
            ~PoseDBObject(){};

            void operator=(PoseDBObject pose);

            std::vector<std::string> get_columns();
            std::vector<std::string> get_values();
            std::vector<std::string> get_column_types();
    };

    class PIDParamDBObject : public DBObject
    {
        public:
            float Kp;
            float Ki;
            float Kd;
            long unsigned int timestamp;

        PIDParamDBObject();
        PIDParamDBObject(float Kp, float Ki, float Kd, long unsigned int timestamp);
        ~PIDParamDBObject(){};

        std::vector<std::string> get_columns();
        std::vector<std::string> get_values();
        std::vector<std::string> get_column_types();
    };


    class DBWriter
    {
            sqlite3 *_db;
            std::string _filename;

        public:
            DBWriter(std::string filename);
            ~DBWriter() {};

            bool open();
            bool close();

            bool exec(std::string query);
            bool insert(DBObject *obj);
            bool create_table(DBObject *obj);
    };    
}

#endif // __DB_H__