/* Nintendulator - Win32 NES emulator written in C++
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/nintendulator/trunk/src/APU.h $
 * $Id: APU.h 1353 2017-09-23 00:27:51Z quietust $
 */

#pragma once

#ifndef	NSFPLAYER
#include <mmsystem.h>
#define DIRECTSOUND_VERSION 0x0800
#include <dsound.h>
#endif	/* !NSFPLAYER */

namespace APU
{
extern short	*buffer;
extern unsigned long	LockSize;
extern int	buflen;
extern int	InternalClock;

#ifdef	NSFPLAYER
extern	short	sample_pos;
extern	BOOL	sample_ok;
#endif	/* NSFPLAYER */

namespace DPCM
{
	void	Fetch (void);
}

void	Init		(void);
void	Destroy		(void);
void	Start		(void);
void	Stop		(void);
#ifndef	NSFPLAYER
int	Save		(FILE *);
int	Load		(FILE *, int ver);
void	SoundOFF	(void);
void	SoundON		(void);
#endif	/* !NSFPLAYER */
void	PowerOn		(void);
void	Reset		(void);
#ifndef	NSFPLAYER
void	Config		(HWND);
#endif	/* !NSFPLAYER */
void	Run		(void);
void	SetRegion	(void);
int	MAPINT	IntRead (int, int);
void	MAPINT	IntWrite (int, int, int);
} // namespace APU
