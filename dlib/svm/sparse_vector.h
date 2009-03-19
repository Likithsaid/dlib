// Copyright (C) 2009  Davis E. King (davisking@users.sourceforge.net)
// License: Boost Software License   See LICENSE.txt for the full license.
#ifndef DLIB_SVm_SPARSE_VECTOR
#define DLIB_SVm_SPARSE_VECTOR

#include "sparse_vector_abstract.h"
#include <cmath>
#include <limits>
#include "../algs.h"


namespace dlib
{

// ----------------------------------------------------------------------------------------

    namespace sparse_vector
    {

        template <typename T, typename U>
        typename T::value_type::second_type distance_squared (
            const T& a,
            const U& b
        )
        {
            typedef typename T::value_type::second_type scalar_type;
            typedef typename U::value_type::second_type scalar_typeU;
            // Both T and U must contain the same kinds of elements
            COMPILE_TIME_ASSERT((is_same_type<scalar_type, scalar_typeU>::value));

            typename T::const_iterator ai = a.begin();
            typename U::const_iterator bi = b.begin();

            scalar_type sum = 0, temp = 0;
            while (ai != a.end() && bi != b.end())
            {
                if (ai->first == bi->first)
                {
                    temp = ai->second - bi->second;
                    ++ai;
                    ++bi;
                }
                else if (ai->first < bi->first)
                {
                    temp = ai->second;
                    ++ai;
                }
                else 
                {
                    temp = bi->second;
                    ++bi;
                }

                sum += temp*temp;
            }

            while (ai != a.end())
            {
                sum += ai->second*ai->second;
            }
            while (bi != b.end())
            {
                sum += bi->second*bi->second;
            }

            return sum;
        }

    // ------------------------------------------------------------------------------------

        template <typename T, typename U>
        typename T::value_type::second_type dot_product (
            const T& a,
            const U& b
        )
        {
            typedef typename T::value_type::second_type scalar_type;
            typedef typename U::value_type::second_type scalar_typeU;
            // Both T and U must contain the same kinds of elements
            COMPILE_TIME_ASSERT((is_same_type<scalar_type, scalar_typeU>::value));

            typename T::const_iterator ai = a.begin();
            typename U::const_iterator bi = b.begin();

            scalar_type sum = 0;
            while (ai != a.end() && bi != b.end())
            {
                if (ai->first == bi->first)
                {
                    sum += ai->second * bi->second;
                    ++ai;
                    ++bi;
                }
                else if (ai->first < bi->first)
                {
                    ++ai;
                }
                else 
                {
                    ++bi;
                }
            }

            return sum;
        }

    // ------------------------------------------------------------------------------------

        template <typename T>
        typename T::value_type::second_type length_squared (
            const T& a
        )
        {
            typedef typename T::value_type::second_type scalar_type;

            typename T::const_iterator i = a.begin();

            scalar_type sum = 0;
            while (i != a.end())
            {
                sum += i->second * i->second;
            }

            return sum;
        }

    }

// ----------------------------------------------------------------------------------------

}

#endif // DLIB_SVm_SPARSE_VECTOR




