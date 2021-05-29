#include <iostream>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

double FhnFun(double h, double H, double Q, double b, double h0){
        double Fhn = 0.00;
        double y,z;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                 y = ((H-((pow(Q,2))/(2*9.80665*(pow(b,2))*(pow(h0,2))))-h0)*(pow(h,2)));
            }
            #pragma omp section
            {
                 z = ((pow(Q,2))/(2*9.80665*(pow(b,2))));
            }
        }
        Fhn = pow(h,3)+y+z;
    return Fhn;
}

double FhnDerivativeFun(double h, double H, double Q, double b, double h0){
    double FhnDerivative = 0.00;
    double y,z;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                 y = ((H-((pow(Q,2))/(2*9.80665*(pow(b,2))*(pow(h0,2))))-h0)*(2*h));
            }
            #pragma omp section
            {
                 z = ((pow(Q,2))/(2*9.80665*(pow(b,2))));
            }
        }
       FhnDerivative = (3*pow(h,2))+y+z;
    return FhnDerivative;
}

double NR(double hn, double Fhn, double FhnDerivative){
    double NR = 0.00;
        NR = hn-(Fhn/FhnDerivative);
    return NR;
}
double Error(double hnBefore, double hnNow){
    double Error = 0.00;
        Error = ((fabs(hnNow-hnBefore))/(fabs(hnNow)))*100;
    return Error;
}
int main()
{

    int iteration = 0;
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
        #pragma omp parallel num_threads(6)
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                Fhn=FhnFun(hn,0.075,1.2,1.8,0.6);
            }
            #pragma omp section
            {
                FhnDerivative=FhnDerivativeFun(hn,0.075,1.2,1.8,0.6);

            }
        }
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
    Fhn=FhnFun(hn,0.0075,0.12,0.18,0.06);
    FhnDerivative=FhnDerivativeFun(hn,0.0075,0.12,0.18,0.06);
    HnplusSatu=NR(hn, Fhn,FhnDerivative);
    cout<<"Iteration = "<<iteration<<endl;
    cout<<"hn = "<<hn<<endl;
    cout<<"Fhn = "<<Fhn<<endl;
    cout<<"FhnDerivative = "<<FhnDerivative<<endl;
    cout<<"HnplusSatu = "<<HnplusSatu<<endl;
    hn=HnplusSatu;
    while(error>=eTolerance){
        hnBefore=hn;
        #pragma omp parallel num_threads(6)
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                Fhn=FhnFun(hn,0.0075,0.12,0.18,0.06);
            }
            #pragma omp section
            {
                FhnDerivative=FhnDerivativeFun(hn,0.0075,0.12,0.18,0.06);

            }
        }
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
