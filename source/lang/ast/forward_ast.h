#pragma once
/**
 * @author Thomas Brandstätter
 * @date 11.05.18.
 */



namespace openloco {
namespace lang {
namespace ast {

    /**
     * ForwardAst
     *
     * The grammer to define has circular dependencies, e.g. between IEC 61131-3 arrays and structures.
     * C++ is not able to reflect such dependencies in the type system, therefore we break the circle with a forward
     * declaration on type basis.
     *
     * @tparam T The type to forward
     */
    template<typename T>
    class ForwardAst
    {
    public:

        /** \addtogroup Object lifecycle */
        /** @{ */

        ForwardAst() : _ptr(new T)
        {
        }

        ForwardAst(ForwardAst const& operand)
            : _ptr(new T(operand.get())) {}

        ForwardAst(ForwardAst&& operand) noexcept
            : _ptr(operand._ptr)
        {
            operand._ptr = nullptr;
        }

        explicit ForwardAst(T const& operand)
            : _ptr(new T(operand))
        {
        }

        explicit ForwardAst(T&& operand)
            : _ptr(new T(std::move(operand)))
        {
        }

        ~ForwardAst()
        {
            delete _ptr;
        }

        /** @} */

        /** \addtogroup Observers */
        /** @{ */

        T& get() { return *_ptr; }  // FIXME: Do I really want this?
        const T& get() const { return *_ptr; }

        /** @} */

        /** \addtogroup Operators */
        /** @{ */

        ForwardAst& operator=(ForwardAst const& rhs)
        {
            assign(rhs.get());
            return *this;
        }

        ForwardAst& operator=(ForwardAst&& rhs) noexcept
        {
            swap(rhs);
            return *this;
        }

        ForwardAst& operator=(T&& rhs)
        {
            get() = std::move(rhs);
            return *this;
        }

        operator T const &() const { return this->get(); }
        operator T &() { return this->get(); }

        /** @} */

    private:


        void swap(ForwardAst& rhs)
        {
            T* temp = rhs._ptr;
            rhs._ptr = _ptr;
            _ptr = temp;
        }

        void assign(const T& rhs) { this->get() = rhs; }

        T* _ptr;
    };


}}}