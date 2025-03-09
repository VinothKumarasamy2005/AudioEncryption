set SynModuleInfo {
  {SRCNAME chensy MODELNAME chensy RTLNAME chensy IS_TOP 1
    SUBMODULES {
      {MODELNAME chensy_faddfsub_32ns_32ns_32_7_full_dsp_1 RTLNAME chensy_faddfsub_32ns_32ns_32_7_full_dsp_1 BINDTYPE op TYPE fsub IMPL fulldsp LATENCY 6 ALLOW_PRAGMA 1}
      {MODELNAME chensy_faddfsub_32ns_32ns_32_6_no_dsp_1 RTLNAME chensy_faddfsub_32ns_32ns_32_6_no_dsp_1 BINDTYPE op TYPE fsub IMPL fabric LATENCY 5 ALLOW_PRAGMA 1}
      {MODELNAME chensy_fmul_32ns_32ns_32_4_max_dsp_1 RTLNAME chensy_fmul_32ns_32ns_32_4_max_dsp_1 BINDTYPE op TYPE fmul IMPL maxdsp LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME chensy_flow_control_loop_pipe RTLNAME chensy_flow_control_loop_pipe BINDTYPE interface TYPE internal_upc_flow_control INSTNAME chensy_flow_control_loop_pipe_U}
    }
  }
}
