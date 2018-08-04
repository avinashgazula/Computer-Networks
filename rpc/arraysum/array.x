struct S{
	int size;
	int a[10];
};

program ARRSUM_PROG{
	version ARRSUM_VERS{
		int ARRAYSUM(S) = 1;
	}=1;
}=0x12345678;
