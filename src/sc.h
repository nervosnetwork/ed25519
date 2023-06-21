#ifndef SC_H
#define SC_H

/*
The set of scalars is \Z/l
where l = 2^252 + 27742317777372353535851937790883648493.
*/

void sc_reduce(unsigned char *s);
void sc_reduce32(unsigned char *s);
void sc_muladd(unsigned char *s, const unsigned char *a, const unsigned char *b, const unsigned char *c);
int sc_check(const unsigned char *);
int sc_isnonzero(const unsigned char *); /* Doesn't normalize */
void sc_0(unsigned char *);
void sc_add(unsigned char *, const unsigned char *, const unsigned char *);
void sc_sub(unsigned char *, const unsigned char *, const unsigned char *);

#endif
