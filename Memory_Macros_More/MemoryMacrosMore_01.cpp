// MemoryMacrosMore_01.cpp : main project file.
#include<windows.h>
#include "malloc.h"
#include <cassert>
#include<iostream>
#include<vector>
//Section 1


struct Foo {
	float Hello;
public:
	char Label;
	Foo(char l, float n) :Label(l), Hello(n) {};
};

class Bar {
	float Goodbye;
public:
	char Label;
	Bar(char l, float n): Label(l), Goodbye(n) {};
};


//struct format:
//union{ struct{ a,b,c };  El[3]; };
//current default ops:
//+ * -(negation) *= +=
#define _decl_VEC_3(_P,_T) union _P##_T{struct{##_T a,b,c;}; ##_T El[3];};\
_P##_T operator+(_P##_T A, _P##_T B){_P##_T result = {}; result.a = A.a+B.a; result.b=A.b+B.b; result.c=A.c+B.c; return result;};\
_P##_T operator*(_P##_T A, ##_T B)  {_P##_T result = {}; result.a = A.a*B; result.b=A.b*B; result.c=A.c*B; return result;};\
_P##_T operator-(_P##_T &A)   {A.a = -A.a; A.b=-A.b; A.c=-A.c; return A;};\
_P##_T operator+=(_P##_T &A, const _P##_T& B){A.a += B.a; A.b+=B.b; A.c+=B.c; return A;};\
_P##_T operator*=(_P##_T &A, const _T& B){A.a *= B; A.b *= B; A.c *= B; return A;};

//v3_int
_decl_VEC_3(v3_, int)

//v3_float
_decl_VEC_3(v3_, float)

class Elephant {
	float Tusk_Size;
	float Trunk_Size;
	float Ear_Size;
public:
	Elephant HankyPanky(const Elephant& Mom, const Elephant& Dad) {
		Elephant Result = {};
		Result.Tusk_Size = Mom.Tusk_Size + Dad.Tusk_Size / 2.0f;
		Result.Trunk_Size = Mom.Trunk_Size + Dad.Trunk_Size / 2.0f;
		Result.Ear_Size = Mom.Ear_Size + Dad.Ear_Size / 2.0f;

		return Result;
	}
};

//_decl_VEC_3(v3_,Elephant)

#undef _decl_VEC_3(_P,_T)

template <class T> class V3 {
public:
	V3() {
		a = (T)0;
		b = (T)0;
		c = (T)0;
	};
	V3(T A, T B, T C) {
		a = A;
		b = B;
		c = C;
	};
	~V3() {};
	V3<T> operator+(const V3<T> &B) { V3<T> result;
		result.Set(this->a + B.a, this->b + B.b, this->c + B.c);
		return result;
	};
	V3<T>& operator+=(const V3<T> &B) {
		this->Set(this->a+B.a, this->b+B.b, this->c+B.c);
		return *this;
	}
	V3<T> operator*(const T &B) { V3<T> result;
		result.Set(this->a * B, this->b * B, this->c * B);
		return result;
	};
	V3<T>& operator*=(const T &B) {
		this->Set(this->a * B, this->b * B, this->c * B);
		return *this;
	}
	V3<T>& operator-() {
		this->a*= (T)-1.0;
		this->b*= (T)-1.0;
		this->c*= (T)-1.0;
		return *this;
	}

	void Set(T A, T B, T C) { 
		this->a = A;
		this->b = B;
		this->c = C;
	};
	void Clear(){
		this->El = {};
	}

	void* operator new(size_t size) {
		return ::operator new(size);
	}

	void operator delete(void *existing) {
		::operator delete(existing);
	}
private:
	union {
		struct {
			T a, b, c;
		};
		T El[3];
	};
};

// V3<Elephant> A = V3<Elephant> A;
// V3<Elephant> B = V3<Elephant> B;

// V3<Elephant> C = A + B;

// v3_Elephant operator+(v3_Elephant A, v3_Elephant B){v3_Elephant result = {}; result = HankyPanky(A,B); return result;};\

// v3_Elephant a = {};
// v3_Elephant b = {};
// v3_Elephant c = a+b;


struct Entity {
	v3_float *WorldPosition;
	V3<float> *WorldPosition_CPP;
	int Something;
	float SomethingElse;
	float SomethingElseElse;
};

int main(int argc, char **argv)
{
	Foo _f = Foo('f', 12.3f);
	Bar _b = Bar('b', 23.3332f);
	
	char label = _f.Label;
	float num = _f.Hello;

	label = _b.Label;
	//num = _b.Goodbye;



	V3<float> a;
	V3<float> b = V3<float>(3.4f, 3.1f, 1.1f);
	a.Set(0.0f, 1.0f, 3.0f);
	a += b;
	auto c = V3<float>();
	c = a + b;

	c += -a;
	c *= 2.0;

	v3_int A = {};
	A.a = 2;
	A.b = 2;
	A.c = 43;
	A.El[2] = 23;
	v3_int B = {};
	B.a = 1;
	B.b = 2;
	B.c = 3;

	auto C = A + B;
	C = A + -B;
	C = A * 4;
	C += A;
	C += -A;
	C *= 12;


	v3_float vecArray_C[10] = {};
	V3<float> vecArray_CPP[10] = {};

	Entity Entities[10] = {};
	for (int Num = 0; Num < 10; ++Num) {
		Entities[Num].WorldPosition = (v3_float *)malloc(sizeof(v3_float));
		//free((void*)TestOverrun);
		Entities[Num].WorldPosition = {};
		v3_float *TestOverrun = (v3_float*)malloc(sizeof(v3_float));
		*TestOverrun = {};

		Entities[Num].WorldPosition_CPP = new V3<float>(0.0f, 0.0f, 0.0f);
		V3<float> *TestDelete = new V3<float>(0.0f,0.0f,0.0f); 
		//delete TestDelete;
		
		std::auto_ptr <V3<float>> TestAutoDelete(new V3<float>(0.0f,0.0f,0.0f));
	}



    return 0;
}
