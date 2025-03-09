############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project rinos
set_top chensy
add_files rinos/chen.cpp
add_files rinos/chen.h
add_files -tb rinos/test_chen.cpp
open_solution "solution1" -flow_target vivado
set_part {xc7a100tcsg324-1}
create_clock -period 10 -name default
config_export -output C:/Windows/vitiS/rinos/solution1
#source "./rinos/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -output C:/Windows/vitiS/rinos/solution1
