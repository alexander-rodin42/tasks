#include <iostream>

struct S1
{
	int i : 3;
	int j : 5;
};

struct S2
{
	int i;
	int j;
};

struct S3
{
	bool i;
	bool j;
	bool k;
};

struct S4
{
	bool i;
	bool j;
	bool k;
	bool z;
};

struct S5
{
	int i;
	bool j;
};

struct S6
{
	double i;
	bool j;
};

int main()
{
	std::cout << alignof(std::max_align_t) << " - max align." << std::endl;
	std::cout << "align: " << alignof(S1) << ", size: " << sizeof(S1)
	          << " - int : 3 + int : 5 (length in bits for each field)" << std::endl;
	std::cout << "align: " << alignof(S2) << ", size: " << sizeof(S2) << " - 2*int" << std::endl;
	std::cout << "align: " << alignof(S3) << ", size: " << sizeof(S3) << " - 3*bool" << std::endl;
	std::cout << "align: " << alignof(S4) << ", size: " << sizeof(S4) << " - 4*bool" << std::endl;
	std::cout << "align: " << alignof(S5) << ", size: " << sizeof(S5) << " - int + bool" << std::endl;
	std::cout << "align: " << alignof(S6) << ", size: " << sizeof(S6) << " - double + bool" << std::endl;

	return EXIT_SUCCESS;
}
