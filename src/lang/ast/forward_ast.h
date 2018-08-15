#pragma once
/**
 * @author Thomas Brandstätter
 * @date 11.05.18.
 */



namespace openloco {
namespace lang {
namespace ast {

    /**
     * forward_ast
     *
     * The grammer to define has circular dependencies, e.g. between IEC 61131-3 arrays and structures.
     * C++ is not able to reflect such dependencies in the type system, therefore we break the circle with a forward
     * declaration on type basis.
     *
     * @tparam T The type to forward
     */
    template<typename T>
    class forward_ast
    {
    public:

        /** \addtogroup Object lifecycle */
        /** @{ */

        forward_ast() : _ptr(new T)
        {
        }

        forward_ast(forward_ast const& operand)
            : _ptr(new T(operand.get())) {}

        forward_ast(forward_ast&& operand)
            : _ptr(operand._ptr)
        {
            operand._ptr = nullptr;
        }

        forward_ast(T const& operand)
            : _ptr(new T(operand))
        {
        }

        forward_ast(T&& operand)
            : _ptr(new T(std::move(operand)))
        {
        }

        ~forward_ast()
        {
            delete _ptr;
        }

        /** @} */

        /** \addtogroup Observers */
        /** @{ */

        T& get() { return *_ptr; }
        const T& get() const { return *_ptr; }

        /** @} */

        /** \addtogroup Operators */
        /** @{ */

        forward_ast& operator=(forward_ast const& rhs)
        {
            assign(rhs.get());
            return *this;
        }

        forward_ast& operator=(forward_ast&& rhs)
        {
            swap(rhs);
            return *this;
        }

        forward_ast& operator=(T&& rhs)
        {
            get() = std::move(rhs);
            return *this;
        }

        operator T const &() const { return this->get(); }
        operator T &() { return this->get(); }

        /** @} */

    private:


        void swap(forward_ast& rhs)
        {
            T* temp = rhs._ptr;
            rhs._ptr = _ptr;
            _ptr = temp;
        }

        void assign(const T& rhs) { this->get() = rhs; }

        T* _ptr;
    };


}}}