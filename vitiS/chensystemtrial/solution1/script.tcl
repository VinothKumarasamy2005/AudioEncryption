############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project chensystemtrial
add_files ../../Users/Mohamed Rinos/Documents/chen_hyperchaos.cpp
add_files chensystemtrial/chen_hyperchaos.h
add_files -tb ../../Users/Mohamed Rinos/Documents/test_chen.cpp
open_solution "solution1" -flow_target vivado
set_part {xc7a100tcsg324-1}
create_clock -period 10 -name default
#source "./chensystemtrial/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
