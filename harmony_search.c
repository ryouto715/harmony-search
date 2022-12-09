/*
######################################## 
### Harmony search method
### HS method  
### programmed by nakazono. [2021/09/17] 
######################################## */

#include<stdio.h> 
#include<stdlib.h> 
#include<math.h>

#include "crane.h" 
#include "nn.h" 
#include "harmony.h"

//normal random number
float rand_n(void)
{
    return sqrt(-2.0*log(drand48()))*cos(2.0*PI*drand48());
}

float sigma(float beta)
{
    float nume,denom;
    nume = tgamma(1.0+beta)*sin(PI*beta/2.0);
    denom = tgamma((1.0+beta)/2.0)*beta*pow(2.0,
    (beta-1.0)/2);
             return pow(nume/denom,1.0/beta);
}

//initial weights
INDIVIDUAL rand_w(void)
{
    int i,j,k;
    INDIVIDUAL init;

    for(j=0;j<J_MAX;j++){
        for(i=0;i<I_MAX;i++){

    init.whid[i][j]=(float)(drand48()*(2.0*XMAX)-XMAX);
                          }
                }
                for(k=0;k<K_MAX;k++){
                         for(j=0;j<J_MAX;j++){
    init.wout[j][k]=(float)(drand48()*(2.0*XMAX)-XMAX);
                          }
                }

                return init;
}


// harmony_renew
INDIVIDUAL harmony_renew(INDIVIDUAL HM[IND_SIZE])
{

    int i,j,k,r;
    INDIVIDUAL new_HS;

    for(j=0;j<J_MAX;j++){
      for(i=0;i<I_MAX;i++){
        if(drand48()<R_A){
            r=lrand48()%IND_SIZE;
            if(drand48()<R_P){
                new_HS.whid[i][j]=HM[r].whid[i][j]+BANDWIDTH*(drand48()*2.0-1.0); // 変更
            } else {
                new_HS.whid[i][j]=HM[r].whid[i][j]; // 複製
            } 
        } else {
            new_HS.whid[i][j]=(drand48()*2.0-1.0);  // 生成
        }
      }
    }
    for(k=0;k<K_MAX;k++){
      for(j=0;j<J_MAX;j++){
        if(drand48()<=R_A){
            r=rand()%IND_SIZE;
            if(drand48()<=R_P){
                new_HS.wout[j][k]=HM[r].wout[j][k]+BANDWIDTH*(drand48()*2.0-1.0); // 変更
            } else {
                new_HS.wout[j][k]=HM[r].wout[j][k];   // 複製
            } 
        } else {
            new_HS.wout[j][k]=(drand48()*2.0-1.0);  // 生成
        }
      }
    }

    return new_HS;
}
    

//convert HS into NC weights
NEURON_w convert_weight(INDIVIDUAL HM)
{
    int i,j,k;
    NEURON_w NCw;
    for(j=0;j<J_MAX;j++)
             for(i=0;i<I_MAX;i++)
                       NCw.n_ij[i][j]=HM.whid[i][j];
    for(j=0;j<J_MAX;j++){
             for(k=0;k<K_MAX;k++){
                       NCw.n_jk[j][k]=HM.wout[j][k];
             }
    }
    return NCw;
}