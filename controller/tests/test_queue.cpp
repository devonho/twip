#include  "catch.hpp"

#include "queue.h"
#include "db.h"
#include <gz/msgs.hh>
#include "GzHelper.h"

TEST_CASE( "push into queue", "[queue]" ) {
    gz::msgs::Pose obj;
    gz::msgs::Pose out;
    twip::Queue<gz::msgs::Pose> q;

    q.push(obj);
    q.push(obj);
    REQUIRE( q.pop_wait(out) );
    REQUIRE( q.pop_wait(out) );
    REQUIRE( q.pop_wait(out) == false );

}

TEST_CASE( "push key into queue", "[queue]" ) {
    gz::msgs::Int32 obj;
    gz::msgs::Int32 out;
    twip::Queue<gz::msgs::Int32> q;
    obj.set_data((long int)twip::GzKey::LEFT_ARROW);

    q.push(obj);
    REQUIRE( q.pop_wait(out) );
    REQUIRE( out.data() == twip::GzKey::LEFT_ARROW );

}