#pragma once
/**
 *
 * @details inspired by boost::spirit::x3 forward_ast class
 *
 * @author Thomas Brandstätter
 * @date 11.05.18.
 */



namespace openloco {
namespace lang {
namespace ast {

    template<typename T>
    class forward_ast
    {

    public:

        using type = T;

        /** \addtogroup Constructors */
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

        /** @} */

        ~forward_ast()
        {
            delete _ptr;
        }

        T& get() { return *_ptr; }
        const T& get() const { return *_ptr; }

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