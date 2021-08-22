# Choose the compiler and compiler options
CC=g++
#CCOPTS = -Wall -g 
CCOPTS = -Wall -O

tests : test_rank test_partial_rank test_quantiles

test_rank : test_rank.cc
	$(CC) test_rank.cc $(CCOPTS) -o $@

test_partial_rank : test_partial_rank.cc
	$(CC) test_partial_rank.cc $(CCOPTS) -o $@

test_quantiles : test_quantiles.cc
	$(CC) test_quantiles.cc $(CCOPTS) -o $@

clean ::
	/bin/rm -f test_rank test_partial_rank test_quantiles

lint ::
	cpplint *.cc *.h

archive ::
	tar cvf ranker.tar *.h *.cc Makefile README.md

