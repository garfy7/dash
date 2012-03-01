
/* Copyright (c) 2011, EFPL/Blue Brain Project
 *                     Stefan Eilemann <stefan.eilemann@epfl.ch>
 *
 * This file is part of DASH <https://github.com/BlueBrain/dash>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *  
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "Attribute.h"

#include "detail/Attribute.h"

namespace dash
{
Attribute::Attribute()
{
    init_();
}

Attribute::Attribute( const Attribute& from )
        : Referenced( from )
{
    impl_ = new detail::Attribute( this, from.impl_ );
    impl_->ref( CO_REFERENCED_PARAM );
}

void Attribute::init_()
{
    impl_ = new detail::Attribute( this );
    impl_->ref( CO_REFERENCED_PARAM );
}

Attribute::~Attribute()
{
    impl_->orphan();
    impl_->unref( CO_REFERENCED_PARAM );
}

Attribute& Attribute::operator = ( const Attribute& from )
{
    if( this == &from )
        return *this;
    *impl_ = *from.impl_;
    return *this;
}

Attribute& Attribute::set_( const boost::any& value )
{
    impl_->set( value );
    return *this;
}

boost::any& Attribute::get_()
{
    return impl_->get();
}

const boost::any& Attribute::get_() const
{
    return impl_->get();
}


}