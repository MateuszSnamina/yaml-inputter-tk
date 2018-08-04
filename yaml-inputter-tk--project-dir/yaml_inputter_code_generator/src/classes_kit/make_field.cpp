#include<algorithm>
#include<cctype>
#include<classes_kit/make_field.hpp>
#include<classes_kit/fill_strategy_yaml_converter.hpp>
#include<classes_kit/container_type_yaml_converter.hpp>
#include<classes_kit/check_stray_fields.hpp>

void key_quotation(std::string& s) {
    bool is_integral = std::all_of(s.begin(), s.end(),
            [](char c) {
                return std::isdigit(c);
            });
    if (s == "") is_integral = false;
    if (!is_integral) s = "\"" + s + "\"";
}

std::shared_ptr<Field> make_field(const YAML::Node & node) {
    if (!node.IsMap()) {
        std::string error1 = "[ERROR] [NodeTypeError]";
        std::string error2 = "Yaml::node defining the class field is not a map-yaml-node.";
        throw std::runtime_error(error1 + " " + error2);
    }
    // *************************************************************************    
    const std::set<std::string> valid_fields = {
        "cpp-name", "cpp-type", "cpp-init",
        "fill-strategy", "input-key",
        "container", "sequence-size"
    };
    check_stray_fields(valid_fields, node);
    // *************************************************************************    
    const YAML::Node cpp_name_node = node["cpp-name"];
    if (!cpp_name_node.IsDefined()) {
        std::string error1 = "[ERROR] [KeyError]";
        std::string error2 = "'cpp-name' sub-node is not defined.";
        throw std::runtime_error(error1 + " " + error2);
    }
    if (!cpp_name_node.IsScalar()) {
        std::string error1 = "[ERROR] [NodeTypeError]";
        std::string error2 = "'cpp-name' sub-node is not a scalar-yaml-node.";
        throw std::runtime_error(error1 + " " + error2);
    }
    const std::string cpp_name = cpp_name_node.as<std::string>();
    // *************************************************************************
    const YAML::Node cpp_type_node = node["cpp-type"];
    if (!cpp_type_node.IsDefined()) {
        std::string error1 = "[ERROR] [KeyError]";
        std::string error2 = "'cpp-type' sub-node is not defined.";
        throw std::runtime_error(error1 + " " + error2);
    }
    if (!cpp_type_node.IsScalar()) {
        std::string error1 = "[ERROR] [NodeTypeError]";
        std::string error2 = "'cpp-type' sub-node is not a scalar-yaml-node.";
        throw std::runtime_error(error1 + " " + error2);
    }
    const std::string cpp_type = cpp_type_node.as<std::string>();
    // *************************************************************************
    const YAML::Node cpp_init_node = node["cpp-init"];
    if (cpp_init_node.IsDefined() && !cpp_init_node.IsScalar()) {
        std::string error1 = "[ERROR] [NodeTypeError]";
        std::string error2 = "'cpp-init' sub-node is not a scalar-yaml-node.";
        throw std::runtime_error(error1 + " " + error2);
    }
    const std::string cpp_init =
            cpp_init_node.IsDefined() ?
            cpp_init_node.as<std::string>() :
            "";
    // *************************************************************************
    const YAML::Node fill_strategy_node = node["fill-strategy"];
    if (fill_strategy_node.IsDefined() && !fill_strategy_node.IsScalar()) {
        std::string error1 = "[ERROR] [NodeTypeError]";
        std::string error2 = "'fill-strategy' sub-node is not a scalar-yaml-node.";
        throw std::runtime_error(error1 + " " + error2);
    }
    FillStrategy fill_strategy;
    try {
        fill_strategy = fill_strategy_node.IsDefined() ?
                fill_strategy_node.as<FillStrategy>() :
                FillStrategy::None;
    } catch (YAML::BadConversion) {
        std::string error1 = "[ERROR] [ConversionError]";
        std::string error2 = "'fill-strategy' sub-node conversion error.";
        throw std::runtime_error(error1 + " " + error2);
    }
    // *************************************************************************
    if (fill_strategy == FillStrategy::None) {
        const std::set<std::string> valid_fields = {"cpp-name", "cpp-type", "cpp-init", "fill-strategy"};
        check_stray_fields(valid_fields, node);
        return std::make_shared<NoFillField>(cpp_type, cpp_name, cpp_init);
    }
    // *************************************************************************
    const YAML::Node input_key_node = node["input-key"];
    if (!input_key_node.IsDefined() && !fill_strategy_node.IsScalar() && !fill_strategy_node.IsSequence()) {
        std::string error1 = "[ERROR] [NodeTypeError]";
        std::string error2 = "'input-key' sub-node is neither a scalar-yaml-node nor a sequence-yaml-node.";
        throw std::runtime_error(error1 + " " + error2);
    }
    std::vector<std::string> input_keys;
    if (!input_key_node.IsDefined()) {
        input_keys.push_back(cpp_name);
    }
    if (input_key_node.IsScalar()) {
        input_keys.push_back(input_key_node.as<std::string>());
    }
    if (input_key_node.IsSequence()) {
        for (unsigned i = 0; i < input_key_node.size(); i++) {
            const YAML::Node temp_node = input_key_node[i];
            if (!temp_node.IsScalar()) {
                std::string error1 = "[ERROR] [NodeTypeError]";
                std::string error2 = "on of the sub-nodes in 'input-key' is not a scalar-yaml-node.";
                throw std::runtime_error(error1 + " " + error2);
            }
            input_keys.push_back(temp_node.as<std::string>());
        }
    }
    for (std::string & s : input_keys)
        key_quotation(s);
    // *************************************************************************
    const YAML::Node container_node = node["container"];
    if (container_node.IsDefined() && !container_node.IsScalar()) {
        std::string error1 = "[ERROR] [NodeTypeError]";
        std::string error2 = "'container' sub-node is not a scalar-yaml-node.";
        throw std::runtime_error(error1 + " " + error2);
    }
    ContainerType container_type;
    try {
        container_type =
                container_node.IsDefined() ?
                container_node.as<ContainerType>() :
                ContainerType::None;
    } catch (YAML::BadConversion) {
        std::string error1 = "[ERROR] [ConversionError]";
        std::string error2 = "'container' sub-node conversion error.";
        throw std::runtime_error(error1 + " " + error2);
    }
    // *************************************************************************    
    if (container_type == ContainerType::None) {
        if (fill_strategy == FillStrategy::Required)
            return std::make_shared<FillerFilledRequiredField>(cpp_type, cpp_name, cpp_init, input_keys);
        if (fill_strategy == FillStrategy::RequiredScalar)
            return std::make_shared<FillerFilledRequiredScalarField>(cpp_type, cpp_name, cpp_init, input_keys);
        if (fill_strategy == FillStrategy::Optional)
            return std::make_shared<FillerFilledOptionalField>(cpp_type, cpp_name, cpp_init, input_keys);
        if (fill_strategy == FillStrategy::OptionalScalar)
            return std::make_shared<FillerFilledOptionalScalarField>(cpp_type, cpp_name, cpp_init, input_keys);
        if (fill_strategy == FillStrategy::Delegated)
            return std::make_shared<DelegatedField>(cpp_type, cpp_name, cpp_init, input_keys);
    }
    // with container_type == ContainerType::RequiredSequence:
    if (container_type == ContainerType::RequiredSequence) {
        if (fill_strategy == FillStrategy::Required)
            return std::make_shared<RequiredSequence < FillerFilledRequiredField > > (cpp_type, cpp_name, cpp_init, input_keys);
        if (fill_strategy == FillStrategy::RequiredScalar)
            return std::make_shared<RequiredSequence < FillerFilledRequiredScalarField > > (cpp_type, cpp_name, cpp_init, input_keys);
        if (fill_strategy == FillStrategy::Optional)
            return std::make_shared<RequiredSequence < FillerFilledOptionalField > > (cpp_type, cpp_name, cpp_init, input_keys);
        if (fill_strategy == FillStrategy::OptionalScalar)
            return std::make_shared<RequiredSequence < FillerFilledOptionalScalarField > > (cpp_type, cpp_name, cpp_init, input_keys);
        if (fill_strategy == FillStrategy::Delegated)
            return std::make_shared<RequiredSequence < DelegatedField> >(cpp_type, cpp_name, cpp_init, input_keys);
    }
    // with container_type == ContainerType::OptionalSequence:
    if (container_type == ContainerType::OptionalSequence) {
        if (fill_strategy == FillStrategy::Required)
            return std::make_shared<OptionalSequence < FillerFilledRequiredField > > (cpp_type, cpp_name, cpp_init, input_keys);
        if (fill_strategy == FillStrategy::RequiredScalar)
            return std::make_shared<OptionalSequence < FillerFilledRequiredScalarField > > (cpp_type, cpp_name, cpp_init, input_keys);
        if (fill_strategy == FillStrategy::Optional)
            return std::make_shared<OptionalSequence < FillerFilledOptionalField > > (cpp_type, cpp_name, cpp_init, input_keys);
        if (fill_strategy == FillStrategy::OptionalScalar)
            return std::make_shared<OptionalSequence < FillerFilledOptionalScalarField > > (cpp_type, cpp_name, cpp_init, input_keys);
        if (fill_strategy == FillStrategy::Delegated)
            return std::make_shared<OptionalSequence < DelegatedField> >(cpp_type, cpp_name, cpp_init, input_keys);
    }
    // *************************************************************************    
    const YAML::Node sequence_size_node = node["sequence-size"];
    if (!sequence_size_node.IsDefined()) {
        std::string error1 = "[ERROR] [KeyError]";
        std::string error2 = "'sequence-size' sub-node is not defined.";
        throw std::runtime_error(error1 + " " + error2);
    }
    if (!sequence_size_node.IsScalar()) {
        std::string error1 = "[ERROR] [NodeTypeError]";
        std::string error2 = "'sequence-size' sub-node is not a scalar-yaml-node.";
        throw std::runtime_error(error1 + " " + error2);
    }
    std::size_t sequence_size;
    try {
        sequence_size = sequence_size_node.as<std::size_t>();
    } catch (YAML::BadConversion) {
        std::string error1 = "[ERROR] [ConversionError]";
        std::string error2 = "'sequence-size' sub-node conversion error.";
        throw std::runtime_error(error1 + " " + error2);
    }
    // *************************************************************************    
    // with container_type == ContainerType::OptionalSequence:
    if (container_type == ContainerType::FixedSizeSequence) {
        if (fill_strategy == FillStrategy::Required)
            return std::make_shared<FixedSizeSequence < FillerFilledRequiredField > > (cpp_type, cpp_name, cpp_init, input_keys, sequence_size);
        if (fill_strategy == FillStrategy::RequiredScalar)
            return std::make_shared<FixedSizeSequence < FillerFilledRequiredScalarField > > (cpp_type, cpp_name, cpp_init, input_keys, sequence_size);
        if (fill_strategy == FillStrategy::Optional)
            return std::make_shared<FixedSizeSequence < FillerFilledOptionalField > > (cpp_type, cpp_name, cpp_init, input_keys, sequence_size);
        if (fill_strategy == FillStrategy::OptionalScalar)
            return std::make_shared<FixedSizeSequence < FillerFilledOptionalScalarField > > (cpp_type, cpp_name, cpp_init, input_keys, sequence_size);
        if (fill_strategy == FillStrategy::Delegated)
            return std::make_shared<FixedSizeSequence < DelegatedField> >(cpp_type, cpp_name, cpp_init, input_keys, sequence_size);
    }
    throw std::logic_error("Internal error while making field instance from yaml-node.");
}