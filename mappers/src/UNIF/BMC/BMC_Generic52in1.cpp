/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/UNIF/BMC/BMC_Generic52in1.cpp $
 * $Id: BMC_Generic52in1.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\..\DLL\d_UNIF.h"
#include	"..\..\Hardware\h_Latch.h"

namespace
{
void	Sync (void)
{
	// rveach: eclipse doesn't support anonymous unions with anonymous structs
	union temp_union
	{
		struct
		{
			unsigned CHRbank : 6;
			unsigned PRG16   : 1;
			unsigned PRGbank : 5;
			unsigned PRGsize : 1;
			unsigned Mir_HV  : 1;
			unsigned         : 2;
		};
		uint16_t addr;
	};
	temp_union temp_var;

	temp_var.addr = Latch::Addr.s0;

	EMU->SetCHR_ROM8(0, temp_var.CHRbank);
	if (temp_var.PRGsize)
	{
		EMU->SetPRG_ROM16(0x8, (temp_var.PRGbank << 1) | (temp_var.PRG16));
		EMU->SetPRG_ROM16(0xC, (temp_var.PRGbank << 1) | (temp_var.PRG16));
	}
	else	EMU->SetPRG_ROM32(0x8, temp_var.PRGbank);
	if (temp_var.Mir_HV)
		EMU->Mirror_H();
	else	EMU->Mirror_V();
}

BOOL	MAPINT	Load (void)
{
	Latch::Load(Sync, FALSE);
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	Latch::Reset(ResetType);
}
void	MAPINT	Unload (void)
{
	Latch::Unload();
}
} // namespace

const MapperInfo MapperInfo_BMC_Generic52in1 =
{
	"BMC-Generic52in1",
	_T("Pirate multicart mapper"),
	COMPAT_FULL,
	Load,
	Reset,
	Unload,
	NULL,
	NULL,
	Latch::SaveLoad_A,
	NULL,
	NULL
};
