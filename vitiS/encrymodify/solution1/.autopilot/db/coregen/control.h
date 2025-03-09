// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 7  - auto_restart (Read/Write)
//        bit 9  - interrupt (Read)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0 - enable ap_done interrupt (Read/Write)
//        bit 1 - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0 - ap_done (Read/TOW)
//        bit 1 - ap_ready (Read/TOW)
//        others - reserved
// 0x40 ~
// 0x7f : Memory 'speechSignal' (16 * 32b)
//        Word n : bit [31:0] - speechSignal[n]
// 0x80 ~
// 0xff : Memory 'encryptedSignal' (16 * 64b)
//        Word 2n   : bit [31:0] - encryptedSignal[n][31: 0]
//        Word 2n+1 : bit [31:0] - encryptedSignal[n][63:32]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define CONTROL_ADDR_AP_CTRL              0x00
#define CONTROL_ADDR_GIE                  0x04
#define CONTROL_ADDR_IER                  0x08
#define CONTROL_ADDR_ISR                  0x0c
#define CONTROL_ADDR_SPEECHSIGNAL_BASE    0x40
#define CONTROL_ADDR_SPEECHSIGNAL_HIGH    0x7f
#define CONTROL_WIDTH_SPEECHSIGNAL        32
#define CONTROL_DEPTH_SPEECHSIGNAL        16
#define CONTROL_ADDR_ENCRYPTEDSIGNAL_BASE 0x80
#define CONTROL_ADDR_ENCRYPTEDSIGNAL_HIGH 0xff
#define CONTROL_WIDTH_ENCRYPTEDSIGNAL     64
#define CONTROL_DEPTH_ENCRYPTEDSIGNAL     16
