#include "stdafx.h"
#include "Nintendulator.h"
#include "Debugger.h"
#include "BreakPoints.h"

#ifdef	ENABLE_DEBUGGER

namespace BreakPoints {

struct tBreakPoint 	*list;

void EraseAll() {
	while (list)
	{
		if (list->next)
		{
			list = list->next;
			delete list->prev;
		}
		else
		{
			delete list;
			list = NULL;
		}
	}
}

tBreakPoint* Get(int pos)
{
	if (pos < 0)
		return NULL;

	tBreakPoint *bp = list;

	while (bp)
	{
		if (!pos)
			break;
		bp = bp->next;
		pos--;
	}

	return bp;
}

void Add(tBreakPoint* nbp)
{
	nbp->next = NULL;

	if (list == NULL)
	{
		list = nbp;
		nbp->prev = NULL;
	}
	else
	{
		tBreakPoint *bp = list;

		while (bp->next) {
			bp = bp->next;
		}

		bp->next = nbp;
		nbp->prev = bp;
	}
}

int Delete(int pos)
{
	tBreakPoint *bp = Get(pos);

	if (bp)
	{
		if (bp->prev)	// not first item in list
			bp->prev->next = bp->next;
		else			// first item in list
			list = bp->next;

		if (bp->next)	// not last item in list
		{
			bp->next->prev = bp->prev;
		}
		else
		{
			//scroll selection down one, this is the end of the listbox
			if (pos != 0)
				pos--;
		}

		delete bp;

		return pos;
	}

	return -1;
}

TCHAR* ToString(tBreakPoint* bp)
{
	static TCHAR str[40];

	// +2
	str[0] = bp->type;
	str[1] = ':';

	// +4
	_stprintf(str + 2, _T("%04X"), bp->addr_start);

	// +5
	if (bp->addr_start != bp->addr_end)
	{
		_tcscat(str, _T("-"));

		int len = _tcslen(str);
		_stprintf(str + len, _T("%04X"), bp->addr_end);
	}

	// +2
	_tcscat(str, _T(": "));

	// +6

	if (bp->flag & DEBUG_BREAK_READ)
		_tcscat(str, _T("R"));
	else
		_tcscat(str, _T("-"));

	if (bp->flag & DEBUG_BREAK_WRITE)
		_tcscat(str, _T("W"));
	else
		_tcscat(str, _T("-"));

	if (bp->flag & DEBUG_BREAK_EXEC)
		_tcscat(str, _T("E"));
	else
		_tcscat(str, _T("-"));

	if (bp->flag & DEBUG_BREAK_NMI)
		_tcscat(str, _T("N"));
	else
		_tcscat(str, _T("-"));

	if (bp->flag & DEBUG_BREAK_IRQ)
		_tcscat(str, _T("I"));
	else
		_tcscat(str, _T("-"));

	if (bp->flag & DEBUG_BREAK_BRK)
		_tcscat(str, _T("B"));
	else
		_tcscat(str, _T("-"));

	// +11
	if (!bp->enabled)
		_tcscat(str, _T(" (DISABLED)"));

	return str;
}

} // namespace BreakPoints

#endif	/* !ENABLE_DEBUGGER */
