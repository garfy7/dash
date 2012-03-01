
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

#ifndef DASH_DETAIL_TYPES_H
#define DASH_DETAIL_TYPES_H

#include <dash/types.h>
#include <dash/Vector.h>
#include <boost/any.hpp>
#include <vector>


namespace dash
{
namespace test
{
int main( int argc, char **argv ); //!< @internal
}

namespace detail
{

template< class T > class ContextPtr;

struct Change;
typedef Vector< Change, 32 > Changes;
typedef std::tr1::shared_ptr< Changes > ChangesPtr;
typedef Changes::iterator ChangesIter;
typedef Changes::const_iterator ChangesCIter;

class Node;
typedef co::base::RefPtr< Node > NodePtr;
typedef co::base::RefPtr< const Node > NodeConstPtr;

typedef std::vector< Node* > Parents;
typedef Parents::iterator ParentsIter;
typedef Parents::const_iterator ParentsCIter;
typedef ContextPtr< Parents > ParentsCtxPtr;

typedef std::vector< dash::NodePtr > Children;
typedef Children::iterator ChildrenIter;
typedef Children::const_iterator ChildrenCIter;
typedef ContextPtr< Children > ChildrenCtxPtr;

class Attribute;
typedef co::base::RefPtr< Attribute > AttributePtr;
typedef co::base::RefPtr< const Attribute > AttributeConstPtr;
typedef Attributes::iterator AttributesIter;
typedef Attributes::const_iterator AttributesCIter;
typedef ContextPtr< dash::Attributes > AttributesCtxPtr;

typedef ContextPtr< boost::any > AnyCtxPtr;
}
}

#endif // DASH_DETAIL_TYPES_H