/*
 * Fil: oo8_LabGraf.cpp
 * Versjon: 1
 * Kommentar: Behandler data fra fila LAB.DAT og skriv ut resultatet i GRAF.DAT 
 *
 * Forfatter: Gaute Hope, h123507
 */

# include <iostream>
# include <fstream>
# include <iomanip>

using namespace std;

int main () {
    fstream lab ("LAB.DAT", ios::in);
    fstream graf ("GRAF.DAT", ios::out);

    if (!lab || !graf) {
        cout << "Kunne ikkje opne inn og/eller utfil!\n";
        lab.close ();
        graf.close ();
        return 1;
    }

    float t = 0.0;
    float y = 0.0; 
    float x = 0.0;
    float x1 = 0.0;
    float x2 = 0.0;

    lab.ignore (256, '\n'); // hopp over header i lab
    graf << "tid  x      y" << endl; // skriv header til graf
    
    lab >> x;
    while (!lab.eof ()) {
        y = 0.3f * x + 0.7f * x1 + 0.3f*x2;

        graf << setw(3) << setprecision (1) << fixed << t;
        graf << setw(7) << setprecision (3) << fixed << x;
        graf << setw(7) << setprecision (3) << fixed << y;
        graf << endl;

        x2 = x1;
        x1 = x;
        t = t + 0.1f; // Samplingrate er på 10Hz, 10 = 1/T

        lab >> x;
    }    

    lab.close ();
    graf.close ();
	cout << "Behandling av LAB.DAT ferdig\n";
	system ("pause");

    return 0;
}

