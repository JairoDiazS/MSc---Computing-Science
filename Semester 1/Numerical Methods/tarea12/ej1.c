/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/****Tarea 12 Metodos de derivacion****/
/***********Metodos Numericos**********/
/**************12/11/2023**************/
/**************************************/
/**************************************/

#include "tarea12.c"

int main(){
    double x1[] = {1.2, 1.3, 1.4};
    double x2[] = {1.29, 1.3, 1.31};
    double fx1[] = {11.59006, 14.04276, 16.86187};
    double fx2[] = {13.78176, 14.04276, 14.30741};

    double df = 26.28170;
    double ddf = 36.59353;
    double df_fw1 = fw_diff(fx1[1], fx1[2], 0.1);
    double df_bw1 = bw_diff(fx1[0], fx1[1], 0.1);
    double df_ct1 = ct_diff(fx1[0], fx1[2], 0.1);
    double ddf1 = midp_secdiff(fx1[0], fx1[1], fx1[2], 0.1);
    double df_fw2 = fw_diff(fx2[1], fx2[2], 0.01);
    double df_bw2 = bw_diff(fx2[0], fx2[1], 0.01);
    double df_ct2 = ct_diff(fx2[0], fx2[2], 0.01);
    double ddf2 = midp_secdiff(fx2[0], fx2[1], fx2[2], 0.01);
    printf("Primer derivada en 1.3 con h = 0.1\n");
    printf("f'(x)\t\terror abs\tMetodo\n");
    printf("%lf\t%lf\tDerivada hacia delante\n", df_fw1, fabs(df_fw1 - df));
    printf("%lf\t%lf\tDerivada hacia atras\n", df_bw1, fabs(df_bw1 - df));
    printf("%lf\t%lf\tDerivada centrada\n", df_ct1, fabs(df_ct1 - df));
    printf("Primer derivada en 1.3 con h = 0.01\n");
    printf("f'(x)\t\terror abs\tMetodo\n");
    printf("%lf\t%lf\tDerivada hacia delante\n", df_fw2, fabs(df_fw2 - df));
    printf("%lf\t%lf\tDerivada hacia atras\n", df_bw2, fabs(df_bw2 - df));
    printf("%lf\t%lf\tDerivada centrada\n", df_ct2, fabs(df_ct2 - df));
    printf("Segunda derivada en 1.3\n");
    printf("f''(x)\t\terror abs\th\n");
    printf("%lf\t%lf\t0.1\n", ddf1, fabs(ddf1 - ddf));
    printf("%lf\t%lf\t0.01\n", ddf2, fabs(ddf2 - ddf));

    return 0;
}