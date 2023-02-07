#define CATCH_CONFIG_MAIN

#include <cstdio>
#include  "catch.hpp"
#include "db.h"


TEST_CASE( "insert into db", "[database]" ) {

    std::string filename = "/var/tmp/foo.db";
    std::remove(filename.c_str());
    twip::DBWriter db(filename);
    twip::PoseDBObject obj1(1,2,3,4,5,6,7);     
    twip::PIDParamDBObject obj2(1,2,3,4);     

    REQUIRE( db.open() );
    REQUIRE( db.create_table(&obj1) );
    REQUIRE( db.insert(&obj1) );
    REQUIRE( db.create_table(&obj2) );
    REQUIRE( db.insert(&obj2) );
    REQUIRE( db.close() );
}