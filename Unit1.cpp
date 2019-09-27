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

        // ������� ������
        for ( int i = 0; i < n; i++ )
        {
                Series1->AddXY(MasX[i], MasY[i]);
        }

        // ����������������� ������
        for ( double x = MasX[0]; x <= MasX[n-1]; x += 0.05 )
        {
                double y = Newton(x, n, MasX, MasY, 1);
                Series2->AddXY(x, y);
        }
}
//---------------------------------------------------------------------------


double Newton(double x, int n, double *MasX, double *MasY, double step)
{
        // �������� ������ ��� ������������ ��������� ������ dy
        double **dy = new double*[n];
        for ( int i = 0; i < n; i++ ) dy[i] = new double[n];

        // ������������ dy
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

        // ��������� �������������� y
        double q = (x-MasX[0]) / step; // ��. �������
        double result = MasY[0]; // ��������� (y) 

        double mult_q = 1; // ������������ �� q*(q-1)*(q-2)*(q-n)
        double fact = 1;  // ���������

        for ( int i = 1; i < n; i++ )
        {
                fact *= i;
                mult_q *= (q-i+1);

                result += mult_q/fact * dy[i][0];
        }

        // ����������� dy
        for ( int i = 0; i < n; i++ ) delete[] dy[i];
        delete[] dy;

        return result;
}
