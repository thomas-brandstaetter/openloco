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

        virtual ~TypeDeclarationBase() {}

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

    template<typename T, int TS, char const * TN>
    struct Elementary : ValueWrapper<T>
    {
        Elementary() = default;
        ~Elementary() = default;
        Elementary& operator=(const Elementary& rhs) = default;

        const std::string type_name { TN };
        const int type_size{TS};
    };

    template<typename T, int TS, char const * TN>
    struct Numeric : public Elementary<T, TS, TN>
    {
    };

    template<typename T, int TS, char const * TN>
    struct Integer : public Numeric<T, TS, TN>
    {
        static const T s_kInfinum  = 0;
        static const T s_kSupremum = (1 << TS) - 1;
    };

    template<typename T, int TS, char const * TN>
    struct SignedInteger : public Integer<T, TS, TN>
    {
    private:
        static const T _2powN_1 = (1 << (TS - 1))-1 ;
    public:
        static const T s_kInfinum = _2powN_1;
        static const T s_kSupremum = _2powN_1 - 1;
    };

    struct SINT : public SignedInteger<int8_t, 8, "SINT"> {};
    struct INT : public Integer<int16_t, 16, "INT"> {};
    struct DINT : public Integer<int32_t, 32, "DINT"> {};
    struct LINT : public Integer<int64_t, 64, "LINT"> {};

    struct BinaryInteger : ValueWrapper<long>
    {
    };

    struct OctalInteger : ValueWrapper<long>
    {
    };

    struct HexInteger : ValueWrapper<long>
    {
    };

    struct BooleanLiteral : ValueWrapper<bool>
    {
    };

    struct BitStringLiteral : Variant<Integer, BinaryInteger, OctalInteger, HexInteger>
    {
        using base = Variant<Integer, BinaryInteger, OctalInteger, HexInteger>;
        using base::base;
    };

    struct IntegerLiteral : Variant<SignedInteger, Integer, BinaryInteger, OctalInteger, HexInteger>
    {
        using base = Variant<SignedInteger, Integer, BinaryInteger, OctalInteger, HexInteger>;
        using base::base;

        enum class integer_type_name;
        integer_type_name type_name;
    };

    struct RealLiteral : ValueWrapper<double>
    {
    };

    struct NumericLiteral : Variant<IntegerLiteral, RealLiteral>
    {
        using base = Variant<IntegerLiteral, RealLiteral>;
        using base::base;
    };

#pragma mark - B.1.2.2 Character Strings

    struct SingleByteCharacterString : ValueWrapper<std::string>
    {
        using base = ValueWrapper<std::string>;
        using base::base;
    };

    struct DoubleByteCharacterString : ValueWrapper<std::string>
    {
        using base = ValueWrapper<std::string>;
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

    struct Interval : ast::Days
    {
    };

    struct Duration : ast::Interval
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

    template<char const* T>
    struct ElementaryTypeName
    {
        std::string typeName { T };
        std::vector<std::string> validList { "ANY_ELEMEARY" };
    };

    template<char const* T>
    struct NumericTypeName : public ElementaryTypeName<T>
    {
        NumericTypeName() : ElementaryTypeName<T>()
        {
            validList.insert("ANY_NUMERIC");

        }
    };

    template <char const* T, int TS>
    struct IntegerTypeName : public NumericTypeName<T>
    {
    };

    //
    //
    // -- SIGNED INTEGER
    //
    //

    template<char const* T, int TS>
    struct SignedIntegerType : public IntegerTypeName<T, TS>
    {

    };

    using SINTTypeName = SignedIntegerType<int8_t,  8>;
    using INTTypeName  = SignedIntegerType<int16_t, 16>;
    using DINTTypeName = SignedIntegerType<int32_t, 32>;
    using LINTTypeName = SignedIntegerType<int64_t, 64>;

    using SignedIntegerTypeName = Identifier;

    //
    //
    // -- UNSIGNED INTEGER
    //
    //


    template<typename T, int TS>
    struct UnsignedIntegerType : public ValueWrapper<T>, IntegerTypeName<T, TS>
    {
    public:
        const T kInfinum = 0;
        const T kSupremum = 1 << IntegerTypeName<T, TS>::_2powN;
    };

    using USINT = UnsignedIntegerType<uint8_t, 8>;
    using UINT  = UnsignedIntegerType<uint16_t,16>;
    using UDINT = UnsignedIntegerType<uint32_t,32>;
    using ULINT = UnsignedIntegerType<uint64_t,64>;

    using UnsignedIntegerTypeName = Identifier;

    //
    //
    // -- REAL
    //
    //


    template<typename T>
    struct RealType : public NumericTypeName<T>, public ValueWrapper<T>
    {
    };

    using REAL = RealType<float>;
    using LREAL = RealType<double>;

    enum class DateTypeName {
        DATE                            = static_cast<int>(ElementaryTypeName::date_type_name) | 1,
        TIME_OF_DAY,
        DATE_AND_TIME
    };

    enum class BitStringTypeName {
        BOOL                            = static_cast<int>(ElementaryTypeName::bit_string_type_name) | 1,
        BYTE,
        WORD,
        DWORD,
        LWORD,
    };


#pragma mark B.1.3.2 Generic data types

    enum class GenericTypeName {
         ANY                = 0x40000000
        ,ANY_DERIVED        = 0x10000000    | static_cast<int>(ANY)
        ,ANY_ELEMENTARY     = 0x20000000    | static_cast<int>(ANY)
        ,ANY_MAGNITUDE      = 0x00100000    | static_cast<int>(ANY_ELEMENTARY)
        ,ANY_NUM            = 0x00010000    | static_cast<int>(ANY_MAGNITUDE)
        ,ANY_REAL           = 0x00001000    | static_cast<int>(ANY_NUM)
        ,ANY_INT            = 0x00002000    | static_cast<int>(ANY_NUM)
        ,ANY_TIME           = 0x00020000    | static_cast<int>(ANY_MAGNITUDE)
        ,ANY_BIT            = 0x00200000    | static_cast<int>(ANY_ELEMENTARY)
        ,ANY_STRING         = 0x00400000    | static_cast<int>(ANY_ELEMENTARY)
        ,ANY_DATE           = 0x00800000    | static_cast<int>(ANY_ELEMENTARY)
    };

    using NonGenericTypeName = std::variant<ElementaryTypeName, std::string>;

#pragma mark B.1.3.3 Derived data types

    // typename ----------------------

    using SimpleTypeName = Identifier;
    using SubrangeTypeName = Identifier;
    using EnumeratedTypeName = Identifier;
    using ArrayTypeName = Identifier;
    using StructureTypeName = Identifier;
    using StringTypeName = Identifier;

    using SingleElementTypeName = Variant<SimpleTypeName, SubrangeTypeName, EnumeratedTypeName>;
    using DerivedTypeName = Variant<SingleElementTypeName, ArrayTypeName, StructureTypeName, StringTypeName>;

    // simple-- ----------------------

    struct SimpleSpecInit : Variant<ElementaryTypeName, SimpleTypeName> {};

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

    struct ArrayInitialElement : public std::variant<
            Constant,
            EnumeratedValue,
            ForwardAst<StructureInitialization>,
            ForwardAst<ArrayInitialization>>
    {
        using base_type = std::variant<
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
            std::variant<
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

    using structure_specification = std::variant<StructureDeclaration, InitializedStructure>;

    struct StructureTypeDeclaration
    {
        Identifier type_name;
        structure_specification specification;
    };

    struct TypeDeclaration
    {
        using List = std::vector<TypeDeclaration>;
        using Iterator = List::iterator;

        using Declaration =
            std::variant<
                SingleElementTypeDeclaration,
                ArrayTypeDeclaration,
                StructureTypeDeclaration,
                StringTypeDeclaration>;

        Declaration decl;
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


    using Var1List = std::vector<std::string>;

    struct Var1InitDecl {
        using SpecInit = std::variant<
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

    struct StructuredVarInitDecl {
        Var1List variables;
        InitializedStructure structure;
    };

    using FbNameList = std::vector<std::string>;
    using FbName = Identifier;

    struct FBNameDecl
    {
        FbNameList fb_names;
        std::string name;
        StructureInitialization initialization;
    };

    struct FBName
    {
        using List = std::vector<FBName>;

        Identifier identifier;
    };

    struct Var1Declaration;
    struct ArrayVarDelcaration;
    struct StructureVarDeclaration;
    struct StringVarDeclaration;

    struct TempVarDecl : Variant<ForwardAst<Var1Declaration>, ForwardAst<ArrayVarDelcaration>, ForwardAst<StructureVarDeclaration>, ForwardAst<StringVarDeclaration>>
    {
        using base = Variant<ForwardAst<Var1Declaration>, ForwardAst<ArrayVarDelcaration>, ForwardAst<StructureVarDeclaration>, ForwardAst<StringVarDeclaration>>;
        using base::base;
    };

    struct VarDeclaration : Variant<TempVarDecl, FBNameDecl>
    {
        using base = Variant<TempVarDecl, FBNameDecl>;
        using base::base;
    };

    struct Var1Declaration
    {
        Var1List varlist;

        struct Specification : Variant<SimpleSpecification, SubrangeSpecification, EnumeratedSpecification>
        {
            using base = Variant<SimpleSpecification, SubrangeSpecification, EnumeratedSpecification>;
            using base::base;
        };
    };

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

    struct LocatedVarDeclaration
    {
        std::vector<LocatedVarDecl> declaration;
    };

    struct LocatedVarDecl
    {
        VariableName name;
        Location location;
        LocatedVarSpecInit specInit;
    };

    // external -------------------------

    struct ExternalDeclaration
    {
        GlobalVarName varName;

        struct Specification : Variant <
            SimpleSpecification,
            SubrangeSpecification,
            EnumeratedSpecification,
            ArraySpecification,
            StructureTypeName,
            FunctionBlockTypeName>
        {
            using base = Variant <
                SimpleSpecification,
                SubrangeSpecification,
                EnumeratedSpecification,
                ArraySpecification,
                StructureTypeName,
                FunctionBlockTypeName>;
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

    using GlobalVarName = Identifier;

    struct GlobalVarDeclarations
    {
        std::vector<GlobalVarDecl> declarations
    };

    struct GlobalVarDecl
    {
        GlobalVarSpec varSpecification;

        struct Specification : Variant<LocatedVarSpecInit, FunctionBlockTypeName>
        {
            using base = Variant<LocatedVarSpecInit, FunctionBlockTypeName>;
            using base::base;
        };
        Specification specification;
    };

    struct GlobalVarSpec
    {
    };

    struct LocatedVarSpecInit : Variant<
        SimpleSpecInit,
        SubrangeSpecInit,
        EnumeratedSpecInit,
        ArraySpecInit,
        InitializedStructure,
        SingleByteStringSpec,
        DoubleByteStringSpec>
    {
        using base = Variant<
            SimpleSpecInit,
            SubrangeSpecInit,
            EnumeratedSpecInit,
            ArraySpecInit,
            InitializedStructure,
            SingleByteStringSpec,
            DoubleByteStringSpec>;
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

    struct SingleByteStringVarDeclaration
    {
        Var1List variables;
        SingleByteStringSpec stringSpec;
    };

    struct SingleByteStringSpec
    {
        Integer size;
        SingleByteCharacterString characterString;
    };

    struct DoubleByteStringVarDeclaration
    {
        Var1List variables;
        DoubleByteStringSpec stringSpec;
    };

    struct DoubleByteStringSpec
    {
        Integer size;
        DoubleByteCharacterString characterString;
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

    struct IncomplLocatedVarDeclarations :

    // TODO:
    struct VarSpec : Variant<SimpleSpecification, SubrangeSpecification, EnumeratedSpecification, ArraySpecification, StructireTypeName>
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

    struct FunctionVarDecls
    {
        std::vector<Var2InitDecl> declarations;
    };

#pragma mark - B.1.5.2 Function Blocks

    struct FunctionBlockTypeName : Variant<StandardFunctionBlockName, DerivedFunctionBlockName>
    {

    };

    struct StandardFunctionBlockName
    {
    };

    struct DerivedFunctionBlockName
    {
        Identifier identifier;
    };

    struct FunctionBlockDeclaration
    {
        DerivedFunctionBlockName functionBlockName;

        struct Declarations : Variant<IOVarDeclarations, OtherVarDeclarations>
        {
            using base = Variant<IOVarDeclarations, OtherVarDeclarations>;
            using base::base;
        };

        std::vector<Declarations> declarations;
        FunctionBlockBody body;
    };

    struct OtherVarDeclarations : Variant<
        ExternalVarDeclarations,
        VarDeclarations,
        RetentiveVarDeclarations,
        NonRetentiveVarDeclarations,
        TempVarDecl,
        IncomplLocatedVarDeclarations>
    {
        using base = Variant<
            ExternalVarDeclarations,
            VarDeclarations,
            RetentiveVarDeclarations,
            NonRetentiveVarDeclarations,
            TempVarDecl,
            IncomplLocatedVarDeclarations>;
        using base::base;
    };

    struct TempVarDecls
    {
        std::vector<TempVarDecl> declarations;
    };

    struct NonRetentiveVarDecls
    {
        VarInitDecl declarations;
    };

    struct FunctionBlockBody : Variant<
        SequentialFunctionChart,
        LadderDiagram,
        FunctionBlockDiagram,
        InstructionList,
        StateMentList>
    {
        using base = Variant<
            SequentialFunctionChart,
            LadderDiagram,
            FunctionBlockDiagram,
            InstructionList,
            StateMentList>;
        using base::base;

    };


#pragma mark - B.1.5.3 Programs

    struct ProgramTypeName
    {
        Identifier identifier;
    };

    struct ProgramDeclaration
    {
        ProgramTypeName typeName;

        struct Declarations : Variant<IoVarDeclaration, OtherVarDeclarations, LocatedVarDeclarations, ProgramAccessDecl>
        {
            using base = Variant<IoVarDeclaration, OtherVarDeclarations, LocatedVarDeclarations, ProgramAccessDecl>;
            using base::base;
        };
    };

    struct ProgramAccessDecl
    {
        AccessName accessName;
        SymbolicVariable symbolicVariable;
        NonGenericTypeName typeName;
    };

    struct ProgramAccessDecls : std::vector<ProgramAccessDecl>
    {

    };


#pragma mark - B.1.6 Sequential function chart elements

    struct SequentialFunctionChart
    {
        std::vector<SFCNetwork> networks;
    };

    // TODO
    struct SFCNetwork
    {
        InitialStep initialStep;

    };

    struct Step
    {
        StepName name;
        ActionAssociation action;
    };

    struct StepName;
    {
        Identifier identifier;
    };

    struct ActionAssociation
    {
        ActionName name;
        ActionQualifier qualifier;
        IndicatorName indicatorName;
    };

    struct ActionName : Variant<Duration, VariableName>
    {
        using base = Variant<Duration, VariableName>;
        using base::base;
    };

    struct  ActionQualifier
    {
        enum class Qualifier
        {
            N, R, S, P,
            L = TimedQualifier::L, D, SD, DS, SL
        }

        Qualifier qualifier;
        ActionTime time;
    };

    enum class TimedQualifier
    {
        L = 1 << 10, D, SD, DS, SL
    };

    struct ActionTime : Variant<Duration, VariableName>
    {
    };

    struct IndicatorName
    {
        VariableName variableName;
    };

    struct TransitionName
    {
        Identifier identifier;
    };

    struct Transition
    {
        TransitionName name;
        Integer priority;
        Steps from;
        Steps to;
    };

    struct Steps
    {
        std::vector<StepName> names;
    };

    struct Action
    {
    };


#pragma mark - B.1.7 Configuration elements

    struct ConfigurationName : Identifier
    {
    };

    struct ResourceTypeName : Identifier
    {
    };

    struct SingleResourceReference;
    struct AccessDeclaration;


    struct ConfigurationDeclaration
    {
        ConfigurationName name;
        GlobalVarReference::List varReferenceList;

        struct References : Variant<SingleResourceReference, std::vector<ResourceReference>>
        {
        };
        References references;
        AccessDeclaration accessDeclaration;
        InstanceSpecificInitializations specificInitializations;
    };

    struct ResourceDeclaration
    {
        ResourceName resourceName;
        ResourceTypeName typeName;
        GlobalVariableDeclaration variableDeclaration;
        SingleResourceDeclaration resourceDeclaration;
    };

    struct SingleResourceDeclaration
    {
        std::vector<TaskConfiguration> taskConfigurations;
        std::vector<ProgrammConfiguration> programConfigurations;
    };

    struct ResourceName
    {
        Identifier name;
    };

    struct AccessPath
    {
        ResourceName resourceName;
        Variant<SymbolicVariable, DirectVariable> variable;
    };

    struct AccessName : Identifier
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

    };



    struct ProgramOutputReference
    {
    };

    struct ProgramName : Identifier
    {
    };

    struct TaskConfiguration
    {
        TaskName name;
        TaskInitialization initialization;
    };

    struct TaskName
    {
        Identifier identifier;
    };

    struct TaskInitialization
    {
        DataSource                  singleSource;
        DataSource                  intervalSource;
        Integer                     priority;
    };

    struct DataSource : Variant<Constant, GlobalVarReference, ProgramOutputReference, DirectVariable>
    {
    };

    struct ProgramConfiguration
    {
        ProgramName                 name;
        TaskName                    taskName;
        ProgramTypeName             typeName;
        ProgConfElements            configurationElement;
    };

    struct ProgConfElements
    {

    };

    struct ProgConfElement : Variant<FBTask, ProgCnxn>
    {
    };

    struct FBTask
    {
        FBName name;
        TaskName taskName;
    };

    struct ProgCnxn
    {
        SymbolicVariable variable;

        sturct Data : Variant<ProgDataSource, DataSource>
        {
        };

        Data data;
    };

    struct ProgDataSource : Variant<Constant, EnumeratedValue, GlobalVarReference, DirectVariable>
    {
        using base = Variant<Constant, EnumeratedValue, GlobalVarReference, DirectVariable>;
        using base::base;
    };

    struct DataSink : Variant<GlobalVarReference, DirectVariable>
    {
        using base = Variant<GlobalVarReference, DirectVariable>;
        using base::base;
    };


    struct InstanceSpecificInit
    {
        struct Variable {
            ResourceName resourceName;
            ProgramName programName;
            FBName fbName;
            VariableName variableName;
            Location location;
            LocatedVarSpecInit specInit;
        }

        struct FunctionBlock {
            FBName fbName;
            FunctionBlockTypeName type_name;

        };
    };

    struct InstanceSpecificInitialization : std::vector<InstanceSpecificInit>
    {
        struct Inits : std::vector<instance_specific_init>
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

	struct ILFormalFunctionCall
	{
		FunctionName name;
		std::optionl<ILParamList> paramList;
	};

    enum class ILCallOperator;
    struct IL_param_list;
    struct ILFbCall
    {
        struct fb
        {
            ForwardAst<ILCallOperator> call_operator;
            FbName name;
            // boost::optional
            ForwardAst<IL_param_list> param_list;
        };

        std::variant<fb, ILOperandList> TODO_name;
    };

    struct IL_param_instruction;
    struct IL_param_list : std::vector<IL_param_instruction>
    {
        using base_type = std::vector<IL_param_instruction>;
        using base_type::base_type;
    };

    struct ILFormalFunctCall
    {
        // todo function_name
        std::string name;
        IL_param_list param_list;
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
        std::vector<XorExpressions> operands;
    };

    struct AndExpression;
    struct XorExpression
    {
        std::vector<AndExpressions> operands;
    };

    struct Comparison;
    struct EquExpression;
    struct AndExpression
    {
        struct ComparisonNQ : Comparison { };
        struct ComparisonEQ : Comparison { };

        std::vector<Comparision> operands;
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
        ValueWrapper<Term> firstOperand;
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
        ValueWrapper<AddExpression> secondOperator;
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
        ValueWrapper<EquExpression> firstOperand;
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


    struct AndExpression
    {
        Comparison first_compare;
        std::vector<Comparison> compares;
    };

    struct XorExpression
    {
        AndExpression first_and;
        std::vector<AndExpression> ands;
    };

    struct Expression
    {
        XorExpression first_expression;
        std::vector<XorExpression> xors;
    };

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

    // TODO:
    struct SubprogramControlStatement : Variant<Return, FBInvocation>
    {
        using base = Variant<Return, FBInvocation>;
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
        ,SignedInteger
        ,EnumeratedValue>
    {
        using base_type = std::variant<Subrange, EnumeratedValue>;
        using base_type::base_type;
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
        ,repeat_statement
        ,exit_statement>
    {
        using base_type = std::variant<ForStatement, WhileStatement, RepeatStatement ,exit_statement>;
        using base_type::base_type;
    };

}}}
