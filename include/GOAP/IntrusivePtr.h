/*
* Copyright (C) 2017, Levchenko Yuriy <irov13@mail.ru>
*
* This software may be modified and distributed under the terms
* of the MIT license.  See the LICENSE file for details.
*/

#	pragma once

#   include <cstddef>

namespace GOAP
{
    namespace Detail
    {
        template<class T>
        class IntrusivePtr
        {
        public:
            typedef T element_type;

        public:
            inline static const IntrusivePtr & none()
            {
                static IntrusivePtr ptr_none;

                return ptr_none;
            }

        public:
            inline IntrusivePtr()
                : m_ptr( nullptr )
            {
            }

            inline IntrusivePtr( std::nullptr_t )
                : m_ptr( nullptr )
            {
            }

            inline IntrusivePtr( const element_type * _ptr )
                : m_ptr( const_cast<element_type *>(_ptr) )
            {
                this->incref();
            }

            template<class U>
            inline IntrusivePtr( const U * _ptr )
                : m_ptr( static_cast<element_type *>(const_cast<U *>(_ptr)) )
            {
                this->incref();
            }

            inline IntrusivePtr( const IntrusivePtr & _rhs )
                : m_ptr( _rhs.get() )
            {
                this->incref();
            }

            template<class U>
            inline IntrusivePtr( const IntrusivePtr<U> & _rhs )
                : m_ptr( static_cast<T *>(_rhs.get()) )
            {
                this->incref();
            }

            inline ~IntrusivePtr()
            {
                this->decref();
            }

            inline IntrusivePtr & operator = ( const IntrusivePtr & _rhs )
            {
                IntrusivePtr swap_ptr( _rhs );
                swap_ptr.swap( *this );

                return *this;
            }

            inline IntrusivePtr & operator = ( element_type * _rhs )
            {
                IntrusivePtr swap_ptr( _rhs );
                swap_ptr.swap( *this );

                return *this;
            }

            inline IntrusivePtr & operator = ( std::nullptr_t )
            {
                this->decref();
                m_ptr = nullptr;

                return *this;
            }

        public:
            inline element_type * get() const
            {
                return m_ptr;
            }

            template<class K>
            inline K getT() const
            {
                K ptr_t = static_cast<K>(m_ptr);

                return ptr_t;
            }

            inline element_type * operator -> () const
            {
                return m_ptr;
            }

            inline void swap( IntrusivePtr & _rhs )
            {
                T * tmp = m_ptr;
                m_ptr = _rhs.m_ptr;
                _rhs.m_ptr = tmp;
            }

        protected:
            inline void incref()
            {
                if( m_ptr != nullptr )
                {
                    T::IntrusivePtrAddRef( m_ptr );
                }
            }

            inline void decref()
            {
                if( m_ptr != nullptr )
                {
                    T::IntrusivePtrDecRef( m_ptr );
                }
            }

        protected:
            element_type * m_ptr;
        };
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        inline void swap( const IntrusivePtr<T> & _left, const IntrusivePtr<T> & _right )
        {
            _left.swap( _right );
        }
        //////////////////////////////////////////////////////////////////////////
        template<class U, class T>
        inline U intrusive_static_cast( const IntrusivePtr<T> & _iptr )
        {
            typedef typename U::element_type U_type;

            T * t_ptr = _iptr.get();
            U_type * u_ptr = static_cast<U_type *>(t_ptr);

            return U( u_ptr );
        }
        //////////////////////////////////////////////////////////////////////////
        template<class U, class T>
        inline U intrusive_dynamic_cast( const IntrusivePtr<T> & _iptr )
        {
            typedef typename U::element_type U_type;

            T * t_ptr = _iptr.get();
            U_type * u_ptr = dynamic_cast<U_type *>(t_ptr);

            return U( u_ptr );
        }
        //////////////////////////////////////////////////////////////////////////
        template<class U, class T>
        inline U intrusive_get( const IntrusivePtr<T> & _iptr )
        {
            T * t_ptr = _iptr.get();
            U u_ptr = static_cast<U>(t_ptr);

            return u_ptr;
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        inline bool operator < ( const IntrusivePtr<T> & _left, const IntrusivePtr<T> & _right )
        {
            const T * l = _left.get();
            const T * r = _right.get();

            return l < r;
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        inline bool operator >( const IntrusivePtr<T> & _left, const IntrusivePtr<T> & _right )
        {
            const T * l = _left.get();
            const T * r = _right.get();

            return l > r;
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        inline bool operator == ( const IntrusivePtr<T> & _left, const IntrusivePtr<T> & _right )
        {
            const T * l = _left.get();
            const T * r = _right.get();

            return l == r;
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        inline bool operator != ( const IntrusivePtr<T> & _left, const IntrusivePtr<T> & _right )
        {
            return !(_left == _right);
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        inline bool operator != ( const IntrusivePtr<T> & _left, const U * _right )
        {
            const T * ptr = _left.get();

            return ptr != static_cast<const T *>(_right);
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        inline bool operator != ( const U * _left, const IntrusivePtr<T> & _right )
        {
            const T * ptr = intrusive_get<T>( _right );

            return ptr != static_cast<const T *>(_left);
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        inline bool operator == ( const U * _left, const IntrusivePtr<T> & _right )
        {
            return !(_left != _right);
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        inline bool operator == ( const IntrusivePtr<T> & _left, const U * _right )
        {
            return !(_left != _right);
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        inline bool operator != ( const IntrusivePtr<T> & _left, std::nullptr_t )
        {
            const T * ptr = _left.get();

            return ptr != nullptr;
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        inline bool operator != ( std::nullptr_t, const IntrusivePtr<T> & _right )
        {
            const T * ptr = intrusive_get<T *>( _right );

            return ptr != nullptr;
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        inline bool operator == ( std::nullptr_t, const IntrusivePtr<T> & _right )
        {
            const T * ptr = intrusive_get<T *>( _right );

            return ptr == nullptr;
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        inline bool operator == ( const IntrusivePtr<T> & _left, std::nullptr_t )
        {
            const T * ptr = _left.get();

            return ptr == nullptr;
        }
    }
}