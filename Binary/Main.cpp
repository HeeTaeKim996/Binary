#include "pch.h"
#include "Test.h"
#include "Bin.h"


int main()
{
	Bin A(17);
	Bin B(-4);
	A.PrintNum();
	B.PrintNum();

	Bin C(Bin::Parallel_Adder_Substractor(A.Number, B.Number, true));
	C.PrintNum();

	Bin D = A + B;
	D.PrintNum();

	Bin E = A - B;
	E.PrintNum();

	Bin F = Bin::Parallel_Substractor(A.Number, B.Number);
	printf("F :  "); F.PrintNum();

	Bin G = A * B;
	G.PrintNum();

	string Quotient;
	string Res;
	Bin::Divide(A.Number, B.Number, Quotient, Res);
	Bin H(Quotient);
	Bin I(Res);
	printf("Q : "); H.PrintNum();
	printf("R : "); I.PrintNum();

	Bin J;
	J.FromHex("3E");
	J.PrintNum();
	J.PrintHex();

	Bin K;
	K.FromOct("37");
	K.PrintNum();
	K.PrintOct();
}

