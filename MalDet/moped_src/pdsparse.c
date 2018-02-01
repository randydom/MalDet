/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         pdsparse
#define yylex           pdslex
#define yyerror         pdserror
#define yydebug         pdsdebug
#define yynerrs         pdsnerrs

#define yylval          pdslval
#define yychar          pdschar

/* Copy the first part of user declarations.  */
#line 1 "pdsparse.y" /* yacc.c:339  */


#include <string.h>

#include "pds.h"
#include "common.h"
#include "variables.h"
#include "reorder.h"
#include "ftree.h"
#include "expr.h"

//int pdslineno = 1;
int pds_p1, pds_y1, pds_p2, pds_y2, pds_y3;
int pp_current_label;
int pdslex();

void pdserror (char*);

extern PushdownSystem mc_pds;
extern int mc_verbose;
extern int mc_restrict;
extern NameTreeList mc_atoms;


#line 99 "pdsparse.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int pdsdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LABEL = 258,
    IDENT = 259,
    NUMBER = 260,
    QUANT = 261,
    PDS_OR = 262,
    PDS_AND = 263,
    PDS_NOT = 264,
    PDS_EQV = 265,
    PDS_XOR = 266,
    PDS_PLUS = 267,
    PDS_MINUS = 268,
    PDS_MULT = 269,
    PDS_DIV = 270,
    PDS_SHL = 271,
    PDS_LE = 272,
    PDS_EQ = 273,
    PDS_NE = 274,
    PDS_GE = 275,
    PDS_FORALL = 276,
    PDS_EXISTS = 277,
    ARROW = 278,
    PRIME = 279,
    GLOBAL = 280,
    LOCAL = 281,
    BOOL = 282,
    INT = 283,
    DEFINE = 284,
    ATOMS = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 27 "pdsparse.y" /* yacc.c:355  */

	char *string;
	int integer;
	NameStack stack;
	NameSet set;
	Name name;
	DdNode *bdd;
	DdNode **varptr;
	ident_t ident;
	identref_t identref;
	FormulaTree etree;
	block_t block;
	const_t quant;

#line 182 "pdsparse.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE pdslval;

int pdsparse (void);



/* Copy the second part of user declarations.  */

#line 199 "pdsparse.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   242

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  182

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      32,    31,     2,     2,    33,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
      37,     2,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    88,    88,    90,    98,    99,   101,   144,   145,   147,
     148,   162,   163,   165,   168,   174,   180,   181,   188,   189,
     191,   192,   194,   203,   212,   215,   221,   228,   229,   233,
     239,   244,   250,   256,   263,   268,   274,   275,   277,   277,
     279,   280,   282,   303,   304,   307,   313,   322,   331,   337,
     342,   348,   349,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   366,   374,   383,   389,   395,   405,   411,   418,
     419,   420,   421,   422,   423,   430,   441,   442,   443,   445,
     446,   447,   448,   449,   450,   452,   460,   466,   472,   474,
     475,   476,   477,   478,   479,   480
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LABEL", "IDENT", "NUMBER", "QUANT",
  "PDS_OR", "PDS_AND", "PDS_NOT", "PDS_EQV", "PDS_XOR", "PDS_PLUS",
  "PDS_MINUS", "PDS_MULT", "PDS_DIV", "PDS_SHL", "PDS_LE", "PDS_EQ",
  "PDS_NE", "PDS_GE", "PDS_FORALL", "PDS_EXISTS", "ARROW", "PRIME",
  "GLOBAL", "LOCAL", "BOOL", "INT", "DEFINE", "ATOMS", "')'", "'('", "','",
  "';'", "'['", "']'", "'<'", "'>'", "'{'", "'}'", "$accept", "automaton",
  "defines", "vardecl", "globals", "locals", "optproc", "symblist",
  "symbols", "varlist", "decl", "boollist", "boolident", "intident",
  "optdim", "intlist", "startconfig", "startstate", "startident",
  "stackident", "stacklist", "atoms", "atom", "$@1", "proplist",
  "propident", "transitionlist", "transition", "simp_trans_wrap",
  "simple_transition", "label", "expr", "quant", "expression", "boolvar",
  "indexvar", "intexpr", "intterm", "comp_op", "variable", "varident",
  "constexp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    41,    40,    44,    59,    91,    93,    60,    62,   123,
     125
};
# endif

#define YYPACT_NINF -90

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-90)))

#define YYTABLE_NINF -67

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -90,     4,    -3,   -90,   -12,   105,   -22,   -90,    21,    35,
     -12,   -90,     8,     8,    81,   -90,    36,    47,    78,   -90,
      47,   -90,   115,   -90,   -90,     8,   193,   193,   -90,    60,
      71,    77,   111,     8,   -90,    21,   -90,   110,    35,   -90,
      86,     8,     8,     8,     8,     8,   141,     2,   146,   -90,
     149,   -90,   130,    80,   -90,     8,   -90,   -90,    50,    50,
     147,   147,   -90,   -90,   151,   142,   -90,   -90,   -90,     2,
     178,   178,     2,    52,   177,   159,   -90,   133,   -90,   109,
      73,   165,   -90,   155,   -90,   190,   -90,   206,   -12,     8,
     -90,   163,     2,   180,   -90,   -90,   181,   184,   150,   -90,
      74,   182,     2,     2,     2,     2,   -90,    52,    52,    52,
      52,    52,   -90,   -90,   -90,   -90,   -90,   -90,    52,    52,
     191,   214,   221,   -90,   194,   -90,    44,   -12,   118,   -90,
     196,   -90,     8,     8,   -90,   -90,   204,   -90,    10,   148,
      58,    58,   212,   212,   -90,   208,   123,   -90,   -90,   197,
     -90,   195,     2,   -90,   225,   -90,   -90,   153,   158,   -90,
     214,   209,   200,   -90,     8,     8,   -90,   230,   -90,   183,
     188,   198,     2,     2,    15,   177,   177,    23,   -90,   199,
     -90,   -90
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     8,     1,     0,     0,     0,     9,     0,     0,
       7,    16,     0,     0,     0,    36,     6,    24,     0,    20,
      24,    27,     0,    17,    95,     0,     3,     4,    32,     0,
      30,    43,    12,     0,    22,     0,    18,     0,     0,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
       2,    11,     0,     0,    21,     0,    28,    94,    89,    90,
      91,    92,    93,    33,    34,     0,    88,    77,    76,     0,
       0,     0,     0,     0,    64,     0,    53,    75,    54,     0,
      74,    85,    38,     0,    44,    51,    47,     0,     0,     0,
      25,     0,     0,     0,    60,    63,     0,     0,     0,    75,
       0,    74,     0,     0,     0,     0,    31,     0,     0,     0,
       0,     0,    80,    81,    82,    83,    79,    84,     0,     0,
      86,     0,     0,    52,    45,    14,     0,    10,     0,    23,
       0,    29,     0,     0,    55,    78,    56,    57,    58,    59,
      69,    70,    71,    72,    73,    68,     0,    87,    42,    39,
      40,     0,     0,    13,     0,    26,    35,     0,     0,    67,
       0,     0,     0,    15,     0,     0,    41,     0,    46,     0,
       0,     0,     0,     0,     0,    61,    62,     0,    50,     0,
      49,    48
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   152,
      -9,   -90,   201,   203,   218,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,    79,   -90,   -90,   -90,   -90,
     -90,   -67,   171,   -89,   -90,   -64,   -90,   -59,   -90,   -40,
     -90,   -13
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,     7,    16,    52,    88,   126,    10,
      11,    18,    19,    21,    34,    22,    15,    29,    30,    64,
      65,    31,    49,   121,   149,   150,    50,    84,    85,    86,
     124,    74,    96,    75,    76,    77,    78,    79,   118,    80,
      81,    26
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      27,    23,    94,   130,     3,    98,    66,    67,    68,    99,
      14,    69,    40,    24,   100,     8,     9,   102,   103,   177,
      53,   105,     4,    70,    71,    17,     5,   179,    58,    59,
      60,    61,    62,   101,    72,   136,   137,   138,   139,    20,
      25,    73,    91,    99,    99,    99,    99,    99,   140,   141,
     142,   143,   144,   178,    99,    99,    66,    67,    68,   145,
     146,   180,    32,   162,    43,    44,    45,   101,   101,   101,
     101,   101,   109,   110,   111,   153,   128,   154,   101,   101,
     -65,   -65,    33,   -65,   -65,    28,   107,   108,   109,   110,
     111,    73,    41,    42,    43,    44,    45,    46,    41,    42,
      43,    44,    45,    47,   -65,   175,   176,    48,   119,    12,
      13,    35,    36,    89,   135,    51,    90,    57,    23,   157,
     158,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      41,    42,    43,    44,    45,   107,   108,   109,   110,   111,
     -66,   -66,    55,   -66,   -66,    63,   116,   117,    38,    39,
      82,   169,   170,    83,   155,   102,   103,   102,   103,   159,
     104,   105,    87,    45,   -66,    41,    42,    43,    44,    45,
      41,    42,    43,    44,    45,    41,    42,    43,    44,    45,
      93,   134,    95,    92,   102,   103,   164,   104,   105,   120,
     106,   165,   122,   123,   129,    41,    42,    43,    44,    45,
      41,    42,    43,    44,    45,    41,    42,    43,    44,    45,
     125,   131,   103,   132,   172,   147,   133,   119,   148,   173,
     107,   108,   109,   110,   111,   151,   152,   156,   111,   163,
     160,   168,   167,   161,   171,   174,    54,   181,    37,   166,
     127,    56,    97
};

static const yytype_uint8 yycheck[] =
{
      13,    10,    69,    92,     0,    72,     4,     5,     6,    73,
      32,     9,    25,     5,    73,    27,    28,     7,     8,     4,
      33,    11,    25,    21,    22,     4,    29,     4,    41,    42,
      43,    44,    45,    73,    32,   102,   103,   104,   105,     4,
      32,    39,    55,   107,   108,   109,   110,   111,   107,   108,
     109,   110,   111,    38,   118,   119,     4,     5,     6,   118,
     119,    38,    26,   152,    14,    15,    16,   107,   108,   109,
     110,   111,    14,    15,    16,    31,    89,    33,   118,   119,
       7,     8,    35,    10,    11,     4,    12,    13,    14,    15,
      16,    39,    12,    13,    14,    15,    16,    37,    12,    13,
      14,    15,    16,    32,    31,   172,   173,    30,    35,     4,
       5,    33,    34,    33,    40,     4,    36,    31,   127,   132,
     133,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      12,    13,    14,    15,    16,    12,    13,    14,    15,    16,
       7,     8,    32,    10,    11,     4,    37,    38,    33,    34,
       4,   164,   165,     4,    36,     7,     8,     7,     8,    36,
      10,    11,    32,    16,    31,    12,    13,    14,    15,    16,
      12,    13,    14,    15,    16,    12,    13,    14,    15,    16,
      38,    31,     4,    32,     7,     8,    33,    10,    11,    24,
      31,    33,    37,     3,    31,    12,    13,    14,    15,    16,
      12,    13,    14,    15,    16,    12,    13,    14,    15,    16,
       4,    31,     8,    32,    31,    24,    32,    35,     4,    31,
      12,    13,    14,    15,    16,     4,    32,    31,    16,     4,
      33,    31,    23,    38,     4,    37,    35,    38,    20,   160,
      88,    38,    71
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    42,    43,     0,    25,    29,    44,    45,    27,    28,
      50,    51,     4,     5,    32,    57,    46,     4,    52,    53,
       4,    54,    56,    51,     5,    32,    82,    82,     4,    58,
      59,    62,    26,    35,    55,    33,    34,    55,    33,    34,
      82,    12,    13,    14,    15,    16,    37,    32,    30,    63,
      67,     4,    47,    82,    53,    32,    54,    31,    82,    82,
      82,    82,    82,     4,    60,    61,     4,     5,     6,     9,
      21,    22,    32,    39,    72,    74,    75,    76,    77,    78,
      80,    81,     4,     4,    68,    69,    70,    32,    48,    33,
      36,    82,    32,    38,    72,     4,    73,    73,    72,    76,
      78,    80,     7,     8,    10,    11,    31,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    37,    38,    79,    35,
      24,    64,    37,     3,    71,     4,    49,    50,    82,    31,
      74,    31,    32,    32,    31,    40,    72,    72,    72,    72,
      78,    78,    78,    78,    78,    78,    78,    24,     4,    65,
      66,     4,    32,    31,    33,    36,    31,    82,    82,    36,
      33,    38,    74,     4,    33,    33,    66,    23,    31,    82,
      82,     4,    31,    31,    37,    72,    72,     4,    38,     4,
      38,    38
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    43,    43,    43,    44,    45,    45,    46,
      46,    47,    47,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    53,    54,    55,    55,    55,    56,    56,    57,
      58,    58,    59,    60,    61,    61,    62,    62,    64,    63,
      65,    65,    66,    67,    67,    68,    68,    69,    70,    70,
      70,    71,    71,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    73,    74,    75,    75,    76,    77,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    79,
      79,    79,    79,    79,    79,    80,    80,    80,    81,    82,
      82,    82,    82,    82,    82,    82
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     4,     4,     0,     2,     2,     0,     0,
       5,     1,     0,     3,     1,     3,     1,     2,     3,     3,
       1,     3,     2,     5,     0,     3,     5,     1,     3,     6,
       1,     4,     1,     1,     1,     4,     0,     2,     0,     4,
       1,     3,     1,     0,     2,     2,     5,     1,    10,     9,
       8,     0,     1,     1,     1,     3,     3,     3,     3,     3,
       2,     8,     8,     1,     1,     1,     1,     4,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     1,     3,
       3,     3,     3,     3,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 91 "pdsparse.y" /* yacc.c:1646  */
    {
		const_t con = common_malloc(sizeof(struct const_element));
		con->name = (yyvsp[-1].name);
		con->value = (yyvsp[0].integer);
		con->next = constlist;
		constlist = con;
	  }
#line 1426 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 6:
#line 102 "pdsparse.y" /* yacc.c:1646  */
    {
		block_t tmp;
		mc_blocks = common_malloc(sizeof(struct block_element));
		mc_blocks->procname = 0;
		mc_blocks->names = NULL;
		mc_blocks->idents = (yyvsp[-1].ident);
		mc_blocks->next = mc_maxblock = tmp = (yyvsp[0].block);

		global_vars = (yyvsp[-1].ident)? (yyvsp[-1].ident)->index + ((yyvsp[-1].ident)->type? (yyvsp[-1].ident)->type : 1)
					    * ((yyvsp[-1].ident)->dim? (yyvsp[-1].ident)->dim : 1) : 0;
		local_vars = 0;
		while (tmp)
		{
			ident_t id = tmp->idents;
			int x = id? id->index + (id->type? id->type : 1)
						* (id->dim? id->dim : 1) : 0;
			if (x>local_vars) { mc_maxblock = tmp; local_vars = x; }
			tmp = tmp->next;
		}

		for (tmp = mc_blocks; tmp; tmp = tmp->next)
		{
			ident_t id = tmp->idents, nl = NULL, tmpid;
			
			while (id)
			{
				tmpid = id->next;
				id->next = nl;
				nl = id;
				id = tmpid;
			}
			tmp->idents = nl;
		}

		pds_p1 = pds_y1 = pds_p2 = pds_y2 = pds_y3 = 0;
		idchain = NULL;
		init_cudd();

		for (tmp = mc_blocks; tmp; tmp = tmp->next)
			build_properties(tmp);
	  }
#line 1472 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 7:
#line 144 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.ident) = (yyvsp[0].ident);   }
#line 1478 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 8:
#line 145 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.ident) = NULL; }
#line 1484 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 9:
#line 147 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.block) = NULL; local_vars = 0; }
#line 1490 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 10:
#line 149 "pdsparse.y" /* yacc.c:1646  */
    {
		NameSet set;
		(yyval.block) = common_malloc(sizeof(struct block_element));
		(yyval.block)->procname = (yyvsp[-2].name);
		(yyval.block)->names = (yyvsp[-1].set);
		(yyval.block)->idents = (yyvsp[0].ident);
		(yyval.block)->next = (yyvsp[-4].block);
		for (set = (yyval.block)->names; set; set = set->next)
			name_tree_insert(&mc_localtree,
				name_tree_mknode(set->name,0,(yyval.block)));
		local_vars = 0;
	  }
#line 1507 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 12:
#line 163 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.name) = 0; }
#line 1513 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 13:
#line 166 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.set) = (yyvsp[-1].set); }
#line 1519 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 14:
#line 169 "pdsparse.y" /* yacc.c:1646  */
    {
		NameSet set = NULL;
		name_set_insert(&set,(yyvsp[0].name));
		(yyval.set) = set;
	  }
#line 1529 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 15:
#line 175 "pdsparse.y" /* yacc.c:1646  */
    {
		name_set_insert(&(yyvsp[-2].set),(yyvsp[0].name));
		(yyval.set) = (yyvsp[-2].set);
	  }
#line 1538 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 17:
#line 182 "pdsparse.y" /* yacc.c:1646  */
    {
		(yyval.ident) = (yyvsp[0].ident);
		while ((yyvsp[0].ident)->next) (yyvsp[0].ident) = (yyvsp[0].ident)->next;
		(yyvsp[0].ident)->next = (yyvsp[-1].ident);
	  }
#line 1548 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 18:
#line 188 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.ident) = (yyvsp[-1].ident); }
#line 1554 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 19:
#line 189 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.ident) = (yyvsp[-1].ident); }
#line 1560 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 20:
#line 191 "pdsparse.y" /* yacc.c:1646  */
    { ((yyval.ident) = (yyvsp[0].ident))->next = NULL; }
#line 1566 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 21:
#line 192 "pdsparse.y" /* yacc.c:1646  */
    { ((yyval.ident) = (yyvsp[0].ident))->next = (yyvsp[-2].ident); }
#line 1572 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 22:
#line 195 "pdsparse.y" /* yacc.c:1646  */
    {
		(yyval.ident) = (yyvsp[0].ident);
		(yyval.ident)->varname = (yyvsp[-1].name);
		(yyval.ident)->type = 0;
		(yyval.ident)->index = local_vars;
		local_vars += (yyval.ident)->dim? (yyval.ident)->dim : 1;
	   }
#line 1584 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 23:
#line 204 "pdsparse.y" /* yacc.c:1646  */
    {
		(yyval.ident) = (yyvsp[-3].ident);
		(yyval.ident)->varname = (yyvsp[-4].name);
		if ((yyvsp[-1].integer) <= 0) pdserror("positive integer expected");
		(yyval.ident)->index = local_vars;
		local_vars += ((yyval.ident)->type = (yyvsp[-1].integer)) * ((yyval.ident)->dim? (yyval.ident)->dim : 1);
	  }
#line 1596 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 24:
#line 212 "pdsparse.y" /* yacc.c:1646  */
    {
		((yyval.ident) = common_malloc(sizeof(struct ident_element)))->dim = 0; 
	  }
#line 1604 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 25:
#line 216 "pdsparse.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-1].integer) <= 0) pdserror("positive integer expected");
		(yyval.ident) = common_malloc(sizeof(struct ident_element));
		(yyval.ident)->dim = (yyvsp[-1].integer); (yyval.ident)->lo = 0; (yyval.ident)->hi = (yyvsp[-1].integer)-1;
	  }
#line 1614 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 26:
#line 222 "pdsparse.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-3].integer) < 0) pdserror("nonnegative integer expected");
		(yyval.ident) = common_malloc(sizeof(struct ident_element));
		(yyval.ident)->dim = (yyvsp[-1].integer)-(yyvsp[-3].integer)+1; (yyval.ident)->lo = (yyvsp[-3].integer); (yyval.ident)->hi = (yyvsp[-1].integer);
	  }
#line 1624 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 27:
#line 228 "pdsparse.y" /* yacc.c:1646  */
    { ((yyval.ident) = (yyvsp[0].ident))->next = NULL; }
#line 1630 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 28:
#line 229 "pdsparse.y" /* yacc.c:1646  */
    { ((yyval.ident) = (yyvsp[0].ident))->next = (yyvsp[-2].ident); }
#line 1636 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 29:
#line 234 "pdsparse.y" /* yacc.c:1646  */
    {
		mc_pds.start_stack = (yyvsp[-2].stack);
	  }
#line 1644 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 30:
#line 240 "pdsparse.y" /* yacc.c:1646  */
    {
		mc_pds.start_state = (yyvsp[0].name);
		mc_pds.start_bdd = fullset;
	  }
#line 1653 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 31:
#line 245 "pdsparse.y" /* yacc.c:1646  */
    {
		mc_pds.start_state = (yyvsp[-3].name);
		mc_pds.start_bdd = (yyvsp[-1].bdd);
	  }
#line 1662 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 32:
#line 251 "pdsparse.y" /* yacc.c:1646  */
    {
		pds_p1 = (yyval.name) = (yyvsp[0].name);
		pds_y1 = pds_p2 = pds_y2 = pds_y3 = 0;
	    }
#line 1671 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 33:
#line 257 "pdsparse.y" /* yacc.c:1646  */
    {
		pds_y1 = (yyval.name) = (yyvsp[0].name);
		pds_p1 = pds_p2 = pds_y2 = pds_y3 = 0;
	    }
#line 1680 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 34:
#line 264 "pdsparse.y" /* yacc.c:1646  */
    {
		(yyval.stack) = name_stack_empty();
		name_stack_push(&(yyval.stack),(yyvsp[0].name),fullset);
	  }
#line 1689 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 35:
#line 269 "pdsparse.y" /* yacc.c:1646  */
    {
		(yyval.stack) = name_stack_empty();
		name_stack_push(&(yyval.stack),(yyvsp[-3].name),(yyvsp[-1].bdd));
	  }
#line 1698 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 38:
#line 277 "pdsparse.y" /* yacc.c:1646  */
    { pp_current_label = (yyvsp[0].name); }
#line 1704 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 42:
#line 283 "pdsparse.y" /* yacc.c:1646  */
    {
		int propos = (yyvsp[0].name);
		NameTreeList tmp = mc_atoms;

		while (tmp)
		{
			if (tmp->name == propos) break;
			tmp = tmp->next;
		}
		if (!tmp)
		{
			tmp = common_malloc(sizeof(struct NameTreeListStruct));
			tmp->name = propos;
			tmp->tree = NULL;
			tmp->next = mc_atoms;
			mc_atoms = tmp;
		}
		name_bal_insert(&(tmp->tree),pp_current_label);
	}
#line 1728 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 45:
#line 308 "pdsparse.y" /* yacc.c:1646  */
    {
		pds_insert_trans(&mc_pds, pds_p1, pds_y1, pds_p2, pds_y2,
					  pds_y3, fullset, (yyvsp[0].string), 0);
		if ((yyvsp[0].string)) free((yyvsp[0].string));
	  }
#line 1738 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 46:
#line 314 "pdsparse.y" /* yacc.c:1646  */
    {
		pds_insert_trans(&mc_pds, pds_p1, pds_y1, pds_p2, pds_y2,
					  pds_y3, (yyvsp[-1].bdd), (yyvsp[-3].string), 0);
		Cudd_RecursiveDeref(mc_mgr,(yyvsp[-1].bdd));
		if ((yyvsp[-3].string)) free((yyvsp[-3].string));
	  }
#line 1749 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 47:
#line 323 "pdsparse.y" /* yacc.c:1646  */
    {
		if (mc_verbose > 1) fprintf(stdout,"-## %s %s %s %s %s\n",
			name_cstring(pds_p1),name_cstring(pds_y1),
			name_cstring(pds_p2),name_cstring(pds_y2),
			name_cstring(pds_y3));
	  }
#line 1760 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 48:
#line 332 "pdsparse.y" /* yacc.c:1646  */
    { 
		pds_p1 = (yyvsp[-9].name); pds_y1 = (yyvsp[-7].name);
		pds_p2 = (yyvsp[-4].name); pds_y2 = (yyvsp[-2].name);
		pds_y3 = (yyvsp[-1].name);
	  }
#line 1770 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 49:
#line 338 "pdsparse.y" /* yacc.c:1646  */
    {
		pds_p1 = (yyvsp[-8].name); pds_y1 = (yyvsp[-6].name);
		pds_p2 = (yyvsp[-3].name); pds_y2 = (yyvsp[-1].name); pds_y3 = 0;
	  }
#line 1779 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 50:
#line 343 "pdsparse.y" /* yacc.c:1646  */
    { 
		pds_p1 = (yyvsp[-7].name); pds_y1 = (yyvsp[-5].name);
		pds_p2 = (yyvsp[-2].name); pds_y2 = pds_y3 = 0;
	  }
#line 1788 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 51:
#line 348 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.string) = NULL; }
#line 1794 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 55:
#line 353 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = (yyvsp[-1].etree); }
#line 1800 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 56:
#line 354 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = etree_create(E_OR,0,(yyvsp[-2].etree),(yyvsp[0].etree)); }
#line 1806 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 57:
#line 355 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = etree_create(E_AND,0,(yyvsp[-2].etree),(yyvsp[0].etree)); }
#line 1812 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 58:
#line 356 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = etree_create(E_EQV,0,(yyvsp[-2].etree),(yyvsp[0].etree)); }
#line 1818 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 59:
#line 357 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = etree_create(E_XOR,0,(yyvsp[-2].etree),(yyvsp[0].etree)); }
#line 1824 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 60:
#line 358 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = etree_create(E_NOT,0,(yyvsp[0].etree),NULL); }
#line 1830 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 61:
#line 360 "pdsparse.y" /* yacc.c:1646  */
    {
		quantlist->lower = (yyvsp[-4].integer);
		quantlist->upper = (yyvsp[-2].integer);
		(yyval.etree) = etree_create(E_FORALL,(identref_t)quantlist,(yyvsp[0].etree),NULL);
		quantlist = quantlist->next;
	  }
#line 1841 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 62:
#line 367 "pdsparse.y" /* yacc.c:1646  */
    {
		quantlist->lower = (yyvsp[-4].integer);
		quantlist->upper = (yyvsp[-2].integer);
		(yyval.etree) = etree_create(E_EXISTS,(identref_t)quantlist,(yyvsp[0].etree),NULL);
		quantlist = quantlist->next;
	  }
#line 1852 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 63:
#line 375 "pdsparse.y" /* yacc.c:1646  */
    {
		const_t q;
		q = common_malloc(sizeof(struct const_element));
		q->name = (yyvsp[0].name);
		q->next = quantlist;
		quantlist = q;
	  }
#line 1864 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 64:
#line 384 "pdsparse.y" /* yacc.c:1646  */
    {
		(yyval.bdd) = build_expr((yyvsp[0].etree));
		free_expr_tree((yyvsp[0].etree));
	  }
#line 1873 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 65:
#line 390 "pdsparse.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].identref)->ident->type) pdserror("boolean variable expected");
		if ((yyvsp[0].identref)->ident->dim) pdserror("missing subscript");
		(yyval.etree) = etree_create(E_BVAR,(yyvsp[0].identref),NULL,NULL);
	  }
#line 1883 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 66:
#line 396 "pdsparse.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].etree)->idref->ident->type)
			pdserror("boolean variable expected");
		(yyval.etree) = (yyvsp[0].etree);
		(yyvsp[0].etree)->token = E_BVAR;
		(yyvsp[0].etree)->left = (FormulaTree) idchain;
		idchain = NULL;
	  }
#line 1896 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 67:
#line 406 "pdsparse.y" /* yacc.c:1646  */
    {
		if (!(yyvsp[-3].identref)->ident->dim) pdserror("unexpected subscript");
		(yyval.etree) = etree_create(0,(yyvsp[-3].identref),NULL,(yyvsp[-1].etree));
	  }
#line 1905 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 68:
#line 412 "pdsparse.y" /* yacc.c:1646  */
    {
		FormulaTree tree = etree_create((yyvsp[-1].integer),0,(yyvsp[-2].etree),(yyvsp[0].etree));
		(yyval.etree) = etree_create(E_IEXPR,0,idchain,tree);
		idchain = NULL;
	  }
#line 1915 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 69:
#line 418 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = etree_create(E_PLUS,0,(yyvsp[-2].etree),(yyvsp[0].etree)); }
#line 1921 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 70:
#line 419 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = etree_create(E_MINUS,0,(yyvsp[-2].etree),(yyvsp[0].etree)); }
#line 1927 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 71:
#line 420 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = etree_create(E_MULT,0,(yyvsp[-2].etree),(yyvsp[0].etree)); }
#line 1933 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 72:
#line 421 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = etree_create(E_DIV,0,(yyvsp[-2].etree),(yyvsp[0].etree)); }
#line 1939 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 73:
#line 422 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = etree_create(E_SHL,0,(yyvsp[-2].etree),(yyvsp[0].etree)); }
#line 1945 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 74:
#line 424 "pdsparse.y" /* yacc.c:1646  */
    {
		if (!(yyvsp[0].identref)->ident->type) pdserror("integer variable expected");
		(yyvsp[0].identref) = add_to_idchain((yyvsp[0].identref));
		(yyval.etree) = etree_create(E_IDENT,(yyvsp[0].identref),NULL,NULL);
		if ((yyvsp[0].identref)->ident->dim) pdserror("missing subscript");
	  }
#line 1956 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 75:
#line 431 "pdsparse.y" /* yacc.c:1646  */
    {
		if (!(yyvsp[0].etree)->idref->ident->type)
			pdserror("integer variable expected");
		(yyval.etree) = (yyvsp[0].etree);
		(yyval.etree)->token = E_IDENT;
		(yyvsp[0].etree)->idref->sub = (yyvsp[0].etree)->right;
		(yyvsp[0].etree)->idref->next = idchain;
		idchain = (yyvsp[0].etree)->idref;
		(yyvsp[0].etree)->right = NULL;
	  }
#line 1971 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 76:
#line 441 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = etree_create(E_QUANT,(identref_t)(yyvsp[0].quant),NULL,NULL); }
#line 1977 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 77:
#line 442 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = etree_create(E_NUMBER,(identref_t)(yyvsp[0].integer),NULL,NULL); }
#line 1983 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 78:
#line 443 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.etree) = (yyvsp[-1].etree); }
#line 1989 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 79:
#line 445 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = E_LT; }
#line 1995 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 80:
#line 446 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = E_LE; }
#line 2001 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 81:
#line 447 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = E_EQ; }
#line 2007 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 82:
#line 448 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = E_NE; }
#line 2013 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 83:
#line 449 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = E_GE; }
#line 2019 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 84:
#line 450 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = E_GT; }
#line 2025 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 85:
#line 453 "pdsparse.y" /* yacc.c:1646  */
    {				/* in init cfg: (x,y) -> (p,y) */
		if (pds_p1 * pds_y1 == 0)
		    (yyval.identref) = find_ident(pds_y1, (yyvsp[0].name), pds_p1? pvars : NULL, yvars);
		else
		    (yyval.identref) = find_ident(pds_y1, (yyvsp[0].name), ppvars, ypvars);
		if (!(yyval.identref)) pdserror("invalid identifier");
	  }
#line 2037 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 86:
#line 461 "pdsparse.y" /* yacc.c:1646  */
    {
		if (pds_p1 * pds_y1 == 0) pdserror("invalid identifier");
		(yyval.identref) = find_ident(pds_y2, (yyvsp[-1].name), pvars, yvars);
		if (!(yyval.identref)) pdserror("invalid identifier");
	  }
#line 2047 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 87:
#line 467 "pdsparse.y" /* yacc.c:1646  */
    {
		(yyval.identref) = find_ident(mc_restrict? 0 : pds_y3, (yyvsp[-2].name), NULL, yppvars);
		if (!(yyval.identref)) pdserror("invalid identifier");
	  }
#line 2056 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 89:
#line 474 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[-2].integer) + (yyvsp[0].integer); }
#line 2062 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 90:
#line 475 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[-2].integer) - (yyvsp[0].integer); }
#line 2068 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 91:
#line 476 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[-2].integer) * (yyvsp[0].integer); }
#line 2074 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 92:
#line 477 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[-2].integer) / (yyvsp[0].integer); }
#line 2080 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 93:
#line 478 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[-2].integer) << (yyvsp[0].integer); }
#line 2086 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 94:
#line 479 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[-1].integer); }
#line 2092 "pdsparse.c" /* yacc.c:1646  */
    break;

  case 95:
#line 480 "pdsparse.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].integer); }
#line 2098 "pdsparse.c" /* yacc.c:1646  */
    break;


#line 2102 "pdsparse.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 482 "pdsparse.y" /* yacc.c:1906  */


#include "pdslex.c"

void pdserror (char *info)
{ 
	common_error("syntax error in pushdown system: %s, line %d",
			info,pdslineno);
}

void parse_pds (char *filename)
{
	mc_pds = pds_empty();
	quantlist = NULL;
	mc_localtree = NULL;
	mc_atoms = NULL;

	if (!(pdsin = fopen(filename,"r")))
		common_error("modelfile %s not found", filename);

	if (pdsparse())
		common_error("parse errors encountered while reading pds");

	fclose(pdsin);
}
