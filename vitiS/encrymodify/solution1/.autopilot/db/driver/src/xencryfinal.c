// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xencryfinal.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XEncryfinal_CfgInitialize(XEncryfinal *InstancePtr, XEncryfinal_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XEncryfinal_Start(XEncryfinal *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEncryfinal_ReadReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_AP_CTRL) & 0x80;
    XEncryfinal_WriteReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XEncryfinal_IsDone(XEncryfinal *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEncryfinal_ReadReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XEncryfinal_IsIdle(XEncryfinal *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEncryfinal_ReadReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XEncryfinal_IsReady(XEncryfinal *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEncryfinal_ReadReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XEncryfinal_EnableAutoRestart(XEncryfinal *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEncryfinal_WriteReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XEncryfinal_DisableAutoRestart(XEncryfinal *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEncryfinal_WriteReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_AP_CTRL, 0);
}

u32 XEncryfinal_Get_speechSignal_BaseAddress(XEncryfinal *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_BASE);
}

u32 XEncryfinal_Get_speechSignal_HighAddress(XEncryfinal *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_HIGH);
}

u32 XEncryfinal_Get_speechSignal_TotalBytes(XEncryfinal *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_HIGH - XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_BASE + 1);
}

u32 XEncryfinal_Get_speechSignal_BitWidth(XEncryfinal *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XENCRYFINAL_CONTROL_WIDTH_SPEECHSIGNAL;
}

u32 XEncryfinal_Get_speechSignal_Depth(XEncryfinal *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XENCRYFINAL_CONTROL_DEPTH_SPEECHSIGNAL;
}

u32 XEncryfinal_Write_speechSignal_Words(XEncryfinal *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_HIGH - XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XEncryfinal_Read_speechSignal_Words(XEncryfinal *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_HIGH - XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_BASE + (offset + i)*4);
    }
    return length;
}

u32 XEncryfinal_Write_speechSignal_Bytes(XEncryfinal *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_HIGH - XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XEncryfinal_Read_speechSignal_Bytes(XEncryfinal *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_HIGH - XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XENCRYFINAL_CONTROL_ADDR_SPEECHSIGNAL_BASE + offset + i);
    }
    return length;
}

u32 XEncryfinal_Get_encryptedSignal_BaseAddress(XEncryfinal *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_BASE);
}

u32 XEncryfinal_Get_encryptedSignal_HighAddress(XEncryfinal *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_HIGH);
}

u32 XEncryfinal_Get_encryptedSignal_TotalBytes(XEncryfinal *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_HIGH - XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_BASE + 1);
}

u32 XEncryfinal_Get_encryptedSignal_BitWidth(XEncryfinal *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XENCRYFINAL_CONTROL_WIDTH_ENCRYPTEDSIGNAL;
}

u32 XEncryfinal_Get_encryptedSignal_Depth(XEncryfinal *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XENCRYFINAL_CONTROL_DEPTH_ENCRYPTEDSIGNAL;
}

u32 XEncryfinal_Write_encryptedSignal_Words(XEncryfinal *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_HIGH - XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XEncryfinal_Read_encryptedSignal_Words(XEncryfinal *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_HIGH - XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_BASE + (offset + i)*4);
    }
    return length;
}

u32 XEncryfinal_Write_encryptedSignal_Bytes(XEncryfinal *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_HIGH - XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XEncryfinal_Read_encryptedSignal_Bytes(XEncryfinal *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_HIGH - XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XENCRYFINAL_CONTROL_ADDR_ENCRYPTEDSIGNAL_BASE + offset + i);
    }
    return length;
}

void XEncryfinal_InterruptGlobalEnable(XEncryfinal *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEncryfinal_WriteReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_GIE, 1);
}

void XEncryfinal_InterruptGlobalDisable(XEncryfinal *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEncryfinal_WriteReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_GIE, 0);
}

void XEncryfinal_InterruptEnable(XEncryfinal *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XEncryfinal_ReadReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_IER);
    XEncryfinal_WriteReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_IER, Register | Mask);
}

void XEncryfinal_InterruptDisable(XEncryfinal *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XEncryfinal_ReadReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_IER);
    XEncryfinal_WriteReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_IER, Register & (~Mask));
}

void XEncryfinal_InterruptClear(XEncryfinal *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEncryfinal_WriteReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_ISR, Mask);
}

u32 XEncryfinal_InterruptGetEnabled(XEncryfinal *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEncryfinal_ReadReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_IER);
}

u32 XEncryfinal_InterruptGetStatus(XEncryfinal *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEncryfinal_ReadReg(InstancePtr->Control_BaseAddress, XENCRYFINAL_CONTROL_ADDR_ISR);
}

