
#include <stdio.h>
#include <cstring>
#include <vector>

/*
	- newmtl name
	- Ns double
	- Ka double double double
	- Kd double double double
	- Ks double double double
	- Ni double
	- d double
	- illum int
	- map_Kd (char*) chemin complet.jpg

*/


class Material {

protected:
	char name[255];
	double Ns;

public:
		Material();
/*
		void setX(double pX);
		void setY(double pY);
		void setZ(double pZ);
		void setW(double pW);

		double getX();
		double getY();
		double getZ();
		double getW();

		void dessiner();
*/
};
