#include <iostream>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

double FhnFun(double h, double H, double Q, double b, double h0){
    double Fhn = 0.00;
    #pragma omp parallel shared(Fhn)
    {
        #pragma omp critical
        Fhn = pow(h,3)+((H-((pow(Q,2))/(2*9.80665*(pow(b,2))*(pow(h0,2))))-h0)*(pow(h,2)))+((pow(Q,2))/(2*9.80665*(pow(b,2))));
    }
    return Fhn;
}

double FhnDerivativeFun(double h, double H, double Q, double b, double h0){
    double FhnDerivative = 0.00;
    #pragma omp parallel shared(FhnDerivative)
    {
        #pragma omp critical
        FhnDerivative = (3*pow(h,2))+((H-((pow(Q,2))/(2*9.80665*(pow(b,2))*(pow(h0,2))))-h0)*(2*h))+((pow(Q,2))/(2*9.80665*(pow(b,2))));
    }
    return FhnDerivative;
}

double NR(double hn, double Fhn, double FhnDerivative){
    double NR = 0.00;
    #pragma omp parallel shared(NR)
    {
        #pragma omp critical
        NR = hn-(Fhn/FhnDerivative);
    }
    return NR;
}
double Error(double hnBefore, double hnNow){
    double Error = 0.00;
        #pragma omp parallel shared(Error)
    {
        #pragma omp critical
        Error = ((fabs(hnNow-hnBefore))/(fabs(hnNow)))*100;
    }
    return Error;
}
int main()
{
    int iteration =0;
    double hnBefore=0;
    double hnNow=0;
    double error=1000;
    double eTolerance=0.0000000000000000000001;
    double hn=6000;
    double Fhn=FhnFun(hn,750,1200,1800,6000);
    double FhnDerivative=FhnDerivativeFun(hn,750,1200,1800,6000);
    double HnplusSatu=NR(hn, Fhn,FhnDerivative);
    cout<<"Iteration = "<<iteration<<endl;
    cout<<"hn = "<<hn<<endl;
    cout<<"Fhn = "<<Fhn<<endl;
    cout<<"FhnDerivative = "<<FhnDerivative<<endl;
    cout<<"HnplusSatu = "<<HnplusSatu<<endl;
    hn=HnplusSatu;
    while(error>=eTolerance){
        hnBefore=hn;
        double Fhn=FhnFun(hn,750,1200,1800,6000);
        double FhnDerivative=FhnDerivativeFun(hn,750,1200,1800,6000);
        double HnplusSatu=NR(hn, Fhn,FhnDerivative);
        hnNow=HnplusSatu;
        error=Error(hnBefore,hnNow);
        iteration++;
        cout<<endl;
        cout<<"Iteration = "<<iteration<<endl;
        cout<<"hn = "<<hn<<endl;
        cout<<"Fhn = "<<Fhn<<endl;
        cout<<"FhnDerivative = "<<FhnDerivative<<endl;
        cout<<"HnplusSatu = "<<HnplusSatu<<endl;
        cout<<"Error = " <<error<<"%"<<endl;
        hn=HnplusSatu;
        hnBefore=hn;
    }

    iteration =0;
    hnBefore=0;
    hnNow=0;
    error=1000;
    eTolerance=0.0000000000000000000001;
    hn=HnplusSatu;
    Fhn=FhnFun(hn,75,120,180,600);
    FhnDerivative=FhnDerivativeFun(hn,75,120,180,600);
    HnplusSatu=NR(hn, Fhn,FhnDerivative);
    cout<<"Iteration = "<<iteration<<endl;
    cout<<"hn = "<<hn<<endl;
    cout<<"Fhn = "<<Fhn<<endl;
    cout<<"FhnDerivative = "<<FhnDerivative<<endl;
    cout<<"HnplusSatu = "<<HnplusSatu<<endl;
    hn=HnplusSatu;
    while(error>=eTolerance){
        hnBefore=hn;
        Fhn=FhnFun(hn,75,120,180,600);
        FhnDerivative=FhnDerivativeFun(hn,75,120,180,600);
        HnplusSatu=NR(hn, Fhn,FhnDerivative);
        hnNow=HnplusSatu;
        error=Error(hnBefore,hnNow);
        iteration++;
        cout<<endl;
        cout<<"Iteration = "<<iteration<<endl;
        cout<<"hn = "<<hn<<endl;
        cout<<"Fhn = "<<Fhn<<endl;
        cout<<"FhnDerivative = "<<FhnDerivative<<endl;
        cout<<"HnplusSatu = "<<HnplusSatu<<endl;
        cout<<"Error = " <<error<<"%"<<endl;
        hn=HnplusSatu;
        hnBefore=hn;
    }
    return 0;
}
