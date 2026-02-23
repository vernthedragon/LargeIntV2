#pragma once

//    OPTIMIZED (HOPEFULLY)
//    BIT STYLE REPRESENTATION
//    32 BITS / 4 BYTES FOR SIZE OF STORED DATA
//    8 BITS * 2147483647 * 2 MAXIMUM UNITS

void _inline bitwiseset(unsigned char* i, unsigned char pos, bool val) {
	if (val)
		*i |= (unsigned char)(1 << pos);
	else
		*i &= (unsigned char)~(1 << pos);
}
bool __forceinline bitwiseget(unsigned char i, unsigned char pos) {
	return ((i) & ((unsigned char)(1 << pos)));
}
constexpr unsigned char bitwise00002222 = 1 + 2 + 2 * 2 + 2 * 2 * 2;
constexpr unsigned char bitwise22220000 = bitwise00002222 << 4;
unsigned char __forceinline bitwisereadright(unsigned char i) {
	return (i & (bitwise22220000)) >> 4;
}
unsigned char __forceinline bitwisereadleft(unsigned char i) {
	return i & bitwise00002222;
}
unsigned char __forceinline bitwisereadrightptr(unsigned char* i) {
	return ((*i) & (bitwise22220000)) >> 4;
}
unsigned char __forceinline bitwisereadleftptr(unsigned char* i) {
	return (*i) & bitwise00002222;
}
unsigned char __forceinline bitwisewriteright(unsigned char i, unsigned char val) {
	return i | (val << 4);
}
unsigned char __forceinline bitwisewriteleft(unsigned char i, unsigned char val) {
	return i | val;
}

void __forceinline bitwisewriterightptr(unsigned char* i, unsigned char val) {
	*i &= bitwise00002222;
	*i |= (val << 4);
}
void __forceinline bitwisewriteleftptr(unsigned char* i, unsigned char val) {
	*i &= bitwise22220000;
	*i |= val;
}

void IntSetSize(void* ptr, int size);
int IntGetSize(void* ptr);
void* IntCreate(int datalength) {

	size_t sz = sizeof(int) + abs(datalength);
	void* ptr = malloc(sz);

	if (!ptr)
		return nullptr;

	memset(ptr, 0, sz);
	IntSetSize(ptr, datalength);
	return ptr;
}

void IntFree(void* ptr) {
	if (!ptr)
		return;

	free(ptr);
	ptr = nullptr;

}
int IntGetSize(void* ptr) {
	if (!ptr)
		return 0;

	return (reinterpret_cast<int*>(ptr))[0];
}
bool __forceinline IntGetSign(void* ptr) {
	return IntGetSize(ptr) < 0;
}

void IntSetSign(void* ptr, bool sign) {
	int sz = IntGetSign(ptr);

	if ((sign && sz > 0) || (!sign && sz < 0))
		sz *= -1;

	IntSetSize(ptr, sz);
}

void* IntResize(void* ptr, int newsize) {
	int oldsize = IntGetSize(ptr);
	IntSetSize(ptr, newsize * (oldsize < 0 ? -1 : 1));


	ptr= realloc(ptr, newsize + sizeof(int));
	oldsize = abs(oldsize);
	memset( reinterpret_cast<void*>((int)ptr + oldsize + sizeof(int)), 0, newsize-oldsize);
	return ptr;
}

void IntSetSize(void* ptr, int size) {
	if (!ptr)
		return;

	(reinterpret_cast<int*>(ptr))[0] = size;
}

void IntSetPlace(void** ptr, int place, unsigned char value) { //here the place is in multiple of two
	
	if (value > 9 || place <= 0 || !ptr)
		return;

	if (!(*ptr))
		return;

	int size = ceil(place / 2.0);
	
	if (size > (int)abs(IntGetSize(*ptr))) {
		//we must resize
		*ptr = IntResize(*ptr, size);
	}

	size = size -1 + sizeof(int); //whole number
	
	if (place & 1) { //odd case which is 1 _ 3 _ 5 _ 7
		bitwisewriteleftptr(&(reinterpret_cast<unsigned char*>(*ptr)[size]), value);
		return;
	}
	//even case
	bitwisewriterightptr(&(reinterpret_cast<unsigned char*>(*ptr)[size]), value);
}

unsigned char IntGetPlace(void* ptr, int place) {
	if ( place <= 0 || !ptr)
		return 0;

	int size = ceil(place / 2.0);

	if (size > (int)abs(IntGetSize(ptr))) 
		return 0;


	size = size - 1 + sizeof(int); //whole number

	if (place & 1) { //odd case which is 1 _ 3 _ 5 _ 7
		return bitwisereadleft(reinterpret_cast<unsigned char*>(ptr)[size]);
	
	}
	//even case
	return bitwisereadright(reinterpret_cast<unsigned char*>(ptr)[size]);
}

bool IntEqual(void* A, void* B) {
	int SizeA = abs(IntGetSize(A));
	int SizeB = abs(IntGetSize(B));
	int SizeLarge = SizeA;
	if (SizeB > SizeLarge) 
		SizeLarge = SizeA;	
	
	for (unsigned int i = 0; i < SizeLarge; i++) {
		if (i < SizeA && i < SizeB) {
			if (reinterpret_cast<unsigned char*>(A)[i + sizeof(int)] != reinterpret_cast<unsigned char*>(B)[i + sizeof(int)])
				return false;
		}
		else if (i >= SizeA) {
			if (reinterpret_cast<int*>(A)[i + sizeof(int)] != 0)
				return false;
		}
		else if (i >= SizeB) {
			if (reinterpret_cast<int*>(B)[i + sizeof(int)] != 0)
				return false;
		}
		
	}

	return true;
}

bool IntNotEqual(void* A, void* B) {
	return !IntEqual(A, B);
}

void* IntAdd(void* First, void* Second) {
	void* ReturnValue = nullptr;

	if (IntGetSign(First) == IntGetSign(Second)) { //both positive
		//add from the smallest to largest place
		int Sizes[3] = { abs(IntGetSize(First)),abs(IntGetSize(Second)), 0 }; // [0] = FirstSize, [1] = SecondSize, [2] = LargestSize
		Sizes[2] = Sizes[0];
		if (Sizes[1] > Sizes[2])
			Sizes[2] = Sizes[1];
		ReturnValue = IntCreate(Sizes[2] * (IntGetSign(First) ? -1 : 1));
		int Calc[3] = { 0,0,0 }; //[0] = first, [1] = second, [2] = carry
		for (unsigned int i = 0; i < Sizes[2]; i++) {
			Calc[0] = bitwisereadleft(reinterpret_cast<unsigned char*>(First)[i + sizeof(int)]) + bitwisereadleft(reinterpret_cast<unsigned char*>(Second)[i + sizeof(int)]) + Calc[2];
			Calc[2] = 0;
			if (Calc[0] >= 10) {
				Calc[2]++;
				Calc[0] -= 10;
			}
			Calc[1] = bitwisereadright(reinterpret_cast<unsigned char*>(First)[i + sizeof(int)]) + bitwisereadright(reinterpret_cast<unsigned char*>(Second)[i + sizeof(int)]) + Calc[2];
			Calc[2] = 0;
			if (Calc[1] >= 10) {
				Calc[2]++;
				Calc[1] -= 10;
			}
			bitwisewriteleftptr(&reinterpret_cast<unsigned char*>(ReturnValue)[i + sizeof(int)], Calc[0]);
			bitwisewriterightptr(&reinterpret_cast<unsigned char*>(ReturnValue)[i + sizeof(int)], Calc[1]);
		}
		if (Calc[2] > 0)
			IntSetPlace(&ReturnValue, Sizes[2] * 2 + 1, Calc[2]);
		return ReturnValue;
	}
	return ReturnValue;
}
