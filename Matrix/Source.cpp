#include <iostream>
#include <memory>
#include <algorithm>

template <class T>
class matrix
{
public:
	matrix (size_t rows_num, size_t collums_num);

	matrix (const matrix<T> & other);
	matrix (matrix<T> && other);
	matrix<T> & operator = (const matrix<T> & rhs);
	matrix<T> & operator = (matrix<T> && rhs);

	matrix<T> & operator = (std::initializer_list<T> list);

	T * operator [] (size_t i);
	T * operator [] (size_t i) const; 

	void swap (matrix<T> & other);

	size_t rows, columns;

protected:
	std::unique_ptr<T[]> m_data;
};

template <class T>
std::ostream & operator << (std::ostream & lhs, const matrix<T> & rhs);

template <class T>
std::istream & operator >> (std::istream & lhs, const matrix<T> & rhs);


template <class T>
matrix<T> operator * (const matrix<T> & lhs, const matrix<T> & rhs);

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

template<class T>
matrix<T>::matrix (size_t rows_num, size_t collums_num) :
	rows (rows_num),
	columns (collums_num),
	m_data (new T[rows_num * collums_num])
{
}

template<class T>
matrix<T>::matrix (const matrix<T> & other) :
	columns (other.columns),
	rows (other.rows),
	m_data (new T[other.rows * other.columns])
{
	for (auto i = 0u; i < rows * columns; i++)
		m_data[i] = other.m_data[i];
}

template<class T>
matrix<T>::matrix (matrix<T> && other) : 
	columns (),
	rows (),
	m_data ()
{
	swap (other);
}

template<class T>
matrix<T> & matrix<T>::operator=(const matrix<T> & rhs)
{
	matrix<T> temp (rhs);
	swap (temp);

	return *this;
}

template<class T>
matrix<T> & matrix<T>::operator=(matrix<T> && rhs)
{
	swap (rhs);

	return *this;
}

template<class T>
matrix<T> & matrix<T>::operator=(std::initializer_list<T> list)
{
	auto i = 0u;

	for (auto && el : list)
		m_data[i++] = el;

	return *this;
}

template<class T>
T * matrix<T>::operator[](size_t i)
{
	return m_data.get() + columns * i;
}

template<class T>
T * matrix<T>::operator[](size_t i) const
{
	return m_data.get () + columns * i;
}

template<class T>
void matrix<T>::swap (matrix<T> & other)
{
	std::swap (this->columns, other.columns);
	std::swap (this->rows, other.rows);
	std::swap (this->m_data, other.m_data);
}

template <class T>
std::ostream & operator<<(std::ostream & lhs, const matrix<T> & rhs)
{
	for (auto i = 0u; i < rhs.rows; i++)
	{
		for (auto j = 0u; j < rhs.columns; j++)
			lhs << rhs[i][j] << " ";
		if (i != rhs.rows - 1) lhs << std::endl;
	}

	return lhs;
}

template<class T>
std::istream & operator>>(std::istream & lhs, const matrix<T> & rhs)
{
	for (auto i = 0u; i < rhs.rows * rhs.columns; i++)
		lhs >> rhs[0][i];

	return lhs;
}

template<class T>
matrix<T> operator*(const matrix<T> & lhs, const matrix<T> & rhs)
{
	if (lhs.columns != rhs.rows)
		std::cerr << "Matrix multiplication forbidden";

	matrix<T> res (lhs.rows, rhs.columns);

	for (auto Si = 0u; Si < res.rows; Si++)
		for (auto Sj = 0u; Sj < res.columns; Sj++)
		{
			res[Si][Sj] = T();

			for (auto i = 0u; i < lhs.columns; i++)
			{
				res[Si][Sj] += lhs[Si][i] * rhs[i][Sj];
			}
		}

	return res;
}
