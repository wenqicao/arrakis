//===-------------------------- random.cpp --------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "random"
#include "system_error"

#ifndef BARRELFISH
#include <fcntl.h>
#include <unistd.h>
#endif
extern "C" {
#include <errno.h>
}

_LIBCPP_BEGIN_NAMESPACE_STD

#ifndef BARRELFISH
random_device::random_device(const string& __token)
    : __f_(open(__token.c_str(), O_RDONLY))
{
    if (__f_ <= 0)
        __throw_system_error(errno, ("random_device failed to open " + __token).c_str());
}

random_device::~random_device()
{
    close(__f_);
}

unsigned
random_device::operator()()
{
    unsigned r;
    read(__f_, &r, sizeof(r));
    return r;
}
#else
random_device::random_device(const string& __token)
{
}

random_device::~random_device()
{
}

unsigned
random_device::operator()()
{
  return 0;
}
#endif

double
random_device::entropy() const
{
    return 0;
}

_LIBCPP_END_NAMESPACE_STD
