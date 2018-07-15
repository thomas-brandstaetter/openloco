# docs to read

* [LLVM Language Reference Manual](https://llvm.org/docs/LangRef.html)
* [WritingAnLLVMBackend](https://llvm.org/docs/WritingAnLLVMBackend.html)
* [The LLVM Target-Independent Code Generator](https://llvm.org/docs/CodeGenerator.html)


# AST

* Don't use C++ types in the AST in order to distinguish types in code generator visitors. For example, if there are more 
  than one std::string ast types, then you cannot distinguish between them in visitors
  
* Name the members of a AST object according to their semantics 
    