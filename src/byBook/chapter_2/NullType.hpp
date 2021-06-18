#pragma once

/** NullType is simple type used as a null maker
 * in type calculations (Loki library). The type
 * should be used in cases in which a type must 
 * be there but doesn't have a semantic sence.
 * @Example: to mark the end of a typelist 
**/
class NullType{};
/** EmptyType is a simple helper type that is legal
 * to inherit from, and can be passed around. 
 * @Example: it can be used as a default type for 
 * a typelist;
**/  
class EmptyType{};
