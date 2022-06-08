
#include<stdio.h>
#include<iostream>
#include<cstdlib>

template <typename T>
test_template(T* array, int count)
{
	for(int i=0; i<count; i++)
	{
		std::cout<<array[i]<<" ";
	}
	std::cout<<std::endl;
	
	return 0;
}

int main()
{
	int boo[5] = {1,2,3,4,5};
	double yah[5] = {1.9,2.8,3.7,4.6,5.5};
	char test[9] = "abcdefgh";
	
	test_template(boo, 5);
	test_template(yah, 5);
	test_template(test, 9);
}