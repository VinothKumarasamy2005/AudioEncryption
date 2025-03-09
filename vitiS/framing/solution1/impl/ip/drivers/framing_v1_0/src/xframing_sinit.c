// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xframing.h"

extern XFraming_Config XFraming_ConfigTable[];

#ifdef SDT
XFraming_Config *XFraming_LookupConfig(UINTPTR BaseAddress) {
	XFraming_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XFraming_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XFraming_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XFraming_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XFraming_Initialize(XFraming *InstancePtr, UINTPTR BaseAddress) {
	XFraming_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XFraming_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XFraming_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XFraming_Config *XFraming_LookupConfig(u16 DeviceId) {
	XFraming_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XFRAMING_NUM_INSTANCES; Index++) {
		if (XFraming_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XFraming_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XFraming_Initialize(XFraming *InstancePtr, u16 DeviceId) {
	XFraming_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XFraming_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XFraming_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

