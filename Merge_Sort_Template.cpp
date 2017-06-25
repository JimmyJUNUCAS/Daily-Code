template <typename T> void Vector<T>::sort (Rank lo, Rank hi){
	switch (rand() % 5){
		case 1: bubbleSort (lo, hi); break;
		case 2: selectionSort (lo, hi); break;
		case 3: mergeSort (lo, hi); break;
		case 4: heapSort (lo, hi); break;
		default: quickSort (lo, hi); break;
	}
}

template <typename T> void Vector <T>::mergeSort (Rank lo, Rnak hi){
	if (hi - lo < 2) return;
	int mi = (lo + hi)/2;
	mergeSort (lo,mi);
	mergeSort (mi,hi);
	merge (lo,mi,hi);
} 

template <typename T> void Vector<T>::merge (Rank lo, Rank mi, Rank hi){
	int lb = mi - lo;
	int lc = hi - mi;
	T* A = _elem + lo;
	T* C = _elem + mi;

	T* B = new T[lb];
	for(Rank i = 0; i < lb; B[i] = A[i++]);

	for(Rank i = 0, j = 0, k = 0; (j < lb)||(k < lc)){
		if((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
		if((k < lc) && (!(j < lb) || (C[k] < B[j]))) A[i++] = C[k++];
	}
	delete [] B;
}