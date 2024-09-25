// Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara
/**
 * @file defines.h
 * @brief Declaration of Basic Data types
 * @ingroup BasicDataTypes
 */

#ifndef LBA_DEFINES_H
#define LBA_DEFINES_H

/**
 * @name The #defines used in our appliation
 */

/**
 * @def NULL
 * @ingroup BasicDataTypes
 */
#ifndef NULL
    #define NULL    (0)
#endif

/**
 * @def MAX_ASCII_CHAR_LIMIT
 * @brief caters to ASCII & ext-ASCII: limit = 255 
 * @ingroup BasicDataTypes
 */
#define MAX_ASCII_CHAR_LIMIT    (255)       

/**
 * @def MAX_UNICODE_CHAR_LIMIT
 * @brief caters to full UTF16 range
 * @ingroup BasicDataTypes
 */
#define MAX_UNICODE_CHAR_LIMIT  (65535) 

/**
 * @def MAX_CHAR_LIMIT
 * @ingroup BasicDataTypes
 */
#ifdef _UNICODE
    #define MAX_CHAR_LIMIT      MAX_UNICODE_CHAR_LIMIT
#else
    #define MAX_CHAR_LIMIT      MAX_ASCII_CHAR_LIMIT
#endif

/**
 * @def LONGLONG_ZERO
 * @ingroup BasicDataTypes
 */

/**
 * @def LONGLONG_MAX
 * @ingroup BasicDataTypes
 */

/**
 * @def LONGLONG_MIN
 * @ingroup BasicDataTypes
 */

/**
 * @def PERIOD_STRING
 */
#define PERIOD_STRING              _TEXT (".")

/**
 * @def DOUBLE_PERIOD_STRING
 */
#define DOUBLE_PERIOD_STRING       _TEXT ("..")

#ifdef __LINUX__
    // Need to define for other platforms as well
    //#define LONG_MAXINT     LONG_MAX
    #define LLONG_MAX       9223372036854775807LL
    #define LLONG_MIN       (-LLONG_MAX - 1LL)
    #define LONGLONG_ZERO   0LL
    #define LONGLONG_MAX    LLONG_MAX
    #define LONGLONG_MIN    LLONG_MIN
#else
    // For windows it will remain 32 for both 32 and 64 bit
    #define LONG_MAXINT     LONG_MAX
    #define LONGLONG_ZERO   0I64
    #define LONGLONG_MAX    _I64_MAX
    #define LONGLONG_MIN    _I64_MIN
#endif

/**
 * @def UNKNOWN
 * @ingroup BasicDataTypes
 */
#define UNKNOWN                 (-1)

/**
 * @def U_UNKNOWN
 * @ingroup BasicDataTypes
 */
#define U_UNKNOWN               (0xffffffff)

/**
 * @def U64_UNKNOWN
 * @ingroup BasicDataTypes
 */
#define U64_UNKNOWN             (0xffffffffffffffff)


/**
 * @def NIBBLE_MASK
 * @ingroup BasicDataTypes
 */
#define NIBBLE_MASK               (0xf)

/**
 * @def BYTE_MASK
 * @ingroup BasicDataTypes
 */
#define BYTE_MASK               (0xff)

/**
 * @def WORD_MASK
 * @ingroup BasicDataTypes
 */
#define WORD_MASK               (0xffff)

/**
 * @def LONG_MASK
 * @ingroup BasicDataTypes
 */
#define LONG_MASK               (0xffffffff)

/**
 * @def LONG64_MASK
 * @ingroup BasicDataTypes
 */
#define LONG64_MASK             (0xffffffffffffffff)

/**
 * @def HILONG
 * @ingroup BasicDataTypes
 */
#define HILONG(x)               (Long) ((x) >> 32)

/**
 * @def LOLONG
 * @ingroup BasicDataTypes
 */
#define LOLONG(x)               (Long) ((x) & LONG_MASK)

/**
 * @def MAKELONG64
 * @ingroup BasicDataTypes
 */
#define MAKELONG64(hi,lo)       (Long64) ((((Long64) (hi)) << 32) + ((Long64) (lo) & LONG_MASK))

/**
 * @def HEX_NUMBER_BASE 
 * @ingroup  hexadecimal number base
 */
#define HEX_NUMBER_BASE         (16)

/**
 * @name Void and Void pointers
 */

/**
 * @typedef Void
 * @brief Any type
 * @ingroup BasicDataTypes
 */
typedef void                    Void;

/**
 * @typedef VPtr
 * @brief Pointer to any type
 * @ingroup BasicDataTypes
 */
typedef void *                  VPtr;

/**
 * @typedef CVPtr
 * @brief Pointer to any constant data type
 * cannot change the value being pointed by the pointer
 * @ingroup BasicDataTypes
 */
typedef void const *            CVPtr;

/**
 * @typedef VCPtr
 * @brief Constant pointer to any data type
 * The location stored in the pointer cannot change or cannot change where this pointer points.
 * @ingroup BasicDataTypes
 */
typedef void * const            VCPtr;

/**
 * @name An unsigned 8-bit data-types
 */

/**
 * @typedef Byte
 * @brief unsigned 8-bit data
 * @ingroup BasicDataTypes
 */
typedef unsigned char           Byte;

/**
 * @typedef BytePtr
 * @brief Pointer to unsigned 8-bit data
 * @ingroup BasicDataTypes
 */
typedef Byte *                  BytePtr;

/**
 * @typedef CBytePtr
 * @brief Pointer to constant unsigned 8-bit data
 * cannot change the value being pointed by the pointer
 * @ingroup BasicDataTypes
 */
typedef Byte const *            CBytePtr;

/**
 * @typedef ByteCPtr
 * @brief Constant pointer to unsigned 8-bit data
 * The location stored in the pointer cannot change or cannot change where this pointer points.
 * @ingroup BasicDataTypes
 */
typedef Byte * const            ByteCPtr;

/**
 * @name Character and string pointers (Platform independent)
 */
/**
 * @typedef Char
 * @brief A wchar_t(16-bit) if UNICODE is defined, a char(8-bit) otherwise
 * @ingroup BasicDataTypes
 */

/**
 * @typedef UChar
 * @brief A wchar_t(16-bit) if UNICODE is defined, a unsigned
 * char(8-bit) otherwise
 * @ingroup BasicDataTypes
 */
#ifdef _UNICODE
    typedef wchar_t             Char;
    typedef wchar_t             UChar;
#else
    typedef char                Char;
    typedef unsigned char       UChar;
#endif

/**
 * @typedef StrPtr
 * @brief Pointer to a null-terminated string of Char
 * @ingroup BasicDataTypes
 */
typedef Char *                  StrPtr;

/**
 * @typedef CStrPtr
 * @brief Pointer to a constant null-terminated string of Char
 * cannot change the value being pointed by the pointer
 * @ingroup BasicDataTypes
 */
typedef Char const *            CStrPtr;
 
/**
 * @typedef StrCPtr
 * @brief Constant pointer to a null-terminated string of Char
 * The location stored in the pointer cannot change or cannot change where this pointer points.
 * @ingroup BasicDataTypes
 */
typedef Char * const            StrCPtr;

/**
 * @name ASCII character and string pointers
 */
/**
 * @typedef AChar
 * @brief  8-bit character
 * @ingroup BasicDataTypes
 */
typedef char                    AChar;

/**
 * @typedef AStrPtr
 * @brief Pointer to a null-terminated string of 8-bit characters
 * @ingroup BasicDataTypes
 */
typedef char *                  AStrPtr;

/**
 * @typedef CAStrPtr
 * @brief Pointer to a constant null-terminated string of 8-bit
 * characters.
 * cannot change the value being pointed by the pointer
 * @ingroup BasicDataTypes
 */
typedef char const *            CAStrPtr;

/**
 * @name Unicode character and string pointers
 */

/**
 * @typedef WChar
 * @brief 16-bit character
 * @ingroup BasicDataTypes
 */
typedef wchar_t                 WChar;

/**
 * @typedef WStrPtr
 * @brief Pointer to a null-terminated string of 16-bit
 * characters
 * @ingroup BasicDataTypes
 */
typedef wchar_t *               WStrPtr;

/**
 * @typedef CWStrPtr
 * @brief Pointer to a constant null-terminated string of 16-bit
 * characters
 * cannot change the value being pointed by the pointer
 * @ingroup BasicDataTypes
 */
typedef wchar_t const *         CWStrPtr;

/**
 * @name 16 bit data-types
 */
/**
 * @typedef Word
 * @brief 16-bit short
 * @ingroup BasicDataTypes
 */
typedef short                   Word;

/**
 * @typedef UWord
 * @brief 16-bit unsigned short
 * @ingroup BasicDataTypes
 */
typedef unsigned short          UWord;

#ifdef __cplusplus
    /**
     * @typedef CWord
     * @brief Constant Word defined for C++ programs only
     * @ingroup BasicDataTypes
     */
    typedef const Word          CWord;
#endif

/**
 * @name 32 bit data-types
 */

/**
 * @typedef Long
 * @brief 32-bit short
 * @ingroup BasicDataTypes
 */
typedef long                    Long;

/**
 * @typedef ULong
 * @brief 32-bit unsigned short
 * @ingroup BasicDataTypes
 */
typedef unsigned long           ULong;

typedef unsigned __int16        UInt16;

typedef unsigned __int32        UInt32;

/**
 * @typedef Double
 * @brief 64-bit double
 * @ingroup BasicDataTypes
 */
typedef double                  Double;

#ifdef __cplusplus
    /**
     * @typedef CLong
     * @brief Constant Long defined for C++ programs only
     * @ingroup BasicDataTypes
     */
    typedef const Long          CLong;
#endif

/**
 * @name 64 bit data-types
 */

/**
 * @typedef Long64
 * @brief 64-bit integer
 * @ingroup BasicDataTypes 
 */
typedef __int64                 Long64;

/**
 * @typedef ULong64
 * @brief 64-bit unsigned integer
 * @ingroup BasicDataTypes
 */
#ifdef __LINUX__
    typedef guint64             ULong64;
#else
    typedef unsigned __int64    ULong64;
#endif

#ifdef __cplusplus
    /**
     * @typedef CLong64
     * @brief Constant Long64 defined for C++ programs only
     * @ingroup BasicDataTypes
     */
    typedef const Long64        CLong64;
#endif

/**
 * @name IO specific data-types
 */

/**
 * @typedef Offset
 * @brief 32-bit Offset
 * @ingroup BasicDataTypes 
 */
typedef ULong                   Offset;

/**
 * @typedef Offset64
 * @brief 64-bit Offset
 * @ingroup BasicDataTypes 
 */
typedef ULong64                 Offset64;

#ifdef __cplusplus
    /**
     * @typedef COffset
     * @brief Constant Offset defined for C++ programs only
     * @ingroup BasicDataTypes
     */
    typedef const Offset        COffset;

    /**
     * @typedef COffset64
     * @brief Constant Offset64 defined for C++ programs only
     * @ingroup BasicDataTypes
     */
    typedef const Offset64      COffset64;
#endif

/**
 * @name Memory Size Specific data-types
 */

/**
 * @typedef Size_T
 * @brief Size of memory
 * @ingroup BasicDataTypes 
 * @note 
 * This is compatible with 32bit and 64Bit OS
 */
typedef     size_t              Size_T;

/**
 * @name NameMgr Specific data-types
 */
/**
 * @typedef NamePtr
 * @brief Pointer to the 'Name'
 * @note
 *  <ul>
 *  <li>NamePtr points to the location 'Name', when refered with
 *  TNameBuffer
 *  <li> Points to the TNameObj, which holds 'Name', when
 *  refered with TNameMgr.
 *  </ul>
 * @ingroup BasicDataTypes
 */
#ifdef DEBUG

    class   TNameObj;

    typedef TNameObj *          NamePtr;

#else

    #ifndef WIN64 
        typedef ULong           NamePtr;
    #else
        typedef ULong64         NamePtr;
    #endif

#endif

/**
 * @typedef NamePtr
 * @brief Offset to the 'Name'
 * @see TNameMgr
 * @ingroup BasicDataTypes
 */
typedef ULong               NameOffset;


/**
 * @note 
 * <ul>
 * <li>Common Long and ULong datatype created to work with 
 * 32bit as well as 64Bit OS
 * <li>This can be removed once we completely shift into 64Bit Environment
 * </ul> 
 */
#ifndef WIN64 
    typedef Long               TLong;
    typedef ULong              TULong;
#else
    typedef Long64             TLong;
    typedef ULong64            TULong;
#endif


/**
 * @def TIME 
 * @brief Get the current calendar time
 *  
 * It is a wrapper for 'time' function for solving the problem 
 * due to diffent sizes of time_t in different senarios. time_t 
 * is 32-bit in compilers below VC 2005 and is 64-bit from VC 
 * 2005. To make this default as 32-bit in any compiler we 
 * use,this and time related macros have been introduced. 
 *  
 * @param pTS   This would be a ULong, in which the timestamp 
 *              would be copied.
 */
#define TIME(pTs)   {\
        time_t  ptime;\
        ::time(&ptime);\
        pTs = (ULong) ptime;\
    }

/**
 * @def LOCALTIME 
 * @brief   To get the 'local time' structure filled (struct tm)
 * with a timestamp we have. 
 *  
 * It is a wrapper around localtime function to get rid of the 
 * problem due to its size explained above in TIME macro. 
 *  
 * pTm is struct tm* type and pTs is a timestamp.
 * @param pTm       This is a pointer to struct tm (struct tm 
 *                   ). This is the strcuture which is filled
 *                   with the localtime information.
 *  
 * @param pTs       The timestamp (ULong) which is to be 
 *                  converted to local time.
 *                 
 */
#define LOCALTIME(pTm,pTs)   {\
        time_t  ptime = pTs;\
        pTm     = ::localtime(&ptime);\
    }

/**
 * @def     MKTIME 
 * @brief   Interprets the contents of the tm structure as a 
 *          calendar time expressed in local time.
 *  
 * It converts struct tm * to a timestamp (which is ULong) 
 *  
 * @param   pTs     Timestamp (a ULong) which is to be made from
 *                  pTm
 * @param   pTm     struct tm *, which contains local time info
 */
#define MKTIME(pTs,pTm) {\
        pTs = (ULong) ::mktime (pTm);\
    }

//#define GMTIME(pTm,pTs)   {\
//        time_t  ptime = pTs;\
//        pTm     = gmtime(&ptime);\
//    }

/** @} */

enum eActionType {

    ACTION_TYPE_UNKNOWN = 0,
    ACTION_TYPE_ENABLE,
    ACTION_TYPE_DISABLE,
    ACTION_TYPE_DELETE,
};

enum eJoinType {

    UNKNOWN_JOIN_TYPE = 0,
    INNER_JOIN_TYPE,
    LEFT_JOIN_TYPE,
    RIGHT_JOIN_TYPE,
    CROSS_JOIN_TYPE,
    DELETE_JOIN_TYPE,
    EQUI_JOIN_TYPE,
    NATURAL_JOIN_TYPE,
    UPDATE_JOIN_TYPE,
};
#endif // LBA_DEFINES_H

