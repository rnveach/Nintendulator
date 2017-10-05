/* Nintendulator - Win32 NES emulator written in C++
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/nintendulator/trunk/src/States.h $
 * $Id: States.h 1353 2017-09-23 00:27:51Z quietust $
 */

#pragma once

#define	STATES_CUR_VERSION	1001	// current savestate version
#define	STATES_MIN_VERSION	950	// minimum supported savestate version

namespace States
{
extern TCHAR BaseFilename[MAX_PATH];
extern int SelSlot;

void	Init (void);
void	SetFilename (TCHAR *name);
void	SetSlot (int Slot);
int	SaveData (FILE *);
BOOL	LoadData (FILE *, int len, int ver);
void	SaveState (void);
void	LoadState (void);
void	SaveVersion (FILE *, int ver);
int	LoadVersion (FILE *);
} // namespace States
