// STTubeDevice.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "usb100.h"
#include "STTubeDevice.h"
#include "STTubeDeviceErr30.h"
#include "STTubeDeviceTyp30.h"
#include "STDevicesMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSTDevicesManager *m_pMgr = NULL;

void STTubeDeviceApp_InitInstance() 
{
	m_pMgr=new CSTDevicesManager();
}

void STTubeDeviceApp_ExitInstance() 
{
	if (m_pMgr)
		delete m_pMgr;
	m_pMgr=NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Exported functions bodies

extern "C" {

DWORD WINAPI STDevice_Open(LPSTR szDevicePath, 
							LPHANDLE phDevice, 
							LPHANDLE phUnPlugEvent)
{
	CString sSymbName;

	if (!sSymbName)
		return STDEVICE_BADPARAMETER;
	
	sSymbName=szDevicePath;
	if (sSymbName.IsEmpty())
		return STDEVICE_BADPARAMETER;

	if (m_pMgr)
		return m_pMgr->Open(sSymbName, phDevice, phUnPlugEvent);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_Close(HANDLE hDevice)
{
	if (m_pMgr)
		return m_pMgr->Close(hDevice);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_OpenPipes(HANDLE hDevice)
{
	if (m_pMgr)
		return m_pMgr->OpenPipes(hDevice);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_ClosePipes(HANDLE hDevice)
{
	if (m_pMgr)
		return m_pMgr->ClosePipes(hDevice);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_GetStringDescriptor(HANDLE hDevice, 
								   UINT nIndex, 
								   LPSTR szString, 
								   UINT nStringLength)
{
	CString sString;
	DWORD nRet=STDEVICE_MEMORY;

	if (m_pMgr)
	{
		// Check parameters we use here. Others are checked in the manager class
		if (!szString)
			return STDEVICE_BADPARAMETER;

		nRet=m_pMgr->GetStringDescriptor(hDevice, nIndex, sString);

		if (nRet==STDEVICE_NOERROR)
			strncpy(szString, (LPCSTR)sString, nStringLength);
	}
	return nRet;
}

DWORD WINAPI STDevice_GetDeviceDescriptor(HANDLE hDevice, 
								   PUSB_DEVICE_DESCRIPTOR pDesc)
{
	if (m_pMgr)
		return m_pMgr->GetDeviceDescriptor(hDevice, pDesc);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_GetNbOfConfigurations(HANDLE hDevice, PUINT pNbOfConfigs)
{
	if (m_pMgr)
		return m_pMgr->GetNbOfConfigurations(hDevice, pNbOfConfigs);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_GetConfigurationDescriptor(HANDLE hDevice, 
										  UINT nConfigIdx, 
										  PUSB_CONFIGURATION_DESCRIPTOR pDesc)
{
	if (m_pMgr)
		return m_pMgr->GetConfigurationDescriptor(hDevice, nConfigIdx, pDesc);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_GetNbOfInterfaces(HANDLE hDevice, 
								 UINT nConfigIdx, 
								 PUINT pNbOfInterfaces)
{
	if (m_pMgr)
		return m_pMgr->GetNbOfInterfaces(hDevice, nConfigIdx, pNbOfInterfaces);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_GetNbOfAlternates(HANDLE hDevice, 
								 UINT nConfigIdx, 
								 UINT nInterfaceIdx, 
								 PUINT pNbOfAltSets)
{
	if (m_pMgr)
		return m_pMgr->GetNbOfAlternates(hDevice, nConfigIdx, nInterfaceIdx, pNbOfAltSets);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_GetInterfaceDescriptor(HANDLE hDevice, 
									  UINT nConfigIdx, 
									  UINT nInterfaceIdx, 
									  UINT nAltSetIdx, 
									  PUSB_INTERFACE_DESCRIPTOR pDesc)
{
	if (m_pMgr)
		return m_pMgr->GetInterfaceDescriptor(hDevice, nConfigIdx, nInterfaceIdx, nAltSetIdx, pDesc);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_GetNbOfEndPoints(HANDLE hDevice, 
								UINT nConfigIdx, 
								UINT nInterfaceIdx, 
								UINT nAltSetIdx, 
								PUINT pNbOfEndPoints)
{
	if (m_pMgr)
		return m_pMgr->GetNbOfEndPoints(hDevice, nConfigIdx, nInterfaceIdx, nAltSetIdx, pNbOfEndPoints);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_GetEndPointDescriptor(HANDLE hDevice, 
									 UINT nConfigIdx, 
									 UINT nInterfaceIdx, 
									 UINT nAltSetIdx, 
									 UINT nEndPointIdx, 
									 PUSB_ENDPOINT_DESCRIPTOR pDesc)
{
	if (m_pMgr)
		return m_pMgr->GetEndPointDescriptor(hDevice, nConfigIdx, nInterfaceIdx, nAltSetIdx, nEndPointIdx, pDesc);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_GetNbOfDescriptors(HANDLE hDevice, 
										BYTE nLevel,
										BYTE nType,
										UINT nConfigIdx, 
										UINT nInterfaceIdx, 
										UINT nAltSetIdx, 
										UINT nEndPointIdx, 
										PUINT pNbOfDescriptors)
{
	if (m_pMgr)
		return m_pMgr->GetNbOfDescriptors(hDevice, nLevel,
												   nType,
												   nConfigIdx, nInterfaceIdx, nAltSetIdx, nEndPointIdx, 
												   pNbOfDescriptors);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_GetDescriptor(HANDLE hDevice, 
								    BYTE nLevel,
									BYTE nType,
									UINT nConfigIdx, 
									UINT nInterfaceIdx, 
									UINT nAltSetIdx, 
									UINT nEndPointIdx, 
									UINT nIdx,
									PBYTE pDesc,
									UINT nDescSize)
{
	if (m_pMgr)
		return m_pMgr->GetDescriptor(hDevice, nLevel,
											  nType, 
											  nConfigIdx, nInterfaceIdx, nAltSetIdx, nEndPointIdx, nIdx,
											  pDesc, nDescSize);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_SelectCurrentConfiguration(HANDLE hDevice, 
										  UINT nConfigIdx, 
										  UINT nInterfaceIdx, 
										  UINT nAltSetIdx)
{
	if (m_pMgr)
		return m_pMgr->SelectCurrentConfiguration(hDevice, nConfigIdx, nInterfaceIdx, nAltSetIdx);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_SetDefaultTimeOut(HANDLE hDevice, DWORD nTimeOut)
{
	if (m_pMgr)
		return m_pMgr->SetDefaultTimeOut(hDevice, nTimeOut);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_SetMaxNumInterruptInputBuffer(HANDLE hDevice,
													WORD nMaxNumInputBuffer)
{
	if (m_pMgr)
		return m_pMgr->SetMaxNumInterruptInputBuffer(hDevice, nMaxNumInputBuffer);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_GetMaxNumInterruptInputBuffer(HANDLE hDevice,
													PWORD pMaxNumInputBuffer)
{
	if (m_pMgr)
		return m_pMgr->GetMaxNumInterruptInputBuffer(hDevice, pMaxNumInputBuffer);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_SetSuspendModeBehaviour(HANDLE hDevice, BOOL Allow)
{
	if (m_pMgr)
		return m_pMgr->SetSuspendModeBehaviour(hDevice, Allow);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_EndPointControl(HANDLE hDevice, 
							   UINT nEndPointIdx, 
							   UINT nOperation)
{
	if (m_pMgr)
		return m_pMgr->EndPointControl(hDevice, nEndPointIdx, nOperation);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_Reset(HANDLE hDevice)
{
	if (m_pMgr)
		return m_pMgr->Reset(hDevice);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_ControlPipeRequest(HANDLE hDevice, PCNTRPIPE_RQ pRequest,
										 PBYTE pData)
{
	if (m_pMgr)
		return m_pMgr->ControlPipeRequest(hDevice, pRequest, pData);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_Read(HANDLE hDevice, 
				    UINT nEndPointIdx,
					PBYTE pBuffer, 
					PUINT pSize, 
					DWORD nTimeOut)
{
	if (m_pMgr)
		return m_pMgr->Read(hDevice, nEndPointIdx, pBuffer, pSize, nTimeOut);

	return STDEVICE_MEMORY;
}

DWORD WINAPI STDevice_Write(HANDLE hDevice, 
				    UINT nEndPointIdx,
					 PBYTE pBuffer, 
					 PUINT pSize, 
					 DWORD nTimeOut)
{
	if (m_pMgr)
		return m_pMgr->Write(hDevice, nEndPointIdx, pBuffer, pSize, nTimeOut);

	return STDEVICE_MEMORY;
}

}