/* Nintendulator - Win32 NES emulator written in C++
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/nintendulator/trunk/src/Nintendulator.h $
 * $Id: Nintendulator.h 1353 2017-09-23 00:27:51Z quietust $
 */

#pragma once

#define	ENABLE_DEBUGGER	// Enable the debugger - emulation is faster without it
//#define	CPU_BENCHMARK	// Run cyctest.nes for 4542110 cycles (10 seconds), then report how long it took
//#define	SHORQ	// Enable ShoRQ(tm) technology - enable green color emphasis whenever there's an active IRQ

extern	int		ConfigVersion;	// Configuration version - used if files get moved around or settings change meaning

extern	HINSTANCE	hInst;	/* current instance */
extern	HWND		hMainWnd;	/* main window */
extern	HMENU		hMenu;	/* main window menu */
extern	HACCEL		hAccelTable;	/* accelerators */

extern	BOOL		MaskKeyboard;	/* mask keyboard accelerators (for when Family Basic Keyboard is active) */
extern	BOOL		MaskMouse;	/* hide mouse cursor (for Arkanoid paddle and SNES Mouse) */
extern	HWND		hDebug;		/* Debug Info window */
extern	BOOL		dbgVisible;	/* whether or not the Debug window is open */

extern	int		SizeMult;	/* window size multiplier */
extern	BOOL		FixAspect;	/* whether to adjust aspect ratio */
extern	TCHAR		ProgPath[MAX_PATH];	/* program path */
extern	TCHAR		DataPath[MAX_PATH];	/* data path */

extern	TCHAR		Path_ROM[MAX_PATH];
extern	TCHAR		Path_NMV[MAX_PATH];
extern	TCHAR		Path_AVI[MAX_PATH];
extern	TCHAR		Path_PAL[MAX_PATH];

extern	void		BrowseFolder (const TCHAR *dir);

extern	BOOL		ProcessMessages	(void);

extern	TCHAR		TitlebarBuffer[256];
extern	int		TitlebarDelay;
extern	void		UpdateTitlebar (void);
extern	void	__cdecl	PrintTitlebar (const TCHAR *Text, ...);
extern	void		AddDebug (const TCHAR *txt);

// Shortcut macros for use in savestate code
#define	writeByte(val) { register unsigned char _val = val; fwrite(&_val, 1, 1, out); clen++; }
#define	writeWord(val) { register unsigned short _val = val; fwrite(&_val, 2, 1, out); clen += 2; }
#define	writeLong(val) { register unsigned long _val = val; fwrite(&_val, 4, 1, out); clen += 4; }
#define	writeArray(val,len) { register int _len = len; fwrite(val, 1, _len, out); clen += _len; }

#define	readByte(val) { register unsigned char _val; fread(&_val, 1, 1, in); val = _val; clen++; }
#define	readWord(val) { register unsigned short _val; fread(&_val, 2, 1, in); val = _val; clen += 2; }
#define	readLong(val) { register unsigned long _val; fread(&_val, 4, 1, in); val = _val; clen += 4; }
#define	readArray(val,len) { register int _len = len; fread(val, 1, _len, in); clen += _len; }
#define	readArraySkip(val,inlen,outlen) { register int readLen = min(inlen, outlen); fread(val, 1, readLen, in); if (inlen > readLen) fseek(in, inlen - readLen, SEEK_CUR); if (outlen > readLen) ZeroMemory((unsigned char *)val + readLen, outlen - readLen); clen += inlen; }
