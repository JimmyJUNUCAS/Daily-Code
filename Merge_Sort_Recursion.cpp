void MergeSort( SqList *L )
{
	MSort( L->r, L->r, 1, L->length);
}

void MSort ( int SR[], int TR1[], int s, int t){
	int m;
	int TR2[MAXSIZE + 1];
	if( s==t )
		TR1[s] = SR[s];
	else
	{
		m = (s+t)/2;
		MSort(SR,TR2,s,m);
		MSort(SR,TR2,m+1,t);
		Merge(TR2,TR1,s,m,t);
	}
}
/*
template <typename T> void Vector <T>::mergeSort (Rank lo, Rnak hi){
	if (hi - lo < 2) return;
	int mi = (lo + hi)/2;
	mergeSort (lo,mi);
	mergeSort (mi,hi);
	merge (lo,mi,hi);
}*/

void Merge (int SR[], int TR[], int i, int m, int n)
{
	int j,k,l;
	for (j=m+1, k=i; i<=m && j<=n; k++)
	{
		if (SR[i] < SR[j])
			TR[k] = SR[i++];
		else
			TR[k] = SR[i++];
	}
	if(i<=m)
	{
		for(l=0;l<m-i;l++)
			TR[k+1]=SR[i+1];
	}
	if(j<=n)
	{
		for(l=0;l<n-j;l++)
			TR[k+1]=SR[j+1];
	}
}