/* ########################################
   ### Rotary crane system 
   ### NC optimized by Harmony Search(HS) method.
   ### Evolution simulation in 1 trial.
   ### Compile: gcc -O2 -o crane-cs01 crane-cs01.c myfopen.c 
   crane_3dmodel.C neural_network.c harmony_search.c crane_control.c -lm
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

//initial weights(harmony_search.c)
extern INDIVIDUAL rand_w(void);

//harmony_renew(harmony_search.c)
extern INDIVIDUAL harmony_renew(INDIVIDUAL HM[IND_SIZE]);

// convert HS into NC weights(harmony_search.c)
extern NEURON_w convert_weight(INDIVIDUAL HM);

int main(void)
{
  FILE *fp1, *fpw;
  int s, iteration, ind, i, j, k, best, worst, u, seed;
  NEURON_w NCw;
  INDIVIDUAL HM[IND_SIZE], new_HS, tmp;  


  

    seed= 2900;
    char filename1[100];
    char filename2[100];
    
    sprintf(filename1,"R_A-0.8/e-harmony%d.dat",seed);
    sprintf(filename2,"R_A-0.8/w-harmony%d.dat",seed);
    fp1 = myfopen(filename1,"w");
    fpw = myfopen(filename2,"w");

    // fp1=myfopen("DATA/e-harmony.dat","w");
    // fpw=myfopen("DATA/w-harmony.dat","w");

    
    printf("seed=%d\n",seed);
    srand48(seed);
    
      //Evolution simulation start
      //initial connection weights
      for(ind=0;ind<IND_SIZE;ind++) {
        //init weights
        HM[ind]=rand_w();
        NCw=convert_weight(HM[ind]);
        // Control start
        HM[ind].E=crane_control_simulation(NCw);
    } // end individuals

    for (iteration=1; iteration<ITERATION; iteration++)
    {
      new_HS = harmony_renew(HM);
      NCw = convert_weight(new_HS);
      new_HS.E = crane_control_simulation(NCw);
      
      if(HM[worst].E > new_HS.E){
        // ハーモニーを交換する
        tmp = new_HS;
        new_HS = HM[worst];
        HM[worst] = tmp;
        
        // 最良ハーモニーの添え字を更新する
        if(HM[best].E > HM[worst].E){
          best = worst;
        }

        // 最悪ハーモニーの添え字を更新する
        worst = 0;   
        for(i=1; i < IND_SIZE; i++){
          if(HM[worst].E < HM[i].E){
            worst = i;
          }
        }
      }
      //評価出力
      fprintf(fp1, "%.12f\n", HM[best].E);
      printf( "seed=%d iteration=%d E[best]=%.12f E[worst]=%.12f\n", seed, iteration, HM[best].E, HM[worst].E);
    } // end iteration

      //save conection weights
      for(j=0;j<J_MAX;j++)
        for(i=0;i<I_MAX;i++)
          fprintf(fpw, "%lf\n", HM[best].whid[i][j]);
      for(k=0;k<K_MAX;k++)
        for(j=0;j<J_MAX;j++)
          fprintf(fpw, "%lf\n", HM[best].wout[j][k]);

  fclose(fp1);
  fclose(fpw);

  return 0;
}//end main
