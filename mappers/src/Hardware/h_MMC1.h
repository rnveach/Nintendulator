/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/Hardware/h_MMC1.h $
 * $Id: h_MMC1.h 1352 2017-09-23 00:20:15Z quietust $
 */

#pragma once

#include	"..\interface.h"

namespace MMC1
{
void		Load		(FSync);
void		Reset		(RESET_TYPE);
void		Unload		(void);
int	MAPINT	SaveLoad	(STATE_TYPE,int,unsigned char *);
void	MAPINT	Write		(int,int,int);

void		SyncMirror	(void);
int		GetPRGBankLo	(void);
int		GetPRGBankHi	(void);
int		GetCHRBankLo	(void);
int		GetCHRBankHi	(void);
BOOL		GetWRAMEnabled	(void);

void		SyncPRG		(int,int);
void		SyncCHR_ROM	(int,int);
void		SyncCHR_RAM	(int,int);
void		SyncWRAM	(void);
} // namespace MMC1
