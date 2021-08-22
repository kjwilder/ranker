# ranker
C++ templates to compute ranks, order permutations and quantiles.

                   **** Compute Ranks, Order Permuations and Quantiles Of
                   Elements In A C++ Array Or Vector ****
                   About:
                       * The file' ranker.h' provides several template
                         functions that compute the ranks, order permutations
                         and quantiles of the elements of an array or C++
                         vector.
                       * The functions' rank,' order' and' quantile' do almost
                         the same thing as R functions with the same name,
                         though faster.
                       * In addition, each function has a version that ends
                         with "high" (e.g.,' rankhigh' and' orderhigh) that
                         compares elements using ">" instead of "<".
                       * The functions use the C++ standard
                         library' sort' and' partial_sort' algorithms in an
                         interesting manner.
                       * Formerly available at http://oldmill.uchicago.edu/
                         ~wilder/Code/ranker/
                       * Contact and licensing info: Please click on my
                         projects links for details.
                       * Last updated: April 5, 2006.
                   ============================================================
                   Usage:
                       * rank(v, w, method)' 
                         -' v' is an input C++ vector' 
                         -' w' is a numeric C++ vector that will be resized if
                         necessary and in which the ranks of the elements
                         of' v' get stored.' 
                         -' method' is the optional method used to assign ranks
                         when there are ties (see below for details).
                       * rank(a, size, w, method)' 
                         -' a' is a pointer to the first element of an array
                         whose length is' size' 
                         -' w' and' method' are as above.
                       * partial_rank(v, w, num, method)
                         partial_rank(a size, w, num, method)
                         - Similar to' rank, but these functions compute only
                         the ranks of the' num' highest ranked elements and
                         assign a rank of 0 to the rest.
                       * order(v, w)
                         order(a, size, w)
                         -' w' is a C++ vector with an integral type that
                         stores a permutation that when applied
                         to' v' or' a' will sort it.
                       * partial_order(v, w, num)
                         partial_order(a, size, w, num)
                         - Similar to' order, but the permutation is of length
                         'num' and only permutes the 'num' highest ranked
                         elements.
*** Navigation ***     * quantile(v, q)
    * ________           quantile(a, size, q)
                         - Compute the q_th quantile of' v' or' a.
                       * method' is an optional string whose value can be
                         "average", "min", "max" or "random". If not specified,
                         it defaults to "average".
                       * The elements of' v' or' a' can be any type that can be
                         compared using' "<".
                       * When' method' == "average", the base type
                         of' w' should be a floating point type as the ranks
                         can be non-integral. For other methods, the base type
                         of' w' can be integral.
                   ============================================================
                   Files:
                       * ________: The header file containing the functions.
                       * ________: A test program using' rank.
                       * ________: A test program using' partial_rank.
                       * ________: A test program that computes quantiles.
                       * ________: The Makefile used to compile the above
                         examples.
                       * __________: A tar archive containing all of the above
                         files.
                   ________
                   (0k)
                   Kenneth Wilder,
                   Feb 16, 2009, 10:24 PM
                   v.1
                   ________
                   (7k)
                   Kenneth Wilder,
                   Feb 16, 2009, 10:24 PM
                   v.1
                   __________
                   (20k)
                   Kenneth Wilder,
                   Feb 16, 2009, 10:24 PM
                   v.1
                   ________
                   (1k)
                   Kenneth Wilder,
                   Feb 16, 2009, 10:24 PM
                   v.1
                   ________
                   (1k)
                   Kenneth Wilder,
                   Feb 16, 2009, 10:24 PM
                   v.1
                   ________
                   (1k)
                   Kenneth Wilder,
                   Feb 16, 2009, 10:24 PM
                   v.1
Powered By ____________
