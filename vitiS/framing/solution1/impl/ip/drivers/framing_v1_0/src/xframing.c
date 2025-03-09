// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xframing.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XFraming_CfgInitialize(XFraming *InstancePtr, XFraming_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XFraming_Start(XFraming *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFraming_ReadReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_AP_CTRL) & 0x80;
    XFraming_WriteReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XFraming_IsDone(XFraming *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFraming_ReadReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XFraming_IsIdle(XFraming *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFraming_ReadReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XFraming_IsReady(XFraming *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFraming_ReadReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XFraming_EnableAutoRestart(XFraming *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFraming_WriteReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XFraming_DisableAutoRestart(XFraming *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFraming_WriteReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_AP_CTRL, 0);
}

void XFraming_InterruptGlobalEnable(XFraming *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFraming_WriteReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_GIE, 1);
}

void XFraming_InterruptGlobalDisable(XFraming *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFraming_WriteReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_GIE, 0);
}

void XFraming_InterruptEnable(XFraming *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XFraming_ReadReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_IER);
    XFraming_WriteReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_IER, Register | Mask);
}

void XFraming_InterruptDisable(XFraming *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XFraming_ReadReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_IER);
    XFraming_WriteReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_IER, Register & (~Mask));
}

void XFraming_InterruptClear(XFraming *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFraming_WriteReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_ISR, Mask);
}

u32 XFraming_InterruptGetEnabled(XFraming *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XFraming_ReadReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_IER);
}

u32 XFraming_InterruptGetStatus(XFraming *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XFraming_ReadReg(InstancePtr->Control_BaseAddress, XFRAMING_CONTROL_ADDR_ISR);
}

