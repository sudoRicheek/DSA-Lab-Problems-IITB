#include "Assign1.h"

int main(int argc, char const *argv[])
{
	int arr[10] = {9, 7, 4, 1, 2, 0, 5, 3, 6, 8};
	permutation ptr(10, arr);

	permutation ptr2;
	ptr2 = ptr;

	cout << ptr2.size() << endl;
	// int* arrnew = ptr2.to_array();
	// for (int i = 0; i < ptr2.size(); ++i)
	// {
	// 	cout << *(arrnew + i) << " ";
	// }
	// cout << "\n";

	// permutation pinv = -ptr2;
	// int* arrnewinv = pinv.to_array();
	// for (int i = 0; i < pinv.size(); ++i)
	// {
	// 	cout << *(arrnewinv + i) << " ";
	// }
	// cout << endl;

	permutation ptr3 = ptr ^ 8;
	ptr2 = ptr ^ 2;
	permutation ptr4 = ptr2 ^ 4;
	for (int i = 0; i < ptr3.size(); ++i)
	{
		cout << *(ptr3.to_array() + i) << " ";
	}
	cout << endl;
	int* arrnew = ptr4.to_array();
	for (int i = 0; i < ptr4.size(); ++i)
	{
		cout << *(arrnew + i) << " ";
	}
	cout << "\n";


	// ptr3 = ptr.naivepower(9);
	// for (int i = 0; i < ptr3.size(); ++i)
	// {
	// 	cout << *(ptr3.to_array() + i) << " ";
	// }
	// cout << endl;

	cout << ptr3.log(ptr2) << endl;

	return 0;
}