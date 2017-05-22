#include "vec.h"
#define N 100
resultVector *
powvector_1_svc(parameters *argp, struct svc_req *rqstp)
{
	static resultVector  result;

	int i;
	int j;
	int number;
	int mult;
	for(i = 0; i < N;i++){
		int mult = argp->vector[i];
		int number = argp->vector[i];
		for(j =1; j < argp->functionParameter ; j++){
			number = number * mult;
		}
		result.rVector[i] = number;
	}
	return &result;
}

resultVector *
shiftvector_1_svc(parameters *argp, struct svc_req *rqstp)
{
	static resultVector  result;

	int i;
	for(i =0; i < N;i++){
		result.rVector[i] = argp->vector[i] + argp->functionParameter;
	}

	return &result;
}

resultVector *
multiplyvector_1_svc(parameters *argp, struct svc_req *rqstp)
{
	static resultVector  result;

	int i;
	for(i =0; i < N;i++){
		result.rVector[i] = argp->vector[i] * argp->functionParameter;
	}


	return &result;
}

int *
sumvector_1_svc(parameters *argp, struct svc_req *rqstp)
{
	static int  result;

	int i;
	for(i =0; i < N;i++){
		if (argp->vector[i] < 0 && argp->functionParameter == 1)
		{
			result = result + (argp->vector[i]) * -1;
		}
		else{
			result = result + argp->vector[i];
		}
	}

	return &result;
}

int *
thresholdvector_1_svc(parameters *argp, struct svc_req *rqstp)
{
	static int  result;

	int i;
	for(i =0; i < N;i++){
		if (argp->vector[i] > argp->functionParameter){
			result = result + 1;
		}
	}
	return &result;
}

int *
edgevector_1_svc(parameters *argp, struct svc_req *rqstp)
{
	static int  result;
	int bigger;
	int smaller;
	for (int i = 0; i < N; ++i)
	{
		if (argp->vector[i] > bigger){
			bigger= argp->vector[i];
		}
		if (argp->vector[i] < smaller){
			bigger= argp->vector[i];
		}	
	}
	if (argp->functionParameter == 1)
	{
		result = bigger;
	}
	else{
		result = smaller;
	}

	return &result;
}

