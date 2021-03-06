/*
* Copyright (C) 2017, Levchenko Yuriy <irov13@mail.ru>
*
* This software may be modified and distributed under the terms
* of the MIT license.  See the LICENSE file for details.
*/

#	pragma once

#	include "GOAP/Config.h"

namespace GOAP
{
	class IfProvider
		: public Factorable
	{
	public:
		virtual bool onIf() = 0;
	};

	typedef IntrusivePtr<IfProvider> IfProviderPtr;

	template<class F>
	class IfProviderT
		: public IfProvider
	{
	public:
		IfProviderT( F _f )
			: m_f( _f )
		{
		}

	public:
		bool onIf() override
		{
			bool result = m_f();

			return result;
		}

	protected:
		F m_f;
	};

	template<class F>
	IfProviderPtr makeIfProvider( F _f )
	{
		IfProviderPtr provider = GOAP_NEW IfProviderT<F>( _f );

		return provider;
	}
}