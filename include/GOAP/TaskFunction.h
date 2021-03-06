/*
* Copyright (C) 2017, Levchenko Yuriy <irov13@mail.ru>
*
* This software may be modified and distributed under the terms
* of the MIT license.  See the LICENSE file for details.
*/

#	pragma once

#	include "GOAP/Task.h"

namespace GOAP
{
	typedef IntrusivePtr<class FunctionProvider> FunctionProviderPtr;

	class TaskFunction
		: public Task
	{
	public:
		TaskFunction( const FunctionProviderPtr & _provider );
		~TaskFunction();

	public:
		bool _onRun() override;

	protected:
		FunctionProviderPtr m_provider;
	};

	typedef IntrusivePtr<TaskFunction> TaskFunctionPtr;
}