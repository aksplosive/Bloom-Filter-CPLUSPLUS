#include "bloomfilter.h"
#include <string>
#include <list>
#include <math.h>
#include <cstdlib> 
#include <algorithm>
#include <sstream>  
#include <stdio.h>

std::string to_string(int i)
{
	std::stringstream ss;
	ss<<i;
	return ss.str();
}

int test(int num_of_items, double  prob_of_false_positive)
{
	// inits
	int str_length = 20;
	std::list<std::string> items;	// these items will be added in the bloom filter
	std::list<std::string> not_added_items;	// will not be added to the bloom filter
	BloomFilter bloomFilter = BloomFilter(num_of_items, prob_of_false_positive); // create bloom filter
	
	for(int i=0; i<num_of_items; i++)
	{
	    // insert numbers (in string form) from 0 to num_of_items-1
	    items.push_back(to_string(i));

	    // numbers (num_of_items to 2 * num_of_items -1) will be tested
	    not_added_items.push_back(to_string(num_of_items+i));
	}

	
	// Insert items in the bloomFilter
	for (std::list<std::string>::iterator item_ptr=items.begin(); item_ptr != items.end(); ++item_ptr)
	{
	    bloomFilter.add(*item_ptr);
	}
	
	int errors = 0;
      
	std::cout<<std::endl;
	
	// check if the items which where not added, appear to be in the bloom filter
	for (std::list<std::string>::iterator item_ptr=not_added_items.begin(); item_ptr != not_added_items.end(); ++item_ptr)
	{
	    
	    // Items is not in the inserted items, but bloom filter contains it (false positive)
	    if(bloomFilter.contains(*item_ptr))
	    {
		// item was not inserted
		if(std::find(items.begin(), items.end(), *item_ptr) == items.end())
		  errors += 1;
	    }
	    
	}
	
	printf("%15f %15d %15d %15f\n", prob_of_false_positive, num_of_items, errors, (double)errors/num_of_items);
}

int main()
{
	printf("%15s %15s %15s %15s \n",  "false positive", "items count", "errors", "error ratio");

	int limit_items = 10000;
	int items_step = 1000;
	float limit_false_positive = 1;
	float false_positive_step = .15;
	
	for(float j=.0001f; j<= limit_false_positive; j+=false_positive_step)
	{
		for(int i=1000; i<= limit_items; i+= items_step)
		{
		    test(i, j);
		}
	}
}