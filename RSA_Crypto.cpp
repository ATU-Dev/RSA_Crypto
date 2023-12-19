#include <iostream>
#include <math.h>
using namespace std;

int gcd(int a, int b) {
	return (b==0 ? a : gcd(b, a % b));
}
int gcdExtended(int a, int b, int &x, int &y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int gcd = gcdExtended(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return gcd;
}

int main()
{
	long p, q, n, e, k, d, phi;
	int msg = 12;

	// Schritt 1: 2 große Primzahlen wählen (p und q)
	p = 3;
	q = 7;

	// Schritt 2: n=p*q berechnen (n wird als modulare Raum verwendet)
	n = p * q;

	// Schritt 3: Eine public Key (e) wählen, der relativ prim zu (p-1)*(q-1) ist
	phi = (p-1)*(q-1);
	for (e = 2; e < phi; e++) {
		if (gcd(e, phi) == 1) break;
	}

	// Schritt 4: Private Key (d) berechnen: d=e^-1 % phi
	for (d = 0; d < phi; d++) {
		k = (e*d) % phi;
		if (k==1) break;
	}

	// Test
	cout << "n="<<n << "\tphi="<<phi << "\te="<<e << "\td="<<d << endl;

	// Schritt 5: Um eine Nachricht zu verschlüsseln, berechnet man:  c = m^e % n
	int enc = pow(msg, e);
	enc %= n;
	cout << "Encrypted Message: " << enc << endl;

	// Schritt 6: Um die Nachricht zu entschlüsseln, berechnet man:  m = c^d % n
    long dec = pow(enc, d);
    cout << dec << endl;
    dec = fmod(dec, n);
    cout << "Decrypted Message: " << dec << endl;

	return 0;
}
