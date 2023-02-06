#include  "catch.hpp"

#include "queue.h"
#include "db.h"
#include <gz/msgs.hh>

TEST_CASE( "push into queue", "[queue]" ) {
    gz::msgs::Pose obj;
    gz::msgs::Pose out;
    twip::Queue q;

    q.push(obj);
    q.push(obj);
    REQUIRE( q.pop_wait(out) );
    REQUIRE( q.pop_wait(out) );
    REQUIRE( q.pop_wait(out) == false );

}