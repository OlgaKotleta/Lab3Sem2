#include <iostream>

template <class T>
class Vector
{
private:
  int position(T value, int entry);
  size_t size;
  T* arr;
public:
  Vector();
  Vector(size_t _size, T* _arr);
  Vector(Vector& obj);
  ~Vector();

  T* GetVector();
  size_t GetSize();
  void SetVector(size_t size);

  Vector<T> operator=(const Vector<T>& obj);
  bool operator ==(const Vector<T>& obj);
  T operator [](const size_t index);
  Vector<T> operator + (const Vector<T>& obj);
  Vector<T> operator-(const Vector<T>& obj);
  T operator*(const Vector<T>& obj);
  Vector<T> operator /(Vector<T>& obj);

  template <class T>
  friend std::ostream& operator<<(std::ostream& out, const Vector<T>& obj);
  template <class T>
  friend std::istream& operator>>(std::istream& in, Vector<T>& obj);
};

template<class T>
Vector<T>::Vector(size_t _size, T* _arr)
{
  arr = nullptr;
  try
  {
    if (_size > 0)
    {
      arr = new T[_size];
      for (size_t i = 0; i < _size; i++)
        arr[i] = _arr[i];
      size = _size;
    }
    else
      throw "size < 0";
  }
  catch (std::exception e)
  {
    std::cout << e.what() << std::endl;
    throw;
  }
}

template<class T>
Vector<T>::Vector(Vector& obj)
{
  arr = new T[obj.size];
  for (size_t i = 0; i < obj.size; i++)
  {
    arr[i] = obj.arr[i];
  }
  size = obj.size;
}
template<class T>
size_t Vector<T>::GetSize()
{
  return size;
}
template<class T>
T* Vector<T>::GetVector()
{
  return arr;
}



template<class T>
void Vector<T>::SetVector(size_t _size)
{
  if (arr != nullptr)
  {
    Vector<T>temp;
    temp = *this;
    for (size_t i = 0; i < size; i++)
      temp.arr[i] = arr[i];
    delete[] arr;

    size = _size;
    arr = new T[size];

    for (size_t i = 0; i < size; i++)
      arr[i] = 0;
    ;
    size_t SIZET = (temp.size < size) ? temp.size : size;

    for (size_t i = 0; i < SIZET; i++)
      arr[i] = temp.arr[i];
  }
  else
  {
    arr = new T[_size];
    for (size_t i = 0; i < _size; i++)
      arr[i] = 0;
    size = _size;
  }
}

template<class T>
Vector<T>::Vector()
{
  size = 1;
  arr = new T[1];
  arr[0] = 0;
}

template<class T>
Vector<T>::~Vector()
{
  if (arr != 0)
  {
    arr = 0;
    delete[] arr;
  }
  size = 0;
}
template<class T>
Vector<T> Vector<T>::operator=(const Vector<T>& obj)
{
  if (*this == obj)
    return *this;
  delete[] arr;
  this->size = obj.size;
  arr = new T[size];
  for (size_t i = 0; i < size; i++)
    arr[i] = obj.arr[i];
  return *this;
}

template<class T>
bool Vector<T>::operator==(const Vector<T>& obj)
{
  if (size == obj.size)
  {
    for (size_t i = 0; i < size; i++)
      if (arr[i] != obj.arr[i])
        return false;
    return true;
  }
  else
    return false;
}

template<class T>
T Vector<T>::operator[](const size_t index)
{
  return arr[index];
}

template<class T>
Vector<T> Vector<T>::operator + (const Vector& obj)
{
  if (size == obj.size)
  {
    Vector<T> vector(size, obj.arr);
    for (size_t i = 0; i < size; i++)
      vector.arr[i] = arr[i] + obj.arr[i];
    return vector;
  }
  else
    throw "this->size != obj.size";
}

template<class T>
Vector<T> Vector<T>::operator-(const Vector<T>& obj)
{
  if (size == obj.size)
  {
    Vector<T> vector(size, obj.arr);
    for (size_t i = 0; i < size; i++)
      vector.arr[i] = arr[i] - obj.arr[i];
    return vector;
  }
  else
    throw "this->size != obj.size";
}

template<class T>
T Vector<T>::operator *(const Vector<T>& obj)
{
  Vector res = 0;
  if (size == obj.size)
  {
    for (size_t i = 0; i < size; i++)
      res = res + (arr[i] * obj.arr[i]);
    return res;
  }
  else
    throw "this->size != obj.size";
}

template<class T>
Vector<T> Vector<T>::operator /(Vector<T>& obj)
{

  if (size == obj.GetSize())
  {
    Vector<T> res;
    res = *this;
    for (size_t i = 0; i < size; i++)
    {
      if (res.arr[i] != 0)
        res.arr[i] = res.arr[i] / obj.arr[i];
    }
    return res;
  }
  else
    throw "this->size != obj.size";
}

template<class T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& obj)
{
  for (size_t i = 0; i < obj.size; i++)
    out << obj.arr[i] << " ";
  out << std::endl;
  return out;
}

template<class T>
std::istream& operator>>(std::istream& in, Vector<T>& obj)
{
  if (obj.size == 0)
  {
    obj.size++;
    obj.SetVector(obj.size);
  }
  for (size_t i = 0; i < obj.size; i++)
    in >> obj.arr[i];
  return in;
}

template <class T>
int Vector<T>::position(T value, int entry)
{
  size_t i, j;

  for (i = 0; i <= size - 1; i++)
  {
    for (j = 0; arr[i + j] == value; j++);
    if (j - 1 == 1 && i == value - 1 && !(entry - 1)) return i;
    if (j == 1)
      if (entry - 1) entry--;
      else return i;
  }

  return -1;
}
