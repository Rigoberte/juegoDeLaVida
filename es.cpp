#include "es.h"
#include "definiciones.h"

/******************************** EJERCICIO cargarToroide *******************************/
toroide cargarToroide(string nombreArchivo, bool &status)
{
	toroide t;
	/**************************** CORTAR INICIO *****************************************/
	ifstream ftoroide(nombreArchivo);

	int filas;
	int columnas;
	int value;
	int checksum = 0;
	int count = 0;

	status = false;

	if (!ftoroide.fail()) {
		ftoroide >> filas;
		ftoroide >> columnas;
		if (filas <= 0 || columnas <= 0)
			goto error;

		t = toroide(filas, vector<bool>(columnas));

		for (int i = 0; i < filas; i++) {
			for (int j = 0; j < columnas; j++) {
				ftoroide >> value;
				if (ftoroide.fail())
					goto error;
				if (value == 1) {
					t[i][j] = true;
					count++;
				}
			}
		}
		ftoroide >> checksum;
		status = (count == checksum);
	}

error:
	/**************************** CORTAR FIN ********************************************/
	return t;
}


/******************************** EJERCICIO escribirToroide *****************************/
bool escribirToroide(string nombreArchivo, toroide &t)
{
	bool res;
	/**************************** CORTAR INICIO *****************************************/
	ofstream ftoroide(nombreArchivo);

	int filas = t.size();
	int columnas = t[0].size();
	int value;
	int count = 0;

	if (!ftoroide.fail()) {
		ftoroide << filas << endl;
		ftoroide << columnas << endl;

		for (int i = 0; i < filas; i++) {
			for (int j = 0; j < columnas; j++) {
				if (t[i][j]) {
					value = 1;
					count++;
				} else
					value = 0;
				ftoroide << value << ((j < columnas-1) ? " " : "");
			}
			ftoroide << endl;
		}
		ftoroide << count << endl;
	}
	
	res = !ftoroide.fail();
	/**************************** CORTAR FIN ********************************************/
	return res;
}
