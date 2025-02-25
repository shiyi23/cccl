//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <iterator>

// move_iterator

// reference operator*() const;
//
//  constexpr in C++17

#include <iterator>
#include <cassert>
#include <memory>

#include "test_iterators.h"
#include "test_macros.h"

class A
{
    int data_;
public:
    A() : data_(1) {}
    ~A() {data_ = -1;}

    friend bool operator==(const A& x, const A& y)
        {return x.data_ == y.data_;}
};

template <class It>
void
test(It i, typename std::iterator_traits<It>::value_type x)
{
    std::move_iterator<It> r(i);
    assert(*r == x);
    typename std::iterator_traits<It>::value_type x2 = *r;
    assert(x2 == x);
}

struct do_nothing
{
    void operator()(void*) const {}
};


int main(int, char**) {
  {
    A a;
    test(&a, A());
  }
  {
    int i;
    std::unique_ptr<int, do_nothing> p(&i);
    test(&p, std::unique_ptr<int, do_nothing>(&i));
  }
#if TEST_STD_VER > 2014
  {
    constexpr const char *p = "123456789";
    typedef std::move_iterator<const char *> MI;
    constexpr MI it1 = std::make_move_iterator(p);
    constexpr MI it2 = std::make_move_iterator(p+1);
    static_assert(*it1 == p[0], "");
    static_assert(*it2 == p[1], "");
  }
#endif

#if TEST_STD_VER > 2017
  // Ensure the `iter_move` customization point is being used.
  {
    int a[] = {0, 1, 2};

    int iter_moves = 0;
    adl::Iterator i = adl::Iterator::TrackMoves(a, iter_moves);
    std::move_iterator<adl::Iterator> mi(i);

    auto x = *mi;
    assert(x == 0);
    assert(iter_moves == 1);
  }
#endif

  return 0;
}
