//#include <stdio.h>
//
//int main()
//{
//	printf("Hello world%s \n","!");
//
//	return 0;
//}

//#include <stdio.h>
//int main()
//{
//	int fahr, celsius;
//	int lower, upper, step;
//	lower = 0; /* lower limit of the
//	temperature scale */
//	upper = 300; /* upper limit */
//	step = 20; /* step size */
//	fahr = lower;
//	while (fahr <= upper) {
//		celsius = 5 * (fahr - 32) / 9;
//		printf("%d\t%d\n", fahr, celsius);
//		fahr = fahr + step;
//	}
//	return 0;
//}

#include <iostream>

using namespace std;

int main()
{
	int i;

	// 1.
	i = 1;
	while (i <= 100)
	{
		cout << i << " ";
		i++;
	}

	cout << endl;

	// 2.
	i = 100;
	while (i > 0)
	{
		cout << i << " ";
		i -= 2;
	}

	cout << endl;

	// 3.
	long long int sum;

	i = 1, sum = 0;
	while (i <= 1000000)
	{
		sum += i;
		i++;
	}

	cout << sum;

	cout << endl;

	// 4.
	// all divisors of a number
	int n;
	
	n = 100;
	i = 0;
	while (i <= 100)
	{

	}

	return 0;
}