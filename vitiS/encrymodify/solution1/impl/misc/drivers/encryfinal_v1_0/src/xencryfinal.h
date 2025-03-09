// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XENCRYFINAL_H
#define XENCRYFINAL_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xencryfinal_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
} XEncryfinal_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XEncryfinal;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XEncryfinal_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XEncryfinal_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XEncryfinal_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XEncryfinal_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XEncryfinal_Initialize(XEncryfinal *InstancePtr, UINTPTR BaseAddress);
XEncryfinal_Config* XEncryfinal_LookupConfig(UINTPTR BaseAddress);
#else
int XEncryfinal_Initialize(XEncryfinal *InstancePtr, u16 DeviceId);
XEncryfinal_Config* XEncryfinal_LookupConfig(u16 DeviceId);
#endif
int XEncryfinal_CfgInitialize(XEncryfinal *InstancePtr, XEncryfinal_Config *ConfigPtr);
#else
int XEncryfinal_Initialize(XEncryfinal *InstancePtr, const char* InstanceName);
int XEncryfinal_Release(XEncryfinal *InstancePtr);
#endif

void XEncryfinal_Start(XEncryfinal *InstancePtr);
u32 XEncryfinal_IsDone(XEncryfinal *InstancePtr);
u32 XEncryfinal_IsIdle(XEncryfinal *InstancePtr);
u32 XEncryfinal_IsReady(XEncryfinal *InstancePtr);
void XEncryfinal_EnableAutoRestart(XEncryfinal *InstancePtr);
void XEncryfinal_DisableAutoRestart(XEncryfinal *InstancePtr);

u32 XEncryfinal_Get_speechSignal_BaseAddress(XEncryfinal *InstancePtr);
u32 XEncryfinal_Get_speechSignal_HighAddress(XEncryfinal *InstancePtr);
u32 XEncryfinal_Get_speechSignal_TotalBytes(XEncryfinal *InstancePtr);
u32 XEncryfinal_Get_speechSignal_BitWidth(XEncryfinal *InstancePtr);
u32 XEncryfinal_Get_speechSignal_Depth(XEncryfinal *InstancePtr);
u32 XEncryfinal_Write_speechSignal_Words(XEncryfinal *InstancePtr, int offset, word_type *data, int length);
u32 XEncryfinal_Read_speechSignal_Words(XEncryfinal *InstancePtr, int offset, word_type *data, int length);
u32 XEncryfinal_Write_speechSignal_Bytes(XEncryfinal *InstancePtr, int offset, char *data, int length);
u32 XEncryfinal_Read_speechSignal_Bytes(XEncryfinal *InstancePtr, int offset, char *data, int length);
u32 XEncryfinal_Get_encryptedSignal_BaseAddress(XEncryfinal *InstancePtr);
u32 XEncryfinal_Get_encryptedSignal_HighAddress(XEncryfinal *InstancePtr);
u32 XEncryfinal_Get_encryptedSignal_TotalBytes(XEncryfinal *InstancePtr);
u32 XEncryfinal_Get_encryptedSignal_BitWidth(XEncryfinal *InstancePtr);
u32 XEncryfinal_Get_encryptedSignal_Depth(XEncryfinal *InstancePtr);
u32 XEncryfinal_Write_encryptedSignal_Words(XEncryfinal *InstancePtr, int offset, word_type *data, int length);
u32 XEncryfinal_Read_encryptedSignal_Words(XEncryfinal *InstancePtr, int offset, word_type *data, int length);
u32 XEncryfinal_Write_encryptedSignal_Bytes(XEncryfinal *InstancePtr, int offset, char *data, int length);
u32 XEncryfinal_Read_encryptedSignal_Bytes(XEncryfinal *InstancePtr, int offset, char *data, int length);

void XEncryfinal_InterruptGlobalEnable(XEncryfinal *InstancePtr);
void XEncryfinal_InterruptGlobalDisable(XEncryfinal *InstancePtr);
void XEncryfinal_InterruptEnable(XEncryfinal *InstancePtr, u32 Mask);
void XEncryfinal_InterruptDisable(XEncryfinal *InstancePtr, u32 Mask);
void XEncryfinal_InterruptClear(XEncryfinal *InstancePtr, u32 Mask);
u32 XEncryfinal_InterruptGetEnabled(XEncryfinal *InstancePtr);
u32 XEncryfinal_InterruptGetStatus(XEncryfinal *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
