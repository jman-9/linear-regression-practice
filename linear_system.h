#pragma once


class linear_system
{
public:
	struct equation
	{
		int xc;
		int yc;
		int k;

		void mul(int sk);
		void subt(equation rhs);
	};

	struct fraction
	{
		int num;
		int den;
	};

	struct solution
	{
		fraction x, y;
	};

public:
	linear_system();
	virtual ~linear_system();

	solution solve(equation eq1, equation eq2);

protected:
};
