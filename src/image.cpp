#include "atom.h"
#include <new>
#include "image.h"
#include <iostream>
atom* imageall(atom* input,int size,double** p,double cutoff,int& virt_size){
	double min=100000;
	for(size_t i=0;i<3;i++){
		if(p[i][i]<min)
			min=p[i][i]; 
	}
	int nimage=ceil(cutoff/min);
	virt_size=nimage*2+1;
	atom* allimage=new atom[virt_size*size*virt_size*virt_size];
	/*copy all the memory to different images*/
	for(size_t i=0;i<virt_size*virt_size*virt_size;i++){
        std::copy(input,input+size,allimage+i*size);
	}
	int shiftv[3]={0,0,0};
	int imagetick=0;
  	for(int k=-1*nimage;k<=nimage;k++)
		for(int j=-1*nimage;j<=nimage;j++)
			for(int i=-1*nimage;i<=nimage;i++){
				shiftv[0]=i;
				shiftv[1]=j;
				shiftv[2]=k;
				imagetick=(i+nimage)+(j+nimage)*virt_size+(k+nimage)*virt_size*virt_size;
				shift(allimage+imagetick*size,size,p,shiftv);
	}
	virt_size=virt_size*virt_size*virt_size*size;
	return allimage;
}
void shift(atom* input,int size,double** p,int* shiftv){
  for(size_t i=0;i<size;i++){
     for(size_t j=0;j<3;j++){//loop over the ( x, y, z)
        for(size_t k=0;k<3;k++){//loop over the ( shift v1 v2 v3 )
        (input+i)->position[j]=(input+i)->position[j]+shiftv[k]*p[k][j];
        }
     }
  }
}
