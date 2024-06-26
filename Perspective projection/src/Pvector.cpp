#include "Pvector.h"
#include <cmath>//apagar esta

Pvector::Pvector(float value1, float value2, float value3) {
	x = value1;
	y = value2;
	z = value3;
}

Pvector::Pvector() {
	x = 0;
	y = 0;
	z = 0;
}
