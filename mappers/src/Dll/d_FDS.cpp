/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/Dll/d_FDS.cpp $
 * $Id: d_FDS.cpp 1352 2017-09-23 00:20:15Z quietust $
 */

#include	"d_FDS.h"

HWND			hWnd;
HINSTANCE		hInstance;
const EmulatorInterface	*EMU;
const ROMInfo		*ROM;

namespace
{
void	MAPINT	UnloadMapper (void)
{
	ROM = NULL;
}

const MapperInfo	*MAPINT	LoadMapper (const ROMInfo *_ROM)
{
	ROM = _ROM;
	if (ROM->ROMType == ROM_UNDEFINED)	/* Allow enumerating mappers */
	{
		unsigned int i = (uintptr_t)ROM->Filename;
		if (i >= 1)
		{
			UnloadMapper();
			return NULL;
		}
		((ROMInfo *)ROM)->ROMType = ROM_FDS;
		return &MapperInfo_FDS;
	}
	if (ROM->ROMType != ROM_FDS)
	{
		UnloadMapper();
		return NULL;
	}
	return &MapperInfo_FDS;
}

DLLInfo	DLL_Info =
{
	_T("FDS.DLL by Quietust"),
	0x20100102,
	0x00040002,
	LoadMapper,
	UnloadMapper
};
} // namespace

extern "C" __declspec(dllexport)	void	MAPINT	UnloadMapperDLL (void)
{
	EMU = NULL;
	hWnd = NULL;
}

extern "C" __declspec(dllexport)	DLLInfo *MAPINT	LoadMapperDLL (HWND hWndEmu, const EmulatorInterface *_EMU, int VersionRequired)
{
	hWnd = hWndEmu;
	EMU = _EMU;
	if (VersionRequired != CurrentMapperInterface)
	{
		UnloadMapperDLL();
		return NULL;
	}
	return &DLL_Info;
}

BOOL	WINAPI	DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	hInstance = hinstDLL;
	return TRUE;
}
