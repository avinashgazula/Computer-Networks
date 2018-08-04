/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */
#include <stdio.h>
#include <time.h>
#include "date.h"

char **
gettime_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "Current local time and date: %s", asctime (timeinfo) );
  
  result = asctime (timeinfo);

	return &result;
}
