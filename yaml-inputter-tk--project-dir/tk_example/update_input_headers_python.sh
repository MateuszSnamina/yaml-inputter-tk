#!/bin/bash

script_dir=`dirname $0`
cd "${script_dir}"
script_dir=`pwd`
project_root_dir=`cd ..; pwd`

echo "script_dir       : ${script_dir}"
echo "project_root_dir : ${project_root_dir}"

#code_generator="${project_root_dir}/external_packages/yaml_inputter_code_generator_python3/yaml_inputter_code_generator.py"
code_generator="${project_root_dir}/yaml_inputter_code_generator_python3/yaml_inputter_code_generator.py"
PYTHONPATH="${project_root_dir}/external_packages/lib"

python3 "$code_generator" 'input_data_specification2.yaml' \
        -i "<vector>" "<length.hpp>" -c 'include/input_data.hpp' \
        -j '<input_data_yaml_conversions.hpp>' -f 'include/input_data_fill_functions.hpp'



