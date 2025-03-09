dict set slaves control {ports {speechSignal {type i_ap_memory width 32} encryptedSignal {type o_ap_memory width 64} ap_start {type ap_ctrl width 1} ap_done {type ap_ctrl width 1} ap_ready {type ap_ctrl width 1} ap_idle {type ap_ctrl width 1}} mems {speechSignal {width 32} encryptedSignal {width 64}} has_ctrl 1}
set datawidth 32
set addrwidth 64
set intr_clr_mode TOW
