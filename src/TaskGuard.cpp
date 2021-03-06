/*
* Copyright (C) 2017, Levchenko Yuriy <irov13@mail.ru>
*
* This software may be modified and distributed under the terms
* of the MIT license.  See the LICENSE file for details.
*/

#	include "GOAP/TaskGuard.h"
#	include "GOAP/GuardProvider.h"

namespace GOAP
{
	//////////////////////////////////////////////////////////////////////////
	TaskGuard::TaskGuard(const GuardProviderPtr & _begin, const GuardProviderPtr & _end)
        : Task( TASK_EVENT_RUN | TASK_EVENT_CANCEL )
		, m_begin(_begin)
		, m_end(_end)
	{}
	//////////////////////////////////////////////////////////////////////////
	TaskGuard::~TaskGuard()
	{}
	//////////////////////////////////////////////////////////////////////////
	bool TaskGuard::_onRun()
	{		
		m_begin->onGuard();

		return false;
	}
	//////////////////////////////////////////////////////////////////////////
	void TaskGuard::_onCancel()
	{
		m_end->onGuard();
	}
}
