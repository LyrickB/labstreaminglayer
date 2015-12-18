#ifndef BOOST_ARCHIVE_BASIC_OARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_oarchive.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.lslboost.org/LICENSE_1_0.txt)

//  See http://www.lslboost.org for updates, documentation, and revision history.

#include <cstddef> // NULL
#include <lslboost/config.hpp>
#include <lslboost/noncopyable.hpp>

#include <lslboost/type_traits/broken_compiler_spec.hpp>

// can't use this - much as I'd like to as borland doesn't support it
// #include <lslboost/scoped_ptr.hpp>

#include <lslboost/archive/basic_archive.hpp>
#include <lslboost/serialization/tracking_enum.hpp>

#include <lslboost/archive/detail/abi_prefix.hpp> // must be the last header

namespace lslboost {
namespace serialization {
    class extended_type_info;
} // namespace serialization

namespace archive {
namespace detail {

class basic_oarchive_impl;
class BOOST_ARCHIVE_DECL(BOOST_PP_EMPTY()) basic_oserializer;
class BOOST_ARCHIVE_DECL(BOOST_PP_EMPTY()) basic_pointer_oserializer;
//////////////////////////////////////////////////////////////////////
// class basic_oarchive - write serialized objects to an output stream
class BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY()) basic_oarchive :
    private lslboost::noncopyable
{
    friend class basic_oarchive_impl;
    // hide implementation of this class to minimize header conclusion
    // in client code. note: borland can't use scoped_ptr
    //lslboost::scoped_ptr<basic_oarchive_impl> pimpl;
    basic_oarchive_impl * pimpl;

    // overload these to bracket object attributes. Used to implement
    // xml archives
    virtual void vsave(const version_type t) =  0;
    virtual void vsave(const object_id_type t) =  0;
    virtual void vsave(const object_reference_type t) =  0;
    virtual void vsave(const class_id_type t) =  0;
    virtual void vsave(const class_id_optional_type t) = 0;
    virtual void vsave(const class_id_reference_type t) =  0;
    virtual void vsave(const class_name_type & t) = 0;
    virtual void vsave(const tracking_type t) = 0;
protected:
    basic_oarchive(unsigned int flags = 0);
    // account for bogus gcc warning
    #if defined(__GNUC__)
    virtual
    #endif
    ~basic_oarchive();
public:
    // note: NOT part of the public interface
    void register_basic_serializer(
        const basic_oserializer & bos
    );
    void save_object(
        const void *x, 
        const basic_oserializer & bos
    );
    void save_pointer(
        const void * t, 
        const basic_pointer_oserializer * bpos_ptr
    );
    void save_null_pointer(){
        vsave(NULL_POINTER_TAG);
    }
    // real public interface starts here
    void end_preamble(); // default implementation does nothing
    library_version_type get_library_version() const;
    unsigned int get_flags() const;
};

} // namespace detail
} // namespace archive
} // namespace lslboost

// required by smart_cast for compilers not implementing 
// partial template specialization
BOOST_TT_BROKEN_COMPILER_SPEC(
    lslboost::archive::detail::basic_oarchive
)

#include <lslboost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif //BOOST_ARCHIVE_BASIC_OARCHIVE_HPP