#define N 100000

struct parameters{
	int vector[N];
	int functionParameter;
};

struct resultVector{
	int rVector[N];
};

program VEC_PROG{
	version VEC_VERS{
		resultVector powVector(parameters) = 1;
		resultVector shiftVector(parameters) = 2;
		resultVector multiplyVector(parameters) = 3;
		int sumVector(parameters) = 4;
		int thresholdVector(parameters) = 5;
		int edgeVector(parameters) = 6;
	} = 1;
}=  0x23451111;
