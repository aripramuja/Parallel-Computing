#include <iostream>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
using namespace std;
double FhnFun(double h, double H, double Q, double b, double h0){
    return pow(h,3)+((H-((pow(Q,2))/(2*9.80665*(pow(b,2))*(pow(h0,2))))-h0)*(pow(h,2)))+((pow(Q,2))/(2*9.80665*(pow(b,2))));
}

double FhnDerivativeFun(double h, double H, double Q, double b, double h0){
    return (3*pow(h,2))+((H-((pow(Q,2))/(2*9.80665*(pow(b,2))*(pow(h0,2))))-h0)*(2*h))+((pow(Q,2))/(2*9.80665*(pow(b,2))));
}

double NR(double hn, double Fhn, double FhnDerivative){
    return hn-(Fhn/FhnDerivative);
}
double Error(double hnBefore, double hnNow){
    return ((fabs(hnNow-hnBefore))/(fabs(hnNow)))*100;
}
int main()
{
    int iteration =0;
    double hnBefore=0;
    double hnNow=0;
    double error=1000;
    double eTolerance=0.0000000000000000000001;
    double hn=0.6;
    double Fhn=FhnFun(hn,0.075,1.2,1.8,0.6);
    double FhnDerivative=FhnDerivativeFun(hn,0.075,1.2,1.8,0.6);
    double HnplusSatu=NR(hn, Fhn,FhnDerivative);
    cout<<"Iteration = "<<iteration<<endl;
    cout<<"hn = "<<hn<<endl;
    cout<<"Fhn = "<<Fhn<<endl;
    cout<<"FhnDerivative = "<<FhnDerivative<<endl;
    cout<<"HnplusSatu = "<<HnplusSatu<<endl;
    hn=HnplusSatu;
    while(error>=eTolerance){
        hnBefore=hn;
        double Fhn=FhnFun(hn,0.0075,0.12,0.18,0.06);
        double FhnDerivative=FhnDerivativeFun(hn,0.0075,0.12,0.18,0.06);
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
    Fhn=FhnFun(hn,0.075,1.2,1.8,0.6);
    FhnDerivative=FhnDerivativeFun(hn,0.075,1.2,1.8,0.6);
    HnplusSatu=NR(hn, Fhn,FhnDerivative);
    cout<<"Iteration = "<<iteration<<endl;
    cout<<"hn = "<<hn<<endl;
    cout<<"Fhn = "<<Fhn<<endl;
    cout<<"FhnDerivative = "<<FhnDerivative<<endl;
    cout<<"HnplusSatu = "<<HnplusSatu<<endl;
    hn=HnplusSatu;
    while(error>=eTolerance){
        hnBefore=hn;
        Fhn=FhnFun(hn,0.0075,0.12,0.18,0.06);
        FhnDerivative=FhnDerivativeFun(hn,0.0075,0.12,0.18,0.06);
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
