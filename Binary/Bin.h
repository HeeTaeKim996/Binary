#pragma once
class Bin
{
public:
	Bin();
	Bin(int32 Decimal, int32 BitCount = 8);
	Bin(string Num);

public:
	void PrintNum(bool IsUnsigned = false);


public:
	Bin& operator = (const Bin& B);
	Bin operator + (Bin& B) ;
	Bin operator - (Bin& B);
	Bin operator * (Bin& B);

public:
	int GetDecimal(bool IsUnsinged = false);
	static string TwosComplement(const string& Num);
	static string OnesComplement(const string& Num);
	static string BitExtension(const string& Num, int BitCount);

public:
	static char NOT(char Val);
	static char AND(char a, char b);
	static char OR(char a, char b);
	static char XOR(char a, char b);
	
	static char NAND(char a, char b);
	static char NOR(char a, char b);
	static char NXOR(char a, char b);


public:
	// Add
	static void FullAdder(char A, char B, char C0, char& S, char& C);
	static string Parallel_Adder(string First, string Second);
	static string AddOne(string Num);
	static string Parallel_Adder_Substractor(string First, string Second, bool IsMinus = false);

public:
	// Deduct
	static void FullSubstractor(char A, char B, char Br0, char& D, char& Br);
	static string Parallel_Substractor(string First, string Second);


public:
	// Mul && Divide
	static string Multiply(string Multiplicated, string Multiplier);
	static void Divide(string Dividened, string Divisor, string& Quotient, string& Remainder);

private:
	static void MakeSameLength(string& A, string& B);

public:
	string Number;
};

