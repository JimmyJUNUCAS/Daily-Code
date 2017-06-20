template <typename T> void Vector<T>::sort (Rank lo, Rank hi){
	switch (rand() % 5){
		case 1: bubbleSort (lo, hi); break;
		case 2: selectionSort (lo, hi); break;
		case 3: mergeSort (lo, hi); break;
		case 4: heapSort (lo, hi); break;
		default: quickSort (lo, hi); break;
	}
}

template <typename T> void Vector<T>::bubbleSort(Rank lo, Rank hi){
	while(!bubble(lo,hi--));
}

template <typename T> bool Vector<T>::bubble (Rank lo, Rank hi){
	bool sorted = true;
	while (++lo < hi)
		if (_elem[lo - 1] > _elem[lo]){
			sorted = false;
			swap(_elem[lo - 1],_elem[lo]);
		}
	return sorted;
}

template <typename T> void Vector <T>::mergeSort (Rank lo, Rnak hi){
	if (hi - lo < 2) return;
	int mi = (lo + hi)/2;
	mergeSort (lo,mi);
	mergeSort (mi,hi);
	merge (lo,mi,hi);
} 

template <typename T> void Vector<T>::merge (Rank lo, Rank mi, Rank hi){
	T* A = _elem + lo;
	int lb = mi - lo;
	T* B = new T[lb];
	for(Rank i = 0; i < lb; B[i] = A[i++]);
	//B[0,lb] = _elem[lo,mi)
	int lc = hi - mi;
	T* C = _elem + mi;
	//C[0,lc] = _elem[mi,hi)
	for( Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); ){
		if(( j < lb ) && (!( k < lc ) || ( B[j] <= C[k] ))) A[i++] = B[j++];
		if(( k < lc ) && (!( j < lb ) || ( C[k] < B[j] ))) A[i++] = C[k++];
	}
	delete [] B;
}

template <typename T> void List<T>::sort (ListNodePosi(T) p, int n){
	switch (rand() % 3){
		case 1: insertionSort (p,n); break;
		case 2: selectionSort (p,n); break;
		default : mergeSort (p,n); break;
	}
}

template <typename T> void List<T>::insertionSort(ListNodePosi(T) p, int n){
	for (int r = 0; r < n; r++)
	{
		insertA (search (p->data,r,p), p->data);
		p = p->succ;
		remove(p->pred)
		/* code */
	}
}

template <typename T> void List<T>::selecetionSort(ListNodePosi(T) p, int n){
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for(int i = 0; i < n; i ++) tail = tail -> succ;
	while ( 1 < n ){
		ListNodePosi(T) max = selectMax (head -> succ, n)
		insertB (tail,remove(max));
		tail = tail->pred;
		n--;
	} 
}

template <typename T> ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n){
	ListNodePosi(T) max = p;
	for (ListNodePosi(T) cur = p; 1 < n; n --)
		if(!lt ((cur = cur->succ)->data, max->data))
			max = cur;
	return max;
	
}

template <typename T> void List<T>::merge (ListNodePosi(T) &p, int n, List<T> &L, ListNodePosi(T) q, int m){
	ListNodePosi(T) pp = p->pred;
	while ( 0 < m )
		if (( 0 < n )&&( p->data <= q->data ))
			{if( q == ( p = p->succ )) break; n--}
		else
			{ insertB( p, L.remove(( q = q->succ ) -> pred)); m--;}

    p = pp->succ;
}

template <typename T> void List<T>::mergeSort(ListNodePosi(T) &p,int n){
	if (n<2) return;
	int m = n >> 1;
	ListNodePosi(T) q = p;
	for (int i = 0; i < m; i++) q = q->succ;
	mergeSort(p,m);
	mergeSort(q,n-m);
	merge(p,m,*this,q,n-m); 
}

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

template <typename T> Rank Vector<T>::partition( Rank lo; Rank hi){
	swap (_elem[lo],_elem[lo + rand() % (hi - lo + 1)]);
	T pivot = _elem[lo];
	while (lo < hi){
		while ( lo < hi )
			if ( pivot < _elem[hi] )
				hi --;
			else
				{ _elem[lo ++] = _elem[hi]; break;}
	    while (lo < hi)
	    	if( _elem[lo] < pivot)
	    		lo ++;
	    	else
	    		{_elem[hi--] = _elem[lo]; break;}	
	}
	_elem[lo] = pivot;
	return lo;
}

template <typename T> T majEleCandidate (Vector<T> A){
	T maj;
	for (int c = 0, i = 0; i < A.size(); i ++)
		if ( 0 == c ){
			maj = A[i]; c = 1;
		} else
		    maj == A[i] ? C++ : C--;
    return maj; 
}

template <typename T> T median (Vector<T>& S1, int lo1, Vector<T>& S2, int lo2, int n){
	if (n < 3) return trivialMedian (S1, lo1, n, S2, lo2, n);
	int mi1 = lo1 + n/2, mi2 = lo2 + (n-1)/2;
	if (S1[mi1]<S2[mi2])
		return median (S1,mi1,S2,lo2,n+lo1-mi1);
	else if (S1[mi1]>S2[mi2])
		return median (S1,lo1,S2,mi2,n+lo2-mi2);
	else
		return S1[mi1];
}

template <typename T> T median (Vector<T>& S1, int lo1, int n1, Vector<T>& S2, int lo2, int n2 ){
	if ( n1 > n2) return median (S2,lo2,n2,S1,lo1,n1,)
}
