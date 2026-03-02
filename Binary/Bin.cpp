#include "pch.h"
#include "Bin.h"

Bin::Bin()
{
	Number = "00000000";
}

Bin::Bin(int32 Decimal, int32 BitCount) // 『 BitCount = 8
{
	Number = string(BitCount, '0');

	int Index = BitCount - 1;
	bool IsMinus = Decimal < 0;
	if (IsMinus)
	{
		Decimal = -Decimal;
	}

	int Muls = 1;

	while (Index >= 0 && Decimal > 0)
	{
		int Val = Decimal % 2;
		Decimal /= 2;
		Muls *= 2;

		Number[Index] = '0' + Val;
		
		Index--;
	}

	if (IsMinus)
	{
		Number = TwosComplement(Number);
	}
}

Bin::Bin(string Num)
{
	if (Num.length() < 8)
	{
		Num = BitExtension(Num, 8);
	}

	Number = Num;
}

void Bin::FromHex(string Hex)
{
	Number = "";
	for (int i = 0; i < Hex.length(); i++)
	{
		char C = Hex[i];
		int Num = 0;
		if (C >= '0' && C <= '9')
		{
			Num = C - '0';
		}
		else if (C >= 'A' && C <= 'F')
		{
			Num = C - 'A' + 10;
		}

		string Nums = string(4, '0');
		for (int j = 3; j >= 0; j--)
		{
			int Val = Num % 2;
			Nums[j] = Val + '0';

			Num /= 2;
		}
		Number += Nums;
	}
}

void Bin::FromOct(string Oct)
{
	Number = "";
	for (int i = 0; i < Oct.length(); i++)
	{
		char C = Oct[i];
		int Num = 0;
		if (C >= '0' && C <= '7')
		{
			Num = C - '0';
		}

		string Nums = string(3, '0');
		for (int j = 2; j >= 0; j--)
		{
			int Val = Num % 2;
			Nums[j] = Val + '0';

			Num /= 2;
		}
		Number += Nums;
	}
}

void Bin::PrintNum(bool IsUnsigned) // 『 IsUnsinged == false
{
	printf("%s(%d)\n", Number.c_str(), GetDecimal(IsUnsigned));
}


// Prelude Unsigned
void Bin::PrintHex()
{
	string Copy = Number;
	int SurplusCount = 4 - Copy.length() % 4;
	if (SurplusCount != 4)
	{
		string Added = "";
		while (SurplusCount-- > 0)
		{
			Added += '0';
		}
		Copy = Added + Copy;
	}


	string PrintSt = "";

	int Rep = Copy.length() / 4;
	for (int i = 0; i < Rep; i++)
	{
		int Sum = 0;
		int Mul = 8;
		
		for (int j = 0; j < 4; j++)
		{
			char C = Copy[i * 4 + j];
			if (C == '1')
			{
				Sum += Mul;
			}

			Mul /= 2;
		}

		if (Sum >= 10)
		{
			PrintSt += Sum + - 10 + 'A';
		}
		else
		{
			PrintSt += Sum + '0';
		}
	}

	printf("%s(Hex)", PrintSt.c_str());
}

// Prelude Unsigned
void Bin::PrintOct()
{
	string Copy = Number;
	int SurplusCount = 3 - Copy.length() % 3;
	if (SurplusCount != 3)
	{
		string Added = "";
		while (SurplusCount-- > 0)
		{
			Added += '0';
		}
		Copy = Added + Copy;
	}

	string PrintSt = "";

	int Rep = Copy.length() / 3;
	for (int i = 0; i < Rep; i++)
	{
		int Sum = 0;
		int Mul = 4;

		for (int j = 0; j < 3; j++)
		{
			char C = Copy[i * 3 + j];
			if (C == '1')
			{
				Sum += Mul;
			}

			Mul /= 2;
		}

		PrintSt += Sum + '0';
	}

	printf("%s(Oct)", PrintSt.c_str());
}





























//---------------------------
//		  operator
//---------------------------
Bin& Bin::operator=(const Bin& B)
{
	Number = B.Number;

	return *this;
}

Bin Bin::operator+(Bin& B)
{
	
	return Bin(Parallel_Adder_Substractor(Number, B.Number));
}

Bin Bin::operator-(Bin& B)
{
	return Bin(Parallel_Adder_Substractor(Number, B.Number, true));
}

Bin Bin::operator*(Bin& B)
{
	return Bin(Multiply(Number, B.Number));
}



















//---------------------------
//		  Utils
//---------------------------
int Bin::GetDecimal(bool IsUnsinged) // 『 IsUnsinged == false
{
	int Ret = 0;
	int Mul = 1;
	for (int i = Number.length() - 1; i > 0; i--)
	{
		if (Number[i] == '1')
		{
			Ret += Mul;
		}

		Mul *= 2;
	}
	
	if (IsUnsinged)
	{
		if (Number[0] == '1')
		{
			Ret += Mul;
		}
	}
	else
	{
		if (Number[0] == '1')
		{
			Ret = -Mul + Ret;
		}
	}

	return Ret;
}

string Bin::TwosComplement(const string& Num)
{
	return AddOne(
		OnesComplement(Num)
	);
}

string Bin::OnesComplement(const string& Num)
{
	string Ret = string(Num.length(), '0');

	for (int i = 0; i < Num.length(); i++)
	{
		if (Num[i] == '0')
		{
			Ret[i] = '1';
		}
	}

	return Ret;
}

string Bin::BitExtension(const string& Num, int BitCount)
{
	string Ret = string(BitCount, Num[0]);
	int Index = BitCount - Num.length();
	Ret.replace(Index, Num.length(), Num);

	return Ret;
}

void Bin::MakeSameLength(string& A, string& B)
{
	if (A.length() > B.length())
	{
		B = BitExtension(B, A.length());
	}
	else if (A.length() < B.length())
	{
		A = BitExtension(A, B.length());
	}
}























//---------------------------
//		  Gate
//---------------------------
char Bin::NOT(char Val)
{
	return Val == '0' ? '1' : '0';
}

char Bin::AND(char a, char b)
{
	return (a == '1' && b == '1') ? '1' : '0';
}

char Bin::OR(char a, char b)
{
	return (a == '1' || b == '1') ? '1' : '0';
}

char Bin::XOR(char a, char b)
{
	return a != b ? '1' : '0';
}

char Bin::NAND(char a, char b)
{
	return NOT(AND(a, b));
}

char Bin::NOR(char a, char b)
{
	return NOT(OR(a, b));
}

char Bin::NXOR(char a, char b)
{
	return NOT(XOR(a, b));
}
























//---------------------------
//		  Add
//---------------------------
void Bin::FullAdder(char A, char B, char C0, char& S, char& C)
{
	char XOR_AB = XOR(A, B);
	S = XOR(XOR_AB, C0);

	C = OR(
		AND(XOR_AB, C0),
		AND(A, B)
	);
}

string Bin::Parallel_Adder(string First, string Second)
{
	MakeSameLength(First, Second);

	string Ret = string(First.length(), '0');
	char C0 = '0';
	char S;
	char C;

	for (int i = First.length() - 1; i >= 0; i--)
	{
		FullAdder(First[i], Second[i], C0, S, C);

		Ret[i] = S;
		C0 = C;
	}

	return Ret;
}

string Bin::AddOne(string Num)
{
	string Second = string(Num.length(), '0');
	Second[Second.length() - 1] = '1';

	return Parallel_Adder(Num, Second);
}

string Bin::Parallel_Adder_Substractor(string First, string Second, bool IsMinus) // 『 IsMinus == false
{
	bool IsSingedOverFlow;
	bool IsUnsignedOverFlow;

	char M = IsMinus ? '1' : '0';

	MakeSameLength(First, Second);

	string Ret = string(First.length(), '0');
	char C0 = M;
	char S;
	char C;
	for (int i = First.length() - 1; i > 0; i--)
	{
		char B = XOR(Second[i], M);
		FullAdder(First[i], B, C0, S, C);

		Ret[i] = S;
		C0 = C;
	}

	{
		char Cn = C0;
		
		char B = XOR(Second[0], M);
		FullAdder(First[0], B, C0, S, C);

		Ret[0] = S;
		C0 = C;

		IsSingedOverFlow = XOR(Cn, C0) == '1';
	}
	
	IsUnsignedOverFlow = XOR(M, C0) == '1';

	return Ret;
}























//---------------------------
//		  Substract
//---------------------------
void Bin::FullSubstractor(char A, char B, char Br0, char& D, char& Br)
{
	char XOR_AB = XOR(A, B);

	D = XOR(XOR_AB, Br0);

	Br = OR(
		AND(NOT(XOR_AB), Br0),
		AND(NOT(A), B)
	);
}

string Bin::Parallel_Substractor(string First, string Second)
{
	MakeSameLength(First, Second);

	string Ret = string(First.length(), '0');
	char Br0 = '0';
	char D;
	char Br;
	for (int i = First.length() - 1; i >= 0; i--)
	{
		FullSubstractor(First[i], Second[i], Br0, D, Br);
		Ret[i] = D;
		Br0 = Br;
	}

	return Ret;
}

































//---------------------------
//		 Mul && Divide
//---------------------------
string Bin::Multiply(string Multiplicated, string Multiplier)
{
	string Lines = string(Multiplier.length() + Multiplicated.length() + 1, '0');
	Lines.replace(Multiplier.length(), Multiplicated.length(), Multiplicated);


	int Rep = Multiplicated.length();
	int Last = Lines.length() - 1;

	while (Rep-- > 0)
	{
		string Front = Lines.substr(0, Multiplier.length());

		if (Lines[Last - 1] == '0' && Lines[Last] == '1')
		{
			Front = Parallel_Adder_Substractor(Front, Multiplier);
		}
		else if (Lines[Last - 1] == '1' && Lines[Last] == '0')
		{
			Front = Parallel_Adder_Substractor(Front, Multiplier, true);
		}

		Lines.replace(0, Front.length(), Front);
		Lines = Lines[0] + Lines.substr(0, Lines.length() - 1);
	}

	return Lines.substr(0, Lines.length() - 1);
}


void Bin::Divide(string Dividened, string Divisor, string& Quotient, string& Remainder)
{
	bool bDividenedNegative = Dividened[0] == '1';
	bool bDivisorNegative = Divisor[0] == '1';

	if (bDividenedNegative)
	{
		Dividened = TwosComplement(Dividened);
	}
	if (bDivisorNegative)
	{
		Divisor = TwosComplement(Divisor);
	}
	
	string Lines = string(Dividened.length() + Divisor.length(), '0');
	Lines.replace(Divisor.length(), Dividened.length(), Dividened);

	int Rep = Dividened.length();

	while (Rep-- > 0)
	{
		// 1) Check whether plus or minus
		bool bAdd = Lines[0] == '1';


		// 2) Left Shift ( 2 * M && LeftShift of Dividened )
		Lines = Lines.substr(1, Lines.length() - 1) + '0';

		// 3) Add Or Substract ( Add Means -2M + M == -M, Substract Means - M. So Make remain -M + R )
		string Front = Lines.substr(0, Divisor.length());
		if (bAdd)
		{
			Front = Parallel_Adder_Substractor(Front, Divisor);
		}
		else
		{
			Front = Parallel_Adder_Substractor(Front, Divisor, true);
		}

		Lines.replace(0, Front.length(), Front);

		// 4) if -R + M > 0, Meaning Left shifted R is Bigger Than M, So Add 1 to Quotient
		if (Front[0] == '0')
		{
			Lines[Lines.length() - 1] = '1';
		}
	}


	string Front = Lines.substr(0, Divisor.length());
	// maybe Front is still -M + R, then Add M 
	if (Lines[0] == '1')
	{
		Front = Parallel_Adder_Substractor(Front, Divisor);
	}


	Remainder = Front;
	Quotient = Lines.substr(Divisor.length(), Dividened.length());



	if (bDividenedNegative != bDivisorNegative)
	{
		Quotient = TwosComplement(Quotient);
	}
	if (bDividenedNegative)
	{
		Remainder = TwosComplement(Remainder);
	}
}











