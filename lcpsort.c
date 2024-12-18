#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "lcp-quicksort.h"

void dumpitems( unsigned char * s[], int n) {
  int i;
  for( i=0; i < n; i++ ) {
    printf( "%s", s[i] );
  };
  //  printf("\n----\n\n");
}

unsigned char ** readitems( char *fname, int *pn ) {
    int n=0;
    unsigned char **s = NULL;
    FILE * fd = fopen(fname, "r");
    if( fd == NULL ) 
      fprintf(stderr, "fopen %s failed\n", fname);
    else {
      int nalloc = 1<<16;
      s=(unsigned char **) calloc(sizeof(unsigned char *), nalloc);

      char buf[32000];
      while( fgets(buf, 32000, fd) ) {
	if( n >= nalloc ) {
	  nalloc <<=1;
	  s = (unsigned char **) realloc( s, sizeof(unsigned char *) * nalloc);
	}
        
	s[n++] = (unsigned char *) strdup(buf);

      }
    }
    *pn = n;
    return s;
}



int main(int argc, char **argv) {

  ncmp=0;
  if( argc >1 ) {
    int n=0, d=0, i;
    unsigned char  **s = readitems( argv[1], &n );

    int t=clock();

    stringsort( s, n );

    float secs = (clock()-t)*1.0/CLOCKS_PER_SEC;
    fprintf(stderr, "n=%d time=%6.5f  ncmp=%ld \n",n, secs, ncmp );

       dumpitems(s,n);
    exit(0);
  }
  else printf("usage: %s <filename>\n", argv[0]);
}
