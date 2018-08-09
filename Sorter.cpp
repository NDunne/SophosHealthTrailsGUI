#include "Sorter.h"

using std::vector;
using std::string;

//Merge sorted lists by map field
vector<HealthEvent*>* Merge(vector<HealthEvent*>* A, vector<HealthEvent*>* B, string field)
{
	vector<HealthEvent*>::iterator ItA = (*A).begin();
	vector<HealthEvent*>::iterator ItB = (*B).begin();

	vector<HealthEvent*> result;

	while (ItA != (*A).end() && ItB != (*B).end())
	{
		string Aval = (*ItA)->getFirstValue(field);
		string Bval = (*ItB)->getFirstValue(field);

		if (Aval < Bval)
		{
			result.push_back(*ItA);
			ItA++;
		}

		else
		{
			result.push_back(*ItB);
			ItB++;
		}
	}
	
	while (ItA != (*A).end())
	{
		result.push_back(*ItA);
		ItA++;
	}

	while (ItB != (*B).end())
	{
		result.push_back(*ItB);
		ItB++;
	}

	OutputDebugString("Merged");

	return &result;
}

//Standard merge sort by map key "field" - alphanumeric for now
vector<HealthEvent*>* MergeSort(vector<HealthEvent*>* arr, string field)
{
	OutputDebugString("MERGE SORTING ");
	OutputDebugString(to_string(arr->size()).c_str());

	if (arr->size() < 2) return arr; //Single or zero return

	OutputDebugString(" - Size > 1");

	int mid = arr->size() / 2;

	vector<HealthEvent*> left(arr->begin(), arr->begin() + mid);
	vector<HealthEvent*> right(arr->begin() + mid, arr->end());	//merge half each

	return Merge(MergeSort(&left, field), MergeSort(&right,field),field);
}