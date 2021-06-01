#pragma once
#include <cstdlib>
#include <memory>
namespace policy
{
    template <typename T>
    struct OpNewCreator
    {
        [[nodiscard]] static T* create()
        {
            return new T;
        }

    protected:
        virtual ~OpNewCreator() = default;
    };

    template <typename  T>
    struct MallocCreator
    {
        [[nodiscard]] static T* create()
        {
            void *buf = std::malloc(sizeof(T));
            if(buf == nullptr){
                return nullptr;
            }
            return new(buf) T;
        }
    protected:
        virtual ~MallocCreator() = default;
    };

    template <typename T>
    struct PrototypeCreator
    {
        explicit PrototypeCreator(T* _prototype = nullptr)
                : prototype{_prototype}
        {}

        [[nodiscard]] T* create() const
        {
            return prototype == nullptr ? nullptr : prototype->clone();
        }

        [[nodiscard]] T* getPrototype() noexcept {
            return prototype.get();
        }
        void setPrototype(T* _prototype) noexcept {
            prototype.reset(_prototype);
        }
    private:
        std::unique_ptr<T> prototype = nullptr;

    protected:
        virtual ~PrototypeCreator() = default;
    };

}


