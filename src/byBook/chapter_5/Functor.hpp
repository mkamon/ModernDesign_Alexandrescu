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
    virtual FunctorImpl* clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename R, typename P1>
class FunctorImpl<R, TYPELIST_1(P1)>
{
public:
    virtual R operator()(P1) = 0;
    virtual FunctorImpl* clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename R, typename P1, typename P2>
class FunctorImpl<R, TYPELIST_2(P1, P2)>
{
public:
    virtual R operator()(P1, P2) = 0;
    virtual FunctorImpl* clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename R, typename P1, typename P2, typename P3>
class FunctorImpl<R, TYPELIST_3(P1, P2, P3)>
{
public:
    virtual R operator()(P1, P2, P3) = 0;
    virtual FunctorImpl* clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename ParentFunctor, typename Fun>
class FunctorHandler : public FunctorImpl
    <
        typename ParentFunctor::ResultType,
        typename ParentFunctor::ParamList
    >
{
public:
    using ResultType = typename ParentFunctor::ResultType;

    FunctorHandler(const Fun& fun) : fun{fun} {}
    FunctorHandler* clone() const override
    {
        return new FunctorHandler(*this);
    }

    ResultType operator()()
    {
        return fun();
    }

    ResultType operator()(typename ParentFunctor::Param1 p1)
    {
        return fun(p1);
    }

    ResultType operator()(typename ParentFunctor::Param1 p1, typename ParentFunctor::Param2 p2)
    {
        return fun(p1, p2);
    }
private:
    Fun fun;
};

template <typename ParentFunctor, typename PointerToObj, typename PointerToMemFn>
class MemFunHandler : public FunctorImpl
    <
        typename ParentFunctor::ResultType,
        typename ParentFunctor::ParamList
    >
{
public:
    using ResultType = typename ParentFunctor::ResultType;

    MemFunHandler(const PointerToObj& pObj, PointerToMemFn pMemFn)
        : pObj{pObj}, pMemFn{pMemFn}
    {}

    MemFunHandler* clone() const override
    {
        return new MemFunHandler(*this);
    }

    ResultType operator()()
    {
        return ((*pObj).*pMemFn)();
    }

    ResultType operator()(typename ParentFunctor::Param1 p1)
    {
        return ((*pObj).*pMemFn)(p1);
    }

    ResultType operator()(typename ParentFunctor::Param1 p1, typename ParentFunctor::Param2 p2)
    {
        return ((*pObj).*pMemFn)(p1, p2);
    }
private:
    PointerToObj pObj;
    PointerToMemFn pMemFn;
};

template <typename R, class TList>
class Functor
{
    using Impl = FunctorImpl<R, TList>;
    std::unique_ptr<Impl> pImpl;
public:
    using ParamList = TList;
    using ResultType = R;
    using Param1 = typename TL::TypeAtNonStrict<TList, 0, EmptyType>::Result;
    using Param2 = typename TL::TypeAtNonStrict<TList, 1, EmptyType>::Result;
    using Param3 = typename TL::TypeAtNonStrict<TList, 2, EmptyType>::Result;

    Functor();

    template <typename Fun>
    Functor(const Fun&);

    template <typename PtrObj, typename MemFun>
    Functor(const PtrObj&, const MemFun&);

    Functor &operator=(const Functor&);
    explicit Functor(std::unique_ptr<Impl> pImpl);

    R operator()(){
        return (*pImpl)();
    }
    R operator()(Param1 p1){
        return (*pImpl)(p1);
    }
    R operator()(Param1 p1, Param2 p2){
        return (*pImpl)(p1, p2);
    }
    R operator()(Param1 p1, Param2 p2, Param3 p3){
        return (*pImpl)(p1, p2, p3);
    }
};

template <typename R, class TList>
template <class Fun>
Functor<R, TList>::Functor(const Fun& fun)
    : pImpl{std::make_unique<FunctorHandler<Functor, Fun>>(fun)}
{
}

template <typename R, class TList>
template <typename PtrObj, typename MemFun>
Functor<R, TList>::Functor(const PtrObj& p, const MemFun& memFn)
    : pImpl{std::make_unique<MemFunHandler<Functor, PtrObj, MemFun>>(p, memFn)}
{};
