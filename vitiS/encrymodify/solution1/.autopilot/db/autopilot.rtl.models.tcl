set SynModuleInfo {
  {SRCNAME encryfinal_Pipeline_VITIS_LOOP_40_1 MODELNAME encryfinal_Pipeline_VITIS_LOOP_40_1 RTLNAME encryfinal_encryfinal_Pipeline_VITIS_LOOP_40_1
    SUBMODULES {
      {MODELNAME encryfinal_sitodp_32ns_64_6_no_dsp_1 RTLNAME encryfinal_sitodp_32ns_64_6_no_dsp_1 BINDTYPE op TYPE sitodp IMPL auto LATENCY 5 ALLOW_PRAGMA 1}
      {MODELNAME encryfinal_flow_control_loop_pipe_sequential_init RTLNAME encryfinal_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME encryfinal_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME encryfinal_Pipeline_2 MODELNAME encryfinal_Pipeline_2 RTLNAME encryfinal_encryfinal_Pipeline_2}
  {SRCNAME encryfinal_Pipeline_VITIS_LOOP_46_3 MODELNAME encryfinal_Pipeline_VITIS_LOOP_46_3 RTLNAME encryfinal_encryfinal_Pipeline_VITIS_LOOP_46_3
    SUBMODULES {
      {MODELNAME encryfinal_dadddsub_64ns_64ns_64_8_full_dsp_1 RTLNAME encryfinal_dadddsub_64ns_64ns_64_8_full_dsp_1 BINDTYPE op TYPE dadd IMPL fulldsp LATENCY 7 ALLOW_PRAGMA 1}
      {MODELNAME encryfinal_ddiv_64ns_64ns_64_59_no_dsp_1 RTLNAME encryfinal_ddiv_64ns_64ns_64_59_no_dsp_1 BINDTYPE op TYPE ddiv IMPL fabric LATENCY 58 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME encryfinal_Pipeline_VITIS_LOOP_50_4 MODELNAME encryfinal_Pipeline_VITIS_LOOP_50_4 RTLNAME encryfinal_encryfinal_Pipeline_VITIS_LOOP_50_4}
  {SRCNAME encryfinal_Pipeline_VITIS_LOOP_86_1 MODELNAME encryfinal_Pipeline_VITIS_LOOP_86_1 RTLNAME encryfinal_encryfinal_Pipeline_VITIS_LOOP_86_1
    SUBMODULES {
      {MODELNAME encryfinal_dmul_64ns_64ns_64_7_max_dsp_1 RTLNAME encryfinal_dmul_64ns_64ns_64_7_max_dsp_1 BINDTYPE op TYPE dmul IMPL maxdsp LATENCY 6 ALLOW_PRAGMA 1}
      {MODELNAME encryfinal_encryfinal_Pipeline_VITIS_LOOP_86_1_chaoticSequence_ROM_AUTO_1R RTLNAME encryfinal_encryfinal_Pipeline_VITIS_LOOP_86_1_chaoticSequence_ROM_AUTO_1R BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME encryfinal_Pipeline_VITIS_LOOP_64_1 MODELNAME encryfinal_Pipeline_VITIS_LOOP_64_1 RTLNAME encryfinal_encryfinal_Pipeline_VITIS_LOOP_64_1}
  {SRCNAME encryfinal MODELNAME encryfinal RTLNAME encryfinal IS_TOP 1
    SUBMODULES {
      {MODELNAME encryfinal_temp_RAM_AUTO_1R1W RTLNAME encryfinal_temp_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME encryfinal_transformedSignal_RAM_AUTO_1R1W RTLNAME encryfinal_transformedSignal_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME encryfinal_control_s_axi RTLNAME encryfinal_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
