#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../include/model.h"

SCENARIO( "model can constructs", "[model]" ) {

    GIVEN( "A model with no vertexes" ) {
        Model m;
        REQUIRE( m.sizeVert() == 0 );
        REQUIRE( m.sizeFace() == 0 );
    }
}

SCENARIO( "model class can read info from obj file", "[model, obj]" ) {

    GIVEN("the model") {
        Model m;
        float epsilon = static_cast<float>(1e-9);
        WHEN("we read the file with 20 vertexes and 18 faces") {
            try {
                m.readModel("test_file_head.obj");
            } catch (std::exception &ex) {
                std::cout << "Ouch! That hurts, because: "
                    << ex.what() << "!\n";
            }
            THEN("the m_vertexes contain 20 vertexes") {
                REQUIRE(m.sizeVert() == 20);
            }
            THEN("comparison first vertex coordinates") {
                Point3D p = m.getVertex(0);
                float x = -0.000581696f;
                float y = -0.734665f;
                float z = -0.623267f;
                REQUIRE(p.x - x < epsilon );
                REQUIRE(p.y - y < epsilon );
                REQUIRE(p.z - z < epsilon );
            }
            THEN("faces vector has 18 elements") {
                REQUIRE(m.sizeFace() == 18);
            }
        }
    }
}
