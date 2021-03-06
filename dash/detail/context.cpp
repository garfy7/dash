
/* Copyright (c) 2011-2012, EPFL/Blue Brain Project
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

#include "context.h"

#include "attribute.h"
#include "change.h"
#include "commit.h"
#include "node.h"

#include <dash/context.h>
#include <dash/node.h>
#include <lunchbox/atomic.h>

namespace dash
{
namespace detail
{

namespace
{
lunchbox::a_ssize_t numSlots_;
LFVector< size_t, 32 > freeSlots_;

static size_t allocSlot_()
{
    size_t slot = 0;
    if( freeSlots_.pop_back( slot ))
        return slot;
    return ((++numSlots_) - 1);
}

class MapVisitor : public dash::Node::Visitor
{
public:
    MapVisitor( const Context& from, const Context& to )
            : from_( from ), to_( to ) {}
    virtual ~MapVisitor() {}

    virtual VisitorResult visitDown( dash::NodePtr node )
        {
            node->getImpl()->map( from_, to_ );
            return ACCEPT_CONTINUE;
        }

    virtual VisitorResult visit( dash::AttributePtr attribute )
        {
            attribute->getImpl()->map( from_, to_ );
            return ACCEPT_CONTINUE;
        }

private:
    const Context& from_;
    const Context& to_;
};

class UnmapVisitor : public dash::Node::Visitor
{
public:
    UnmapVisitor( Context& context ) : context_( context ) {}
    virtual ~UnmapVisitor() {}

    virtual VisitorResult visitUp( dash::AttributePtr attribute )
        {
            attribute->getImpl()->unmap( context_ );
            return ACCEPT_CONTINUE;
        }

    virtual VisitorResult visitUp( dash::NodePtr node )
        {
            node->getImpl()->unmap( context_ );
            return ACCEPT_CONTINUE;
        }

private:
    Context& context_;
};

}

Context::Context()
        : slot_( allocSlot_( ))
        , commit_()
{
}

Context::~Context()
{
    LBASSERTINFO( commit_.empty(), "Destroyed context has active changes");

    freeSlots_.push_back( slot_ );
    if( slot_ == 0 ) // main context dtor
    {
        LBASSERTINFO( int32_t( freeSlots_.size( )) == numSlots_,
                      "Active context during main context destruction? : " <<
                      freeSlots_.size() << " != " << numSlots_ );
        freeSlots_.clear();
        numSlots_ = 0;
    }
}

Context& Context::getCurrent()
{
    return dash::Context::getCurrent().getImpl();
}

size_t Context::getNumSlots()
{
    return numSlots_;
}

void Context::map( dash::NodePtr node, const Context& to )
{
    if( !commit_.empty( ))
    {
        std::stringstream out;
        out << "Source dash::context.has pending changes: " << commit_
            << ", called from " << lunchbox::backtrace;
        throw std::runtime_error( out.str( ));
    }

    MapVisitor mapper( *this, to );
    node->accept( mapper );
}

void Context::unmap( dash::NodePtr node )
{
    UnmapVisitor unmapper( *this );
    node->accept( unmapper );
}

void Context::map( AttributePtr attribute, const Context& to )
{
    attribute->map( *this, to );
}

void Context::unmap( AttributePtr attribute )
{
    attribute->unmap( *this );
}

void Context::addChange( const ContextChange& change )
{
    if( numSlots_ > 1 ) // OPT: Single context does not need to record changes
        commit_.add( change );
}

dash::Commit Context::commit()
{
    LB_TS_SCOPED( thread_ );

    dash::Commit current;
    *current.getImpl() = commit_;
    commit_ = ContextCommit();
    return current;
}

void Context::apply( ConstCommitPtr cmt )
{
    LB_TS_SCOPED( thread_ );
    cmt->apply();
}

}
}
