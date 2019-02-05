#pragma once
/**
 * @author Thomas Brandstätter
 * @date 07.07.18
 */

#include <ostream>

//#include <llvm/IR/LLVMContext.h>
//#include <llvm/IR/Module.h>


namespace openloco {
namespace lang {

    /**
     * The entry point for emitting code for a llvm module.
     */
    class CodeGenerator
    {
    public:
        /** @addtogroup Object lifecycle */
        /** @{ */

        CodeGenerator( //llvm::LLVMContext &context,
                        std::ostream& output)
            //: context_(context),
            : output_(output) {}

        /** @} */

        /** @addtogroup Emitter */
        /** @{ */

        void emit(/*llvm::Module &*/);

        /** @} */

    protected:
        void pre_emit()  {}  /**< executed before children will emitting code; */
        void post_emit() {}  /**< executed after all children have emitted code; */

    private:
        //llvm::LLVMContext& context_;
        std::ostream& output_;
    };

}}
