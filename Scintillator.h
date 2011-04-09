#ifndef SCINTILLATOR_H
#define SCINTILLATOR_H

class Scintillator {
    string name;
    int yMesh, zmesh;
    double xLength, yLength, zLength, xVert, yVert, zVert;
    

    public:
    // Constructors
    Scintillator::Scintillator(double xLen, double yLen, double zLen, int yMesh, int zMesh, double xVert, double yVert, double zVert); 
    
    // Setters
    void setYMesh(int y) {this->yMesh = y;}
    void setZMesh(int z) {this->zmesh = z;}
    void setXLength(double x) { this->xLength = x;}
    void setYLength(double Y) {this->yLength = y;}
    void setZLength(double z) {this->zLength = z;}
    void setXVert(double x) {this->xVert = x;}
    void setYVert(double y) {this->yVert = y;}
    void setZVert(double z) {this->zVert = z;}

    // Getters
    int getYMesh(void) {return this->yMesh;}
    int getZMesh(void) {return this->zmesh;}
    double getXLength(void) {return this->xLength;}
    double getYLength(void) {return this->yLength;}
    double getZLength(void) {return this->zLength;}
    double getXVert(void) {return this->xVert;}
    double getYVert(void) {return this->yVert;}
    double getZVert(void) {return this->zVert;}
};

Scintillator::Scintillator(double xLen, double yLen, double zLen, int yMesh, int zMesh, double xVert, double yVert, double zVert) {
    this->xLen = xLen;
    this->yLen = yLen;
    this->zLen = zLen;
    this->yMesh = yMesh;
    this->zMesh = zMesh;
    this->xVert = xVert;
    this->yVert = yVert;
    this->zVert = zVert;
}
#endif
