/* Header file generated automatically by yaml-inputter-tk-code-generator.
 * The header content is based on the provided input-data-specification file.
 * File generation date: Sat Aug 19 19:44:34 2017
 * WARNING: Do not modify this file!
 * (Every change will be overridden during the next compilation.)
 */

#ifndef INPUT_DATA_FILL_FUNCTIONS_HPP
#define INPUT_DATA_FILL_FUNCTIONS_HPP

#include<set> // set used in check-stray-fields block
#include<yaml_inputter/templated_filler.hpp>
#include<input_data_yaml_conversions.hpp> // user request header

template<class... Ts>
void fill(InputData::Segment::Point& instance, const yaml_inputter::Filler & filler, Ts&&... keys) {
    filler.target(instance.x).fill_required_scalar(std::forward<Ts>(keys)..., "x");
    filler.target(instance.y).fill_required_scalar(std::forward<Ts>(keys)..., "y");
    {  // check-stray-fields block
        std::set<std::string> correct_fields = {"x", "y"};
        filler.check_stray_fields(correct_fields, std::forward<Ts>(keys)...);
    } // end of check-stray-fields block
} // end of fill function

template<class... Ts>
void fill(InputData::Segment& instance, const yaml_inputter::Filler & filler, Ts&&... keys) {
    fill(instance.pA, filler, std::forward<Ts>(keys)..., "pA");
    fill(instance.pB, filler, std::forward<Ts>(keys)..., "pB");
    {  // check-stray-fields block
        std::set<std::string> correct_fields = {"pA", "pB"};
        filler.check_stray_fields(correct_fields, std::forward<Ts>(keys)...);
    } // end of check-stray-fields block
} // end of fill function

template<class... Ts>
void fill(InputData& instance, const yaml_inputter::Filler & filler, Ts&&... keys) {
    filler.target(instance.E).fill_required_scalar(std::forward<Ts>(keys)..., "energy");
    filler.target(instance.theory).fill_optional_scalar(std::forward<Ts>(keys)..., "theory");
    {
        std::size_t size = filler.required_sequence_size("segments");
        instance.rs.resize(size);
        for(std::size_t index = 0; index < size; index++) {
            fill(instance.rs[index], filler, std::forward<Ts>(keys)..., "segments", index);
        }
    }
    {
        std::size_t size = filler.optional_sequence_size("optional-segments");
        instance.os.resize(size);
        for(std::size_t index = 0; index < size; index++) {
            fill(instance.os[index], filler, std::forward<Ts>(keys)..., "optional-segments", index);
        }
    }
    {
        std::size_t size = 3;
        instance.fi.resize(size);
        for(std::size_t index = 0; index < size; index++) {
            filler.target(instance.fi[index]).fill_required_scalar(std::forward<Ts>(keys)..., "fixed-ints", index);
        }
    }
    {  // check-stray-fields block
        std::set<std::string> correct_fields = {"energy", "theory", "segments", "optional-segments", "fixed-ints"};
        filler.check_stray_fields(correct_fields, std::forward<Ts>(keys)...);
    } // end of check-stray-fields block
} // end of fill function

#endif // end of #ifndef INPUT_DATA_FILL_FUNCTIONS_HPP
