/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/Hardware/h_MMC3.h $
 * $Id: h_MMC3.h 1352 2017-09-23 00:20:15Z quietust $
 */

#pragma once

#include	"..\interface.h"

namespace MMC3
{
void		Load		(FSync);
void		Reset		(RESET_TYPE);
void		Unload		(void);
void		SyncMirror	(void);
int		GetPRGBank	(int);
int		GetCHRBank	(int);
void		SyncPRG		(int,int);
void		SyncWRAM	(void);
void		SyncCHR_ROM	(int,int);
void		SyncCHR_RAM	(int,int);
int	MAPINT	SaveLoad	(STATE_TYPE,int,unsigned char *);
void	MAPINT	CPUWrite67	(int,int,int);
void	MAPINT	CPUWrite89	(int,int,int);
void	MAPINT	CPUWriteAB	(int,int,int);
void	MAPINT	CPUWriteCD	(int,int,int);
void	MAPINT	CPUWriteEF	(int,int,int);
void	MAPINT	PPUCycle	(int,int,int,int);
} // namespace MMC3
