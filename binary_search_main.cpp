#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

//Create a class for unit testing
class unit_test_class
{
private:
	string simple_test;
	string all_same;
	string palindrome;
	string numbers_and_symbols;
	string with_slashes;
	string long_string;
	string empty_string;
	char char_array[20];
protected:
	int counter;
	int passed;
	double percentage;
public:
	unit_test_class()
	{
		simple_test="I am Saeid";
		all_same="aaaaaaaaaa";
		palindrome="abcddcba";
		numbers_and_symbols="1278%27136%^%@__&^@^%6%@^%^5@#6627q138778";
		with_slashes="hhh\\/\]]s";
		empty_string="";
		long_string="This project is aimed at visualizing data obtained from multiple surveillance cameras for the purpose of re-identification. ";
		strcpy(char_array,"This is a char array");
		counter=0;
		passed=0;
	}
	bool unit_test_simple()
	{
		reverse_string(simple_test);
		if(simple_test.compare("dieaS ma I"))
		{
			cout<<"simple test passed!"<<endl;
			counter++;
			passed++;
			return true;
		}
		else
		{
			return false;
			counter++;
		}
	}


//the merge function for merge sort
void merge(float* input_array,int begin, int mid, int end,int* indices,int size)
{
	int n_1=mid-begin+1;
	int n_2=end-mid;
	float* Left=new float[n_1];
	float* Right=new float[n_2];
	int* temp_ind=new int[size];
	memcpy(temp_ind,indices,sizeof(int)*(size));
	for (int i=0;i<n_1;i++)
	{
		Left[i]=input_array[begin+i];
	}
	for (int i=0;i<n_2;i++)
	{
		Right[i]=input_array[mid+i+1];
	}
	//set the last element to infinity 2^32
	Left[n_1]=4294967296;
	Right[n_2]=4294967296;
	int m=0,n=0;
	for (int k=begin;k<=end;k++)
	{
		if (Left[m]<=Right[n])
		{
			input_array[k]=Left[m];
			indices[k]=temp_ind[begin+m];
			m++;
		}
		else
		{
			input_array[k]=Right[n];
			indices[k]=temp_ind[mid+n+1];
			n++;
		}
	}
	return;
}

//helper function to sort the array
//takes a pointer to an array of floats and 
//returns a pointer to the sorted array;
void merge_sort(float* input_array,int begin, int end, int* indices, int size)
{
	int length=end-begin;
	if (input_array==NULL)
	{
		return;
	}
	else if (length<1)
	{
		return;
	}
	int mid=(begin+end)/2;
	float* output=new float[length];
	merge_sort(input_array,begin,mid,indices,size);
	merge_sort(input_array,mid+1,end,indices,size);
	merge(input_array,begin,mid,end,indices,size);
	
	return;
}

//helper function to print out arrays
void print_array(float* array, int length)
{
	if (array==NULL)
	{
		return;
	}
	for (int i=0;i<length;i++)
	{
		cout<<*(array+i)<<" , ";
	}
	cout<<endl;
	return;
}


//binary search method
//input_array: pointer to the the sorted array of type float
//length: length of the input array
//query: the query floating point value that we are searching for
//Return value: the index of the value in the input array, -1 if item is not found
int binary_search(float* input_array,int* indices,int length, float query)
{
	if (input_array==NULL)
	{
		return -1;
	}
	int low=0, high=length-1,mid;
	if ((query<input_array[low])||(query>input_array[high]))
	{
		return -1;
	}

	while((high-low)>1)
	{
		mid=low+(high-low)/2;
		if (query==input_array[mid])
		{
			return indices[mid];
		}
		else if (query<input_array[mid])
		{
			high=mid;
		}
		else
			low=mid;
	}
	if (query==input_array[high])
	{
		return indices[high];
	}
	else if (query==input_array[low])
	{
		return indices[low];
	}
	return -1;
	
}

//Driver function
int main()
{
	//float test_case[]={214,122,8,66,28,012,88,52,1,-1,2};
	float test_case[]={12,88,52,1,-1,2};
	//float test_case[]={1.2548,2.4588,8.1,1.2547,0.58795,12,-1.2548,-1.2549,1,-1,2};
	int length=sizeof(test_case)/sizeof(float);
	int* indices=new int[length];
	for (int i=0;i<length;i++)
	{
		indices[i]=i;
	}
	print_array(test_case,length);
	merge_sort(test_case,0,length-1,indices,length);
	print_array(test_case,length);
	cout<<binary_search(test_case,indices,length,88)<<endl;
	getchar();
	return 0;
}