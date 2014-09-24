#include "OMR_Recognition.h"

int main() {

		clock_t st = clock(); 

		OMR Object;
		Object.OMR_Evaluate();

		clock_t en = clock();

		//fprintf(stdout, "%.3lf\n", (double) ( en - st ) / CLOCKS_PER_SEC );

		return 0;

}