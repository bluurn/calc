#pragma once
#include "token_stream.h"
/*
 * Grammar:
 *
 *     Expression:
 *        Term
 *        Expression "+" Term
 *        Expression "-" Term
 *     Term:
 *        Primary
 *        Term "*" Primary
 *        Term "/" Primary
 *     Primary:
 *        Number
 *        "(" Expression ")"
 *     Number:
 *        floating-point-literal
 */
double term(TokenStream& ts);
double primary(TokenStream& ts);
double expression(TokenStream& ts);
double term(TokenStream& ts);
