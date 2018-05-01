
%%

void
openloco::lang::parser::error(const location_type &loc, const std::string& message) {
    std::cerr
        << "parser error at "
        << loc
        << ": " << message << std::endl;
    std::cerr << std::flush;
}
