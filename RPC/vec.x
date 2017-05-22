#define N 100

struct parameters{
	int vector[N];
	int function;
	int functionParameter;
};

struct resultVector{
	int rVector[N];
};

program VEC_PROG{
	version VEC_VERS{
		resultVector powVector(parameters) = 1;
		resultVector logVector(parameters) = 2;
		resultVector multiplyVector(parameters) = 3;
		int sumVector(parameters) = 4;
		int normVector(parameters) = 5;
		int edgeVector(parameters) = 6;
	} = 1;
}=  0x23451111;
