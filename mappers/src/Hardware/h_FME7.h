/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/Hardware/h_FME7.h $
 * $Id: h_FME7.h 1352 2017-09-23 00:20:15Z quietust $
 */

#pragma once

#include	"..\interface.h"

namespace FME7
{
void		Load		(FSync);
void		Reset		(RESET_TYPE);
void		Unload		(void);
void		SyncMirror	(void);
void		SyncPRG		(int,int);
void		SyncCHR		(int,int);
int	MAPINT	SaveLoad	(STATE_TYPE,int,unsigned char *);
void	MAPINT	Write89		(int,int,int);
void	MAPINT	WriteAB		(int,int,int);
void	MAPINT	WriteCDEF	(int,int,int);
void	MAPINT	CPUCycle	(void);
int	MAPINT	GenSound	(int);
} // namespace FME7
