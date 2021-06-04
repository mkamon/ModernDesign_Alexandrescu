#pragma once

namespace widgets
{
    template
    <
        typename T,
        template<typename> class CheckingPolicy,
        template<typename> class ThreadingModel,
        template<typename> class CreationPolicy
    >
    class SmartPtr
            : public CheckingPolicy<T>
            , public ThreadingModel<SmartPtr<T, CheckingPolicy, ThreadingModel, CreationPolicy> >
            , public CreationPolicy<T>
    {
    public:
        void createPointer()
        {
            pointee = CreationPolicy<T>::create();
        }

        T* operator->()
        {
            typename ThreadingModel<SmartPtr>::Lock guard(*this);
            CheckingPolicy<T>::check(pointee);
            return pointee;
        }

        ~SmartPtr()
        {
            if(pointee != nullptr){
                delete pointee;
                pointee = nullptr;
            }
        }

    private:
        T *pointee = nullptr;
    };

}