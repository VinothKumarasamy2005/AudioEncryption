############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project try2
add_files chensystemtrial/chen_hype.h
add_files main_hyperchaos.cpp
add_files -tb test_hyperchaos.cpp
open_solution "solutionss" -flow_target vivado
set_part {xc7a100tcsg324-1}
create_clock -period 10 -name default
#source "./try2/solutionss/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
