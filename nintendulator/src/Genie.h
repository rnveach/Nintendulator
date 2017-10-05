/* Nintendulator - Win32 NES emulator written in C++
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/nintendulator/trunk/src/Genie.h $
 * $Id: Genie.h 1353 2017-09-23 00:27:51Z quietust $
 */

#pragma once

namespace Genie
{
extern unsigned char CodeStat;

int	MAPINT	Read (int, int);
int	MAPINT	Read1 (int, int);
int	MAPINT	Read2 (int, int);
int	MAPINT	Read3 (int, int);

void	Reset (void);
void	Init (void);
int	Save (FILE *);
int	Load (FILE *, int ver);
} // namespace Genie
