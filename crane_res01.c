/* ########################################
   ### Rotary crane system 
   ### NC optimized by Cuckoo Search(CS) method.
   ### Evolution simulation in 1 trial.
   ### Compile: gcc -O2 -o crane-cs01 crane-cs01.c myfopen.c 
   crane_3dmodel.C neural_network.c cuckoo_search.c crane_control.c -lm
   ### programmed by nakazono. [2021/09/17]
   ######################################## */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "crane.h"
#include "nn.h"
#include "harmony.h"

//my file structure(myfopen.c)
extern FILE *myfopen(char *fname, char *mode);

//control simulation(crane_control.c)
extern float crane_control_simulation(NEURON_w NCw);
extern float crane_control_simulation_data(NEURON_w NCw);

//initial weights(cuckoo_search.c)
extern INDIVIDUAL rand_w(void);

//harmony_renew(harmony_search.c)
extern INDIVIDUAL harmony_renew(INDIVIDUAL HM[IND_SIZE]);

// convert HS into NC weights(harmony_search.c)
extern NEURON_w convert_weight(INDIVIDUAL HM);

int main(void)
{
  FILE *fp1, *fpw;
  int seed, iteration, ind, i, j, k;
  float weight;
  NEURON_w NCw;
  INDIVIDUAL HM, new_HS, tmp;

  fpw=myfopen("w-harmony.dat","r");

  // read connection weights
  for(j=0;j<J_MAX;j++)
            for(i=0;i<I_MAX;i++){
                fscanf(fpw, "%f¥n", &weight);
                HM.whid[i][j]=weight;
           }
  for(k=0;k<K_MAX;k++)
            for(j=0;j<J_MAX;j++){
                fscanf(fpw, "%f¥n", &weight);
                HM.whid[j][k]=weight;
           }
  // init weights
  NCw = convert_weight(HM);
  // Control start
  HM.E = crane_control_simulation_data(NCw);

  fclose(fpw);

  return 0;
} // end main