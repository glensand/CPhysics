//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"



class cInterpltn
{
public:
cInterpltn();
~cInterpltn();

       // Points
bool BGetPoints(double **PtsLoc, int NNLoc, bool BPtsArStorWayLoc, double hloc);
bool GetBPtsGot();
unsigned int GetNumPoints() {return NN;}
double DGetPtsX(int xind);
double DGetPtsY(int yind);
bool GetBXRngEql() {return BXRngEql;}
       // Common
bool BDelIntrVars();
double DDyAndDqMax;
       // Newton polynoms
bool GetBPrepNewton() {return BPrepNewton;}
bool BPrepIntrNewton();
double DIntrNewton(double x);
       // Lagrang polynoms
bool GetBPrepLagrang() {return BPrepLagrang;}
bool BPrepIntrLagrang();
double DIntrLagrang(double x);
       // Splines
bool GetBPrepSplines() {return BPrepSplines;}
bool BPrepIntrSplines(int NLoc, char *ChExprLoc);
double DIntrSplines(double x, bool BInclNewton);
       // Any option (analizing)
double DIntegral(double a, double b, unsigned int UINRange);
double DYMax(double a, double b, unsigned int UINRange);
double DYMin(double a, double b, unsigned int UINRange);
double DXYMax();
double DXYMin();
      // Errors, warnings.
char *GetChWarErMessage() {return ChWarErMessage;}
unsigned int GetICodWarEr() {return ICodWarEr;}

private:
       // Points
double **Pts;
unsigned int NN;      // NN  - number of points
bool BPtsArStorWay;
bool BDelPts();
bool BXRngEql;
bool BTestXRngEql();
double dxhalf;
       // Common
unsigned int N;              // N   - pow of polyn
double *DXRngIntrPart;
bool BPrepPolynSeg;
unsigned int NNN;   // NNN - number of segments
unsigned int ExprPartHelp[4];
bool PrepIntrNewtonCom(int NLoc);
double DIntrNewtonCom(double x);
bool BDivideOnSegm(int NLoc); // Universal prepare interpolation function (dividing on segments)
double DIntrLagrangCom(double x, int i, int k);
bool BDividedOnSegm;
bool BDatReadyNewton;
bool BXConvrg(double x, unsigned int UIBegIndLoc, unsigned int UIEndIndLoc);
       // Newton polynoms
bool BPrepNewton;
double h, hobr;
double **DDifNFor; double **DDifNRev;
int *UIBegInd, *UIEndInd;
double DDyAndDq;          // important var, watch on increasing dx (error)
       // Lagrang polynoms
double DIntrLagrang(double x, int i, int k);
bool BPrepLagrang;
       // Splines only
char *ChExpr;
bool BNewtonSplReady;
bool BPrepSplines;
int ICodFun;
      // Errors, warnings.
char ChWarErMessage[255];
int ICodWarEr;
bool BWriteChWarEr(char *ChWarErMessageLoc);
};




cInterpltn :: cInterpltn():
DDyAndDqMax(10000000)
{
       // Points
//Pts[0]=NULL; Pts[1]=NULL;
Pts=NULL;
NN=0;
BPtsArStorWay=true;
BXRngEql=false;
dxhalf=0;



N=0;
DXRngIntrPart=0;
BPrepPolynSeg=0;
NNN=0;   // NNN - number of segments
ExprPartHelp[0]=0; ExprPartHelp[1]=0; ExprPartHelp[2]=0; ExprPartHelp[3]=0;
BDatReadyNewton=0;
BDividedOnSegm=false;
       // Newton polynoms
BPrepNewton=0;
h=1, hobr=1;
DDifNFor=0; DDifNRev=0;
UIBegInd=0; UIEndInd=0;
       // Lagrang polynoms
BPrepLagrang=0;
char ChExpr=0;
      // Splines.
BPrepSplines=0;
BNewtonSplReady=0;
ICodFun=0;
      // Errors, warnings.
ICodWarEr=0;
  for (int i=0; i < 200; i++)
  {ChWarErMessage[i]=' ';}

}


cInterpltn :: ~cInterpltn()
{
BDelPts();
}



                               // Point getting
                               // if (hloc != 0)   PtsX(PtsLoc[0][k])  are calc here:  PtsX(PtsLoc[0][k]=PtsX(PtsLoc[0][0]+k*h.
                               // PtsX(PtsLoc[0][0] should be get, it's first pt
                               // BPtsArStorWayLoc
                               // if (BPtsArStorWayLoc == true) we get new memory
                               // else we must get pointer, store data must manage function
bool cInterpltn:: BGetPoints(double **PtsLoc, int NNLoc, bool BPtsArStorWayLoc, double hloc=0)
{
  if (NNLoc < 2)
  {
  ICodWarEr=2;
  char cherror[]="Error! Counts of points is less than 2!"; BWriteChWarEr(cherror); return false;
  }
  if (NNLoc > 10000000)
  {
  ICodWarEr=2;
  char cherror[]="Counts of points is more than 10000000!"; BWriteChWarEr(cherror); return false;
  }

BDelPts();
NN=NNLoc;
BPtsArStorWay=BPtsArStorWayLoc;
       // Test of increasing
  for (unsigned int i=1; i < NN; i++)
  {
    if (PtsLoc[0][i] < PtsLoc[0][i-1])
    {BPtsArStorWay=true; break;}
  }

  if (BPtsArStorWay == true)
  {
  Pts=new double*[2];
  Pts[0]=new double[NN];
  Pts[1]=new double[NN];
    if (hloc != 0)
    {
    Pts[0][0]=PtsLoc[0][0]; Pts[1][0]=PtsLoc[1][0];
      for (unsigned int i=1; i < NN; i++)
      {Pts[0][i]=Pts[0][i-1]+hloc; Pts[1][i]=PtsLoc[1][i];}
    }
    else
    {
      for (unsigned int j=0; j < NN; j++)
      {Pts[0][j]=PtsLoc[0][j]; Pts[1][j]=PtsLoc[1][j];}
    }
  double temp=0;
    for (unsigned int i=1; i < NN; i++)
    {
      if (PtsLoc[0][i] < PtsLoc[0][i-1])
      {
        for (unsigned int j=0; j < i; j++)
        {
          if (PtsLoc[0][j] > PtsLoc[0][i])
          {
          temp=PtsLoc[0][j]; PtsLoc[0][j]=PtsLoc[0][i];PtsLoc[0][i]=temp;
          temp=PtsLoc[1][j]; PtsLoc[1][j]=PtsLoc[1][i];PtsLoc[1][i]=temp;
          }
        }
      }
    }
  }
  else
  {
    if (hloc != 0)
    {
      for (unsigned int i=1; i < NN; i++)
      {PtsLoc[0][i]=PtsLoc[0][i-1]+hloc;}
    }
  Pts=PtsLoc;
  }
dxhalf=(Pts[0][NN-1]-Pts[0][0])*0.5;
BTestXRngEql();
return true;
}



bool cInterpltn:: BDelPts()
{
  if (GetBPtsGot())
  {
  BDelIntrVars();
    if (BPtsArStorWay == true)
    {
      if (Pts != 0)
      {
        if (Pts[0] != 0) {delete[] Pts[0]; Pts[0]=NULL;}
        if (Pts[1] != 0) {delete[] Pts[1]; Pts[1]=NULL;}
      delete[] Pts;
      Pts=NULL;
      }
    }
  NN=0;
  BPtsArStorWay=true;
  BXRngEql=false;
  dxhalf=0;
  }
return true;
}


double cInterpltn:: DGetPtsX(int xind)
{
  if (xind < 0) {xind=0;}
  if (GetBPtsGot())
  {
    if (xind < 100000) {return Pts[0][xind];} else {return 0;}
  } else {return 0;}
};

double cInterpltn:: DGetPtsY(int yind)
{
  if (yind < 0) {yind=0;}
  if (GetBPtsGot())
  {
    if (yind < NN) {return Pts[1][yind];} else {return 0;}
  } else {return 0;}
};

bool cInterpltn:: BTestXRngEql()
{
double temp=Pts[0][1]-Pts[0][0];
  for (unsigned int i=2; i < NN; i++)
  {
    if ((Pts[0][i]-Pts[0][i-1]-temp) > 0.00000001)
    {BXRngEql=false; return false;}
  }
BXRngEql=true;
return true;
}


bool cInterpltn :: GetBPtsGot()
{
  if (Pts)
  {
    if ((Pts[0]) && (Pts[1]))
    {return true;}
    else {return false;}
  }
  else
  {return false;}
}


bool cInterpltn :: BDelIntrVars()
{
       // Common
N=0;
DDyAndDq=0;
  if (DXRngIntrPart) {delete[] DXRngIntrPart; DXRngIntrPart=NULL;};
BPrepPolynSeg=0;
NNN=0;   // NNN - number of segments
ExprPartHelp[0]=0; ExprPartHelp[1]=0; ExprPartHelp[2]=0; ExprPartHelp[3]=NULL;
BDatReadyNewton=0;
BDividedOnSegm=false;
       // Newton polynoms
BPrepNewton=0;
h=1; hobr=1;
  if (DDifNFor)
  {
    for (int i=0; i < NNN; i++)
    {
      if (DDifNFor[i])
      {delete[] DDifNFor[i], DDifNRev[i]; DDifNFor[i]=0; DDifNRev[i]=0;}
    }
  delete[] DDifNFor, DDifNRev; DDifNFor=0; DDifNRev=0;
  }


  if (UIBegInd) {delete[] UIBegInd; UIBegInd=0;}
  if (UIEndInd) {delete[] UIEndInd; UIEndInd=0;}
       // Lagrang polynoms
BPrepLagrang=0;
char ChExpr=0;
      // Splines.
BPrepSplines=0;
ICodFun=0;
      // Errors, warnings.
ICodWarEr=0;
return true;
}

bool cInterpltn :: BXConvrg(double x, unsigned int UIBegIndLoc, unsigned int UIEndIndLoc)
{
dxhalf=(Pts[0][UIBegIndLoc]+Pts[0][UIEndIndLoc])*0.5;
  if
  (
        (  ( ((fabs(x-Pts[0][UIBegIndLoc]) > 20) && (N > 1 )) || ((fabs(x-Pts[0][UIBegIndLoc]) > 2) && (N > 5)) ||
             ((fabs(x-Pts[0][UIBegIndLoc]) > 1) &&  (N > 20)) ) && (x < dxhalf)        ) ||
        (  ( ((fabs(x-Pts[0][UIEndIndLoc]) > 20) && (N > 1 )) || ((fabs(x-Pts[0][UIEndIndLoc]) > 2) && (N > 5)) ||
             ((fabs(x-Pts[0][UIEndIndLoc]) > 1) &&  (N > 20)) ) && (x > dxhalf)    )
  )
  {return false;}
return true;
}


bool cInterpltn :: BDivideOnSegm(int NLoc)
{
  if (!GetBPtsGot())
  {return false;}
      //  The most difficult part: divide code area on more small segments
      //  ExprPartHelp[] - main var
      //  [2] and [4] shows numer of pts in range (index begin with 0)
      //  [3] number of pos 3d range,  [1] number of last pos 1d range
      //   1     2     3     4     5     6     7     8     9     10
      //   *     *     *     *     *     *     *     *     *     *
      //1) _ _ _ _ _ _ _ _ _ _
      //2)                                     _ _ _ _ _ _ _ _ _ _
      //3)                   _ _ _ _ _ _ _ _ _ _
      //3)                    ..... ..... .....
      // 1) ExprPartHelp[0]=3 1) ExprPartHelp[1]=4 1) ExprPartHelp[2]=6 1) ExprPartHelp[3]=4
BDelIntrVars();
  if (N+1 > NN)
  {
  ICodWarEr=1; char cherror[]="Warning! Power of polynom was decreased!"; BWriteChWarEr(cherror);
  N=NN-1;
  }


  if ((NN < 2) || (NLoc < 1 ))
  {
  // error!!
  ICodWarEr=2;
  char cherror[]="Error! Counts of number less than 2!"; BWriteChWarEr(cherror); return false;
  }
  else
  {
  N=NLoc;
  unsigned int N2=N+1;
    if ((N+1)%2 == 1)  {N2=((N+1)+1)/2;} else {N2=(N+1)/2;}

    if (NN-(N+1) > 0)
    {
    ExprPartHelp[0]=(N2+1)-1;
      if (NN-(N+1) > 1)
      {
        if ((N+1)%2 == 0)
        {ExprPartHelp[3]=ExprPartHelp[0]+1;}           // even case N+1
        else {ExprPartHelp[3]=(ExprPartHelp[0]+1)-1;}  // odd  case N+1
      ExprPartHelp[2]=NN-ExprPartHelp[3];
      ExprPartHelp[1]=NN-ExprPartHelp[3]-(ExprPartHelp[0]+1)+2;
      }
      else
      {
      ExprPartHelp[3]=NN-ExprPartHelp[0]+1;
      ExprPartHelp[1]=0;
      ExprPartHelp[2]=ExprPartHelp[0];
      }
    }
    else
    {ExprPartHelp[0]=NN-1; ExprPartHelp[1]=0; ExprPartHelp[2]=0; ExprPartHelp[3]=0;}
  }

NNN=1;    // numeric of interpolations
  if (ExprPartHelp[3] > 1)
  {
  NNN+=1;
    if (ExprPartHelp[1] > 1)
    {NNN+=ExprPartHelp[1]-1;}
  }

      // Creating of boundary X-points.
      //   1     2     3     4     5     6     7     8     9     10
      //   *     *     *     *     *     *     *     *     *     *
      //1) _ _ _ _ _ _ _ _ _ _
      //2)                                     _ _ _ _ _ _ _ _ _ _
      //3)                   _ _ _ _ _ _ _ _ _ _
      //3)                    ..... ..... .....
      //                     *     *     *     *
      //                     0     1     2     3(=NNN-2) boundary X-points
      //  Put its 4 X-points to XRngIntrPart

  if (NNN == 1) {DXRngIntrPart=new double[NNN];}
  else {DXRngIntrPart=new double[NNN-1];}
DXRngIntrPart[0]=Pts[0][ExprPartHelp[0]];
  if (ExprPartHelp[1] > 1)
  {
    for (unsigned int i=1; i < NNN-1; i++)
    {DXRngIntrPart[i]=Pts[0][ExprPartHelp[0]+i];}
  }

BDividedOnSegm=true;
return true;
}

                                       // Interpolation Newton polynoms
bool cInterpltn:: PrepIntrNewtonCom(int NLoc)
{
  if (!BDividedOnSegm)
  {return false;}

  if (!BTestXRngEql())
  {return false;}
// N   - pow of polyn
// NN  - number of points
// NNN - number of steps
DDyAndDq=0;    // important var, watch on increasing dx (error)

DDifNFor=new double*[NNN]; DDifNRev=new double*[NNN];
UIBegInd=new  int[NNN]; UIEndInd=new  int[NNN];

  for (unsigned int ipart=0; ipart < NNN; ipart++)
  {
    if (ipart == 0)
    {UIBegInd[0]=0; UIEndInd[0]=N;}
    else
    {
      if (ipart == NNN-1)
      {
      UIBegInd[ipart]=NN-(N+1); UIEndInd[ipart]=NN-1;
      }
      else
      {UIBegInd[ipart]=ipart; UIEndInd[ipart]=ipart+N;}
    }

  DDifNFor[ipart]=new double[N+1]; DDifNRev[ipart]=new double[N+1];

  double DHelp1For=0.0, DHelp1Rev=0.0;
  DDifNFor[ipart][0]=Pts[1][UIBegInd[ipart]]; DDifNRev[ipart][0]=Pts[1][N-UIBegInd[ipart]];
  h=(Pts[0][NN-1]-Pts[0][0])/(NN*1.0-1.0); hobr=1.0/h;
  double fctrl=1.0;

    for (unsigned int i=1; i <= N; i++)
    {
    DDifNFor[ipart][i]=Pts[1][UIBegInd[ipart]+i]; DDifNRev[ipart][i]=Pts[1][N+UIBegInd[ipart]-i];
    }
  DHelp1For=DDifNFor[ipart][0]; DHelp1Rev=DDifNRev[ipart][0];
  double DHelpFor2=1.0;
    for (unsigned int i=1; i <= N; i++)
    {
      for (unsigned int j=N; j > i-1; j--)
      {
      DDifNFor[ipart][j]=DDifNFor[ipart][j]-DDifNFor[ipart][j-1];
      }
    DDifNFor[ipart][i-1]=DHelp1For; DDifNRev[ipart][i-1]=DHelp1Rev;

      if ((fabs(DDifNFor[ipart][i-1]) > DDyAndDqMax)  || (fabs(DDifNRev[ipart][i-1]) > DDyAndDqMax))           // Test of convergence!
      {ICodWarEr=2; char cherror[]="Error! No convergence!"; BWriteChWarEr(cherror); return false;}

    DHelp1For=DDifNFor[ipart][i]/fctrl ;  DHelp1Rev=DDifNFor[ipart][N]/fctrl;
    fctrl*=(DHelpFor2+1.0);
    DHelpFor2+=1.0;
    }
  DDifNFor[ipart][N]=DHelp1For; DDifNRev[ipart][N]=DHelp1Rev;
    if ((DDifNRev[ipart][N] > DDyAndDqMax) || (DDifNFor[ipart][N] > DDyAndDqMax))        // Test of convergence!
    { ICodWarEr=2; char cherror[]="Error! No convergence!"; BWriteChWarEr(cherror); return false;}
  }

BDatReadyNewton=true;
DDyAndDq=fabs(DIntrNewtonCom((Pts[0][0]+Pts[0][1])*0.5));    // Test of convergence!
double DDyAndDqTemp=DDyAndDq;
  for (unsigned int i=1; i < NN-1; i++)
  {
  DDyAndDqTemp=fabs(DIntrNewtonCom((Pts[0][i+1]+Pts[0][i])*0.5));
    if (fabs(DDyAndDqTemp-DDyAndDq) > DDyAndDqMax)
    {ICodWarEr=2; BDatReadyNewton=false; char cherror[]="Error! Not convergence!"; BWriteChWarEr(cherror); return false;}
  DDyAndDq=DDyAndDqTemp;
  }
DDyAndDq=fabs(DIntrNewtonCom((Pts[0][0]+Pts[0][NN-1])*0.5));
BDatReadyNewton=true;
return true;
}


double cInterpltn :: DIntrNewtonCom(double x)
{

    if (BDatReadyNewton)
    {
    unsigned int ipart=NNN-1;
      for (unsigned int i=0; i < NNN-1; i++)
      { if (x <= DXRngIntrPart[i]) {ipart=i; break;}  }
       // Convergence test
      if (!BXConvrg(x, UIBegInd[ipart], UIEndInd[ipart]))
      {ICodWarEr=2; char cherror[]="Error! x is too far from x0!"; BWriteChWarEr(cherror); return 0;}
    dxhalf=(Pts[0][UIBegInd[ipart]]+Pts[0][UIEndInd[ipart]])*0.5;
    double Answ;
    double q=0, q0=0;
      if (x < dxhalf)
      {
      q=(x-Pts[0][UIBegInd[ipart]])*hobr; q0=q; Answ=DDifNFor[ipart][0];
        for (int i=1; i <= N; i++)
        {Answ+=q*DDifNFor[ipart][i]; q*=q0-i;}
      }
      else
      {
      q=(x-Pts[0][UIEndInd[ipart]])*hobr; q0=q; Answ=DDifNRev[ipart][0];
        for (int i=1; i <= N; i++)
        {Answ+=q*DDifNRev[ipart][i]; q*=q0+i;}
      }
                   // Convergence test
      if ((fabs(Answ-DDyAndDq) > DDyAndDqMax) || (fabs(q) > DDyAndDqMax*10000))
      {ICodWarEr=2; char cherror[]="Error! No convergence!"; BWriteChWarEr(cherror); return 0;}
    DDyAndDq=Answ;

    return Answ;
    }

ICodWarEr=2;
return 0;
}


bool  cInterpltn :: BPrepIntrNewton()
{
  if (GetBPrepNewton()) {return true;}

  if (!GetBPtsGot())
  {ICodWarEr=2; char cherror[]="Error! Points are not got!"; BWriteChWarEr(cherror); return false;}

BDelIntrVars();

  if (!BDivideOnSegm(NN-1))
  {ICodWarEr=2; char cherror[]="Error! Dividing on segments is unable!"; BWriteChWarEr(cherror); return false;}
BPrepLagrang=true;

    if (!PrepIntrNewtonCom(NN-1))
    {ICodWarEr=2; char cherror[]="Error! Newton polynom interpolation is unable!"; BWriteChWarEr(cherror); return false;}
BPrepNewton=true;
return true;
}


double  cInterpltn :: DIntrNewton(double x)
{
  if (ICodWarEr == 2)
  {return 0;}

  if (GetBPrepNewton()) {return DIntrNewtonCom(x);}
  else
  {
    if (BPrepIntrNewton()) {return DIntrNewtonCom(x);}
    else
    {ICodWarEr=2; char cherror[]="Error! Newton polynom interpolation is unable!"; BWriteChWarEr(cherror); return 0;}
  }
}

       // Lagrang polynoms
bool cInterpltn :: BPrepIntrLagrang()
{
  if ((GetBPrepLagrang())  || (GetBPrepNewton())) {return true;}

  if (!GetBPtsGot())
  {ICodWarEr=2; char cherror[]="Error! Points are not got!"; BWriteChWarEr(cherror); return false;}

BDelIntrVars();

  if (!BDivideOnSegm(NN-1))
  {ICodWarEr=2; char cherror[]="Error! Dividing on segments is unable!"; BWriteChWarEr(cherror); return false;}
BPrepLagrang=true;
return true;
}


double cInterpltn :: DIntrLagrang(double x)
{
  if (ICodWarEr == 2) {return 0;}

  if (GetBPrepLagrang()) { return DIntrLagrangCom(x, 0, N);}
  else
  {
    if (BPrepIntrLagrang()) {return DIntrLagrangCom(x, 0, N);}
    else
    {ICodWarEr=2; char cherror[]="Error! Lagrang polynom interpolation is uable!"; BWriteChWarEr(cherror); return 0;}
  }
}


double cInterpltn :: DIntrLagrangCom(double x, int i, int k)
{
unsigned int ipart=NNN-1;
  for (unsigned int ii=0; ii < NNN-1; ii++)
  { if (x <= DXRngIntrPart[ii]) {ipart=ii; break;}  }

  if (i == k) {return Pts[1][ipart+i];}
double DLagr1=DIntrLagrangCom(x, i, k-1), DLagr2=DIntrLagrangCom(x, i+1, k), DLagr3;
DLagr3=((Pts[0][ipart+k]-x)*DLagr1+(x-Pts[0][ipart+i])*DLagr2)/(Pts[0][ipart+k]-Pts[0][ipart+i]);
       // Convergence test
  if ((fabs(DLagr3-DLagr1) > DDyAndDqMax) || (fabs(DLagr3-DLagr2) > DDyAndDqMax))
  {ICodWarEr=2; char cherror[]="Error! Lagrang polynom interpolation is uable!"; BWriteChWarEr(cherror); return 0;}
  else
  {return DLagr3;}
return 0;
}







bool cInterpltn:: BPrepIntrSplines(int NLoc, char *ChExprLoc)
{
BDelIntrVars();

  if (!GetBPtsGot())
  {ICodWarEr=2; char cherror[]="Error! Points are not got!"; BWriteChWarEr(cherror); return false;}

  if (NLoc != 0)
  {
    if (!BDivideOnSegm(NN-1))
    {ICodWarEr=2; char cherror[]="Error! Dividing on segments is unable!"; BWriteChWarEr(cherror); return false;}

  ICodFun=NLoc;
    if (GetBXRngEql())
    {
      if (PrepIntrNewtonCom(NLoc)) {BPrepSplines=true; BNewtonSplReady=true; return true;}
      else {BNewtonSplReady=false; return true;}
    }
    else
    {BPrepSplines=true; return true;;}
  }
  else
  {
    if (ChExprLoc)
    {
    //Any function interpoltn segment interpoltn
    }
  }
return true;
}


double cInterpltn:: DIntrSplines(double x, bool BInclNewton=true)
{
  if (ICodWarEr == 2) {return 0;}

  if (!GetBPrepSplines())
  { ICodWarEr=2; char cherror[]="Error! Spline interpolation is not prepared!"; BWriteChWarEr(cherror); return false;}

double DAnsw=0;
  if (ICodFun > 0)
  {
    if ((BNewtonSplReady) && (BInclNewton))
    {
    DAnsw=DIntrNewtonCom(x);
      if (ICodWarEr == 2)
      {
      ICodWarEr=0; DAnsw=DIntrLagrangCom(x, 0, N);
        if (ICodWarEr == 2) {return 0;}
      }
      else {return DAnsw;}
    }
  DAnsw=DIntrLagrangCom(x, 0, N);
    if (ICodWarEr == 2) {return 0;}
    else {return DAnsw;}
  }
  else
  {
  //Any function
  return x;
  }

return 0;
}


double cInterpltn :: DYMax(double a, double b, unsigned int UINRange=200)
{
  if (GetBPrepSplines())
  {
  double DAnsw=DIntrSplines(a, false), x=a+h, temp=0;
  double hloc=(b-a)/((double) UINRange);
    for (unsigned int i=0; i < UINRange; i++)
    {
    temp=DIntrSplines(x, false);
      if (temp > DAnsw) {DAnsw=temp;}
      if (ICodWarEr == 2) {return 0;}
    x+=hloc;
    }
  return DAnsw;
  }
}

double cInterpltn :: DYMin(double a, double b, unsigned int UINRange=200)
{
  if (GetBPrepSplines())
  {
  double DAnsw=DIntrSplines(a, false), x=a+h, temp=0;
  double hloc=(b-a)/((double) UINRange);
    for (unsigned int i=0; i < UINRange; i++)
    {
    temp=DIntrSplines(x, false);
      if (temp < DAnsw) {DAnsw=temp;}
      if (ICodWarEr == 2) {return 0;}
    x+=hloc;
    }
  return DAnsw;
  }
}



double cInterpltn :: DIntegral(double a, double b, unsigned int UINRange=200)
{
  if (GetBPrepSplines())
  {
  double DAnsw=0, x=a;
  double hloc=(b-a)/((double) UINRange);
    for (unsigned int i=0; i < UINRange; i++)
    {
    DAnsw+=0.5*(DIntrSplines(x, false)+DIntrSplines(x+hloc, false))*hloc; x+=hloc;
      if (ICodWarEr == 2) {return 0;}
    }
  return DAnsw;
  /*
  double *xpowi=new double[N+1];
  xpow[0]=1;
    for (unsigned int i=1; i <= N; i++)
    {xpow[i]=xpow[i-1]*x;}
  double *t=new double[N];
  double DAnsw=0, k=0, DAnsw1, id=1;

    for (unsigned int n=0; n <= N; n++)
    {
      for (unsigned int j=0; j < N; j++)
      {  if (j != n) {t[j]=Pt[0][n];} }
    // вычисление k

      for (unsigned int i=0; i <= N; i++)
      {
      DAnsw1
      DAnsw1*=xpow[N-i];
        if (i%2 == 1) {DAnsw1*=-1;}
      }
    DAnsw+=DAnsw1*k;  DAnsw1=0;
    }
  delete[] xpowi, t;
  */
  }
return 0;
}



bool cInterpltn :: BWriteChWarEr(char *ChWarErMessageLoc)
{
  for (int i=0; i < 255; i++)
  {
  ChWarErMessage[i]=ChWarErMessageLoc[i];
    if (ChWarErMessageLoc[i] == '\0') {break;}
  }
return true;
}




TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
unsigned int N=6;

StringGrid1->ColCount=StrToInt(Edit1->Text);
StringGrid1->Cells[0][0]=0;
StringGrid1->Cells[1][0]=1;
StringGrid1->Cells[2][0]=2;
StringGrid1->Cells[3][0]=3;
StringGrid1->Cells[4][0]=4;
StringGrid1->Cells[5][0]=5;


StringGrid1->Cells[0][1]=2;
StringGrid1->Cells[1][1]=6;
StringGrid1->Cells[2][1]=7;
StringGrid1->Cells[3][1]=5;
StringGrid1->Cells[4][1]=3;
StringGrid1->Cells[5][1]=6;

  for (int i=0; i < N; i++)
  {Chart1->Series[0]->AddXY(StrToFloat(StringGrid1->Cells[i][0]), StrToFloat(StringGrid1->Cells[i][1]));}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
unsigned int N=6;
StringGrid1->ColCount=StrToInt(Edit1->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
char *mymessage;
ShowMessage("Hellow!");

cInterpltn *oInterpltn1=new cInterpltn();


unsigned int NNb=6;

double **Pts=new double*[2];
Pts[0]=new double[NNb];
Pts[1]=new double[NNb];

  for (int j=0; j < NNb; j++)
  {
  Pts[0][j]=StrToFloat(StringGrid1->Cells[j][0]);
  Pts[1][j]=StrToFloat(StringGrid1->Cells[j][1]);
  }

oInterpltn1->BGetPoints(Pts, 6, false, 1);

  if (oInterpltn1->BPrepIntrNewton())
  {
    for (double x=0; x <= 6; x+=0.2)
    {
    Chart1->Series[1]->AddXY(x, oInterpltn1->DIntrNewton(x));
      if (oInterpltn1->GetICodWarEr() == 2) {mymessage=oInterpltn1->GetChWarErMessage(); ShowMessage(mymessage); break;}
    }
  }

delete oInterpltn1;
delete[] Pts[1], Pts[0],Pts;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
char *mymessage;
ShowMessage("Hellow!");

cInterpltn *oInterpltn1=new cInterpltn();


unsigned int NNb=6;

double **Pts=new double*[2];
Pts[0]=new double[NNb];
Pts[1]=new double[NNb];

  for (int j=0; j < NNb; j++)
  {
  Pts[0][j]=StrToFloat(StringGrid1->Cells[j][0]);
  Pts[1][j]=StrToFloat(StringGrid1->Cells[j][1]);
  }

oInterpltn1->BGetPoints(Pts, 6, false, 1);

  if (oInterpltn1->BPrepIntrNewton())
  {
    for (double x=0; x <= 6; x+=0.2)
    {
    Chart1->Series[1]->AddXY(x, oInterpltn1->DIntrNewton(x));
      if (oInterpltn1->GetICodWarEr() == 2) {mymessage=oInterpltn1->GetChWarErMessage(); ShowMessage(mymessage); break;}
    }
  }

delete oInterpltn1;
delete[] Pts[1], Pts[0],Pts;

}
//---------------------------------------------------------------------------

