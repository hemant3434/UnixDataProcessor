#include<stdio.h>
#include<stdlib.h>

int main(int arg, char** args){

  double a[5];
  for(int i = 1; i<6; i++){
    a[i-1] = atof(args[i]);
  }
  double x[3] = {0};
  double y[3] = {0};

  while (scanf("%lf", &(x[2]))!=EOF){
    y[2] = a[0]*( x[2]+ (a[1]*x[1]) + (a[2]*x[0]) )-(a[3]*y[1])-(a[4]*y[0]);
    x[0] = x[1];
    x[1] = x[2];
    y[0] = y[1];
    y[1] = y[2];
    printf("%g\n", y[2]);
  }
  return 0;
}
