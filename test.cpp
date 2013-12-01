#include "bloomfilter.h"
#include <string>
#include <list>
#include <math.h>
#include <cstdlib> 
#include <algorithm>
#include <sstream>  
#include <stdio.h>
/* This test inserts 1 to num_of_items into the bloom filter, each time checking if the 
* number is alread there, if so we have a false positive */

std::string to_string(int i)
{
	std::stringstream ss;
	ss<<i;
	return ss.str();
}

int test(int num_of_items, double  prob_of_false_positive)
{
	// Number of errors (false positive)
	int errors = 0;	
	// Initialise the bloom filter with the expected number of items, and the intended false positive
	BloomFilter bloomFilter = BloomFilter(num_of_items, prob_of_false_positive);
	std::string num_as_str="";

	for(int i=1; i<=num_of_items; i++)
	{
		num_as_str = to_string(i);

		if(bloomFilter.contains(num_as_str))
		{// False positive
			errors++;
		}else
		{
			bloomFilter.add(num_as_str);
		}
	}

	std::cout<<std::endl;

	printf("%15f %15d %15d %15f\n", prob_of_false_positive, num_of_items, errors, (double)errors/num_of_items);
}

int main()
{
	printf("%15s %15s %15s %15s\n",  "false positive", "items count", "errors", "error ratio");

	int limit_items = 10000;
	int items_step = 1000;
	double limit_false_positive = 1;
	double false_positive_step = .15;
	
	for(double j=.0001; j<= limit_false_positive; j+=false_positive_step)
	{
		for(int i=1000; i<= limit_items; i+= items_step)
		{
		    test(i, j);
		}
	}
	
}