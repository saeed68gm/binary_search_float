#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace std;




float* null_array;
float simple_test[]={12,88,52,1,-1,2};
float more_precision[]={1.2548,2.4588,8.1,1.2547,0.58795,12,-1.2548,-1.2549,1,-1,2};
float repeated_values[]={2.222,2.222,2.222,2.222,2.222,2.222};
float max_float_value[]={221.3,4294967296,2.6,51.2,683.25};
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
	
	if (input_array==NULL)
	{
		return;
	}
	int length=end-begin;
	if (length<1)
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

//Create a class for unit testing
class unit_test_class
{
private:

	int counter;
	int passed;
	double percentage;
public:
	unit_test_class::unit_test_class()
	{
		counter=0;
		passed=0;
	}
	void unit_test_simple()
	{
		
		int length=sizeof(simple_test)/sizeof(float);
		int* indices=new int[length];
		for (int i=0;i<length;i++)
		{
			indices[i]=i;
		}
		merge_sort(simple_test,0,length-1,indices,length);
		//test case when the value is found
		int output=binary_search(simple_test,indices,length,88);
		if(output==1)
		{
			cout<<"value found, simple test passed!"<<endl;
			counter++;
			passed++;
		}
		else
		{
			counter++;
		}
		//test case when the value is not found
		output=binary_search(simple_test,indices,length,666);
		if(output==-1)
		{
			cout<<"non-existent value not found, simple test passed!"<<endl;
			counter++;
			passed++;

		}
		else
		{
			counter++;
		}
		return;
	}
	void unit_test_precision()
	{

		int length=sizeof(more_precision)/sizeof(float);
		int* indices=new int[length];
		for (int i=0;i<length;i++)
		{
			indices[i]=i;
		}
		merge_sort(more_precision,0,length-1,indices,length);
		//test case when the value is found
		int output=binary_search(more_precision,indices,length,0.58795);
		if(output==4)
		{
			cout<<"value found, simple test passed!"<<endl;
			counter++;
			passed++;
		}
		else
		{
			counter++;
		}
		//test case when the value is not found
		output=binary_search(more_precision,indices,length,1.226658);
		if(output==-1)
		{
			cout<<"non-existent value not found, simple test passed!"<<endl;
			counter++;
			passed++;

		}
		else
		{
			counter++;
		}
		return;
	}
	void unit_test_null()
	{

		int length=0;
		int* indices=new int[length];
		for (int i=0;i<length;i++)
		{
			indices[i]=i;
		}
		merge_sort(null_array,0,length-1,indices,length);
		int output=binary_search(null_array,indices,length,88);
		if(output==-1)
		{
			cout<<"null array test passed!"<<endl;
			counter++;
			passed++;
		}
		else
		{
			counter++;
		}
		return;
	}
	void unit_test_repeated()
	{

		int length=sizeof(repeated_values)/sizeof(float);
		int* indices=new int[length];
		for (int i=0;i<length;i++)
		{
			indices[i]=i;
		}
		merge_sort(repeated_values,0,length-1,indices,length);
		//test case when the value is found
		int output=binary_search(repeated_values,indices,length,2.222);
		if(output==(length-1)/2)
		{
			cout<<"value found,repeated value test passed!"<<endl;
			counter++;
			passed++;

		}
		else
		{
			counter++;
		}
		//test case when the value is not found
		output=binary_search(repeated_values,indices,length,3.5);
		if(output==-1)
		{
			cout<<"non-existent value not found, repeated value test passed!"<<endl;
			counter++;
			passed++;

		}
		else
		{

			counter++;
		}
		return;
	}
	void unit_test_max_value()
	{

		int length=sizeof(max_float_value)/sizeof(float);
		int* indices=new int[length];
		for (int i=0;i<length;i++)
		{
			indices[i]=i;
		}
		merge_sort(max_float_value,0,length-1,indices,length);
		//test case when the value is found
		int output=binary_search(max_float_value,indices,length,4294967296);
		if(output==1)
		{
			cout<<"value found,max value test passed!"<<endl;
			counter++;
			passed++;
		}
		else
		{
			counter++;
		}
		//test case when the value is not found
		output=binary_search(simple_test,indices,length,4294967296);
		if(output==-1)
		{
			cout<<"non-existent value not found, max value test passed!"<<endl;
			counter++;
			passed++;
		}
		else
		{

			counter++;
		}
		return;
	}
	double unit_test_all()
	{
		unit_test_simple();
		unit_test_precision();
		unit_test_repeated();
		unit_test_max_value();
		unit_test_null();
		if (counter==0)
		{
			percentage=0;
		}
		else
			percentage=((double)passed/(double)counter)*100;
		cout<<"success rate is: "<<percentage<<endl;
		return percentage;
	}
};



//Driver function
int main()
{
	unit_test_class unit_test;
	unit_test.unit_test_all();
	getchar();
	return 0;
}