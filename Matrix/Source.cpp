#include "matrix.hpp"

void matcalc ()
{
	auto Ar = 0u, Ac = 0u;

	std::cout << "A rows: ";
	std::cin >> Ar;

	std::cout << "A columns: ";
	std::cin >> Ac;

	matrix<int> A (Ar, Ac);

	std::cout << "A data:\n";
	std::cin >> A;

	std::cout << "\n";

	auto Br = 0u, Bc = 0u;

	std::cout << "B rows: ";
	std::cin >> Br;

	std::cout << "B columns: ";
	std::cin >> Bc;

	matrix<int> B (Br, Bc);

	std::cout << "B data:\n";
	std::cin >> B;

	std::cout << "\n";

	auto C = A * B;

	std::cout << "C =\n" << C;

}

int main ()
{
	while (true)
	{
		matcalc ();

		std::cout << "\n\n";
	}
}
