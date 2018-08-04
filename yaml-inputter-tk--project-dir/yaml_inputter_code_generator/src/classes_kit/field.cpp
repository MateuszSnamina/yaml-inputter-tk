#include<classes_kit/field.hpp>
#include<join.hpp>
#include<writer_kit/writer.hpp>
#include<ansi_escape_code.hpp>
#include<concatenate_vectors.hpp>

// *****************************************************************************
// ***************  Field - abstract base class  *******************************
// *****************************************************************************

Field::Field(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init) :
cpp_type(cpp_type),
cpp_name(cpp_name),
cpp_init(cpp_init) {
}

Field::~Field() = default;

std::string Field::leaflet() const {
    std::string str;
    str += utility::BgColorCyan + cpp_type + utility::Reset;
    str += utility::BgColorCyan + " " + utility::Reset;
    str += utility::BgColorCyan + utility::Bold + cpp_name + utility::Reset;
    str += utility::BgColorCyan + cpp_init + utility::Reset;
    str += utility::BgColorCyan + "; " + utility::Reset;
    return str;
}

std::string Field::definition() const {
    return cpp_type + " " + cpp_name + cpp_init + ";";
}

std::vector<std::string> Field::fill() const {
    std::vector<std::string> result;
    return result;
}

// *****************************************************************************

FieldWithKeys::FieldWithKeys(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init,
        const std::vector<std::string>& input_keys) :
Field(cpp_type, cpp_name, cpp_init),
input_keys(input_keys) {
}

FieldWithKeys::~FieldWithKeys() = default;

// *****************************************************************************

FillerFilledField::FillerFilledField(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init,
        const std::vector<std::string>& input_keys) :
FieldWithKeys(cpp_type, cpp_name, cpp_init, input_keys) {
}

std::string FillerFilledField::leaflet() const {
    std::string str = Field::leaflet();
    str += utility::BgColorBlue + "**" + fill_strategy_name() + "**" + utility::Reset;
    str += utility::BgColorBlue + " " + utility::Reset;
    str += utility::BgColorBlue + "yaml-key: " + utility::Reset;
    str += utility::BgColorBlue + utility::Bold + utility::Italic + join(input_keys, "->") + utility::Reset;
    return str;
}

std::string FillerFilledField::definition() const {
    std::string str = Field::definition();
    str += " // ";
    str += "fill-strategy: " + fill_strategy_name();
    str += ", ";
    str += "yaml-key: " + join(input_keys, "->");
    return str;
}

std::vector<std::string> FillerFilledField::fill() const {
    std::string str;
    str += "filler";
    str += ".target";
    str += "(instance." + cpp_name + ")";
    str += "." + proxy_object_method_name();
    str += "(std::forward<Ts>(keys)..., " + join(input_keys, ", ") + ")";
    str += ";";
    return {str};
}

// *****************************************************************************

template <class T>
SequenceWrapper<T>::SequenceWrapper(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init,
        const std::vector<std::string>& input_keys) :
FieldWithKeys(cpp_type, cpp_name, cpp_init, input_keys),
sequence_element(cpp_type + "::value_type", cpp_name + "[index]", "", concatenate_vectors(input_keys,{"index"})) {
}

template <class T>
std::string SequenceWrapper<T>::leaflet() const {
    std::string str = Field::leaflet();
    str += utility::BgColorGreen + " " + utility::Reset;
    str += utility::BgColorGreen + container_type_name() + utility::Reset;
    str += utility::BgColorGreen + " of " + utility::Reset;
    str += sequence_element.leaflet();
    return str;
}

template <class T>
std::string SequenceWrapper<T>::definition() const {
    std::string str = Field::definition();
    str += " // ";
    str += container_type_name();
    str += " of ";
    str += sequence_element.definition();
    return str;
}

template <class T>
std::vector<std::string> SequenceWrapper<T>::fill() const {
    std::vector<std::string> result;

    VectorWriter writer(result);
    {
        std::string str = "{"; // code-block open brace
        writer.write_line(str);
    }
    writer.push_back_indent();
    {
        std::string str = "std::size_t size = ";
        str += get_size_cpp_code();
        str += ";";
        writer.write_line(str);
    }
    {
        std::string str = "instance." + cpp_name + ".resize(size);";
        writer.write_line(str);
    }
    {
        std::string str = "for(std::size_t index = 0; index < size; index++) {";
        writer.write_line(str);
    }
    writer.push_back_indent();
    {
        writer.write_lines(sequence_element.fill());
    }
    writer.pop_indent();
    {
        std::string str = "}"; // loop close brace
        writer.write_line(str);
    }
    writer.pop_indent();
    {
        std::string str = "}"; // code-block close brace
        writer.write_line(str);
    }
    return result;
}

// *****************************************************************************
// ***************  Field - concrete subclasses  *******************************
// *****************************************************************************

NoFillField::NoFillField(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init) :
Field(cpp_type, cpp_name, cpp_init) {
}

std::string NoFillField::leaflet() const {
    std::string str = Field::leaflet();
    str += " // fill-strategy: none";
    return str;
}

std::string NoFillField::definition() const {
    std::string str = Field::definition();
    str += " // fill-strategy: none";
    return str;
}

// *****************************************************************************

FillerFilledRequiredField::FillerFilledRequiredField(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init,
        const std::vector<std::string>& input_keys) :
FillerFilledField(cpp_type, cpp_name, cpp_init, input_keys) {
}

std::string FillerFilledRequiredField::fill_strategy_name() const {
    return "required";
}

std::string FillerFilledRequiredField::proxy_object_method_name() const {
    return "fill_required";
}

// *****************************************************************************

FillerFilledRequiredScalarField::FillerFilledRequiredScalarField(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init,
        const std::vector<std::string>& input_keys) :
FillerFilledField(cpp_type, cpp_name, cpp_init, input_keys) {
}

std::string FillerFilledRequiredScalarField::fill_strategy_name() const {
    return "required-scalar";
}

std::string FillerFilledRequiredScalarField::proxy_object_method_name() const {
    return "fill_required_scalar";
}

// *****************************************************************************

FillerFilledOptionalField::FillerFilledOptionalField(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init,
        const std::vector<std::string>& input_keys) :
FillerFilledField(cpp_type, cpp_name, cpp_init, input_keys) {
}

std::string FillerFilledOptionalField::fill_strategy_name() const {
    return "optional";
}

std::string FillerFilledOptionalField::proxy_object_method_name() const {
    return "fill_optional";
}

// *****************************************************************************

FillerFilledOptionalScalarField::FillerFilledOptionalScalarField(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init,
        const std::vector<std::string>& input_keys) :
FillerFilledField(cpp_type, cpp_name, cpp_init, input_keys) {
}

std::string FillerFilledOptionalScalarField::fill_strategy_name() const {
    return "optional-scalar";
}

std::string FillerFilledOptionalScalarField::proxy_object_method_name() const {
    return "fill_optional_scalar";
}

// *****************************************************************************

DelegatedField::DelegatedField(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init,
        const std::vector<std::string>& input_keys) :
FieldWithKeys(cpp_type, cpp_name, cpp_init, input_keys) {
}

std::string DelegatedField::leaflet() const {
    std::string str = Field::leaflet();
    str += utility::BgColorBlue + "**delegated**" + utility::Reset;
    str += utility::BgColorBlue + " " + utility::Reset;
    str += utility::BgColorBlue + "yaml-key: " + utility::Reset;
    str += utility::BgColorBlue + utility::Bold + utility::Italic + join(input_keys, "->") + utility::Reset;
    return str;
}

std::string DelegatedField::definition() const {
    std::string str = Field::definition();
    str += " // ";
    str += "fill-strategy: delegated";
    str += ", ";
    str += "yaml-key: " + join(input_keys, "->");
    return str;
}

std::vector<std::string> DelegatedField::fill() const {
    std::string str;
    str += "fill";
    str += "(";
    str += "instance." + cpp_name;
    str += ", ";
    str += "filler";
    str += ", ";
    str += "std::forward<Ts>(keys)..., " + join(input_keys, ", ");
    str += ")";
    str += ";";
    return {str};
}

// *****************************************************************************

template <class T>
RequiredSequence<T>::RequiredSequence(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init,
        const std::vector<std::string>& input_keys) :
SequenceWrapper<T>(cpp_type, cpp_name, cpp_init, input_keys) {
}

template<class T>
std::string RequiredSequence<T>::container_type_name() const {
    return "required-sequence";
}

template<class T>
std::string RequiredSequence<T>::get_size_cpp_code() const {
    return "filler.required_sequence_size(" + join(this->input_keys, ", ") + ")";
}

template class RequiredSequence<FillerFilledRequiredField>;
template class RequiredSequence<FillerFilledOptionalField>;
template class RequiredSequence<FillerFilledRequiredScalarField>;
template class RequiredSequence<FillerFilledOptionalScalarField>;
template class RequiredSequence<DelegatedField>;

// *****************************************************************************

template <class T>
OptionalSequence<T>::OptionalSequence(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init,
        const std::vector<std::string>& input_keys) :
SequenceWrapper<T>(cpp_type, cpp_name, cpp_init, input_keys) {
}

template<class T>
std::string OptionalSequence<T>::container_type_name() const {
    return "optional-sequence";
}

template<class T>
std::string OptionalSequence<T>::get_size_cpp_code() const {
    return "filler.optional_sequence_size(" + join(this->input_keys, ", ") + ")";
}

template class OptionalSequence<FillerFilledRequiredField>;
template class OptionalSequence<FillerFilledOptionalField>;
template class OptionalSequence<FillerFilledRequiredScalarField>;
template class OptionalSequence<FillerFilledOptionalScalarField>;
template class OptionalSequence<DelegatedField>;

// *****************************************************************************

template <class T>
FixedSizeSequence<T>::FixedSizeSequence(
        const std::string& cpp_type,
        const std::string& cpp_name,
        const std::string& cpp_init,
        const std::vector<std::string>& input_keys,
        std::size_t sequence_size) :
SequenceWrapper<T>(cpp_type, cpp_name, cpp_init, input_keys),
sequence_size(sequence_size) {
}

template<class T>
std::string FixedSizeSequence<T>::container_type_name() const {
    return "fixed-size-sequence (size=" + std::to_string(sequence_size) + ")";
}

template<class T>
std::string FixedSizeSequence<T>::get_size_cpp_code() const {
    return std::to_string(sequence_size);
}

template class FixedSizeSequence<FillerFilledRequiredField>;
template class FixedSizeSequence<FillerFilledOptionalField>;
template class FixedSizeSequence<FillerFilledRequiredScalarField>;
template class FixedSizeSequence<FillerFilledOptionalScalarField>;
template class FixedSizeSequence<DelegatedField>;

// *****************************************************************************