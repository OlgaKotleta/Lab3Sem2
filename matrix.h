#include <iostream>
template<class M>
class Matrix
{
private:
  void MOut(size_t _R, size_t _B);
  size_t R;
  size_t B;
  M** mtrx;
public:
  Matrix();
  Matrix(size_t _R, size_t _B);
  Matrix(size_t _R, size_t _B, M** _mtrx);
  Matrix(const Matrix<M>& obj);
  ~Matrix();
  M** GetMatrix();
  size_t GetR();
  size_t GetB();
  void SetMatrix(size_t _R, size_t _B);

  Matrix<M> operator=(const Matrix<M>& obj);
  bool operator ==(const Matrix<M>& obj);
  M*& operator [](const size_t index);
  Matrix<M> operator+(const Matrix<M>& obj);
  Matrix<M> operator-(const Matrix<M>& obj);
  Matrix<M> operator*(const Matrix<M>& obj);

  template<class M>
  friend std::ostream& operator<<(std::ostream& out, const Matrix<M>& obj);
  template<class M>
  friend std::istream& operator>>(std::istream& in, Matrix<M>& obj);
};

template<class M>
void Matrix<M>::MOut(size_t _R, size_t _B)
{
  mtrx = new M * [_R];
  for (size_t i = 0; i < _R; i++)
    mtrx[i] = new M[_B];
}

template<class M>
Matrix<M>::Matrix(size_t _R, size_t _B, M** _mtrx)
{
  MOut(_R, _B);
  for (size_t i = 0; i < _R; i++)
    for (size_t j = 0; j < _B; j++)
      mtrx[i][j] = _mtrx[i][j];
  R = _R;
  B = _B;
}

template<class M>
Matrix<M>::Matrix()
{
  R = 1;
  B = 1;
  MOut(R, B);
  mtrx[0][0] = 0;
}

template<class M>
Matrix<M>::Matrix(size_t _R, size_t _B)
{
  MOut(_R, _B);
  for (size_t i = 0; i < _R; i++)
  {
    for (size_t j = 0; j < _B; j++)
    {
      mtrx[i][j] = 0;
    }
  }
  R = _R;
  B = _B;
}

template<class M>
Matrix<M>::Matrix(const Matrix<M>& obj)
{
  MOut(obj.R, obj.B);
  for (size_t i = 0; i < obj.R; i++)
  {
    for (size_t j = 0; j < obj.B; j++)
    {
      mtrx[i][j] = obj.mtrx[i][j];
    }
  }
  R = obj.R;
  B = obj.B;
}

template<class M>
Matrix<M>::~Matrix()
{
  if (mtrx != nullptr)
  {
    for (size_t i = 0; i < R; i++)
    {
      delete[] mtrx[i];
    }
    delete[] mtrx;
  }
  R = 0;
  B = 0;
}
template<class M>
size_t Matrix<M>::GetR()
{
  return R;
}

template<class M>
size_t Matrix<M>::GetB()
{
  return B;
}

template<class M>
M** Matrix<M>::GetMatrix()
{
  return mtrx;
}

template<class M>
void Matrix<M>::SetMatrix(size_t _R, size_t _B)
{
  if (mtrx != nullptr)
  {
    Matrix<M>temp(R, B);
    for (size_t i = 0; i < R; i++)
    {
      for (size_t j = 0; j < B; j++)
        temp.mtrx[i][j] = mtrx[i][j];
    }
    for (size_t i = 0; i < R; i++)
      delete[] mtrx[i];
    delete[]  mtrx;

    R = _R;
    B = _B;
    mtrx = new M * [R];
    for (size_t i = 0; i < R; i++)
      mtrx[i] = new M[B];
    for (size_t i = 0; i < R; i++)
    {
      for (size_t j = 0; j < B; j++)
        mtrx[i][j] = 0;
    }
    size_t R_ = (temp.R < R) ? temp.R : R;
    size_t B_ = (temp.B < B) ? temp.B : B;
   
    for (size_t i = 0; i < R_; i++)
    {
      for (size_t j = 0; j < B_; j++)
        mtrx[i][j] = temp.mtrx[i][j];
    }
  }
  else
  {
    R = _R;
    B = _B;
    mtrx = new M * [R];
    for (size_t i = 0; i < R; i++)
      mtrx[i] = new M[B];
    for (size_t i = 0; i < R; i++)
    {
      for (size_t j = 0; j < B; j++)
        mtrx[i][j] = 0;
    }
  }
}

template<class M>
Matrix<M> Matrix<M>::operator=(const Matrix<M>& obj)
{
  if (this != &obj)
  {
    for (size_t i = 0; i < R; i++)
    {
      delete[] mtrx[i];
    }
    delete[] mtrx;

    R = obj.R;
    B = obj.B;
    MOut(R, B);
    for (size_t i = 0; i < R; i++)
    {
      for (size_t j = 0; j < B; j++)
      {
        mtrx[i][j] = obj.mtrx[i][j];
      }
    }
  }
  return *this;
}

template<class M>
M*& Matrix<M>::operator [](const size_t index)
{
  return mtrx[index];
}

template<class M>
bool Matrix<M>::operator==(const Matrix<M>& obj)
{
  if (R == obj.R && B == obj.B)
  {
    for (size_t i = 0; i < R; i++)
      for (size_t j = 0; j < B; j++)
        if (mtrx[i][j] != obj.mtrx[i][j])
          return false;
    return true;
  }
  else
    return false;
}

template<class M>
Matrix<M> Matrix<M>::operator+(const Matrix<M>& obj)
{
  if (B == obj.B && R == obj.R)
  {
    Matrix<M> res(R, B);
    for (size_t i = 0; i < R; i++)
    {
      for (size_t j = 0; j < B; j++)
        res.mtrx[i][j] = mtrx[i][j] + obj.mtrx[i][j];
    }
    return res;
  }
  else
    throw "this->R!=obj.B";
}

template<class M>
Matrix<M> Matrix<M>::operator-(const Matrix<M>& obj)
{
  if (B == obj.B && R == obj.R)
  {
    Matrix<M> res(R, B);
    for (size_t i = 0; i < R; i++)
    {
      for (size_t j = 0; j < B; j++)
        res.mtrx[i][j] = mtrx[i][j] - obj.mtrx[i][j];
    }
    return res;
  }
  else
    throw "this->R!=obj.B";
}

template<class M>
Matrix<M> Matrix<M>::operator*(const Matrix<M>& obj)
{
  if (B == obj.R)
  {
    Matrix<M> res(R, obj.B);
    M sum;
    for (size_t i = 0; i < R; i++)
    {
      for (size_t j = 0; j < obj.B; j++)
      {
        sum = 0;
        for (size_t k = 0; k < obj.R; k++)
        {
          sum = sum + mtrx[i][k] * obj.mtrx[k][j];
        }
        res[i][j] = sum;
      }
    }
    return res;
  }
  else
    throw "this->R!=obj.B";
}

template<class M>
std::ostream& operator<<(std::ostream& out, const Matrix<M>& obj)
{
  if (obj.B != 0 && obj.R != 0)
  {
    for (size_t i = 0; i < obj.B; i++)
    {
      for (size_t j = 0; j < obj.R; j++)
        out << obj.mtrx[i][j] << " ";
      out << std::endl;
    }
    return out;
  }
  else
    throw "obj.B == 0 || obj.R == 0";
}

template<class M>
std::istream& operator>>(std::istream& in, Matrix<M>& obj)
{
  if ((obj.R == 0) || (obj.B == 0))
  {
    obj.R++;
    obj.B++;
    obj.SetMatrix(obj.R, obj.B);
  }
  for (size_t i = 0; i < obj.B; i++)
  {
    for (size_t j = 0; j < obj.R; j++)
      in >> obj.mtrx[i][j];
  }
  return in;
}
