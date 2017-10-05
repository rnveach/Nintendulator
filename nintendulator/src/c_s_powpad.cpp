/* Nintendulator - Win32 NES emulator written in C++
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/nintendulator/trunk/src/c_s_powpad.cpp $
 * $Id: c_s_powpad.cpp 1353 2017-09-23 00:27:51Z quietust $
 */

#include "stdafx.h"
#include "Nintendulator.h"
#include "resource.h"
#include "Movie.h"
#include "Controllers.h"

namespace Controllers
{
#include <pshpack1.h>
struct StdPort_PowerPad_State
{
	unsigned char Bits1;
	unsigned char Bits2;
	unsigned char BitPtr;
	unsigned char Strobe;
	unsigned char NewBit1;
	unsigned char NewBit2;
};
#include <poppack.h>
int	StdPort_PowerPad::Save (FILE *out)
{
	int clen = 0;
	unsigned short len = sizeof(*State);

	writeWord(len);
	writeArray(State, len);

	return clen;
}
int	StdPort_PowerPad::Load (FILE *in, int version_id)
{
	int clen = 0;
	unsigned short len;

	readWord(len);
	readArraySkip(State, len, sizeof(*State));

	return clen;
}
void	StdPort_PowerPad::Frame (unsigned char mode)
{
	int i;
	const unsigned char CBits1[12] = {0x02,0x01,0x00,0x00,0x04,0x10,0x80,0x00,0x08,0x20,0x40,0x00};
	const unsigned char CBits2[12] = {0x00,0x00,0x02,0x01,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x04};
	if (mode & MOV_PLAY)
	{
		State->NewBit1 = MovData[0];
		State->NewBit2 = MovData[1];
	}
	else
	{
		State->NewBit1 = 0;
		State->NewBit2 = 0;
		for (i = 0; i < 12; i++)
		{
			if (IsPressed(Buttons[i]))
			{
				State->NewBit1 |= CBits1[i];
				State->NewBit2 |= CBits2[i];
			}
		}
	}
	if (mode & MOV_RECORD)
	{
		MovData[0] = State->NewBit1;
		MovData[1] = State->NewBit2;
	}
}
unsigned char	StdPort_PowerPad::Read (void)
{
	unsigned char result = 0;
	if (State->Strobe)
	{
		State->Bits1 = State->NewBit1;
		State->Bits2 = State->NewBit2;
		State->BitPtr = 0;

	}
	if (State->BitPtr < 8)
		result |= ((unsigned char)(State->Bits1 >> State->BitPtr) & 1) << 3;
	else	result |= 0x08;
	if (State->BitPtr < 4)
		result |= ((unsigned char)(State->Bits2 >> State->BitPtr) & 1) << 4;
	else	result |= 0x10;
	if ((!State->Strobe) && (State->BitPtr < 8))
		State->BitPtr++;
	return result;
}
void	StdPort_PowerPad::Write (unsigned char Val)
{
	if ((State->Strobe) || (Val & 1))
	{
		State->Strobe = Val & 1;
		State->Bits1 = State->NewBit1;
		State->Bits2 = State->NewBit2;
		State->BitPtr = 0;
	}
}
INT_PTR	CALLBACK	StdPort_PowerPad_ConfigProc (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const int dlgLists[12] = {IDC_CONT_D0,IDC_CONT_D1,IDC_CONT_D2,IDC_CONT_D3,IDC_CONT_D4,IDC_CONT_D5,IDC_CONT_D6,IDC_CONT_D7,IDC_CONT_D8,IDC_CONT_D9,IDC_CONT_D10,IDC_CONT_D11};
	const int dlgButtons[12] = {IDC_CONT_K0,IDC_CONT_K1,IDC_CONT_K2,IDC_CONT_K3,IDC_CONT_K4,IDC_CONT_K5,IDC_CONT_K6,IDC_CONT_K7,IDC_CONT_K8,IDC_CONT_K9,IDC_CONT_K10,IDC_CONT_K11};
	StdPort *Cont;
	if (uMsg == WM_INITDIALOG)
	{
		SetWindowLongPtr(hDlg, GWLP_USERDATA, lParam);
		Cont = (StdPort *)lParam;
	}
	else	Cont = (StdPort *)GetWindowLongPtr(hDlg, GWLP_USERDATA);
	if ((uMsg == WM_COMMAND) && (LOWORD(wParam) == IDC_CONT_FLIP))
	{
		int i;
		int Buttons[12];
		for (i = 0; i < 12; i++)
			Buttons[i] = Cont->Buttons[i];
		Cont->Buttons[0] = Buttons[3];
		Cont->Buttons[1] = Buttons[2];
		Cont->Buttons[2] = Buttons[1];
		Cont->Buttons[3] = Buttons[0];
		Cont->Buttons[4] = Buttons[7];
		Cont->Buttons[5] = Buttons[6];
		Cont->Buttons[6] = Buttons[5];
		Cont->Buttons[7] = Buttons[4];
		Cont->Buttons[8] = Buttons[11];
		Cont->Buttons[9] = Buttons[10];
		Cont->Buttons[10] = Buttons[9];
		Cont->Buttons[11] = Buttons[8];
		for (i = 0; i < 12; i++)
			ConfigButton(&Cont->Buttons[i], Cont->Buttons[i] >> 16, GetDlgItem(hDlg, dlgButtons[i]), FALSE);
		return TRUE;
	}
	return ParseConfigMessages(hDlg, uMsg, wParam, lParam, 12, 0, dlgLists, dlgButtons, Cont ? Cont->Buttons : NULL);
}
void	StdPort_PowerPad::Config (HWND hWnd)
{
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_STDPORT_POWERPAD), hWnd, StdPort_PowerPad_ConfigProc, (LPARAM)this);
}
void	StdPort_PowerPad::SetMasks (void)
{
}
StdPort_PowerPad::~StdPort_PowerPad (void)
{
	delete State;
	delete[] MovData;
}
StdPort_PowerPad::StdPort_PowerPad (DWORD *buttons)
{
	Type = STD_POWERPAD;
	NumButtons = 12;
	Buttons = buttons;
	State = new StdPort_PowerPad_State;
	MovLen = 2;
	MovData = new unsigned char[MovLen];
	ZeroMemory(MovData, MovLen);
	State->Bits1 = 0;
	State->Bits2 = 0;
	State->BitPtr = 0;
	State->Strobe = 0;
	State->NewBit1 = 0;
	State->NewBit2 = 0;
}
} // namespace Controllers
