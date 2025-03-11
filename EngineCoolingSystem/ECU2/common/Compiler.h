#ifndef COMPILER_H
#define COMPILER_H

#include <Compiler_Cfg.h>

/* Definitions */
#define AUTOMATIC            
#define TYPEDEF              
#define STATIC static
#define NULL_PTR ((void *)0) 
#define INLINE                
#define LOCAL_INLINE          

/* Macros */
#define FUNC(rettype, memclass) rettype                                   
#define FUNC_P2CONST(rettype, ptrclass, memclass) const rettype *          
#define FUNC_P2VAR(rettype, ptrclass, memclass) rettype *                  
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *                       
#define P2CONST(ptrtype, memclass, ptrclass) ptrtype const *               
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const            
#define CONSTP2CONST(ptrtype, memclass, ptrclass) ptrtype const * const   
#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const ptrclass fctname) 
#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname) ptrclass    

#define CONST(consttype, memclass) const consttype                        
#define VAR(vartype, memclass) vartype                                  
#endif /* COMPILER_H */