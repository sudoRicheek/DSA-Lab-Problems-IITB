#include "Assign1.h"

int main(int argc, char const *argv[])
{
	int arr[10] = {9, 7, 4, 1, 2, 0, 5, 3, 6, 8};
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

	permutation ptr3 = ptr ^ 30;
	permutation ptr4 = ptr ^ 7;
	// ptr2 = ptr ^ 2;
	// permutation ptr4 = ptr2 ^ 4;
	int* arrnewptr3 = ptr3.to_array();
	for (int i = 0; i < ptr3.size(); ++i)
	{
		cout << *(arrnewptr3 + i) << " ";
	}
	cout << endl;

	cout << "is_power : " << ptr3.is_power(ptr4) << endl;
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