#include "Assign1.h"

int main(int argc, char const *argv[])
{
	int arr[10] = {7, 4, 8, 2, 0, 1, 9, 3, 6, 5};
	//int arr2[11] = {3, 4, 1, 0, 2, 10, 5, 6, 7, 8, 9};
	permutation ptr(10, arr);

	permutation ptr2;
	ptr2 = ptr;

	cout << ptr.size() << endl;
	int* arrnew = ptr2.to_array();
	for (int i = 0; i < ptr2.size(); ++i)
	{
		cout << *(arrnew + i) << " ";
	}
	cout << "\n";


	// permutation pinv = -ptr2;
	// int* arrnewinv = pinv.to_array();
	// for (int i = 0; i < pinv.size(); ++i)
	// {
	// 	cout << *(arrnewinv + i) << " ";
	// }
	// cout << endl;

	permutation ptr3 = ptr ^ 101;
	permutation ptr4 = ptr ^ 1;
	// ptr2 = ptr ^ 2;
	// permutation ptr4 = ptr2 ^ 4;
	int* arrnewptr3 = ptr3.to_array();

	for (int i = 0; i < ptr3.size(); ++i)
	{
		cout << *(arrnewptr3 + i) << " ";
	}
	cout << endl;
	int* arrnewptr4 = ptr4.to_array();
	for (int i = 0; i < ptr4.size(); ++i)
	{
		cout << *(arrnewptr4 + i) << " ";
	}
	cout << "\n";


	// ptr3 = ptr.naivepower(9);
	// for (int i = 0; i < ptr3.size(); ++i)
	// {
	// 	cout << *(ptr3.to_array() + i) << " ";
	// }
	// cout << endl;

	// cout << ptr3.log(ptr2) << endl;

	//permutation ptrtemp(11, arr2);
	cout << "is_power : " << ptr3.log(ptr4) << endl;
	//cout << "naive_is_power : " << ptr3.naive_is_power(ptr) << endl;

	// permutation ptrxx = ptr3;
	// for (int i = 0; i < 1; ++i)
	// {
	// 	ptrxx = ptrxx.square_root();
	// }
	// int* arrnewptrxx = ptrxx.to_array();
	// for (int i = 0; i < ptrxx.size(); ++i)
	// {
	// 	cout << *(arrnewptrxx + i) << " ";
	// }
	// cout << endl;


	// int* arrnew = ptr4.to_array();
	// for (int i = 0; i < ptr4.size(); ++i)
	// {
	// 	cout << *(arrnew + i) << " ";
	// }
	// cout << "\n";


	// ptr3 = ptr.naivepower(632527);
	// for (int i = 0; i < ptr3.size(); ++i)
	// {
	// 	cout << *(ptr3.to_array() + i) << " ";
	// }
	// cout << endl;

	//cout << ptr3.log(ptr2) << endl;

	return 0;
}