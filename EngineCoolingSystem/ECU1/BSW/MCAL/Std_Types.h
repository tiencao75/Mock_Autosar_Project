#ifndef STD_TYPES_H
#define STD_TYPES_H

/* Định nghĩa các kiểu dữ liệu cơ bản của AUTOSAR */
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned long       uint32;
typedef signed char         sint8;
typedef signed short        sint16;
typedef signed long         sint32;
typedef float               float32;
typedef double              float64;
typedef uint8               boolean;

/* Định nghĩa kiểu trả về chuẩn AUTOSAR */
typedef uint8               Std_ReturnType; /* Định nghĩa Std_ReturnType là uint8 */

/* Định nghĩa các giá trị trả về chuẩn */
#define E_OK       0x00U  /* Thành công */
#define E_NOT_OK   0x01U  /* Lỗi */

#define NULL_PTR   ((void *)0) /* Con trỏ NULL */

#endif // STD_TYPES_H