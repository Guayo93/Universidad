template< class I >
bool is_sorted(I first, I last)
{
  bool flag = true;
  I i = first;
  I j = i;
  j++;
  for(; j != last; ++i, ++j)
  {
    flag &= (*(i) <= *(j));
  }

  return (flag);
}

/*
  for i in `seq 1000 1000 100000`; do ./prueba $i; done > results.txt
*/
