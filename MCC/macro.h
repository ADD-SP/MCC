#ifndef _MACRO_H_
#define _MACRO_H_ 0

#define CAST(var, type) (dynamic_cast<type>(var))
#define GET_VALUE(var, index) ((*var)[index])
#define GET_LEAF(var, index) ((*var)(index))

#endif // !_MACRO_H_

