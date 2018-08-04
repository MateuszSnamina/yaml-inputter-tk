/* Header file generated automatically by yaml-inputter-tk-code-generator.
 * The header content is based on the provided input-data-specification file.
 * File generation date: Sat Aug 19 19:44:34 2017
 * WARNING: Do not modify this file!
 * (Every change will be overridden during the next compilation.)
 */

#ifndef INPUT_DATA_HPP
#define INPUT_DATA_HPP

#include<vector> // user request header
#include<length.hpp> // user request header

struct InputData {
    enum Theory {
        SINGLE_POINT,
        OPTIMIZATION
    };
    struct Segment {
        struct Point {
            Length x; // fill-strategy: required-scalar, yaml-key: "x"
            Length y; // fill-strategy: required-scalar, yaml-key: "y"
        };
        Point pA; // fill-strategy: delegated, yaml-key: "pA"
        Point pB; // fill-strategy: delegated, yaml-key: "pB"
    };
    double E{5.7}; // fill-strategy: required-scalar, yaml-key: "energy"
    Theory theory{OPTIMIZATION}; // fill-strategy: optional-scalar, yaml-key: "theory"
    std::vector<Segment> rs; // required-sequence of std::vector<Segment>::value_type rs[index]; // fill-strategy: delegated, yaml-key: "segments"->index
    std::vector<Segment> os; // optional-sequence of std::vector<Segment>::value_type os[index]; // fill-strategy: delegated, yaml-key: "optional-segments"->index
    std::vector<int> fi; // fixed-size-sequence (size=3) of std::vector<int>::value_type fi[index]; // fill-strategy: required-scalar, yaml-key: "fixed-ints"->index
};

#endif // end of #ifndef INPUT_DATA_HPP
