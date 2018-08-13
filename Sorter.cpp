#include "Sorter.h"

using std::vector;
using std::string;

int rec = 0;

//Merge sorted lists by map field
List< HealthEvent^ >^ Merge(List< HealthEvent^ >^ A, List< HealthEvent^ >^ B, String^ field, bool order)
{
	List< HealthEvent^ >::Enumerator enumA = A->GetEnumerator();
	List< HealthEvent^ >::Enumerator enumB = B->GetEnumerator();

	enumA.MoveNext();
	enumB.MoveNext();

	List< HealthEvent^ >^ result = gcnew List< HealthEvent^ >(0);

	while (true)
	{
		String^ Aval = enumA.Current->getFirstValue(field);
		String^ Bval = enumB.Current->getFirstValue(field);

		if (order ? (Aval->CompareTo(Bval)) : (Aval->CompareTo(Bval)))
		{
			result->Add(enumA.Current);
			if (!enumA.MoveNext())
			{
				do
				{
					result->Add(enumB.Current);
				} while (enumB.MoveNext());
				break;
			}
			
		}

		else
		{
			result->Add(enumB.Current);
			if (!enumB.MoveNext())
			{
				do
				{
					result->Add(enumA.Current);
				} while (enumA.MoveNext());
				break;
			}
		}
	}

	return result;
}

//Standard merge sort by map key "field" - alphanumeric for now
List< HealthEvent^ >^ MergeSort(List< HealthEvent^ >^ arr, String^ field, bool order)
{

	if (arr->Count < 2) return arr; //Single or zero return

	int mid = arr->Count / 2;

	List< HealthEvent^ >^ left(arr->GetRange(0,mid));
	List< HealthEvent^ >^ right(arr->GetRange(mid, arr->Count - mid));
	
	return Merge(MergeSort(left,field,order), MergeSort(right,field,order), field, order);

}