#!/bin/bash

function create_directory {
  [ -d "$1" ] || mkdir "$1"
}

my_dir=`dirname $0`
echo "my_dir : ${my_dir}"
echo ""
cd "${my_dir}"

create_directory outputs

for inp in inputs_examples/*.yaml; do
  echo "inp    : ${inp}"
  baseinp=`basename "${inp}"`
  out="outputs/${baseinp}.out"
  outerr="outputs/${baseinp}.outerr"
  echo "out    : ${out}"
  echo "outerr : ${outerr}"
  "./run_filler_api_example1" "${inp}">"${out}" 2>"${outerr}"
  echo ""
done

