//mjz5zf
//I pledge I have neither given nor received any aid on this assignment
//g++ -O -Wall mjz5zf_chi2fit.cpp -o mjz5zf_chi2fit $P2660FLAGS

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include"random.hpp"
#include"hist.hpp"

typedef struct{//Each one of these structures represents a line
  double jet1,jet2,jet3,eta1,eta2,eta3,met,ht,njet;
} datum;

int main(){
  //Creating histograms
  killplots();
  h1 hist1,hist2,hist3;
  h1init(&hist1,50,0,1000,"ht values for data");
  h1labels(&hist1,"Ht value","Frequency");
  h1init(&hist2,50,0,1000,"ht values for signal");
  h1labels(&hist2,"Ht value","Frequency");
  h1init(&hist3,50,0,1000,"ht values for background");
  h1labels(&hist3,"Ht value","Frequency");

  //Initializing the data storage
  datum data[10000];
  datum signal[10000];
  datum bkgd[10000];

  FILE *inputdat,*inputsign,*inputbkg;//Opening files
  inputdat=fopen("data.dat","r");
  inputsign=fopen("signal_templates.dat","r");
  inputbkg=fopen("bkgd_templates.dat","r");


  char str[10];//Placeholder string
  int status;
  fscanf(inputdat,"%s %s %s",str,str,str);//getting through the labels
  fscanf(inputdat,"%s %s %s",str,str,str);
  fscanf(inputdat,"%s %s %s",str,str,str);
  fscanf(inputdat,"%s %s",str,str);
  fscanf(inputdat,"%s %s",str,str);
  fscanf(inputdat,"%s %s",str,str);
  fscanf(inputdat,"%s",str);
  fscanf(inputdat,"%s",str);
  fscanf(inputdat,"%s",str);

  fscanf(inputsign,"%s %s %s",str,str,str);//getting through the labels
  fscanf(inputsign,"%s %s %s",str,str,str);
  fscanf(inputsign,"%s %s %s",str,str,str);
  fscanf(inputsign,"%s %s",str,str);
  fscanf(inputsign,"%s %s",str,str);
  fscanf(inputsign,"%s %s",str,str);
  fscanf(inputsign,"%s",str);
  fscanf(inputsign,"%s",str);
  fscanf(inputsign,"%s",str);
  fscanf(inputbkg,"%s %s %s",str,str,str);//getting through the labels
  fscanf(inputbkg,"%s %s %s",str,str,str);
  fscanf(inputbkg,"%s %s %s",str,str,str);
  fscanf(inputbkg,"%s %s",str,str);
  fscanf(inputbkg,"%s %s",str,str);
  fscanf(inputbkg,"%s %s",str,str);
  fscanf(inputbkg,"%s",str);
  fscanf(inputbkg,"%s",str);
  fscanf(inputbkg,"%s",str);
  int i=0;
  while (1){
    //reading through and storing data in "data.dat"
    status=fscanf(inputdat,"%lf %lf %lf %lf %lf %lf %lf %lf %lf",&data[i].jet1,$
    if (status==EOF || status!=9) break;
    h1fill(&hist1,data[i].ht,1);
    //printf("%lf %lf %lf %lf %lf %lf %lf %lf %lf\n",data[i].jet1,data[i].jet2,$

    i+=1;
  }
  i=0;
  while (1){
    //reading signals
    status=fscanf(inputsign,"%lf %lf %lf %lf %lf %lf %lf %lf %lf",&signal[i].je$
    if (status==EOF || status!=9) break;
    h1fill(&hist2,signal[i].ht,404.0/3190.0);
    //printf("%lf %lf %lf %lf %lf %lf %lf %lf %lf\n",signal[i].jet1,signal[i].j$

    i+=1;
  }
  i=0;
  while (1){
    //reading signals
    status=fscanf(inputsign,"%lf %lf %lf %lf %lf %lf %lf %lf %lf",&signal[i].je$
    if (status==EOF || status!=9) break;
    h1fill(&hist2,signal[i].ht,404.0/3190.0);
    //printf("%lf %lf %lf %lf %lf %lf %lf %lf %lf\n",signal[i].jet1,signal[i].j$

    i+=1;
  }
  i=0;
  while (1){
    //reading background data
    status=fscanf(inputbkg,"%lf %lf %lf %lf %lf %lf %lf %lf %lf",&bkgd[i].jet1,$
    if (status==EOF || status!=9) break;
    h1fill(&hist3,bkgd[i].ht,404.0/3190.0);
    //printf("%lf %lf %lf %lf %lf %lf %lf %lf %lf\n",bkgd[i].jet1,bkgd[i].jet2,$

    i+=1;
  }

  //Minimizing the Chi squared values
  //Chi squared is defined by (observed-expected)^2/expected
  double chi2=0;
  double nObserved;
  double sigma;
  for (i=0;i<50;i++){
    if (hist1.h_array[i]!=0){
      chi2+=(hist1.h_array[i]-hist2.h_array[i]*.5+hist3.h_array[i]*.5)*(hist1.h$
       }
  }
  printf("Chi^2 Value assuming a 50/50 mix: %lf\n",chi2);
  double fS,fSmin;
  double chi2min=chi2;
  for (fS=0.0;fS<=1.0;fS+=.0001){
    chi2=0;
    for (i=0;i<50;i++){
      if (hist1.h_array[i]!=0){
        chi2+=(hist1.h_array[i]-hist2.h_array[i]*fS+hist3.h_array[i]*(1-fS))*(h$
      }
    }
    if (chi2min>chi2) {
      fSmin=fS;
      chi2min=chi2;
    }
  }
  printf("At fs of %lf and fb %lf a minimum chi^2 value of %lf was found\n",fSm$
  //h1plot(&hist1,"mjz5zf_data.pdf");
  //h1plot(&hist2,"mjz5zf_SigShape.pdf");
  //h1plot(&hist3,"mjz5zf_BkgShape.pdf");
  h1plot(&hist1,"");
  h1plot(&hist2,"");
  h1plot(&hist3,"");
  fclose(inputdat);
  fclose(inputsign);
  fclose(inputbkg);
  return(0);
}
  

    

