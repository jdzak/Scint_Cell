#include <fstream>
#include <vector>
#include "MeshScintillator.h"
#include "Scintillator.h"
#include "Sphereisect.h"
using namespace std;


int main () {
    Scintillator* scint = new Scintillator();

    ScintellatorSphereIntersection* isect = new ScintellatorSphereIntersection(scint1, sphere1);

    MergedRegionScintellatorView* view =  new MergedRegionScintellatorView(isect);

    ofstream geoOut, latOut, gatOut;

    GEOblock.open ("GEOinp.txt", ios::out | ios::app );
    GATblock.open ("GATinp.txt", ios::out | ios::app );
    LATblock.open ("LATinp.txt", ios::out | ios::app );

    vector<MeshRegion> regions = view.getMeshRegions();
    for (int i = 0; i < regions.size(); i++) {
        geoOut << regions[i]->toGeo();
        gatOut << regions[i]->toLat();            
        latOut << regions[i]->toGat();
    }

    geoOut.close();
    gatOut.close();
    latOut.close();

	return 0;
}