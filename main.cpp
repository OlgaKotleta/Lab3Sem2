#include "vector_and_matrix.h"
#include <chrono>
#include <iomanip>

int main()
{
  srand((size_t)time(NULL));

  int* _arrvector;
  size_t size = 14;

  _arrvector = new int[size];
  for (size_t i = 0; i < size; i++)
    _arrvector[i] = rand() % 10;

  size_t R = 1;
  size_t B = 10;

  int** _arrmat = new int* [R];
  for (size_t i = 0; i < R; i++)
    _arrmat[i] = new int[B];

  for (size_t i = 0; i < R; i++)
  {
    for (size_t j = 0; j < B; j++)
      _arrmat[i][j] = rand() % 10;
  }

  Vector<int> VectorA(10, _arrvector);
  Matrix<int> MatrixB(1, 10, _arrmat);

  Vector<int> VectorC;
  VectorC = MatrixB * VectorA;
  std::cout << VectorC << std::endl;
  Matrix<int> MatrixD;
  MatrixD = VectorA * MatrixB;
  std::cout << MatrixD << std::endl;

  Vector<double> _Vector;
  Vector<double> log0;
  Vector<int> log1(10, _arrvector);

  std::cout << log1 << std::endl;
  _Vector.SetVector(10);

  Vector<double> Vector1;

  Vector<double> VectorDouble;

  Vector1 = _Vector;

  VectorDouble = (_Vector / Vector1);
  Matrix<int> Vector;
  Vector.SetMatrix(1, 3);

  std::cout << Vector.GetR() << " " << Vector.GetB() << std::endl;

  Matrix<int> mat0(13, 13);


  mat0 = Vector;

  if (mat0 == Vector)
    std::cout << mat0.GetR() << " " << mat0.GetB() << std::endl;

  mat0.SetMatrix(3, 1);

  Matrix<int> mat1;
  mat1 = Vector * mat0;
  std::cout << mat1.GetR() << " " << mat1.GetB() << std::endl;

  for (size_t i = 0; i < mat1.GetR(); i++)
  {
    for (size_t j = 0; j < mat1.GetB(); j++)
    {
      std::cout << mat1.GetMatrix()[i][j] << std::endl;
    }
  }

  class Timer
  {
  private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;

  public:
    Timer() : m_beg(clock_t::now())
    {
    }

    void reset()
    {
      m_beg = clock_t::now();
    }

    double elapsed() const
    {
      return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
  };
  return 0;
}
