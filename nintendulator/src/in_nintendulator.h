/* in_nintendulator - NSF player plugin for Winamp, based on Nintendulator
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/nintendulator/trunk/src/in_nintendulator.h $
 * $Id: in_nintendulator.h 1353 2017-09-23 00:27:51Z quietust $
 */

#pragma once

#include <windows.h>
#include <stddef.h>
#include <tchar.h>

#ifdef UNICODE
#define IN_VER (0x0F000000 | 0x100)
#else
#define IN_VER 0x100
#endif

// warnings we don't care about
#pragma warning(disable:4100)	// "unreferenced formal parameter" - functions which don't use every parameter (mostly controllers)
#pragma warning(disable:4201)	// "nonstandard extension used : nameless struct/union" - used in several places in mapper interface
#pragma warning(disable:4244)	// "conversion from 'foo' to 'bar', possible loss of data" - I/O handlers all pass 'int' values and get crammed into bytes/shorts

#define OUT_VER 0x10

typedef struct 
{
	int version;				// module version (OUT_VER)
	char *description;			// description of module, with version string
	intptr_t id;						// module id. each input module gets its own. non-nullsoft modules should
								// be >= 65536. 

	HWND hMainWindow;			// winamp's main window (filled in by winamp)
	HINSTANCE hDllInstance;		// DLL instance handle (filled in by winamp)

	void (*Config)(HWND hwndParent); // configuration dialog 
	void (*About)(HWND hwndParent);  // about dialog

	void (*Init)();				// called when loaded
	void (*Quit)();				// called when unloaded

	int (*Open)(int samplerate, int numchannels, int bitspersamp, int bufferlenms, int prebufferms); 
					// returns >=0 on success, <0 on failure

					// NOTENOTENOTE: bufferlenms and prebufferms are ignored in most if not all output plug-ins. 
					//    ... so don't expect the max latency returned to be what you asked for.
					// returns max latency in ms (0 for diskwriters, etc)
					// bufferlenms and prebufferms must be in ms. 0 to use defaults. 
					// prebufferms must be <= bufferlenms
					// pass bufferlenms==-666 to tell the output plugin that it's clock is going to be used to sync video
					//   out_ds turns off silence-eating when -666 is passed

	void (*Close)();	// close the ol' output device.

	int (*Write)(char *buf, int len);	
					// 0 on success. Len == bytes to write (<= 8192 always). buf is straight audio data. 
					// 1 returns not able to write (yet). Non-blocking, always.

	int (*CanWrite)();	// returns number of bytes possible to write at a given time. 
						// Never will decrease unless you call Write (or Close, heh)

	int (*IsPlaying)(); // non0 if output is still going or if data in buffers waiting to be
						// written (i.e. closing while IsPlaying() returns 1 would truncate the song

	int (*Pause)(int pause); // returns previous pause state

	void (*SetVolume)(int volume); // volume is 0-255
	void (*SetPan)(int pan); // pan is -128 to 128

	void (*Flush)(int t);	// flushes buffers and restarts output at time t (in ms) 
							// (used for seeking)

	int (*GetOutputTime)(); // returns played time in MS
	int (*GetWrittenTime)(); // returns time written in MS (used for synching up vis stuff)

} Out_Module;

typedef struct 
{
	int version;				// module type (IN_VER)
	char *description;			// description of module, with version string

	HWND hMainWindow;			// winamp's main window (filled in by winamp)
	HINSTANCE hDllInstance;		// DLL instance handle (Also filled in by winamp)

	char *FileExtensions;		// "mp3\0Layer 3 MPEG\0mp2\0Layer 2 MPEG\0mpg\0Layer 1 MPEG\0"
								// May be altered from Config, so the user can select what they want
	
	int is_seekable;			// is this stream seekable? 
	int UsesOutputPlug;			// does this plug-in use the output plug-ins? (musn't ever change, ever :)
													// note that this has turned into a "flags" field
													// see IN_MODULE_FLAG_*

	void (*Config)(HWND hwndParent); // configuration dialog
	void (*About)(HWND hwndParent);  // about dialog

	void (*Init)();				// called at program init
	void (*Quit)();				// called at program quit

	void (*GetFileInfo)(const TCHAR *file, TCHAR *title, int *length_in_ms); // if file == NULL, current playing is used

	int (*InfoBox)(const TCHAR *file, HWND hwndParent);
	
	int (*IsOurFile)(const TCHAR *fn);	// called before extension checks, to allow detection of mms://, etc
	// playback stuff
	int (*Play)(const TCHAR *fn);		// return zero on success, -1 on file-not-found, some other value on other (stopping winamp) error
	void (*Pause)();			// pause stream
	void (*UnPause)();			// unpause stream
	int (*IsPaused)();			// ispaused? return 1 if paused, 0 if not
	void (*Stop)();				// stop (unload) stream

	// time stuff
	int (*GetLength)();			// get length in ms
	int (*GetOutputTime)();		// returns current output time in ms. (usually returns outMod->GetOutputTime()
	void (*SetOutputTime)(int time_in_ms);	// seeks to point in stream (in ms). Usually you signal your thread to seek, which seeks and calls outMod->Flush()..

	// volume stuff
	void (*SetVolume)(int volume);	// from 0 to 255.. usually just call outMod->SetVolume
	void (*SetPan)(int pan);	// from -127 to 127.. usually just call outMod->SetPan
	
	// in-window builtin vis stuff

	void (*SAVSAInit)(int maxlatency_in_ms, int srate);		// call once in Play(). maxlatency_in_ms should be the value returned from outMod->Open()
	// call after opening audio device with max latency in ms and samplerate
	void (*SAVSADeInit)();	// call in Stop()


	// simple vis supplying mode
	void (*SAAddPCMData)(void *PCMData, int nch, int bps, int timestamp); 
											// sets the spec data directly from PCM data
											// quick and easy way to get vis working :)
											// needs at least 576 samples :)

	// advanced vis supplying mode, only use if you're cool. Use SAAddPCMData for most stuff.
	int (*SAGetMode)();		// gets csa (the current type (4=ws,2=osc,1=spec))
							// use when calling SAAdd()
	int (*SAAdd)(void *data, int timestamp, int csa); // sets the spec data, filled in by winamp


	// vis stuff (plug-in)
	// simple vis supplying mode
	void (*VSAAddPCMData)(void *PCMData, int nch, int bps, int timestamp); // sets the vis data directly from PCM data
											// quick and easy way to get vis working :)
											// needs at least 576 samples :)

	// advanced vis supplying mode, only use if you're cool. Use VSAAddPCMData for most stuff.
	int (*VSAGetMode)(int *specNch, int *waveNch); // use to figure out what to give to VSAAdd
	int (*VSAAdd)(void *data, int timestamp); // filled in by winamp, called by plug-in


	// call this in Play() to tell the vis plug-ins the current output params. 
	void (*VSASetInfo)(int srate, int nch); // <-- Correct (benski, dec 2005).. old declaration had the params backwards


	// dsp plug-in processing: 
	// (filled in by winamp, calld by input plug)

	// returns 1 if active (which means that the number of samples returned by dsp_dosamples
	// could be greater than went in.. Use it to estimate if you'll have enough room in the
	// output buffer
	int (*dsp_isactive)(); 

	// returns number of samples to output. This can be as much as twice numsamples. 
	// be sure to allocate enough buffer for samples, then.
	int (*dsp_dosamples)(short int *samples, int numsamples, int bps, int nch, int srate);


	// eq stuff
	void (*EQSet)(int on, char data[10], int preamp); // 0-64 each, 31 is +0, 0 is +12, 63 is -12. Do nothing to ignore.

	// info setting (filled in by winamp)
	void (*SetInfo)(int bitrate, int srate, int stereo, int synched); // if -1, changes ignored? :)

	Out_Module *outMod; // filled in by winamp, optionally used :)
} In_Module;

namespace NES
{
extern int PRGSizeROM, PRGSizeRAM;
extern int PRGMaskROM, PRGMaskRAM;

// Maximum supported data sizes, since it's far easier than dynamically allocating them

// 8192KB PRG ROM
#define	MAX_PRGROM_SIZE	0x800
#define	MAX_PRGROM_MASK	(MAX_PRGROM_SIZE - 1)

// 64KB PRG RAM
#define	MAX_PRGRAM_SIZE	0x10
#define	MAX_PRGRAM_MASK	(MAX_PRGRAM_SIZE - 1)

extern unsigned char PRG_ROM[MAX_PRGROM_SIZE][0x1000];
extern unsigned char PRG_RAM[MAX_PRGRAM_SIZE][0x1000];

enum Region { REGION_NONE, REGION_NTSC, REGION_PAL, REGION_DENDY, REGION_MAX };
extern Region CurRegion;
} // namespace NES

extern	In_Module	mod;

// post this to the main window at end of file (after playback as stopped)
#define WM_WA_MPEG_EOF WM_USER+2

// raw configuration
#define NCH 1
#define SAMPLERATE 44100
#define BPS 16

extern	In_Module mod;
extern	char sample_buffer[576*NCH*(BPS/8)*2]; // sample buffer
