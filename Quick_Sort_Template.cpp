template <typename T> void Vector<T>::quickSort(Rank lo, Rank hi){
	if(hi - lo < 2) return;
	Rank mi = partition ( lo, hi - 1 );
	quickSort (lo,mi);
	quickSort (mi + 1, hi);
}

template <typename T> Rank Vector<T>::partition(Rank lo, Rank hi){
	swap (_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);
	T pivot = _elem[lo];
	while( lo < hi ){
		while(( lo < hi )&&( pivot <= _elem[hi] ))
			hi --;
		_elem[lo] = _elem[hi];
		while(( lo < hi)&&(_elem[lo]<=pivot))
			lo ++;
		_elem[hi] = _elem[lo];

	}
	_elem[lo] = pivot;
	return lo;
}

template <typename T> Rank Vector<T>::partition_iteration( Rank lo; Rank hi){
	swap (_elem[lo],_elem[lo + rand() % (hi - lo + 1)]);
	T pivot = _elem[lo];
	while (lo < hi){
		while ( lo < hi )
			if ( pivot < _elem[hi] )
				hi --;
			else
				{ _elem[lo ++] = _elem[hi]; break;}
	    while (lo < hi)
	    	if( _elem[lo] < pivot )
	    		lo ++;
	    	else
	    		{_elem[hi--] = _elem[lo]; break;}	
	}
	_elem[lo] = pivot;
	return lo;
}
