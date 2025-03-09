// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XFRAMING_H
#define XFRAMING_H

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
#include "xframing_hw.h"

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
} XFraming_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XFraming;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XFraming_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XFraming_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XFraming_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XFraming_ReadReg(BaseAddress, RegOffset) \
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
int XFraming_Initialize(XFraming *InstancePtr, UINTPTR BaseAddress);
XFraming_Config* XFraming_LookupConfig(UINTPTR BaseAddress);
#else
int XFraming_Initialize(XFraming *InstancePtr, u16 DeviceId);
XFraming_Config* XFraming_LookupConfig(u16 DeviceId);
#endif
int XFraming_CfgInitialize(XFraming *InstancePtr, XFraming_Config *ConfigPtr);
#else
int XFraming_Initialize(XFraming *InstancePtr, const char* InstanceName);
int XFraming_Release(XFraming *InstancePtr);
#endif

void XFraming_Start(XFraming *InstancePtr);
u32 XFraming_IsDone(XFraming *InstancePtr);
u32 XFraming_IsIdle(XFraming *InstancePtr);
u32 XFraming_IsReady(XFraming *InstancePtr);
void XFraming_EnableAutoRestart(XFraming *InstancePtr);
void XFraming_DisableAutoRestart(XFraming *InstancePtr);


void XFraming_InterruptGlobalEnable(XFraming *InstancePtr);
void XFraming_InterruptGlobalDisable(XFraming *InstancePtr);
void XFraming_InterruptEnable(XFraming *InstancePtr, u32 Mask);
void XFraming_InterruptDisable(XFraming *InstancePtr, u32 Mask);
void XFraming_InterruptClear(XFraming *InstancePtr, u32 Mask);
u32 XFraming_InterruptGetEnabled(XFraming *InstancePtr);
u32 XFraming_InterruptGetStatus(XFraming *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
