/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/FDS/FDS_Mapper.cpp $
 * $Id: FDS_Mapper.cpp 1352 2017-09-23 00:20:15Z quietust $
 */

#include	"..\DLL\d_FDS.h"
#include	"..\Hardware\h_FDS.h"

namespace
{
BOOL	MAPINT	Load (void)
{
	return FDS::Load();
}

void	MAPINT	Reset (RESET_TYPE ResetType)
{
	FDS::Reset(ResetType);
}

void	MAPINT	Unload (void)
{
	FDS::Unload();
}
} // namespace

const MapperInfo MapperInfo_FDS =
{
	NULL,
	_T("Famicom Disk System"),
	COMPAT_NEARLY,
	Load,
	Reset,
	Unload,
	FDS::CPUCycle,
	NULL,
	FDS::SaveLoad,
	FDS::MapperSnd,
	FDS::Config
};
