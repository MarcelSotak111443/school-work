#include <stdio.h>

double vypispozicie(double t,double h , double v ,int s);

int main() {
    double m,T,v0,H,g,vsoft,dt=0,df,A,de,h=0,v=0,a=0,s=0;
    double t,total;

    scanf("%lf",&m);
    scanf("%lf",&T);
    scanf("%lf",&v0);
    scanf("%lf",&H);
    scanf("%lf",&g);
    scanf("%lf",&vsoft);
    scanf("%lf",&dt);

    printf("m=%.3lf\n",m);
    printf("T=%.3lf\n",T);
    printf("v0=%.3lf\n",v0);
    printf("H=%.3lf\n",H);
    printf("g=%.3lf\n",g);
    printf("vsoft=%.3lf\n",vsoft);
    printf("dt=%.3lf\n",dt);
    h = H;
    A=T/m;
    df=((A - g)*H)/A;
    de=H - df;
    printf("df=%.3lf\n",df);

    while (h > 0){
        do {
            s = 0;
            vypispozicie(t,h,v,s);
            a = -g;
            h = h + (v * dt) + (a *dt *dt * 0.5);
            v = v +(a * dt);
            t=t + dt;
        }while (h > de );
        while(v < vsoft){
            s = 1;
            vypispozicie(t, h, v, s);
            a = A - g;
            h = h + (v * dt) + (a * dt * dt * 0.5);
            v = v + (a * dt);
            t = t + dt;
            total = total + dt;
        }
    }
    s= 0;
    printf("t=%.3lf h=%.3lf v=%.3lf\n",t,h,v);
    printf("total=%.3lf",total);

}
    double vypispozicie(double t,double h, double v ,int s){
    printf("t=%.3lf h=%.3lf v=%.3lf s=%d\n",t,h,v,s);
}
