#include <iostream>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

double FhnminusSatuFun(double h, double H, double Q, double b, double h0){
    double FhnminusSatu=0.00;
    #pragma omp parallel shared(FhnminusSatu)
    {
        #pragma omp critical
        FhnminusSatu = pow(h,3)+((H-((pow(Q,2))/(2*9.80665*(pow(b,2))*(pow(h0,2))))-h0)*(pow(h,2)))+((pow(Q,2))/(2*9.80665*(pow(b,2))));
    }
    return FhnminusSatu;
}
double FhnFun(double h, double H, double Q, double b, double h0){
    double Fhn=0.00;
    #pragma omp parallel shared(Fhn)
    {
        #pragma omp critical
        Fhn=pow(h,3)+((H-((pow(Q,2))/(2*9.80665*(pow(b,2))*(pow(h0,2))))-h0)*(pow(h,2)))+((pow(Q,2))/(2*9.80665*(pow(b,2))));
    }
    return Fhn;

}
double Secant(double hn, double hnminusSatu, double Fhn, double FhnminusSatu){
    double Secant=0.00;
    #pragma omp parallel shared(Secant)
    {
        #pragma omp critical
        Secant=hn-((Fhn*(hnminusSatu-hn))/(FhnminusSatu-Fhn));
    }
    return Secant;
}
double Error(double hnBefore, double hnNow){
    double Error=0.00;
    #pragma omp parallel shared(Error)
    {
        #pragma omp critical
        Error=((fabs(hnNow-hnBefore))/(fabs(hnNow)))*100;
    }
    return Error;
}

int main()
{
    int iteration=0;
    double hnBefore=0;
    double hnNow=0;
    double eTolerance=0.00000000000000001;
    double hnminusSatu=0;
    double hn=6000;
    double error=0;
    double FhnminusSatu=FhnminusSatuFun(hnminusSatu,750,1200,1800,6000);
    double Fhn=FhnFun(hn,750,1200,1800,6000);

    double HnplusSatu=Secant(hn, hnminusSatu, Fhn, FhnminusSatu);
    error=Error(0,HnplusSatu);
    cout<<"Iteration = "<<iteration<<endl;
    cout<<"hnminusSatu = "<<hnminusSatu<<endl;
    cout<<"hn = "<<hn<<endl;
    cout<<"FhnminusSatu = "<<FhnminusSatu<<endl;
    cout<<"Fhn = "<<Fhn<<endl;
    cout<<"HnplusSatu = "<<HnplusSatu<<endl;
    cout<<"Error = " <<error<<"%"<<endl;
    cout<<endl;
        hnminusSatu=hn;
        hn=HnplusSatu;

    while(error>=eTolerance){
        hnBefore=HnplusSatu;
        FhnminusSatu=FhnminusSatuFun(hnminusSatu,750,1200,1800,6000);
        Fhn=FhnFun(hn,750,1200,1800,6000);
        HnplusSatu=Secant(hn, hnminusSatu, Fhn, FhnminusSatu);
        iteration++;
        hnNow=HnplusSatu;
        error=Error(hnBefore, hnNow);

        cout<<endl;
        cout<<"Iteration = "<<iteration<<endl;
        cout<<"hnminusSatu = "<<hnminusSatu<<endl;
        cout<<"hn = "<<hn<<endl;
        cout<<"FhnminusSatu = "<<FhnminusSatu<<endl;
        cout<<"Fhn = "<<Fhn<<endl;
        cout<<"HnplusSatu = "<<HnplusSatu<<endl;
        cout<<"Error = " <<error<<"%"<<endl;
        cout<<endl;
        hnminusSatu=hn;
        hn=HnplusSatu;
    }
    iteration=0;
    hnBefore=0;
    hnNow=0;
    eTolerance=0.0000000000000000000001;
    hnminusSatu=0;
    hn=HnplusSatu;
    error=0;
    FhnminusSatu=FhnminusSatuFun(hnminusSatu,75,120,180,600);
    Fhn=FhnFun(hn,75,120,180,600);

    HnplusSatu=Secant(hn, hnminusSatu, Fhn, FhnminusSatu);
    error=Error(0,HnplusSatu);
    cout<<"Iteration = "<<iteration<<endl;
    cout<<"hnminusSatu = "<<hnminusSatu<<endl;
    cout<<"hn = "<<hn<<endl;
    cout<<"FhnminusSatu = "<<FhnminusSatu<<endl;
    cout<<"Fhn = "<<Fhn<<endl;
    cout<<"HnplusSatu = "<<HnplusSatu<<endl;
    cout<<"Error = " <<error<<"%"<<endl;
    cout<<endl;
        hnminusSatu=hn;
        hn=HnplusSatu;
    while(error>=eTolerance){
        hnBefore=HnplusSatu;
        FhnminusSatu=FhnminusSatuFun(hnminusSatu,75,120,180,600);
        Fhn=FhnFun(hn,75,120,180,600);
        HnplusSatu=Secant(hn, hnminusSatu, Fhn, FhnminusSatu);
        iteration++;
        hnNow=HnplusSatu;
        error=Error(hnBefore, hnNow);

        cout<<endl;
        cout<<"Iteration = "<<iteration<<endl;
        cout<<"hnminusSatu = "<<hnminusSatu<<endl;
        cout<<"hn = "<<hn<<endl;
        cout<<"FhnminusSatu = "<<FhnminusSatu<<endl;
        cout<<"Fhn = "<<Fhn<<endl;
        cout<<"HnplusSatu = "<<HnplusSatu<<endl;
        cout<<"Error = " <<error<<"%"<<endl;
        cout<<endl;
        hnminusSatu=hn;
        hn=HnplusSatu;
    }
    return 0;
}
