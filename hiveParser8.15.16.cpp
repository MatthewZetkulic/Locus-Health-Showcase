#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

struct info{
	int poscol;
	long int pos;
	int cov;
	int covcol;
	int maxcol;
	int finished;};

//updates int inputs with column # associated, returns position of maxcol
int headerGrab(FILE *inp, int *c, int *p){
	*p=0;
	*c=0;
	char line[500];
	fgets(line, 500, inp);
	char key1[]="pos";
	char key2[]="col1";
	char *str;
	int foundcov=0;
	int foundpos=0;

	str=strtok(line,",");
	while (foundcov==0 && foundpos==0){
		if (strcmp(str,key1)!=0 && foundpos==0){
		*p+=1;}
		else foundpos=1;
	
		if (strcmp(str,key2)!=0 && foundcov==0){
		*c+=1;}
		else foundcov=1;
		str=strtok(NULL,",");
	}
	if (*c>*p)
		return *c;
	else
		return *p;
}

int main(int argc, char **argv){
	int i,j,k;
	//setting up the output file
	FILE *output=fopen("output.csv","w+");
	fprintf(output,"pos,");
	
	for (i=0; i<argc-1; i++){
		fprintf(output,"%s,",argv[i+1]);
	}
	FILE **files = malloc(argc * sizeof(FILE *));
	if (files==NULL)
		return(1);
	
	//info for files
	struct info *infos= malloc(argc * sizeof(struct info ));
	if (infos==NULL)
		return(1);
	
	for (i=0; i<argc-1; i++){
		files[i]=fopen(argv[i+1],"r");
		if (files[i]==NULL){
			printf("Error!");
			return 1;
		}
	}
	
	for (i=0; i<argc-1; i++){
		infos[i].maxcol=headerGrab(files[i],&infos[i].covcol,&infos[i].poscol);
		infos[i].finished=0;
	}
	char line[50];
	char *str;
	//store first line of file
	for (i=0; i<argc-1; i++){
		fgets(line,50,files[i]);
		str=strtok(line,",");
		for (j=0;j<=infos[i].maxcol;j++){
			if (j==infos[i].covcol)
				infos[i].cov=atoi(str);
			if (j==infos[i].poscol)
				infos[i].pos=atoi(str);
			str=strtok(NULL,",");						
		}
	}

	int currLow,oldLow;
	long int currPos,oldPos;
	currLow=0;
	oldLow=0;
	//determine which file the next output is coming from
	for (i=0; i<argc-1;i++){
		if (infos[i].pos<infos[currLow].pos){
			currLow=i;
		}
	}
	fprintf(output,"\n%d,",infos[currLow].pos);

	oldPos=infos[currLow].pos;
	currPos=infos[currLow].pos;
	while (true){
		//setting up output
		if (infos[currLow].finished==0){
			if (currPos>oldPos){
				if (oldLow!=argc-1){
				for (i=oldLow;i<argc-2;i++){
					fprintf(output,",");}}
				fprintf(output,"\n%d,",infos[currLow].pos);
				for (i=0;i<currLow;i++)
					fprintf(output,",");
				fprintf(output,"%d",infos[currLow].cov);
			}
			else{
				for (i=oldLow;i<currLow;i++)
					fprintf(output,",");
				fprintf(output,"%d",infos[currLow].cov);}
			}
		oldLow=currLow;
		oldPos=currPos;

		if (fgets(line,500,files[currLow])){
		str=strtok(line,",");
		for (j=0;j<=infos[currLow].maxcol;j++){
			if (j==infos[currLow].covcol)
				infos[currLow].cov=atoi(str);
			if (j==infos[currLow].poscol)
				infos[currLow].pos=atoi(str);
			str=strtok(NULL,",");						
		}}//if done with file
		else {
			infos[currLow].pos=LONG_MAX;
			infos[currLow].finished=1;
		}

		for (i=0; i<argc-1;i++){
		if (infos[i].pos<infos[currLow].pos)
			currLow=i;
		if ((infos[i].pos==infos[currLow].pos)&&(i<currLow))
			currLow=i;
		}
		currPos=infos[currLow].pos;
		k=0;
		for (i=0;i<argc-1;i++){
			if (infos[currLow].finished==false) k=1;
		}
		if (k==0) break;}
	//finishing up the end of the file
	if (oldLow!=argc-2){
		for (i=oldLow;i<argc-1;i++){
			fprintf(output,",");}}

	for (i=0; i<argc-1; i++){
		fclose(files[i]);
	}
	free(files);
	free(infos);
	fclose(output);
	return 0;
	}

