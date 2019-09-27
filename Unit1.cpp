//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

double Newton(double x, int n, double *MasX, double *MasY, double step);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        const int n = 6;
        double MasX[n] = {0,1,2,3,4,5};
        double MasY[n] = {1,4,7,4,1,3};

        // простой график
        for ( int i = 0; i < n; i++ )
        {
                Series1->AddXY(MasX[i], MasY[i]);
        }

        // интерполированный график
        for ( double x = MasX[0]; x <= MasX[n-1]; x += 0.05 )
        {
                double y = Newton(x, n, MasX, MasY, 1);
                Series2->AddXY(x, y);
        }
}
//---------------------------------------------------------------------------


double Newton(double x, int n, double *MasX, double *MasY, double step)
{
        // выделяем память под динамический двумерный массив dy
        double **dy = new double*[n];
        for ( int i = 0; i < n; i++ ) dy[i] = new double[n];

        // подсчитываем dy
        for ( int i = 0; i < n; i++ )
        {
                dy[0][i] = MasY[i];
        }

        for ( int i = 1; i < n; i++ )
        {
                for ( int j = 0; j < n-i; j++ )
                {
                        dy[i][j] = dy[i-1][j+1] - dy[i-1][j];
                }
        }

        // вычисляем результирующий y
        double q = (x-MasX[0]) / step; // см. формулу
        double result = MasY[0]; // результат (y) 

        double mult_q = 1; // произведение из q*(q-1)*(q-2)*(q-n)
        double fact = 1;  // факториал

        for ( int i = 1; i < n; i++ )
        {
                fact *= i;
                mult_q *= (q-i+1);

                result += mult_q/fact * dy[i][0];
        }

        // осводождаем dy
        for ( int i = 0; i < n; i++ ) delete[] dy[i];
        delete[] dy;

        return result;
}
