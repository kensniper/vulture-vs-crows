/**
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote
        products derived from this software without specific prior written
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/
#ifndef _RANDOMNUMBERS_
#define _RANDOMNUMBERS_


#include <stdio.h>
#include <time.h>

/** Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /** constant vector a */
#define UPPER_MASK 0x80000000UL /** most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /** least significant r bits */



class RND{

 public:

    static RND* Instance();

    ~RND()
    {
        delete [] mt;
    }

    /** initializes mt[N] with a seed */
    void init(unsigned long s);

    /** initialize by an array with array-length
        init_key is the array for initializing keys
        key_length is its length
        slight change for C++, 2004/2/26 */
    void init_by_array(unsigned long init_key[], int key_length);

    /**randomly generates true or false**/
    bool boolean(void);

    /**randomly generates -1 or 1**/
    int sign(void);

    /** generates a random number on [0,0xffffffff]-interval */
    unsigned long int32(void);

    /** generates a random number on [0,0x7fffffff]-interval */
    long int31(void);

    /** generates a random number on [0,1]-real-interval */
    double real(void);

     /** generates a random number on [-1,1]-real-interval */
    double real1(void);

    /** generates a random number on [0,1)-real-interval */
    double real2(void);

    /** generates a random number on (0,1)-real-interval */
    double real3(void);

    /** generates a random number on [0,1) with 53-bit resolution*/
    double real4(void);


    /** These real versions are due to Isaku Wada, 2002/01/09 added */


 private:

    RND()
    {
        IB1=1;
        IB2=2;
        IB5=16;
        IB18=131072;
        MASK=IB1+IB2+IB5;
        mt=new unsigned long[N]; /** the array for the state vector  */
        mti=N+1; /** mti==N+1 means mt[N] is not initialized */
        init(time(NULL));
    }


    static RND* pinstance;


    unsigned long IB1,IB2,IB5,IB18;
    unsigned long MASK;
    unsigned long *mt; /** the array for the state vector  */
    int mti; /** mti==N+1 means mt[N] is not initialized */
    unsigned long iseed;


};

#undef N
#undef M
#undef MATRIX_A  /* constant vector a */
#undef UPPER_MASK/* most significant w-r bits */
#undef LOWER_MASK/* least significant r bits */


#endif
