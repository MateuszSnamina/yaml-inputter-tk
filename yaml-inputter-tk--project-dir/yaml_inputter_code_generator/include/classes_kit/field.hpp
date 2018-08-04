#ifndef CLASSES_KIT__FIELD_HPP
#define CLASSES_KIT__FIELD_HPP

#include<string>
#include<vector>

// *****************************************************************************
// ***************  Field - abstract base class  *******************************
// *****************************************************************************

class Field {
public:
    Field(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init);
    virtual std::string leaflet() const;
    virtual std::string definition() const;
    virtual std::vector<std::string> fill() const;
    virtual ~Field() = 0;
public:
    const std::string cpp_type;
    const std::string cpp_name;
    const std::string cpp_init;
};

class FieldWithKeys : public Field {
public:
    FieldWithKeys(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init,
            const std::vector<std::string>& input_keys);
    const std::vector<std::string> input_keys;
    virtual ~FieldWithKeys() = 0;

};

class FillerFilledField : public FieldWithKeys {
public:
    FillerFilledField(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init,
            const std::vector<std::string>& input_keys);
    std::string leaflet() const override;
    std::string definition() const override;
    std::vector<std::string> fill() const override;
    virtual std::string fill_strategy_name() const = 0;
    virtual std::string proxy_object_method_name() const = 0;
    virtual ~FillerFilledField() = default;
};

template <class T> // T = FillerFilledRequiredField, ...
class SequenceWrapper : public FieldWithKeys {
public:
    SequenceWrapper(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init,
            const std::vector<std::string>& input_keys);
    std::string leaflet() const override;
    std::string definition() const override;
    std::vector<std::string> fill() const override;
    virtual std::string container_type_name() const = 0;
    virtual std::string get_size_cpp_code() const = 0;  
    virtual ~SequenceWrapper() = default;
private:
    const T sequence_element;    
};

// *****************************************************************************
// ***************  Field - concrete subclasses  *******************************
// *****************************************************************************

class NoFillField : public Field {
public:
    NoFillField(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init);

    std::string leaflet() const override;
    std::string definition() const override;
};

// *****************************************************************************

class FillerFilledRequiredField : public FillerFilledField {
public:
    FillerFilledRequiredField(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init,
            const std::vector<std::string>& input_keys);
    virtual std::string fill_strategy_name() const override;
    virtual std::string proxy_object_method_name() const override;
};


// *****************************************************************************

class FillerFilledRequiredScalarField : public FillerFilledField {
public:
    FillerFilledRequiredScalarField(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init,
            const std::vector<std::string>& input_keys);
    virtual std::string fill_strategy_name() const override;
    virtual std::string proxy_object_method_name() const override;
};

// *****************************************************************************

class FillerFilledOptionalField : public FillerFilledField {
public:
    FillerFilledOptionalField(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init,
            const std::vector<std::string>& input_keys);
    virtual std::string fill_strategy_name() const override;
    virtual std::string proxy_object_method_name() const override;
};

// *****************************************************************************

class FillerFilledOptionalScalarField : public FillerFilledField {
public:
    FillerFilledOptionalScalarField(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init,
            const std::vector<std::string>& input_keys);
    virtual std::string fill_strategy_name() const override;
    virtual std::string proxy_object_method_name() const override;
};

// *****************************************************************************

class DelegatedField : public FieldWithKeys {
public:
    DelegatedField(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init,
            const std::vector<std::string>& input_keys);

    std::string leaflet() const override;
    std::string definition() const override;
    std::vector<std::string> fill() const override;
};

// *****************************************************************************

template <class T>
class RequiredSequence : public SequenceWrapper<T> {
public:
    RequiredSequence(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init,
            const std::vector<std::string>& input_keys);
    virtual std::string container_type_name() const override;
    virtual std::string get_size_cpp_code() const override;  
};

// *****************************************************************************

template <class T>
class OptionalSequence : public SequenceWrapper<T> {
public:
    OptionalSequence(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init,
            const std::vector<std::string>& input_keys);
    virtual std::string container_type_name() const override;
    virtual std::string get_size_cpp_code() const override;  
};

// *****************************************************************************

template <class T>
class FixedSizeSequence : public SequenceWrapper<T> {
public:
    FixedSizeSequence(
            const std::string& cpp_type,
            const std::string& cpp_name,
            const std::string& cpp_init,
            const std::vector<std::string>& input_keys,
            std::size_t sequence_size);
    virtual std::string container_type_name() const override;
    virtual std::string get_size_cpp_code() const override;  
private:
    const std::size_t sequence_size;
};

// *****************************************************************************

#endif