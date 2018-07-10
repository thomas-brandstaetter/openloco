#pragma once
/**
 * @author Thomas Brandstätter
 * @date 07.07.18.
 */

// #include <llvm/IR/Value.h>


class codegen
{
public:
    codegen()
    {
    }
    virtual ~codegen()
    {
    }

    /**
     * codegen
     *
     * AST objects are used to build llvm::Value objects. Implemented methods handles the transformation from AST to
     * LLVM IR. In other words a value is used to build IR code by llvm.
     *
     * @see http://llvm.org/doxygen/classllvm_1_1Value.html
     * @return llvm::Value
     *
     * @todo llvm::value has a protected desctructor
     */
    // virtual llvm::Value * generate() = 0;
};