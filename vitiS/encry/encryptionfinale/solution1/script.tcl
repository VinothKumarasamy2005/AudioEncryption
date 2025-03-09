############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project encryptionfinale
set_top encryfinal
add_files encryptionfinale/chaotic_encrypt.cpp
add_files -tb encryptionfinale/tb.cpp
open_solution "solution1" -flow_target vivado
set_part {xc7a100tcsg324-1}
create_clock -period 10 -name default
config_export -output C:/Windows/vitiS/encry/encryptionfinale
#source "./encryptionfinale/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -output C:/Windows/vitiS/encry/encryptionfinale
