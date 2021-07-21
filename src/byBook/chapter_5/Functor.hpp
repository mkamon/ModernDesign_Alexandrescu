#pragma once

#include <memory>
#include "chapter_3/TypeList.hpp"


template <typename R, typename TList>
class FunctorImpl;

template <typename R>
class FunctorImpl<R, NullType>
{
public:
    virtual R operator()() = 0;
    virtual FunctorImpl *clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename R, typename P1>
class FunctorImpl<R, TYPELIST_1(P1)>
{
public:
    virtual R operator()(P1) = 0;
    virtual FunctorImpl *clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename R, typename P1, typename P2>
class FunctorImpl<R, TYPELIST_2(P1, P2)>
{
public:
    virtual R operator()(P1, P2) = 0;
    virtual FunctorImpl *clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename R, typename P1, typename P2, typename P3>
class FunctorImpl<R, TYPELIST_3(P1, P2, P3)>
{
public:
    virtual R operator()(P1, P2, P3) = 0;
    virtual FunctorImpl *clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename R, class TList>
class Functor
{
    Functor();
    Functor(const Functor &);
    Functor &operator(const Functor&);
    explicit Funcor(std::unique_ptr<Functor> pImpl);

private:
    using Impl = Functor<R, TList>;
    std::unique_ptr<Impl> pImpl;

};



