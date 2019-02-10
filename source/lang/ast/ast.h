#pragma once
/**
 *
 *
 * @details The hierachical structure of types as defined in IEC-61131 is encoded in
 * the type inheritance.
 *
 * @author Thomas Brandstätter
 * @date 27.01.19.
 */

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>
#include <variant>

#include "forward_ast.h"
#include "meta.h"

namespace openloco {
namespace lang {
namespace ast {

    /**
     * value_wrapper
     *
     * On some places cpp requires non-fundamental types, therefore we wrap it.
     *
     * @see https://en.cppreference.com/w/cpp/language/types
     * @tparam FT The fundamental type to wrap
     */
    template<typename FT>
    struct ValueWrapper
    {
        ValueWrapper() : value() {}
        virtual ~ValueWrapper() {}
        FT value;
    };

    /**
     *
     * @tparam VT The variant types
     */
    template<typename ...VT>
    struct Variant : public std::variant<VT...>
    {
        typedef std::variant<VT...> base;
        using base::base;
        using base::operator=;

        base value;
        base operator()()
        {
            return value;
        }
    };


    /**
     * type_declaration_base
     *
     * All type declarations in IEC 61131-3 have the same structure, this struct implements the common structure.
     *
     * @tparam TNT The type name type
     * @tparam ST The specification type
     * @tparam VT The value type
     */
    template<typename TNT, typename ST, typename VT>
    struct TypeDeclarationBase {

        virtual ~TypeDeclarationBase() = default;

        struct SpecInit
        {
            ST specification;
            VT value;
        };

        void set_spec_init(SpecInit si)
        {
            specification = si.specification;
            value = si.value;
        }

        TNT type_name;
        ST specification;
        VT value;
    };

#pragma mark - B.1 Common elements
#pragma mark - B.1.1 Letters, digits and identifiers

    struct Identifier : public ValueWrapper<std::string>
    {
    };

#pragma mark - B.1.2.1 Numeric literals

    template <typename T>
    struct Elementary : ValueWrapper<T> {
        Elementary() : typeSize(sizeof(T)) {}
        ~Elementary() override = default;
        Elementary(const Elementary &) = default;
        Elementary& operator=(const Elementary& rhs) = default;

        const unsigned int typeSize;
    };

    template <typename T>
    struct Numeric : public Elementary<T>
    {
    };

    template<typename T>
    struct IntegerBase : Elementary<T>
    {
        static const T s_kInfinum  = 0;
        static const T s_kSupremum = 0 - 1;
    };

    struct USINT : public IntegerBase<uint8_t> {};
    struct UINT  : public IntegerBase<uint16_t> {};
    struct UDINT : public IntegerBase<uint32_t> {};
    struct ULINT : public IntegerBase<uint64_t> {};

    struct Integer : Variant<USINT, UINT, UDINT, ULINT>
    {
        using base = Variant<USINT, UINT, UDINT, ULINT>;
        using base::base;
    };

    template<typename T>
    struct SignedIntegerBase : IntegerBase<T>
    {
    public:
        static const T s_kInfinum = (1 << (sizeof(T) - 1));
        static const T s_kSupremum = ((1 << (sizeof(T) - 1))-1); // FIXME: 0-1
    };

    struct SINT : public SignedIntegerBase<int8_t> {};
    struct INT  : public SignedIntegerBase<int16_t> {};
    struct DINT : public SignedIntegerBase<int32_t> {};
    struct LINT : public SignedIntegerBase<int64_t> {};

    struct SignedInteger : Variant<SINT, INT, DINT, LINT>
    {
        using base_type = Variant<SINT, INT, DINT, LINT>;
        using base_type::base_type;
    };

    struct BinaryInteger : ValueWrapper<unsigned long>
    {
    };

    struct OctalInteger : ValueWrapper<unsigned long>
    {
    };

    struct HexInteger : ValueWrapper<unsigned long>
    {
    };

    struct BooleanLiteral : ValueWrapper<unsigned long>
    {
    };

    struct BitStringLiteral : Variant<BinaryInteger, OctalInteger, HexInteger> // FIXME: add Integer
    {
        using base = Variant<BinaryInteger, OctalInteger, HexInteger>;
        using base::base;
    };

    struct IntegerLiteral : Variant<BinaryInteger, OctalInteger, HexInteger> // FIXME: add Integer
    {
        using base = Variant<BinaryInteger, OctalInteger, HexInteger>;
        using base::base;

        enum class integer_type_name;
        integer_type_name type_name;
    };

    struct RealLiteral : public ValueWrapper<double>
    {
    };

    struct NumericLiteral : Variant<IntegerLiteral, RealLiteral>
    {
        using base = Variant<IntegerLiteral, RealLiteral>;
        using base::base;
    };

#pragma mark - B.1.2.2 Character Strings

    struct SingleByteCharacterString : public ValueWrapper<std::string>
    {
        using base = ValueWrapper<std::string>;
        using base::base;
    };

    struct DoubleByteCharacterString : ValueWrapper<std::wstring>
    {
        using base = ValueWrapper<std::wstring>;
        using base::base;
    };

    struct CharacterString : Variant<SingleByteCharacterString, DoubleByteCharacterString>
    {
        using base = Variant<SingleByteCharacterString, DoubleByteCharacterString>;
        using base::base;
    };

#pragma mark - B.1.2.3 Time literals


#pragma mark - B.1.2.3.1 Duration

    struct Days : ValueWrapper<double>
    {
        using base = ValueWrapper<double>;
        using base::base;
    };

    struct Interval : Days
    {
    };

    struct Duration : Interval
    {
        Duration& operator=(const Interval rhs)
        {
            value = rhs.value;
            return *this;
        }
    };

    struct FixedPoint : ValueWrapper<double>
    {
        using base = ValueWrapper<double>;
        using base::base;
    };

#pragma mark B.1.2.3.2 Time of day and date

    struct Daytime
    {
        ValueWrapper<double> hour;
        ValueWrapper<double> minute;
        ValueWrapper<double> second;
    };

    struct TimeOfDay : Daytime
    {
        TimeOfDay & operator=(Daytime & rhs)
        {
            std::swap(hour, rhs.hour);
            std::swap(minute, rhs.minute);
            std::swap(second, rhs.second);
            return *this;
        }
    };

    struct DateLiteral
    {
        long year;
        long month;
        long day;
    };

    struct DateAndTime
    {
        DateLiteral date;
        Daytime time;
    };

    struct TimeLiteral : Variant<Duration, TimeOfDay, DateLiteral, DateAndTime>
    {
        using base = Variant<Duration, TimeOfDay, DateLiteral, DateAndTime>;
        using base::base;

    };

    struct Constant : Variant<
            NumericLiteral,
            TimeLiteral,
            BitStringLiteral,
            BooleanLiteral,
            CharacterString>
    {
        using base = Variant<
            NumericLiteral,
            TimeLiteral,
            BitStringLiteral,
            BooleanLiteral,
            CharacterString>;
        using base::base;

    };



#pragma mark - B.1.3 Data types


#pragma mark B.1.3.1 Elementary data types

//    enum class ElementaryTypeName {
//        elementary_type_name            = 0x40000000,
//        numeric_type_name               = elementary_type_name | 0x00010000,
//        date_type_name                  = elementary_type_name | 0x00800000,
//        bit_string_type_name            = elementary_type_name | 0x00200000,
//        STRING                          = elementary_type_name | 0x00400001,
//        WSTRING                         = elementary_type_name | 0x00400002,
//        TIME                            = elementary_type_name | 0x00020000,
//    };

//    template<const char* TName>
//    struct ElementaryTypeName
//    {
//        const std::string& typeName()
//        {
//            static std::string tn { TName };
//            return tn;
//        }
//    };
//
//
//    template<const char* TName>
//    struct NumericTypeName : public ElementaryTypeName<TName>
//    {
//    };
//
//    template <const char* TName>
//    struct IntegerTypeName : public NumericTypeName<TName>
//    {
//    };

    //
    //
    // -- SIGNED INTEGER
    //
    //

//    template<const char* TName>
//    struct SignedIntegerTypeName : public IntegerTypeName<TName>
//    {
//    };
//
//    constexpr char* kSINT = "SINT";
//
//    using SINTTypeName = SignedIntegerTypeName<kSINT>;
//    using INTTypeName  = SignedIntegerTypeName<"INT">;
//    using DINTTypeName = SignedIntegerTypeName<"DINT">;
//    using LINTTypeName = SignedIntegerTypeName<"LINT">;


    //
    //
    // -- UNSIGNED INTEGER
    //
    //

//    using USINTTypeName = IntegerTypeName<"USINT">;
//    using UINTTypeName  = IntegerTypeName<"UINT">;
//    using UDINTTypeName = IntegerTypeName<"UDINT">;
//    using ULINTTypeName = IntegerTypeName<"ULINT">;

    //
    //
    // -- REAL
    //
    //


//    template<const char* TName>
//    struct RealType : public NumericTypeName<T>
//    {
//    };
//
//    using REAL  = RealType<"REAL">;
//    using LREAL = RealType<"LREAL">;
//
//    template<const char* TName>
//    struct DateTypeName : public ElementaryTypeName<TName>
//    {
//    };
//
//    using DATE = DateTypeName<"DATE">;
//    using TIME_OF_DAY = DateTypeName<"TIME_OF_DAY">;
//    using DATE_AND_TIME = DateTypeName<"DATE_AND_TIME">;
//
//    template<const char* TName>
//    struct BitStringTypeName : public ElementaryTypeName<TName>
//    {
//    };
//
//    using BOOL = DateTypeName<"BOOL">;
//    using BYTE = DateTypeName<"BYTE">;
//    using WORD = DateTypeName<"WORD">;
//    using DWORD = DateTypeName<"DWORD">;
//    using LWORD = DateTypeName<"LWORD">;

#pragma mark B.1.3.2 Generic data types

//    enum class GenericTypeName {
//         ANY                = 0x40000000
//        ,ANY_DERIVED        = 0x10000000    | static_cast<int>(ANY)
//        ,ANY_ELEMENTARY     = 0x20000000    | static_cast<int>(ANY)
//        ,ANY_MAGNITUDE      = 0x00100000    | static_cast<int>(ANY_ELEMENTARY)
//        ,ANY_NUM            = 0x00010000    | static_cast<int>(ANY_MAGNITUDE)
//        ,ANY_REAL           = 0x00001000    | static_cast<int>(ANY_NUM)
//        ,ANY_INT            = 0x00002000    | static_cast<int>(ANY_NUM)
//        ,ANY_TIME           = 0x00020000    | static_cast<int>(ANY_MAGNITUDE)
//        ,ANY_BIT            = 0x00200000    | static_cast<int>(ANY_ELEMENTARY)
//        ,ANY_STRING         = 0x00400000    | static_cast<int>(ANY_ELEMENTARY)
//        ,ANY_DATE           = 0x00800000    | static_cast<int>(ANY_ELEMENTARY)
//    };
//
//    using NonGenericTypeName = std::variant<ElementaryTypeName, std::string>;

    using ElementaryTypeName = Identifier;
    using NonGenericTypeName = Identifier;
    using IntegerTypeName = Identifier;

#pragma mark B.1.3.3 Derived data types

    // typename ----------------------

    using SimpleTypeName = Identifier;
    using SubrangeTypeName = Identifier;
    using EnumeratedTypeName = Identifier;
    using ArrayTypeName = Identifier;
    struct StructureTypeName : public Identifier {};
    using StringTypeName = Identifier;

    using SingleElementTypeName = Variant<SimpleTypeName, SubrangeTypeName, EnumeratedTypeName>;
    using DerivedTypeName = Variant<SingleElementTypeName, ArrayTypeName, StructureTypeName, StringTypeName>;

    // simple-- ----------------------


    struct SimpleSpecification : Variant<ElementaryTypeName, SimpleTypeName> {};

    struct SimpleSpecInit
    {
        SimpleSpecification specification;
        Constant constant;
    };

    struct SimpleTypeDeclaration : TypeDeclarationBase<
        SubrangeTypeName,
        SimpleSpecInit,
        Constant
    >
    {
    };






    // subrange ----------------------

    struct Subrange {
        long min;       // TODO: IEC type instead of C++ ones?
        long max;

        using List = std::vector<Subrange>;
    };


    struct ss_specification
    {
        IntegerTypeName type_name;
        Subrange value;
    };

    using SubrangeTypeName = Identifier;
    using SubrangeSpecification = Variant<SubrangeTypeName, ss_specification>;

    struct SubrangeTypeDeclaration : TypeDeclarationBase<
        std::string,
        SubrangeSpecification,
        Constant>
    {
    };

    // enumerated --------------------

    struct EnumeratedValue
    {
        using List = std::vector<EnumeratedValue>;

        std::string type_name;
        std::string value;
    };

    struct EnumeratedSpecification : Variant<EnumeratedValue::List, EnumeratedTypeName>
    {
        using base_type = Variant<EnumeratedValue::List, EnumeratedTypeName>;
        using base_type::base_type;
    };

    struct EnumeratedTypeDeclaration : TypeDeclarationBase<std::string, EnumeratedSpecification, EnumeratedValue>
    {
    };


    // string ------------------------

    struct StringTypeDeclaration
    {
        ast::ElementaryTypeName type_name;
        unsigned long size;
        ast::CharacterString value;
    };

    // -------------------------------
    struct SingleElementTypeDeclaration : std::variant<
            SimpleTypeDeclaration,
            SubrangeTypeDeclaration,
            EnumeratedTypeDeclaration>
    {
        using base_type = std::variant<
            SimpleTypeDeclaration,
            SubrangeTypeDeclaration,
            EnumeratedTypeDeclaration>;

        using base_type::base_type;
    };

    // array -------------------------

    struct ArraySpecification {
        NonGenericTypeName          type_name;
        std::vector<Subrange>       dimension;
    };

    struct StructureInitialization;
    struct ArrayInitialization;

    struct ArrayInitialElement : public Variant<
            Constant,
            EnumeratedValue,
            ForwardAst<StructureInitialization>,
            ForwardAst<ArrayInitialization>>
    {
        using base_type = Variant<
            Constant,
            EnumeratedValue,
            ForwardAst<StructureInitialization>,
            ForwardAst<ArrayInitialization>>;

        using base_type::base_type;
    };


    struct ArrayInitialElements {
        long size;
        ArrayInitialElement element;
    };

    struct ArrayInitialization
    {
        using List = std::vector<ArrayInitialElements>;
        List elements;
    };

    struct ArrayTypeDeclaration : TypeDeclarationBase<
            std::string,
            ArraySpecification,
            ArrayInitialization>
    {
    };

    // structure ---------------------

    struct StructureElementInitialization
    {
        using value =
            std::variant<
                Constant,
                EnumeratedValue,
                ArrayInitialization,
                ForwardAst<StructureInitialization>>;

        value init_value;
        Identifier name;
    };

    struct StructureInitialization
    {
        using List = std::vector<StructureElementInitialization>;
        using Iterator = List::iterator;

        List element_initializations;
    };

    struct InitializedStructure
    {
        Identifier type_name;
        StructureInitialization initialization;
    };

    struct structure_element_declaration
    {
        Identifier element_name;

        using spec_init =
            Variant<
                SimpleTypeDeclaration::SpecInit,
                SubrangeTypeDeclaration::SpecInit,
                EnumeratedTypeDeclaration::SpecInit,
                ArrayTypeDeclaration::SpecInit,
                InitializedStructure>;

        spec_init specification_init;
    };

    struct StructureDeclaration
    {
        using List = std::vector<structure_element_declaration>;
        using Iterator = List::iterator;
        List declarations;
    };

    struct StructureSpecification : Variant<StructureDeclaration, InitializedStructure>
    {
        using base = Variant<StructureDeclaration, InitializedStructure>;
        using base::base;
    };

    struct StructureTypeDeclaration
    {
        Identifier type_name;
        StructureSpecification specification;
    };



    struct TypeDeclaration
    {
        using List = std::vector<TypeDeclaration>;
        using Iterator = List::iterator;

        struct Declaration__ : public Variant<
            SingleElementTypeDeclaration,
            ArrayTypeDeclaration,
            StructureTypeDeclaration,
            StringTypeDeclaration>
        {
            using base = Variant<SingleElementTypeDeclaration, ArrayTypeDeclaration, StructureTypeDeclaration, StringTypeDeclaration>;
            using base::base;
        };

        TypeDeclaration() = default;
//        TypeDeclaration& operator=(TypeDeclaration &) = default;

//        Declaration__ decl;
        Identifier type_name;
    };

    // -------------------------------
    struct DataTypeDeclaration
    {
        TypeDeclaration::List declarations;

    };

    /**
     * The name is program. This typedef is used as long as the grammar is not
     * completed and will change over time.
     */
    using temporary_root = TypeDeclaration::List;

    using root = temporary_root;


#pragma mark - B.1.4. Variables
    struct DirectVariable;
    struct ArrayVariable;
    struct StructuredVariable;

    using MultiElementVariable = Variant<
        ForwardAst<ArrayVariable>,
        ForwardAst<StructuredVariable>>;

    using VariableName = std::string;

    using SymbolicVariable = Variant<
        VariableName,
        ForwardAst<MultiElementVariable>>;

    struct Variable : std::variant<ForwardAst<DirectVariable>, SymbolicVariable>
    {
        using base = std::variant<ForwardAst<DirectVariable>, SymbolicVariable>;
        using base::base;

    };


#pragma mark - B.1.4.1 Directly represented variables


    enum class SizePrefix
    {
        X, B, W, D, L
    };

    enum class LocationPrefix
    {
        I, Q, M
    };

    struct DirectVariable
    {
        using positions = std::vector<long>;

        LocationPrefix location;
        SizePrefix size;

        positions position;
    };


#pragma mark - B.1.4.2 Multi-element variables

    using FieldSelector = std::string;
    using RecordVariable = SymbolicVariable;

    struct StructuredVariable
    {
        RecordVariable record;
        FieldSelector field;
    };

    using Subscript = std::string;
    using SubscriptedVariable = SymbolicVariable;
    using SubscriptList = std::vector<Subscript>;

    struct ArrayVariable {
        SubscriptedVariable variable;
        SubscriptList subscripts;
    };

#pragma mark - B.1.4.3 Declaration and initialization

    enum class RetainValue {
        RETAIN, NON_RETAIN, CONSTANT, UNDEFINED
    };

    enum class EdgeValue {
        R_EDGE, F_EDGE, UNDEFINED
    };



    using Var1List = std::vector<VariableName>;

    struct EdgeDeclaration
    {
        Var1List variableList;
        EdgeValue edge;
    };

    struct VarInitDecl;
    struct InputDeclaration : public Variant<ForwardAst<VarInitDecl>, EdgeDeclaration>
    {
    };

    struct InputDeclarations
    {
        RetainValue retain;
        std::vector<InputDeclaration> declarations;
    };

    struct Var1InitDecl;
    struct ArrayVarInitDecl;
    struct StructuredVarInitDecl;
    struct FbNameDecl;
    struct StringVarDecl;

    struct VarInitDecl : Variant<
        ForwardAst<Var1InitDecl>,
        ForwardAst<ArrayVarInitDecl>,
        ForwardAst<StructuredVarInitDecl>,
        ForwardAst<FbNameDecl>,
        ForwardAst<StringVarDecl>>
    {

    };

    struct Var1InitDecl : Variant<
        SimpleTypeDeclaration::SpecInit,
        SubrangeTypeDeclaration::SpecInit,
        EnumeratedTypeDeclaration::SpecInit>
    {

        using SpecInit = Variant<
            SimpleTypeDeclaration::SpecInit,
            SubrangeTypeDeclaration::SpecInit,
            EnumeratedTypeDeclaration::SpecInit>;

        SpecInit specification;
        Var1List variables;
    };

    struct ArrayVarInitDecl
    {
        Var1List variables;
        ArrayTypeDeclaration::SpecInit specification;
    };

    struct StructuredVarInitDecl
    {
        Var1List variables;
        InitializedStructure structure;
    };

    /** FbName **/
    using FunctionBlockName = Identifier;
    using FbNameList = std::vector<FunctionBlockName>;

    struct FbNameDecl
    {
        FbNameList names;
        FunctionBlockName name;
        StructureInitialization initialization;
    };

    struct OutputDeclarations
    {
        RetainValue retain;
        std::vector<VarInitDecl> variableInitDeclarations;
    };

    struct Var1Declaration
    {
        Var1List variableList;
        Variant<SimpleSpecification, SubrangeSpecification, EnumeratedSpecification> specification;
    };

    struct ArrayVarDeclaration
    {
        Var1List variableList;
        ArraySpecification specification;
    };

    struct StructuredVarDelcaration
    {
        Var1List variableList;
        StructureTypeName specification;
    };

    struct StringVarDeclaration;
    struct TempVarDecl : Variant<Var1Declaration, ArrayVarDeclaration, StructuredVarDelcaration, ForwardAst<StringVarDeclaration>>
    {
        using base = Variant<Var1Declaration, ArrayVarDeclaration, StructuredVarDelcaration, ForwardAst<StringVarDeclaration>>;
        using base::base;
    };

    struct VarDeclaration : Variant<TempVarDecl, FbNameDecl>
    {
        using base = Variant<TempVarDecl, FbNameDecl>;
        using base::base;
    };

    struct RetentiveVarDeclarations
    {
        RetainValue retain;
        std::vector<VarInitDecl> initDeclarations;
    };

    struct InputOutputDeclarations
    {
        std::vector<VarDeclaration> declarations;
    };

//    struct Var1Declaration;
//    struct ArrayVarDelcaration;
//    struct StructureVarDeclaration;
//    struct StringVarDeclaration;

//    struct VarDeclaration : Variant<TempVarDecl, FbNameDecl>
//    {
//        using base = Variant<TempVarDecl, FBNameDecl>;
//        using base::base;
//    };

//    struct Var1Declaration
//    {
//        Var1List varlist;
//
//        struct Specification : Variant<SimpleSpecification, SubrangeSpecification, EnumeratedSpecification>
//        {
//            using base = Variant<SimpleSpecification, SubrangeSpecification, EnumeratedSpecification>;
//            using base::base;
//        };
//    };

    struct OutputDeclaration
    {
        std::vector<VarInitDecl> initDecls;
    };

    struct InputOutputDeclaration
    {
        std::vector<VarDeclaration> declarations;
    };

    struct ArrayVarSpecification
    {
        Var1List varList;
        ArraySpecification specification;
    };

    struct StructuredVarDeclaration
    {
        Var1List varList;
        StructureTypeName typeName;
    };

    struct VarDeclarations
    {
        bool isConstant;
        std::vector<VarInitDecl> declarations;
    };

    struct RetentiveVarDeclaration
    {
        std::vector<VarInitDecl> declarationss;
    };

    struct LocatedVarDecl;
    struct LocatedVarDeclarations
    {
        RetainValue retain;
        std::vector<LocatedVarDecl> declaration;
    };

    struct Location;
    struct LocatedVarSpecInit;
    struct LocatedVarDecl
    {
        VariableName name;
        ForwardAst<Location> location;
        ForwardAst<LocatedVarSpecInit> specInit;
    };

    // external -------------------------

    struct GlobalVarName;
    struct FunctionBlockTypeName;
    struct ExternalDeclaration
    {
        ForwardAst<GlobalVarName> varName;

        struct Specification : Variant <
            SimpleSpecification,
            SubrangeSpecification,
            EnumeratedSpecification,
            ArraySpecification,
            StructureTypeName,
            ForwardAst<FunctionBlockTypeName>>
        {
            using base = Variant <
                SimpleSpecification,
                SubrangeSpecification,
                EnumeratedSpecification,
                ArraySpecification,
                StructureTypeName,
                ForwardAst<FunctionBlockTypeName>>;
            using base::base;
        };

        Specification specification;
    };

    struct ExternalVarDeclarations
    {
        bool isConstant;
        std::vector<ExternalDeclaration> declarations;
    };


    // global ---------------------------

    struct GlobalVarName : public Identifier
    {
    };

    struct GlobalVarSpec
    {
    };

    struct LocatedVarSpecInit;
    struct GlobalVarDecl
    {
        GlobalVarSpec varSpecification;

        struct Specification : Variant<ForwardAst<LocatedVarSpecInit>, ForwardAst<FunctionBlockTypeName>>
        {
            using base = Variant<ForwardAst<LocatedVarSpecInit>, ForwardAst<FunctionBlockTypeName>>;
            using base::base;
        };
        Specification specification;
    };

    struct GlobalVarDeclarations
    {
        std::vector<GlobalVarDecl> declarations;
    };

    struct SubrangeSpecInit;
    struct EnumeratedSpecInit;
    struct ArraySpecInit;
    struct SingleByteStringSpec;
    struct DoubleByteStringSpec;

    struct LocatedVarSpecInit : public Variant<
        SimpleSpecInit,
        ForwardAst<SubrangeSpecInit>,
        ForwardAst<EnumeratedSpecInit>,
        ForwardAst<ArraySpecInit>,
        ForwardAst<InitializedStructure>,
        ForwardAst<SingleByteStringSpec>,
        ForwardAst<DoubleByteStringSpec>>
    {
        using base = Variant<
            SimpleSpecInit,
            ForwardAst<SubrangeSpecInit>,
            ForwardAst<EnumeratedSpecInit>,
            ForwardAst<ArraySpecInit>,
            ForwardAst<InitializedStructure>,
            ForwardAst<SingleByteStringSpec>,
            ForwardAst<DoubleByteStringSpec>>;
        using base::base;
    };

    struct Location
    {
        DirectVariable variable;
    };

    struct GlobalVarList
    {
        std::vector<GlobalVarName> names;
    };

    // string ---------------------------

    struct SingleByteStringSpec
    {
        UINT size;
        SingleByteCharacterString characterString;
    };

    struct SingleByteStringVarDeclaration
    {
        Var1List variables;
        SingleByteStringSpec stringSpec;
    };

    struct DoubleByteStringSpec
    {
        UINT size;
        DoubleByteCharacterString characterString;
    };

    struct DoubleByteStringVarDeclaration
    {
        Var1List variables;
        DoubleByteStringSpec stringSpec;
    };

    struct StringVarDeclaration : Variant<SingleByteStringVarDeclaration, DoubleByteStringVarDeclaration>
    {
        using base = Variant<SingleByteStringVarDeclaration, DoubleByteStringVarDeclaration>;
        using base::base;
    };

    // incompleted ---------------------

    enum class IncomplLocation
    {
        I, Q, M
    };

    struct VarSpec;
    struct IncomplLocatedVarDecl
    {
        VariableName variableName;
        IncomplLocation location;
        ForwardAst<VarSpec> varSpec;
    };

    struct IncomplLocatedVarDeclarations
    {
    };

    // TODO:
    struct VarSpec : Variant<SimpleSpecification, SubrangeSpecification, EnumeratedSpecification, ArraySpecification, StructureTypeName>
    {
    };

#pragma mark - B.1.5 Program organization units

#pragma mark - B.1.5.1 Functions

    struct StandardFunctionName
    {
        Identifier identifier;
    };

    struct DerivedFunctionName
    {
        Identifier identifier;
    };

    struct FunctionName : Variant<StandardFunctionName, DerivedFunctionName>
    {
    };

    struct IoVarDeclaration : Variant<
        InputDeclarations,
        OutputDeclarations,
        InputOutputDeclarations>
    {
        using base = Variant<InputDeclarations, OutputDeclarations, InputOutputDeclarations>;
        using base::base;
    };

    struct Var2InitDecl : public Variant<Var1InitDecl, ArrayVarInitDecl, StructuredVarInitDecl, StringVarDeclaration>
    {
        using base = Variant<Var1InitDecl, ArrayVarInitDecl, StructuredVarInitDecl, StringVarDeclaration>;
        using base::base;
    };

    struct FunctionVarDecls
    {
        std::vector<Var2InitDecl> declarations;
    };

#pragma mark - B.1.5.2 Function Blocks

    struct StandardFunctionBlockName : public Identifier
    {
    };

    struct DerivedFunctionBlockName : public Identifier
    {
    };

    struct FunctionBlockTypeName : public Variant<StandardFunctionBlockName, DerivedFunctionBlockName>
    {
        using base = Variant<StandardFunctionBlockName, DerivedFunctionBlockName>;
        using base::base;
    };

    struct NonRetentiveVarDecls
    {
        std::vector<VarInitDecl> initDeclaratoins;
    };


    struct OtherVarDeclarations : Variant<
        ExternalVarDeclarations,
        VarDeclarations,
        RetentiveVarDeclarations,
        NonRetentiveVarDecls,
        TempVarDecl,
        IncomplLocatedVarDeclarations>
    {
        using base = Variant<
            ExternalVarDeclarations,
            VarDeclarations,
            RetentiveVarDeclarations,
            NonRetentiveVarDecls,
            TempVarDecl,
            IncomplLocatedVarDeclarations>;
        using base::base;
    };

    struct SequentialFunctionChart;
    struct LadderDiagram;
    struct FunctionBlockDiagram;
    struct InstructionList;
    struct StatementList;

    struct FunctionBlockBody : Variant<ForwardAst<SequentialFunctionChart>, ForwardAst<LadderDiagram>, ForwardAst<FunctionBlockDiagram>, ForwardAst<InstructionList>, ForwardAst<StatementList>>
    {
        using base = Variant<ForwardAst<SequentialFunctionChart>, ForwardAst<LadderDiagram>, ForwardAst<FunctionBlockDiagram>, ForwardAst<InstructionList>, ForwardAst<StatementList>>;
        using base::base;
    };

    struct FunctionBlockDeclaration
    {
        DerivedFunctionBlockName functionBlockName;

        struct Declarations : Variant<IoVarDeclaration, OtherVarDeclarations>
        {
            using base = Variant<IoVarDeclaration, OtherVarDeclarations>;
            using base::base;
        };

        std::vector<Declarations> declarations;
        FunctionBlockBody body;
    };

    struct TempVarDecls
    {
        std::vector<TempVarDecl> declarations;
    };

//    struct FunctionBlockTypeName : Variant<StandardFunctionBlockName, DerivedFunctionBlockName>
//    {
//    };



#pragma mark - B.1.5.3 Programs

    struct ProgramTypeName
    {
        Identifier identifier;
    };

    struct ProgramAccessDecl;
    struct ProgramDeclaration
    {
        ProgramTypeName typeName;

        struct Declarations : Variant<IoVarDeclaration, OtherVarDeclarations, LocatedVarDeclarations, ForwardAst<ProgramAccessDecl>>
        {
            using base = Variant<IoVarDeclaration, OtherVarDeclarations, LocatedVarDeclarations, ForwardAst<ProgramAccessDecl>>;
            using base::base;
        };
    };

    struct AccessName;
    struct ProgramAccessDecl
    {
        ForwardAst<AccessName> accessName;
        SymbolicVariable symbolicVariable;
        NonGenericTypeName typeName;
    };

    struct ProgramAccessDecls : std::vector<ProgramAccessDecl>
    {

    };


#pragma mark - B.1.6 Sequential function chart elements



    struct InitialStep;
    struct Step;
    struct Transition;
    struct Action;
    struct SFCNetwork
    {
        ForwardAst<InitialStep> initialStep;

        struct Steps : Variant<ForwardAst<Step>, ForwardAst<Transition>, ForwardAst<Action>>
        {
            using base = Variant<ForwardAst<Step>, ForwardAst<Transition>, ForwardAst<Action>>;
            using base::base;
        };

        std::vector<Steps> steps;
    };

    struct SequentialFunctionChart
    {
        std::vector<SFCNetwork> networks;
    };

    struct StepName : public Identifier
    {
    };

    struct ActionName : Variant<Duration, VariableName>
    {
        using base = Variant<Duration, VariableName>;
        using base::base;
    };

    struct ActionTime : Variant<Duration, VariableName>
    {
    };

    enum class TimedQualifier
    {
        L = 1 << 10, D, SD, DS, SL
    };

    struct  ActionQualifier
    {
        enum class Qualifier
        {
            N, R, S, P,
            L = 1 << 10, D, SD, DS, SL      // TODO:
        };

        Qualifier qualifier;
        ActionTime time;
    };

    struct IndicatorName
    {
        VariableName variableName;
    };

    struct ActionAssociation
    {
        ActionName name;
        ActionQualifier qualifier;
        IndicatorName indicatorName;
    };

    struct Step
    {
        StepName name;
        ActionAssociation action;
    };

    struct InitialStep : public Step
    {
    };

    struct TransitionName
    {
        Identifier identifier;
    };

    struct Steps : public std::vector<StepName>
    {
    };

    struct Transition
    {
        TransitionName name;
        int64_t priority;
        Steps from;
        Steps to;
    };

    struct Action
    {
        ActionName name;
        FunctionBlockBody body;
    };


#pragma mark - B.1.7 Configuration elements

    struct ConfigurationName : Identifier
    {
    };

    struct ResourceTypeName : Identifier
    {
    };

    struct SingleResourceDeclaration;
    struct AccessDeclaration;
    struct GlobalVarReference;
    struct ResourceDeclaration;
    struct InstanceSpecificInitializations;

    struct ConfigurationDeclaration
    {
        ConfigurationName name;
        std::vector<GlobalVarReference> varReferenceList;

        struct References : public Variant<ForwardAst<SingleResourceDeclaration>, std::vector<ResourceDeclaration>>
        {
            using base = Variant<ForwardAst<SingleResourceDeclaration>, std::vector<ResourceDeclaration>>;
            using base::base;
        };
        References references;
        ForwardAst<AccessDeclaration> accessDeclaration;
        ForwardAst<InstanceSpecificInitializations> specificInitializations;
    };

    struct ResourceName : public Identifier
    {
    };

    struct TaskConfiguration;
    struct ProgrammConfiguration; // FIXME: typo
    struct SingleResourceDeclaration
    {
        std::vector<TaskConfiguration> taskConfigurations;
        std::vector<ProgrammConfiguration> programConfigurations;
    };

    struct ResourceDeclaration
    {
        ResourceName name;
        ResourceTypeName typeName;
        std::vector<GlobalVarDeclarations> globalVariableDeclarations;
        std::vector<SingleResourceDeclaration> singleResourceDeclarations;
    };

    struct AccessPath
    {
        ResourceName resourceName;
        Variant<SymbolicVariable, DirectVariable> variable;
    };

    struct AccessName : public Identifier
    {
    };

    struct AccessDeclaration
    {
        AccessName name;
        AccessPath path;
        NonGenericTypeName typeName;
        //TODO: Direction direction;
    };

    struct GlobalVarReference
    {
        ResourceName resourceName;
        GlobalVarName varName;
        // TODO:
    };

    struct ProgramOutputReference
    {
    };

    struct ProgramName : Identifier
    {
    };

    struct TaskName
    {
        Identifier identifier;
    };

    struct DataSource : public Variant<Constant, GlobalVarReference, ProgramOutputReference, DirectVariable>
    {
        using base = Variant<Constant, GlobalVarReference, ProgramOutputReference, DirectVariable>;
        using base::base;
    };

    struct TaskInitialization
    {
        DataSource                  singleSource;
        DataSource                  intervalSource;
        int                     priority; // TODO:
    };

    struct TaskConfiguration
    {
        TaskName name;
        TaskInitialization initialization;
    };

    struct ProgConfElements
    {

    };

    struct ProgramConfiguration
    {
        ProgramName                 name;
        TaskName                    taskName;
        ProgramTypeName             typeName;
        ProgConfElements            configurationElement;
    };


    struct FbTask
    {
        FunctionBlockName name;
        TaskName taskName;
    };

    struct ProgDataSource : public Variant<Constant, EnumeratedValue, GlobalVarReference, DirectVariable>
    {
        using base = Variant<Constant, EnumeratedValue, GlobalVarReference, DirectVariable>;
        using base::base;
    };

    struct ProgCnxn
    {
        SymbolicVariable variable;

        struct Data : Variant<ProgDataSource, DataSource>
        {
            using base = Variant<ProgDataSource, DataSource>;
            using base::base;
        };

        Data data;
    };

    struct ProgConfElement : public Variant<FbTask, ProgCnxn>
    {
        using base = Variant<FbTask, ProgCnxn>;
        using base::base;
    };

    struct DataSink : Variant<GlobalVarReference, DirectVariable>
    {
        using base = Variant<GlobalVarReference, DirectVariable>;
        using base::base;
    };


    struct InstanceSpecificInit
    {
        struct Variable
        {
            ResourceName resourceName;
            ProgramName programName;
            FunctionBlockName fbName;
            VariableName variableName;
            Location location;
            LocatedVarSpecInit specInit;
        };

        struct FunctionBlock
        {
            FunctionBlockName fbName;
            FunctionBlockTypeName type_name;
        };
    };

    struct InstanceSpecificInitialization : std::vector<InstanceSpecificInit>
    {
        struct Inits : public std::vector<InstanceSpecificInit>
        {
        };

        Inits initializations;
    };



#pragma mark - B.2 Language IL (Instruction List)

#pragma mark - B.2.1 Instructions and operands

    struct ILInstruction;
    struct ILSimpleOperation;
    struct ILExpression;
    enum class ILSimpleOperator;
    enum class ILExprOperator;
    struct ILJumpOperation;
    struct ILFbCall;
    //struct ILFormalFunctCall;
    enum class ILReturnOperator;
    struct OperandList;
    struct SimpleInstructionList;


    struct InstructionList : std::vector<ILInstruction>
    {
    };

    struct Label : std::string
    {
        using base_type = std::string;
        using base_type::base_type;
    };


    struct ILOperand : std::variant<Constant, Variable, EnumeratedValue>
    {
        using base_type = std::variant<Constant, Variable, EnumeratedValue>;
        using base_type::base_type;
    };

    struct ILOperandList : std::vector<ILOperand>
    {
        using base_type = std::vector<ILOperand>;
        using base_type::base_type;
    };

    struct ILSimpleOperation
    {
        struct Function
        {
            Identifier name;
            std::optional<ILOperandList> operands;
        };

        struct Operator
        {
            ILSimpleOperator operator_;
            std::optional<ILOperand> operand;
        };

        Variant<ILSimpleOperator, Function> operation;
    };

    struct ILFormalFunctCall;
    struct ILExpression;
    struct ILSimpleInstruction : std::variant<
         ILSimpleOperation
        ,ForwardAst<ILExpression>
        ,ForwardAst<ILFormalFunctCall>>
    {
        using base_type = std::variant<ILSimpleOperation, ForwardAst<ILExpression>, ForwardAst<ILFormalFunctCall>>;
        using base_type::base_type;
    };

    struct SimpleInstrList : std::vector<ILSimpleInstruction>
    {
        using base_type = std::vector<ILSimpleInstruction>;
        using base_type::base_type;
    };

    struct ILExpression
    {
        ForwardAst<ILExprOperator> operator_;
        std::vector<ILOperand> operands;
        ForwardAst<SimpleInstructionList> instruction_list;
    };

    enum class ILJumpOperator;
    struct ILJumpOperation
    {
        ForwardAst<ILJumpOperator> jump_operator;
        struct Label label;
    };

    enum class ILCallOperator;

    struct IL_param_instruction;
    struct ILParamList : std::vector<IL_param_instruction>
    {
        using base_type = std::vector<IL_param_instruction>;
        using base_type::base_type;
    };

    struct ILFormalFunctionCall
    {
        FunctionName name;
        std::optional<ForwardAst<ILParamList>> paramList;
    };

    struct ILFbCall
    {
        struct fb
        {
            ForwardAst<ILCallOperator> call_operator;
            FunctionBlockName name;
            // boost::optional
            ForwardAst<ILParamList> param_list;
        };

        std::variant<fb, ILOperandList> TODO_name;
    };

    struct ILParamAssignment;
    struct ILParamOutAssignment;
    struct IL_param_instruction : std::variant<
        ForwardAst<ILParamAssignment>,
        ForwardAst<ILParamOutAssignment>>
    {
    };

    struct ILAssignOperator;
    struct ILParamAssignment
    {
        ForwardAst<ILAssignOperator> operator_;
        Variant<ILOperand, SimpleInstrList> operand;
    };

    struct ILAssignOutOperator;
    struct ILParamOutAssignment
    {
        ForwardAst<ILAssignOutOperator> assign_out_operator;
        Variable variable;
    };

    struct ILInstruction
    {
        using instruction = std::variant<
             ILSimpleOperator
            ,ILExpression
            ,ILJumpOperation
            ,ILFbCall
            //,ILFormalFunctCall
            ,ILReturnOperator
        >;

        struct Label label;
        instruction instr;
    };

#pragma mark - B.2.2 Operators

    /**
     * append IL_expr_operator, or at least ensure both usages
     */
    enum class ILSimpleOperator
    {
        LD, LDN, ST, STN, NOT,
        S, R, S1, R1,
        CLK, CU, CD,
        PV, IN, PT
    };

    enum class ILExprOperator
    {
        AND, AND_, OR, XOR, ANDN, _N, ORN, XORN,
        ADD, SUB, MUL, DIV, MOD,
        GT, GE, EQ, LT, LE, NE
    };

    struct ILAssignOperator : std::string
    {
        using base_type = std::string;
        using base_type::base_type;
    };

    struct ILAssignOutOperator
    {
        bool is_negated;
        std::string name;
    };

    enum class ILCallOperator
    {
        CAL, CALC, CLCN
    };

    enum class ILReturnOperator
    {
        RET, RETC, RETCN
    };

    enum class ILJumpOperator
    {
        JMP, JMPC, JMPCN
    };


#pragma mark - B.3 Language ST (Structured Text)

#pragma mark - B.3.1 Expressions

    struct XorExpression;
    struct Expression
    {
        std::vector<XorExpression> operands;
    };

    struct AndExpression;
    struct XorExpression
    {
        std::vector<AndExpression> operands;
    };

    struct Comparison;
    struct EquExpression;
    struct AndExpression
    {
        struct ComparisonNQ : public ForwardAst<Comparison>
        {
        };

        struct ComparisonEQ : public ForwardAst<Comparison>
        {
        };

        std::vector<Comparison> operands;
    };




    struct ParamAssignment;
    struct PrimaryExpressionFc
    {
        std::string function_name;
        std::vector<ParamAssignment> param_assignments;
    };

    struct Expression;
    struct PrimaryExpression : std::variant<
         Constant
        ,EnumeratedValue
        //,variable
        ,ForwardAst<Expression>
        ,PrimaryExpressionFc>
    {
        using base_type = std::variant<Constant, EnumeratedValue, ForwardAst<Expression>, PrimaryExpressionFc>;
        using base_type::base_type;
    };

    enum class UnaryOperator
    {
        MINUS, NOT
    };

    struct unary_expression
    {
        UnaryOperator operator_;
        ForwardAst<PrimaryExpression> expression;
    };

    struct PowerExpression
    {
        unary_expression base;
        unary_expression exponent;
    };

    enum class MultiplyOperator
    {
         Multiplication
        ,Division
        ,Modulo
    };

    struct Term
    {
        ForwardAst<Term> firstOperand;
        MultiplyOperator operator_;
        PowerExpression expression;
    };

    enum class AddOperator
    {
        Plus, Minus
    };

    struct AddExpression
    {
        Term firstOperator;
        ForwardAst<AddExpression> secondOperator;
    };

    enum class ComparisonOperator
    {
        LT, GT, LTE, GTE
    };

    /*
     * TODO: generalize the following:
     *
        std::vector<add_operator> adds;
        std::vector<term> terms;

        void add_summand(add_operator operator_, term term_)
        {
            adds.push_back(operator_);
            terms.push_back(term_);
            assert (adds.size() == terms.size());
        }
     */


    struct EquExpression
    {
        ForwardAst<EquExpression> firstOperand;
        AddExpression secondOperand;
        ComparisonOperator operator_;
    };

    struct Comparison
    {

        enum class EqualOperator
        {
            EQ, NEQ
        };

        std::vector<EqualOperator> comparisons;
        std::vector<EquExpression> equs;

        void add_comparison(EqualOperator operator_, ForwardAst<EquExpression> equ_expr)
        {
            comparisons.push_back(operator_);
            equs.push_back(equ_expr);
            assert (equs.size() == comparisons.size());
        }
    };


//    struct AndExpression
//    {
//        Comparison first_compare;
//        std::vector<Comparison> compares;
//    };
//
//    struct XorExpression
//    {
//        AndExpression first_and;
//        std::vector<AndExpression> ands;
//    };
//
//    struct Expression
//    {
//        XorExpression first_expression;
//        std::vector<XorExpression> xors;
//    };

#pragma mark - B.3.2 Statements

    struct AssignmentStatement;
    struct SubprogramControlStatement;
    struct SelectionStatement;
    struct IterationStatement;

    struct Statement : std::variant<
         ForwardAst<AssignmentStatement>
        ,ForwardAst<SubprogramControlStatement>
        ,ForwardAst<SelectionStatement>
        ,ForwardAst<IterationStatement>>
    {
        using base_type = std::variant<
             ForwardAst<AssignmentStatement>
            ,ForwardAst<SubprogramControlStatement>
            ,ForwardAst<SelectionStatement>
            ,ForwardAst<IterationStatement>>;
        using base_type::base_type;
    };

    struct StatementList : std::vector<Statement>
    {
        using base_type = std::vector<Statement>;
        using base_type::base_type;
    };


#pragma mark - B.3.2.1 Assignment statements

    // TODO:
    struct AssignmentStatement
    {
        //variable var;
        Expression exp;
    };

#pragma mark - B.3.2.2 Subprogram control statements

    struct Return {};

    struct FunctionBlockInvokation
    {

    };

    // TODO:
    struct SubprogramControlStatement : Variant<Return, FunctionBlockInvokation>
    {
        using base = Variant<Return, FunctionBlockInvokation>;
        using base::base;
    };

    struct ParamAssignment
    {
        struct assigment
        {
            //VariableName name;
            Expression exp;
        };

        // TODO
        struct TODO_find_a_name
        {
            // VariableName name;
            // variable var;
        };
    };

#pragma mark - B.3.2.3 Selection statements

    struct CaseListElement : std::variant<
         Subrange
    //        ,SignedInteger TODO:
        ,EnumeratedValue>
    {
        using base = std::variant<Subrange, EnumeratedValue>;
        using base::base;
    };

    struct CaseList : std::vector<CaseListElement>
    {
        using base_type = std::vector<CaseListElement>;
        using base_type::base_type;
    };

    struct CaseElement
    {
        CaseList case_;
        StatementList statement;
    };

    struct CaseStatement
    {
        Expression condition;
        std::vector<CaseElement> elements;
        StatementList else_statements;
    };

    struct IfStatement
    {
        struct IfThen
        {
            Expression condition;
            StatementList then_statements;
        };

        struct ElseIfThen
        {
            Expression condition;
            StatementList then_statements;
        };

        IfThen if_;
        std::vector<ElseIfThen> else_if;
        StatementList else_;
    };

    struct SelectionStatement : std::variant<IfStatement, CaseStatement>
    {
        using base_type = std::variant<IfStatement, CaseStatement>;
        using base_type::base_type;
    };

#pragma mark - B.3.2.4 Iteration statements

    struct ControlVariable : Identifier
    {
        using base_type = Identifier;
        using base_type::base_type;
    };

    struct ForList
    {
        Expression from;
        Expression to;
        Expression by;
    };

    struct ForStatement
    {
        ControlVariable control;
        ForList list;
        StatementList statements;
    };

    struct WhileStatement
    {
        Expression while_;
        StatementList do_;
    };

    struct RepeatStatement
    {
        StatementList repeat_statements;
        Expression until_expression;
    };

    struct ExitStatement
    {
    };

    struct IterationStatement : std::variant<
         ForStatement
        ,WhileStatement
        ,RepeatStatement
        ,ExitStatement>
    {
        using base = std::variant<ForStatement, WhileStatement, RepeatStatement ,ExitStatement>;
        using base::base;
    };

}}}
