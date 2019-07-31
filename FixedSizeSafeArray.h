#ifndef __FIXED_SIZE_SAFE_ARRAY_H_
#define __FIXED_SIZE_SAFE_ARRAY_H_

template<typename T>
class FixedSizeSafeArray
{

public:

	// Default constructor
	//FixedSizeSafeArray(const int parametricLength);	
	
	
	FixedSizeSafeArray(T* classToBeContained, const int parametricLength)
		:
		length(parametricLength)
	{
	};

	// Destructor
	virtual ~FixedSizeSafeArray() {};

	const int length;

	int FixedSizeSafeArray::lastIndex() const
	{
		return ( length - 1 );
	}

	bool FixedSizeSafeArray::isValidIndex(const int index) const
	{
		return ( index < length );
	}
	
	T* operator() (const int index) { return data[index]; }

private:

	T* data;

};

#endif // __FIXED_SIZE_SAFE_ARRAY_H_


