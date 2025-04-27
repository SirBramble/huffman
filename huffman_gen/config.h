/** Encode array options */
#ifndef ENCODE_UINT8
#define ENCODE_UINT8 0
#endif

#ifndef ENCODE_UINT16
#define ENCODE_UINT16 0
#endif

#ifndef ENCODE_UINT32
#define ENCODE_UINT32 0
#endif

#if(ENCODE_UINT8 == 0 && ENCODE_UINT16 == 0 && ENCODE_UINT32 == 0)
#pragma error "Please define a encode datatype"
#endif

/** Typecast switch for array mapping */
#if (ENCODE_UINT8 != 0)
#define ENCODE_TYPE uint8_t
#define ENCODED_BIT_LIMIT 8
#endif

#if (ENCODE_UINT16 != 0)
#define ENCODE_TYPE uint16_t
#define ENCODED_BIT_LIMIT 16
#endif

#if (ENCODE_UINT32 != 0)
#define ENCODE_TYPE uint32_t
#define ENCODED_BIT_LIMIT 32
#endif