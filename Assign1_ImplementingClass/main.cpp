#include "Assign1.h"

int main(int argc, char const *argv[])
{
	int arr[10] = {1, 9, 0, 7, 2, 3, 8, 4, 6, 5};
	permutation ptr(10, arr);

	permutation ptr2;
	ptr2 = ptr;

	cout << ptr2.size() << endl;
	int* arrnew = ptr2.to_array();
	for (int i = 0; i < 10; ++i)
	{
		cout << *(arrnew + i) << " ";
	}
	cout << endl;

	permutation pinv = -ptr2;
	int* arrnewinv = pinv.to_array();
	for (int i = 0; i < pinv.size(); ++i)
	{
		cout << *(arrnewinv + i) << " ";
	}
	cout << endl;

	permutation ptr3 = ptr.square_root();
	for (int i = 0; i < ptr3.size(); ++i)
	{
		cout << *(ptr3.to_array() + i) << " ";
	}
	cout << endl;

	return 0;
}