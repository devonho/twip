#include "db.h"

namespace twip
{

PIDParamDBObject::PIDParamDBObject()
{
    Kp = 0.0;
    Ki = 0.0;
    Kd = 0.0;
    timestamp = 0;
    name = "PIDParam";
}

PIDParamDBObject::PIDParamDBObject(float Kp, float Ki, float Kd, long unsigned int timestamp)
{
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->timestamp = timestamp;
    name = "PIDParam";
}

std::vector<std::string> PIDParamDBObject::get_columns()
{
    std::vector<std::string> vec;
    vec.push_back("Kp");
    vec.push_back("Ki");
    vec.push_back("Kd");
    vec.push_back("timestamp");
    return vec;
}

std::vector<std::string> PIDParamDBObject::get_values()
{
    std::vector<std::string> vec;
    vec.push_back(std::to_string(Kp));
    vec.push_back(std::to_string(Ki));
    vec.push_back(std::to_string(Kd));
    vec.push_back(std::to_string(timestamp));
    return vec;
}

std::vector<std::string> PIDParamDBObject::get_column_types()
{
    std::vector<std::string> vec;
    vec.push_back("dec");
    vec.push_back("dec");
    vec.push_back("dec");
    vec.push_back("bigint");
    return vec;
}


PoseDBObject::PoseDBObject()
{
    orientx = 0.0;
    orienty = 0.0;
    orientz = 0.0;
    posx = 0.0;
    posy = 0.0;
    posz = 0.0;
    timestamp = 0;
    name = "Pose";
}

PoseDBObject::PoseDBObject(float orientx, float orienty, float orientz, float posx, float posy, float posz, long unsigned int timestamp)
{
    this->orientx = orientx;
    this->orienty = orienty;
    this->orientz = orientz;
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;
    this->timestamp = timestamp;
    name = "Pose";
}

std::vector<std::string> PoseDBObject::get_columns()
{
    std::vector<std::string> vec;
    vec.push_back("orientx");
    vec.push_back("orienty");
    vec.push_back("orientz");
    vec.push_back("posx");
    vec.push_back("posy");
    vec.push_back("posz");
    vec.push_back("timestamp");
    return vec;
}

std::vector<std::string> PoseDBObject::get_values()
{
    std::vector<std::string> vec;
    vec.push_back(std::to_string(orientx));
    vec.push_back(std::to_string(orienty));
    vec.push_back(std::to_string(orientz));
    vec.push_back(std::to_string(posx));
    vec.push_back(std::to_string(posy));
    vec.push_back(std::to_string(posz));
    vec.push_back(std::to_string(timestamp));
    return vec;
}

std::vector<std::string> PoseDBObject::get_column_types()
{
    std::vector<std::string> vec;
    vec.push_back("dec");
    vec.push_back("dec");
    vec.push_back("dec");
    vec.push_back("dec");
    vec.push_back("dec");
    vec.push_back("dec");
    vec.push_back("bigint");
    return vec;
}


}

