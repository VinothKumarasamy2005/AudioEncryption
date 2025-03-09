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
#include "xencryfinal.h"

extern XEncryfinal_Config XEncryfinal_ConfigTable[];

#ifdef SDT
XEncryfinal_Config *XEncryfinal_LookupConfig(UINTPTR BaseAddress) {
	XEncryfinal_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XEncryfinal_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XEncryfinal_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XEncryfinal_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XEncryfinal_Initialize(XEncryfinal *InstancePtr, UINTPTR BaseAddress) {
	XEncryfinal_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XEncryfinal_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XEncryfinal_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XEncryfinal_Config *XEncryfinal_LookupConfig(u16 DeviceId) {
	XEncryfinal_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XENCRYFINAL_NUM_INSTANCES; Index++) {
		if (XEncryfinal_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XEncryfinal_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XEncryfinal_Initialize(XEncryfinal *InstancePtr, u16 DeviceId) {
	XEncryfinal_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XEncryfinal_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XEncryfinal_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

