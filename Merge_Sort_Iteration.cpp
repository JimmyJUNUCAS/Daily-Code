void MergeSort2(SqList *L)
{
	int* TR = (*int) malloc (L->length*sizeof(int));
	int k = 1;
	while ( k < L->length )
	{
		MergePass( L->r, TR, k, L->length);
		k = 2*k;
		MergePass( TR, L->r, k, L->length);
		k = 2*k;
	}
}

void MergePass(int SR[], int TR[], int s, int n)
{   //SR 初始无序状态 TR 新申请的序列 s 是序列的起点，n 是整个序列的长度
	int i = 1;
	int j;
	while (i <= n-2*s-1)
	{
		Merge (SR, TR, i, i+s-1, i+2*s-1);
		i = i+2*s;
	}
	if (i<n-s+1)
		Merge (SR, TR, i, i+s-1, n);
	else
		for (j=i;j<=n;j++)
			TR[j] = SR[j];
}

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