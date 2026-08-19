#pragma once

class Systemindstillinger {
	public:
	static void init(int lys, int tid); // erstating for constructor, som ikke giver mening at have i en static class. Kaldes ved opstart.
	static int  getLysintensitet();
	static int  getTidsfoelsomhed();
	static bool setLysintensitet(int nyLysintensitet);
	static bool setTidsfoelsomhed(int nyTidsfoelsomhed);

	private:
	static int lysintensitet;
	static int tidsfoelsomhed;
};