#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <vector>

class MergedRegionScintellatorView {
    vector<MeshedRegion> getMeshedRegions() {
        // set up variables to analyze meshes
        	double Mesh_Height=scint1.getZLength()/scint1.getZMesh();
        	double z_top=scint1.getZLength()+scint1.getZVert();
        	double z_isect[4], sorted_isect[4];  //This defines the elevation where the four edges of the RPP or three edges of the TRI intersect 
        													 // the sphere
        	double z_bottom=scint1.getZVert();
        	int z_numb;
        	vector <double> z_elvs;
         	z_elvs.resize(scint1.getZMesh()+1);

        	z_elvs[0]=scint1.getZVert();
        	for (i=1;i<scint1.getZMesh()+1;++i){
        		z_elvs[i]=z_elvs[i-1]+Mesh_Height;
        	}

        // Test and print sectors
        	for (i=0;i<Row;++i){	
        		for (j=0;j<Col;++j) {
        			if ((S1Mesh[i][j].getPT() == Tri_Plain) || (S1Mesh[i][j].getPT() == RPP_Plain)){ 		
        				//Print TRI_plain or RPP_plain!!!
        				cout<<"line 87"<<endl;
        				PrintPart(i,j,S1Mesh,z_elvs,scint1.getZMesh(), scint1, sphere1); 
        			} 
        			else if ((S1Mesh[i][j].getPT() == Tri_Isect) || (S1Mesh[i][j].getPT() == RPP_Isect)) {  

        				DefineIsects(i, j, S1Mesh, sphere1, z_isect);
        				if ((z_isect[0]!=z_isect[0])||(z_isect[1]!=z_isect[1])||(z_isect[2]!=z_isect[2])||(z_isect[3]!=z_isect[3])){
        					cout<<"line 106"<<endl;
        					PrintPart(i,j,S1Mesh,z_elvs,scint1.getZMesh(), scint1, sphere1); 	
        					continue; // No voided regions. Print TRI_isect or RPP_isect
        				}  
        				if 
        				((z_isect[0]<0)||(z_isect[1]<0)||(z_isect[2]<0)||(z_isect[3]<0)){
        					cout<<"line 114"<<endl;
        					PrintPart(i,j,S1Mesh,z_elvs,scint1.getZMesh(), scint1, sphere1);
        					continue; // No voided regions. Print TRI_isect or RPP_isect
        				}  

        				for (int k=0;k<4;++k){
        					sorted_isect[k]=z_isect[k];
        				}
        				bubbleSort(sorted_isect, 4);
        				//cout<<sorted_isect[0]<<", "<<sorted_isect[1]<<", "<<sorted_isect[2]<<", "<<sorted_isect[3]<<endl;


        				double top_isect=sorted_isect[3];
        				double bot_isect=sorted_isect[0];
        				int z_numb=0;
        				vector <double> test_elvs;
        				test_elvs.resize(scint1.getZMesh()+1);
        				test_elvs[0]=bot_isect;
        				//number of full RPPs
        				double temp=z_top;
        				while (temp > top_isect){		
        					temp=temp - Mesh_Height;
        					z_numb++;
        				}
        				double test_top;
        				temp=z_top;
        				if (z_numb > 1) {
        					//cout<<"line 130, "<<S1Mesh[i][j].getxMin()<<", "<<S1Mesh[i][j].getyMin()<<", "<<z_numb<<", "<<top_isect<<", "<<z_top<<endl;
        					test_elvs.resize(z_numb);
        					for (int n=z_numb;n>=0;--n){
        						//cout<<"OK_n="<<n<<endl;
        						test_elvs[n]=temp;
        						temp= temp - Mesh_Height;
        					}
        					//cout<<"OK_2"<<endl;
        					test_top=test_elvs[0];
        					//cout<<"line 137"<<endl;
        					PrintPart(i,j,S1Mesh,test_elvs,z_numb, scint1, sphere1); 
        				} 
        				else{
        					//cout<<"line 141, "<<i<<", "<<j<<", "<<z_numb<<", "<<top_isect<<", "<<z_top<<endl;
        					test_top=z_top;
        				}

        				//find upper height of voided region
        				double test_bottom = z_bottom;
        				while (test_bottom < bot_isect-Mesh_Height) {
        					test_bottom = test_bottom + Mesh_Height;
        				}

        				z_numb=0;
        				temp=test_bottom;
        				while (temp < test_top){		
        					temp=temp + Mesh_Height;
        					z_numb++;
        				}
        				test_elvs.resize(z_numb);
        				// Test intersecting region
        				temp=test_bottom;
        				test_elvs[0]=test_bottom;
        				int n=0;
        				double Total_Vol=abs(Mesh_Height*(S1Mesh[i][j].getyMax()-S1Mesh[i][j].getyMin())*(S1Mesh[i][j].getxMax()-S1Mesh[i][j].getxMin()));
        				double testHeight,test_Vol;

        				while (temp < test_top) {
        					cout<<temp<<", "<<S1Mesh[i][j].getxMin()<<", "<<S1Mesh[i][j].getyMin()<<", "<<test_top<<", "<<bot_isect<<endl;
        					temp = temp + Mesh_Height;
        					if (temp < sorted_isect[2]){
        						if (temp < sorted_isect[1]){
        							// test using volume of tetrahedron
        							testHeight=temp-bot_isect;
        							test_Vol=FindTetraVol(sorted_isect,z_isect,i,j,S1Mesh,sphere1,temp, testHeight); 

        							if (test_Vol < 0.05*Total_Vol){
        								cout<<"Too small of a volume. Tetra_Vol= "<<test_Vol<<", Total_Vol= "<<Total_Vol<<endl;
        								continue; //Too small of a volume
        							} else{
        								n++;
        								test_elvs[n]=temp; 
        								cout<<"line182 n="<<n<<", Tetra_Vol= "<<test_Vol<<", Total_Vol= "<<Total_Vol<<endl;
        							}
        						} else {
        							// test using frustrum of tetrahedron
        							testHeight=temp-bot_isect;
        							test_Vol=FindFrustumTetra(sorted_isect,z_isect,i,j,S1Mesh,sphere1,temp, testHeight); 

        							if (test_Vol < 0.05*Total_Vol){
        								cout<<"Too small of a volume. Frustum_Vol= "<<test_Vol<<", Total_Vol= "<<Total_Vol<<endl;
        								continue; //Too small of a volume
        							} else{
        								n++;
        								test_elvs[n]=temp; 
        								cout<<"line194 n="<<n<<". Frustum_Vol=  "<<test_Vol<<", Total_Vol= "<<Total_Vol<<endl;
        							}						
        						}
        					} else {
        						n++;
        						test_elvs[n]=temp; 
        						//cout<<"line199 n="<<n<<endl;
        					}
        				}
        				//cout<<"line 266"<<endl;
        				PrintPart(i,j,S1Mesh,test_elvs,n, scint1, sphere1); 

        			} else {	//part is null do nothing	
        			} 
        		}
        	}
        
    }
    
    void DefineIsects(int i, int j,vector< vector<MeshScintillator > >& S1Mesh, Sphereisect sphere1, double z_isect[]){
    	z_isect[0]=FindSpherePoint(sphere1.getRadius(),S1Mesh[i][j].getxMax()-sphere1.getXVert(), \
    					S1Mesh[i][j].getyMax()-sphere1.getYVert()) +sphere1.getZVert();  //Fix for arrays 1,2 and 3
    	z_isect[1]=sqrt( sphere1.getRadius()*sphere1.getRadius() - pow(S1Mesh[i][j].getxMin()-sphere1.getXVert(),2) \
    					- pow(S1Mesh[i][j].getyMax()-sphere1.getYVert(),2) ) +sphere1.getZVert();
    	z_isect[2]=sqrt( sphere1.getRadius()*sphere1.getRadius() - pow(S1Mesh[i][j].getxMax()-sphere1.getXVert(),2) \
    					- pow(S1Mesh[i][j].getyMin()-sphere1.getYVert(),2) ) +sphere1.getZVert();
    	z_isect[3]=sqrt( sphere1.getRadius()*sphere1.getRadius() - pow(S1Mesh[i][j].getxMin()-sphere1.getXVert(),2) \
    					- pow(S1Mesh[i][j].getyMin()-sphere1.getYVert(),2) ) +sphere1.getZVert();

    }

    double FindSpherePoint(double r, double dim1, double dim2) {
    	double Point=sqrt( pow(r,2) - pow(dim1,2) - pow(dim2,2) );
    	return Point;
    }


    void bubbleSort(double arr[], int n) {
          bool swapped = true;
          int j = 0;
          double tmp;
          while (swapped) {
                swapped = false;
                j++;
                for (int i = 0; i < n - j; i++) {
                      if (arr[i] > arr[i + 1]) {
                            tmp = arr[i];
                            arr[i] = arr[i + 1];
                            arr[i + 1] = tmp;
                            swapped = true;
                      }
                }
          }
    }
    
    double FindFrustumTetra(double sorted_isect[],double z_isect[],int i, int j,vector < vector<MeshScintillator > >& S1Mesh,Sphereisect  sphere1,double temp, double testHeight){

    	double A1,A2,test_Xlen,test_Xlen2,test_Ylen,test_Ylen2,test_Vol;
    	if(sqrt(abs(pow(sphere1.getRadius(),2)-pow(temp-sphere1.getZVert(),2)))<=abs(S1Mesh[i][j].getxMax())){
    		test_Xlen=abs(S1Mesh[i][j].getxMax())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getyMax()-sphere1.getYVert())+sphere1.getXVert());
    		A1=0.5*test_Xlen*testHeight;
    		test_Xlen2=abs(S1Mesh[i][j].getxMax())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getyMin()-sphere1.getYVert())+sphere1.getXVert());
    		A2=0.5*test_Xlen2*testHeight;
    		test_Vol=(A1+A2+sqrt(A1*A2))/3;
    		cout<<"line 264, Ylen= "<<test_Ylen<<", Ylen2= "<<test_Ylen2<<", Zlen= "<<testHeight<<", ";
    	}
    	else if (sqrt(abs(pow(sphere1.getRadius(),2)-pow(temp-sphere1.getZVert(),2)))<=abs(S1Mesh[i][j].getxMin())){
    		test_Xlen=abs(S1Mesh[i][j].getxMin())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getyMax()-sphere1.getYVert())+sphere1.getXVert());
    		A1=0.5*test_Xlen*testHeight;
    		test_Xlen2=abs(S1Mesh[i][j].getxMin())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getyMin()-sphere1.getYVert())+sphere1.getXVert());
    		A2=0.5*test_Xlen2*testHeight;
    		test_Vol=(A1+A2+sqrt(A1*A2))/3;
    		cout<<"line 272, Ylen= "<<test_Ylen<<", Ylen2= "<<test_Ylen2<<", Zlen= "<<testHeight<<", ";
    	}
    	else if (sqrt(abs(pow(sphere1.getRadius(),2)-pow(temp-sphere1.getZVert(),2)))<=abs(S1Mesh[i][j].getyMax())){
    		test_Ylen=abs(S1Mesh[i][j].getyMax())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getxMin()-sphere1.getXVert())+sphere1.getYVert());
    		A1=0.5*test_Ylen*testHeight;
    		test_Ylen2=abs(S1Mesh[i][j].getyMax())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getxMax()-sphere1.getXVert())+sphere1.getYVert());
    		A2=0.5*test_Ylen2*testHeight;
    		test_Vol=(A1+A2+sqrt(A1*A2))/3;
    		cout<<"line 280, Ylen= "<<test_Ylen<<", Ylen2= "<<test_Ylen2<<", Zlen= "<<testHeight<<", ";
    	}
    	else{
    		test_Ylen=abs(S1Mesh[i][j].getyMin())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getxMax()-sphere1.getXVert())+sphere1.getYVert());
    		A1=0.5*test_Ylen*testHeight;
    		test_Ylen2=abs(S1Mesh[i][j].getyMin())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getxMin()-sphere1.getXVert())+sphere1.getYVert());
    		A2=0.5*test_Ylen2*testHeight;
    		test_Vol=(A1+A2+sqrt(A1*A2))/3;
    		cout<<"line 288, Ylen= "<<test_Ylen<<", Ylen2= "<<test_Ylen2<<", Zlen= "<<testHeight<<", ";
    	}
    	return test_Vol;
    } 


    double FindTetraVol(double sorted_isect[],double z_isect[],int i, int j,vector < vector<MeshScintillator > >& S1Mesh,Sphereisect  sphere1,double temp, double testHeight){
    	double test_Xlen,test_Ylen, test_Vol;
    	if(sorted_isect[0]==z_isect[0]){
    		test_Xlen=abs(S1Mesh[i][j].getxMax())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getyMax()-sphere1.getYVert())+sphere1.getXVert());
    		test_Ylen=abs(S1Mesh[i][j].getyMax())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getxMax()-sphere1.getXVert())+sphere1.getYVert());		 
    		test_Vol=testHeight*test_Xlen*test_Ylen/6;
    	}
    	else if (sorted_isect[0]==z_isect[1]){
    		test_Xlen=abs(S1Mesh[i][j].getxMin())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getyMax()-sphere1.getYVert())+sphere1.getXVert());
    		test_Ylen=abs(S1Mesh[i][j].getyMax())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getxMin()-sphere1.getXVert())+sphere1.getYVert());
    		test_Vol=testHeight*test_Xlen*test_Ylen/6;
    	}
    	else if (sorted_isect[0]==z_isect[2]){
    		test_Xlen=abs(S1Mesh[i][j].getxMax())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getyMin()-sphere1.getYVert())+sphere1.getXVert());
    		test_Ylen=abs(S1Mesh[i][j].getyMin())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getxMax()-sphere1.getXVert())+sphere1.getYVert());
    		test_Vol=testHeight*test_Xlen*test_Ylen/6;
    	}
    	else{
    		test_Xlen=abs(S1Mesh[i][j].getxMin())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getyMin()-sphere1.getYVert())+sphere1.getXVert());					 
    		test_Ylen=abs(S1Mesh[i][j].getyMin())-abs(FindSpherePoint(sphere1.getRadius(),temp-sphere1.getZVert()\
    						,S1Mesh[i][j].getxMin()-sphere1.getXVert())+sphere1.getYVert());
    		test_Vol=testHeight*test_Xlen*test_Ylen/6;
    	}
    	return test_Vol;
    }
    
}