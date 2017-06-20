Sorting
bubbkesort1A(int A[], int n)
{
	bool sorted = false;
	while(!sorted)
	{
		sorted = true;
		for (int i = 1; i < n; i++)
		{
			if (A[i-1] > A[i])
			{
				swap (A[i-1],A[i]);
				sorted = false;
			}
		}
		n--;
	}
}

_int64 fib (int n){
	return (2>n) ? (_int64) n : fib (n-1) + fib(n-2);
}

线性递归版本
_int64 fib (int n, _int64& prev){
	if (0 == n)
		{ prev = 1; return 0;}
	else
	{
		_int64 prevPrev;
		prev = fib(n-1,prevPrev);
		return prevPrev + prev;

	}
}

_int64 fibI (int n){
	_int64 f = 1, g = 0;
	while( 0 < n-- ){ g += f; f= g-f; }
	return g;
}