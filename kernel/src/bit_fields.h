#ifndef BIT_FIELDS_H
#define BIT_FIELDS_H

#define SBIT(b) (1UL << b)
#define BIT(x, b) ((x << b) & (1 << b))

//#define BITS(x, b, s) ((x << b) & ((1 << s << b) - 1))
#define BITS(x,b,s) (x & ((1 << s) - 1)) << b

#define GET_BIT(x, b) ((x >> b) & 1)
#define GET_BITS(x,b, s) ((x >> b) & ((1 << s) - 1))

#endif
