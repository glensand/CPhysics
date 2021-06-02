#pragma once

#include "ITask.h"

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <fstream>

#include "CVPlot/CVPlot.h"

void plot(const std::vector<double>& x, const std::vector<double>& y)
{
    const Plotter::GraphParams graphParams{ x , y };

    Plotter::CVPlot plot1;
    plot1.AddGraph(&graphParams);
    plot1.Show();
    plot1.Close();
}

template<typename T1, typename T2>
void plot(const std::vector<T1>&x, const std::vector<T2>& y)
{
    std::vector<double> yD;
    std::vector<double> xD;
    yD.reserve(y.size());
    xD.reserve(y.size());

    for (auto yI : y)
        yD.emplace_back(yI);

    for (auto xI : x)
        xD.emplace_back(xI);

    plot(xD, yD);
}

class Task14 final :
    public ITask
{
public:
    Task14() = default;
    ~Task14() = default;

    void Run(const Params* params = nullptr) const override;
};

class Kletka {
public:
    double li0;
    double l[2];
    double dl;
    double li;
    double lr[2];
    double L[2];
    double dL;
    double z1[2];
    double z2[2];
    double tr[2];
    double t0;   //время рождения
    double S;    //площадь стенки с соседней клеткой
    double A;    //координата верхней границы клетки
    int DZ; //идентификатор зоны деления, если =1, то в DZ, если 0 то в EZ
    int trihom;//идентификатор трихом
    //если trihom = 0, то в этом ряду трихом быть не может
    //если trihom = 1, то в этом ряду могут быть трихомы, а сама клетка обычная
    //если trihom = 2, то эта клетка трихома
};

Kletka X[1000000][5];

inline void Task14::Run(const Params* params) const
{

    using namespace std;

    //int NNN[200000];

    setlocale(LC_ALL, "Russian");

    //константы
    constexpr double z1min = 0.1;
    constexpr double z2min = 0.005;
    constexpr int trmin = 20;
    constexpr int Lmax = 10;
    constexpr int Pc = 2;
    constexpr int r = 4;
    constexpr double etha = 0.15;
    constexpr int b1z1 = 4;
    constexpr int b1z2 = 4;
    constexpr double b1tr = 3;
    constexpr int b2z1 = 5;
    constexpr int b2z2 = 5;
    constexpr int b2tr = 5;
    constexpr int nuz1 = 0.001;
    constexpr double nuz2 = 0.00001;//0.001
    constexpr int nutr = 6.0;
    constexpr int dz1 = 1.1;
    constexpr double dz2 = 0.95;//1.4
    constexpr double dtr = 0.2;//0.13

    //начальные данные
    constexpr int NN = 5;
    int MM[5] = { 6, 4, 8, 5, 3 };

    for (int j = 0; j < NN; j++) {
        for (int i = 0; i < MM[j]; i++) {
            X[i][j].l[0] = 5.1 + (i + j) * 0.01;
            X[i][j].L[0] = 5.1 + (i + j) * 0.01;
            X[i][j].li = 6.5 + (i + j) * 0.01;
            X[i][j].li0 = 6.5 + (i + j) * 0.01;
            X[i][j].lr[0] = 5.06 + (i + j) * 0.01;
            X[i][j].z1[0] = 6;
            X[i][j].z2[0] = 18;
            X[i][j].tr[0] = 0;
            X[i][j].t0 = 0;
            X[i][j].DZ = 1;

            if (((j == 0) || (j == 2)) || ((j == 4) || (j == 6))) {
                X[i][j].trihom = 0;
            }
            else if (((j == 1) || (j == 3)) || (j == 5)) {
                X[i][j].trihom = 1;
            }
        }
    };

    //начинаем алгоритм по времени
    double Posm;
    double Pturg;
    double dli;
    double t[2]; //массив шагов времени
    vector<double> Y(0); //массив времени для графика
    vector<int> X1(0); //число трихом
    int trihoms = 0;
    vector<int> NNN(0); //число всех клеток
    vector<double> LT(0);
    vector<double> Lm1(0);
    vector<double> Lm2(0);
    vector<double> Z1m1(0);
    vector<double> Z1m2(0);
    vector<double> Z2m1(0);
    vector<double> Z2m2(0);
    vector<double> Trm1(0);
    vector<double> Trm2(0);
    vector<double> X2(0); //среднее значение z1
    vector<double> X3(0); //среднее значение z2
    vector<double> X4(0); //среднее значение tr
    vector<double> XL(0); //среднее значение длины
    vector<double> XB(0);
    t[0] = 0;

    ofstream fout(L"результат.txt");
    ofstream f1out(L"число трихом.txt");
    ofstream f2out(L"средняя длина трихом.txt");
    ofstream f3out(L"число клеток.txt");
    ofstream f4out(L"Максимальная длина.txt");
    ofstream f5out(L"Минимальная длина.txt");
    ofstream f6out(L"Z1max.txt");
    ofstream f7out(L"Z1min.txt");
    ofstream f8out(L"Z2max.txt");
    ofstream f9out(L"Z2min.txt");
    ofstream f10out(L"Trmax.txt");
    ofstream f11out(L"Trmin.txt");
    ofstream f12out(L"Z1__.txt");
    ofstream f13out(L"Z2__.txt");
    ofstream f14out(L"Tr__.txt");
    ofstream f15out(L"L__.txt");
    ofstream f16out(L"Верхняя грань.txt");

    for (int h = 0; h <= 200000; h++) {
        X2.push_back(0);
        X3.push_back(0);
        X4.push_back(0);
        XL.push_back(0);
        XB.push_back(0);
        LT.push_back(0);
        NNN.push_back(0);
        X1.push_back(0);

        t[1] = t[0] + 0.0001;

        Y.push_back(t[0]);

        //задаем функции l,lr,li для каждой клетки
        for (int n = 0; n < NN; n++) {
            for (int m = 0; m < MM[n]; m++) {

                if (t[0] != 0) {
                    X[m][n].li = X[m][n].li0 + (t[0] - X[m][n].t0) * X[m][n].li0 * 0.0417;
                };

                dli = X[m][n].li0 * 0.0417;

                Posm = (10 - 10 * (X[m][n].l[0] / X[m][n].li));

                Pturg = (100 * (X[m][n].l[0] / X[m][n].lr[0]) - 100);

                X[m][n].dl = 160 * X[m][n].l[0] * (Posm - Pturg);

                X[m][n].l[1] = (X[m][n].l[0] + (t[1] - t[0]) * X[m][n].dl);

                if (Pturg < Pc) {
                    X[m][n].lr[1] = X[m][n].lr[0];
                }
                else {
                    X[m][n].lr[1] = X[m][n].lr[0] + etha * dli * (t[1] - t[0]) * (Pturg - Pc) * (Pturg - Pc) * (Pturg - Pc);
                };

                X[m][n].A = 0;
                for (int i = 0; i <= m; i++) {
                    X[m][n].A += X[i][n].L[0];
                };

                if (X[m][n].trihom == 2) {
                    LT[h] += X[m][n].L[0];
                };

                NNN[h]++;
            }
        };

        vector<double> lamda(0); //верхняя грань фрагмента
        //присвоим массиву lamda верхние грани клеток
        for (int j = 0; j < NN; j++) {
            for (int i = 0; i < MM[j]; i++) {
                lamda.push_back(X[i][j].A);
            }
        };

        sort(lamda.begin(), lamda.end());

        vector<double> la1(0);   //длина фрагмента с нулями
        //присвоим массиву la1 длины фрагментов вместо координат их верхних граней
        for (int i = 0; i < lamda.size() - 1; i++) {
            la1.push_back(lamda[i + 1] - lamda[i]);
        };

        vector<double> la(0);    //длина фрагмента без нулей
        //исключаем нули из массива la1, создав массив la;
        for (int i = 0; i < la1.size(); i++) {
            if (la1[i] != 0) {
                la.push_back(la1[i]);
            }
        };

        vector<double> B(la.size());     //массив верхних граней ненулевых фрагментов
        //массив верхних граней ненулевых фрагментов
        for (int i = 0; i < la.size(); i++) {
            B[i] = 0;
        };
        for (int i = 0; i < la.size(); i++) {
            for (int j = 0; j <= i; j++) {
                B[i] += la[j];
            }
        };
        XB[h] = B[B.size() - 1];
        //fout << "Самая верхняя грань = " << B[B.size() - 1] << "; ";

        //dL/dt для каждой клетки
        for (int n = 0; n < NN; n++) {
            for (int m = 0; m < MM[n]; m++) {
                long double s1 = 0;
                for (int i = 0; i < la.size(); i++) {
                    long double sum = 0;
                    //если фрагмент принадлежит клетке mn
                    //если клетка некрайняя снизу
                    if (m != 0) {
                        if ((B[i] > X[m - 1][n].A) && (B[i] <= X[m][n].A)) {
                            //значит iй фрагмент принадлежит mn клетке
                            //значит начинаем поиски клеток в которых ещё лежит этот фрагмент
                            for (int q = 0; q < NN; q++) {
                                for (int p = 0; p < MM[q]; p++) {
                                    //если фрагмент принадлежит клетке pq
                                    //если клетка некрайняя снизу
                                    if (p != 0) {
                                        if ((B[i] > X[p - 1][q].A) && (B[i] <= X[p][q].A)) {
                                            //нашли клетку, в которой есть iй фрагмент
                                            sum += X[p][q].dl;
                                        }
                                    }
                                    //если клетка крайняя снизу
                                    else if (p == 0) {
                                        if (B[i] <= X[p][q].A) {
                                            //нашли клетку, в которой есть iй фрагмент
                                            sum += X[p][q].dl;
                                        }
                                    }
                                }
                            };
                            sum = sum * la[i];
                            s1 += sum;
                        }
                    }
                    //если клетка крайняя снизу
                    else if (m == 0) {
                        if (B[i] <= X[m][n].A) {
                            //значит iй фрагмент принадлежит mn клетке
                            //значит начинаем поиски клеток в которых ещё лежит этот фрагмент
                            for (int q = 0; q < NN; q++) {
                                for (int p = 0; p < MM[q]; p++) {
                                    //если фрагмент принадлежит клетке pq
                                    //если клетка некрайняя снизу
                                    if (p != 0) {
                                        if ((B[i] > X[p - 1][q].A) && (B[i] <= X[p][q].A)) {
                                            //нашли клетку, в которой есть iй фрагмент
                                            sum += X[p][q].dl;
                                        }
                                    }
                                    else if (p == 0) {
                                        if (B[i] <= X[p][q].A) {
                                            //нашли клетку, в которой есть iй фрагмент
                                            sum += X[p][q].dl;
                                        }
                                    }
                                }
                            };
                            sum = sum * la[i];
                            s1 += sum;
                        }
                    }
                };
                X[m][n].dL = s1 / NN;
                X[m][n].L[1] = X[m][n].L[0] + abs(X[m][n].dL * 0.0001);
                XL[h] += X[m][n].L[1];
            }
        };

        vector<double> a1(0);
        for (int j = 0; j < NN; j++) {
            for (int i = 0; i < MM[j]; i++) {
                a1.push_back(X[i][j].L[1]);
            }
        };

        sort(a1.begin(), a1.end());
        Lm1.push_back(a1[a1.size() - 1]);
        Lm2.push_back(a1[0]);
        //cout << "Lmax = " << a1[a1.size()-1] << "; ";

        a1.clear();

        B.clear();
        lamda.clear();
        la.clear();
        la1.clear();

        //поиск соседних клеток
        for (int n = 0; n < NN; n++) {
            for (int m = 0; m < MM[n]; m++) {

                //соседи слева
                vector<Kletka> Y1(0);    //соседи слева
                //убеждаемся, что они есть
                if (n > 0) /*если не крайний слева*/ {
                    for (int i = 0; i < MM[n - 1]; i++) /*идём по соседнему ряду слева*/ {
                        if (m == 0) {
                            if (i == 0) {
                                if (X[i][n - 1].A <= X[m][n].A) {
                                    Y1.push_back(X[i][n - 1]);
                                    Y1[Y1.size() - 1].S = X[i][n - 1].A;
                                }
                                else if (X[i][n - 1].A > X[m][n].A) {
                                    Y1.push_back(X[i][n - 1]);
                                    Y1[Y1.size() - 1].S = X[m][n].A;
                                }
                            }
                            else if (i != 0) {
                                if (X[i][n - 1].A <= X[m][n].A) {
                                    Y1.push_back(X[i][n - 1]);
                                    Y1[Y1.size() - 1].S = X[i][n - 1].A - X[i - 1][n - 1].A;
                                }
                                else if ((X[i - 1][n - 1].A < X[m][n].A) && (X[m][n].A <= X[i][n - 1].A)) {
                                    Y1.push_back(X[i][n - 1]);
                                    Y1[Y1.size() - 1].S = X[m][n].A - X[i - 1][n - 1].A;
                                }
                            }
                        }
                        else if (m != 0) {
                            if (i == 0) {
                                if ((X[m - 1][n].A < X[i][n - 1].A) && (X[i][n - 1].A <= X[m][n].A)) {
                                    Y1.push_back(X[i][n - 1]);
                                    Y1[Y1.size() - 1].S = X[i][n - 1].A - X[m - 1][n].A;
                                }
                                else if (X[m][n].A <= X[i][n - 1].A) {
                                    Y1.push_back(X[i][n - 1]);
                                    Y1[Y1.size() - 1].S = X[m][n].A - X[m - 1][n].A;
                                }
                            }
                            else if (i != 0) {
                                if ((X[i - 1][n - 1].A <= X[m - 1][n].A) && ((X[m - 1][n].A < X[i][n - 1].A) && (X[i][n - 1].A <= X[m][n].A))) {
                                    Y1.push_back(X[i][n - 1]);
                                    Y1[Y1.size() - 1].S = X[i][n - 1].A - X[m - 1][n].A;
                                }
                                else if ((X[i][n - 1].A >= X[m][n].A) && ((X[m][n].A > X[i - 1][n - 1].A) && (X[i - 1][n - 1].A >= X[m - 1][n].A))) {
                                    Y1.push_back(X[i][n - 1]);
                                    Y1[Y1.size() - 1].S = X[m][n].A - X[i - 1][n - 1].A;
                                }
                                else if ((X[m][n].A >= X[i][n - 1].A) && (X[i - 1][n - 1].A >= X[m - 1][n].A)) {
                                    Y1.push_back(X[i][n - 1]);
                                    Y1[Y1.size() - 1].S = X[i][n - 1].A - X[i - 1][n - 1].A;
                                }
                                else if ((X[i][n - 1].A >= X[m][n].A) && (X[m - 1][n].A >= X[i - 1][n - 1].A)) {
                                    Y1.push_back(X[i][n - 1]);
                                    Y1[Y1.size() - 1].S = X[m][n].A - X[m - 1][n].A;
                                }
                            }
                        }
                    }
                };

                //соседи справа
                vector<Kletka> Y2(0);    //соседи справа
                //убеждаемся, что они есть
                if (n < NN - 1) /*если не крайний справа*/ {
                    for (int i = 0; i < MM[n + 1]; i++) /*идём по соседнему ряду справа*/ {
                        if (m == 0) {
                            if (i == 0) {
                                if (X[i][n + 1].A <= X[m][n].A) {
                                    Y2.push_back(X[i][n + 1]);
                                    Y2[Y2.size() - 1].S = X[i][n + 1].A;
                                }
                                else if (X[i][n + 1].A > X[m][n].A) {
                                    Y2.push_back(X[i][n + 1]);
                                    Y2[Y2.size() - 1].S = X[m][n].A;
                                }
                            }
                            else if (i != 0) {
                                if (X[i][n + 1].A <= X[m][n].A) {
                                    Y2.push_back(X[i][n + 1]);
                                    Y2[Y2.size() - 1].S = X[i][n + 1].A - X[i - 1][n + 1].A;
                                }
                                else if ((X[i - 1][n + 1].A < X[m][n].A) && (X[m][n].A <= X[i][n + 1].A)) {
                                    Y2.push_back(X[i][n + 1]);
                                    Y2[Y2.size() - 1].S = X[m][n].A - X[i - 1][n + 1].A;
                                }
                            }
                        }
                        else if (m != 0) {
                            if (i == 0) {
                                if ((X[m - 1][n].A < X[i][n + 1].A) && (X[i][n + 1].A <= X[m][n].A)) {
                                    Y2.push_back(X[i][n + 1]);
                                    Y2[Y2.size() - 1].S = X[i][n + 1].A - X[m - 1][n].A;
                                }
                                else if (X[m][n].A <= X[i][n + 1].A) {
                                    Y2.push_back(X[i][n + 1]);
                                    Y2[Y2.size() - 1].S = X[m][n].A - X[m - 1][n].A;
                                }
                            }
                            else if (i != 0) {
                                if ((X[i - 1][n + 1].A <= X[m - 1][n].A) && ((X[m - 1][n].A < X[i][n + 1].A) && (X[i][n + 1].A <= X[m][n].A))) {
                                    Y2.push_back(X[i][n + 1]);
                                    Y2[Y2.size() - 1].S = X[i][n + 1].A - X[m - 1][n].A;
                                }
                                else if ((X[i][n + 1].A >= X[m][n].A) && ((X[m][n].A > X[i - 1][n + 1].A) && (X[i - 1][n + 1].A >= X[m - 1][n].A))) {
                                    Y2.push_back(X[i][n + 1]);
                                    Y2[Y2.size() - 1].S = X[m][n].A - X[i - 1][n + 1].A;
                                }
                                else if ((X[m][n].A >= X[i][n + 1].A) && (X[i - 1][n + 1].A >= X[m - 1][n].A)) {
                                    Y2.push_back(X[i][n + 1]);
                                    Y2[Y2.size() - 1].S = X[i][n + 1].A - X[i - 1][n + 1].A;
                                }
                                else if ((X[i][n + 1].A >= X[m][n].A) && (X[m - 1][n].A >= X[i - 1][n + 1].A)) {
                                    Y2.push_back(X[i][n + 1]);
                                    Y2[Y2.size() - 1].S = X[m][n].A - X[m - 1][n].A;
                                }
                            }
                        }
                    }
                };

                //z1
                double sum1 = 0;
                for (int i = 0; i < Y1.size(); i++) {
                    sum1 += b1z1 * Y1[i].S * (Y1[i].z1[0] - X[m][n].z1[0]);
                };
                sum1 = sum1 / (X[m][n].L[0] * r);
                double sum2 = 0;
                for (int i = 0; i < Y2.size(); i++) {
                    sum2 += b1z1 * Y2[i].S * (Y2[i].z1[0] - X[m][n].z1[0]);
                };
                sum2 = sum2 / (X[m][n].L[0] * r);
                double sum3 = 0;
                //если крайняя снизу
                if (m == 0) {
                    sum3 = b2z1 * (X[m + 1][n].z1[0] - X[m][n].z1[0]) / (X[m][n].L[0]);
                }
                //если крайняя сверху
                else if (m == (MM[n] - 1)) {
                    sum3 = b2z1 * (X[m - 1][n].z1[0] - X[m][n].z1[0]) / (X[m][n].L[0]);
                }
                //если ни та ни другая
                else {
                    sum3 = b2z1 * (X[m - 1][n].z1[0] + X[m + 1][n].z1[0] - 2 * X[m][n].z1[0]) / (X[m][n].L[0]);
                };
                X[m][n].z1[1] = (X[m][n].z1[0] + (t[1] - t[0]) * (sum1 + sum2 + sum3 + nuz1 - dz1 * X[m][n].z1[0] - (X[m][n].z1[0] * X[m][n].dL / X[m][n].L[0])));
                X2[h] += X[m][n].z1[1];

                //tr
                sum1 = 0;
                for (int i = 0; i < Y1.size(); i++) {
                    sum1 += b1tr * Y1[i].S * (Y1[i].tr[0] - X[m][n].tr[0]);
                };
                sum1 = sum1 / (X[m][n].L[0] * r);
                sum2 = 0;
                for (int i = 0; i < Y2.size(); i++) {
                    sum2 += b1tr * Y2[i].S * (Y2[i].tr[0] - X[m][n].tr[0]);
                };
                sum2 = sum2 / (X[m][n].L[0] * r);
                sum3 = 0;
                //если крайняя снизу
                if (m == 0) {
                    sum3 = b2tr * (X[m + 1][n].tr[0] - X[m][n].tr[0]) / (X[m][n].L[0]);
                }
                //если крайняя сверху
                else if (m == (MM[n] - 1)) {
                    sum3 = b2tr * (X[m - 1][n].tr[0] - X[m][n].tr[0]) / (X[m][n].L[0]);
                }
                //если ни та ни другая
                else {
                    sum3 = b2tr * (X[m - 1][n].tr[0] + X[m + 1][n].tr[0] - 2 * X[m][n].tr[0]) / (X[m][n].L[0]);
                };
                X[m][n].tr[1] = abs(X[m][n].tr[0] + (t[1] - t[0]) * (sum1 + sum2 + sum3 + nutr - dtr * X[m][n].tr[0] - (X[m][n].tr[0] * X[m][n].dL / X[m][n].L[0])));
                X4[h] += X[m][n].tr[1];

                //z2
                sum1 = 0;
                for (int i = 0; i < Y1.size(); i++) {
                    sum1 += b1z2 * Y1[i].S * (Y1[i].z2[0] - X[m][n].z2[0]);
                };
                sum1 = sum1 / (X[m][n].L[0] * r);
                sum2 = 0;
                for (int i = 0; i < Y2.size(); i++) {
                    sum2 += b1z2 * Y2[i].S * (Y2[i].z2[0] - X[m][n].z2[0]);
                };
                sum2 = sum2 / (X[m][n].L[0] * r);
                sum3 = 0;
                //если крайняя снизу
                if (m == 0) {
                    sum3 = b2z2 * (X[m + 1][n].z2[0] - X[m][n].z2[0]) / (X[m][n].L[0]);
                }
                //если крайняя сверху
                else if (m == (MM[n] - 1)) {
                    sum3 = b2z2 * (X[m - 1][n].z2[0] - X[m][n].z2[0]) / (X[m][n].L[0]);
                }
                //если ни та ни другая
                else {
                    sum3 = b2z2 * (X[m - 1][n].z2[0] + X[m + 1][n].z2[0] - 2 * X[m][n].z2[0]) / (X[m][n].L[0]);
                };
                X[m][n].z2[1] = abs(X[m][n].z2[0] + (t[1] - t[0]) * (sum1 + sum2 + sum3 + nuz2 - dz2 * X[m][n].z2[0] - (X[m][n].z2[0] * X[m][n].dL / X[m][n].L[0])));
                X3[h] += X[m][n].z2[1];

                Y1.clear();
                Y2.clear();
            }
        };

        vector<double> a2(0);
        for (int j = 0; j < NN; j++) {
            for (int i = 0; i < MM[j]; i++) {
                a2.push_back(X[i][j].z1[1]);
            }
        };
        sort(a2.begin(), a2.end());
        Z1m1.push_back(a2[a2.size() - 1]);
        Z1m2.push_back(a2[0]);
        //cout << "z1min = " << a2[0] << "; ";
        a2.clear();

        vector<double> a3(0);
        for (int j = 0; j < NN; j++) {
            for (int i = 0; i < MM[j]; i++) {
                a3.push_back(X[i][j].tr[1]);
            }
        };
        sort(a3.begin(), a3.end());
        Trm1.push_back(a3[a3.size() - 1]);
        Trm2.push_back(a3[0]);
        //cout << "trmax = " << a3[a3.size()-1] << endl;
        a3.clear();

        vector<double> a4(0);
        for (int j = 0; j < NN; j++) {
            for (int i = 0; i < MM[j]; i++) {
                a4.push_back(X[i][j].z2[1]);
            }
        };
        sort(a4.begin(), a4.end());
        Z2m1.push_back(a4[a4.size() - 1]);
        Z2m2.push_back(a4[0]);
        //cout << "Z2max = " << a4[a4.size()-1] << endl;
        a4.clear();

        //деление клеток
        double temp;
        for (int n = 0; n < NN; n++) {
            for (int m = 0; m < MM[n]; m++) {
                //начальное условие деления
                if ((X[m][n].L[1] > Lmax) && ((X[m][n].trihom != 2) && (X[m][n].t0 != t[1]))) {
                    //тогда клетка делится
                    //если ряд обычных клеток
                    if ((X[m][n].trihom == 0) && (X[m][n].z2[1] >= z2min)) {
                        MM[n]++;
                        for (int i = MM[n] - 1; i > m; i--) {
                            X[i][n] = X[i - 1][n];
                        };
                        X[m][n].t0 = t[1];
                        X[m + 1][n].t0 = t[1];
                        X2[h] += X[m][n].z1[1];
                        X3[h] += X[m][n].z2[1];
                        X4[h] += X[m][n].tr[1];
                        XL[h] += X[m][n].L[1];

                        temp = X[m][n].l[1];
                        X[m][n].l[1] = 0.5 * temp;
                        temp = X[m][n].lr[1];
                        X[m][n].lr[1] = 0.5 * temp;
                        temp = X[m][n].L[1];
                        X[m][n].L[1] = 0.5 * temp;

                        temp = X[m + 1][n].l[1];
                        X[m + 1][n].l[1] = 0.5 * temp;
                        temp = X[m + 1][n].lr[1];
                        X[m + 1][n].lr[1] = 0.5 * temp;
                        temp = X[m + 1][n].L[1];
                        X[m + 1][n].L[1] = 0.5 * temp;

                        NNN[h]++;
                    }
                    //если ряд с трихомами
                    else if ((X[m][n].trihom == 1) && (X[m][n].z2[1] >= z2min)) {
                        if ((X[m][n].tr[1] < trmin) && (X[m][n].z1[1] < z1min)) {
                            MM[n]++;
                            for (int i = MM[n] - 1; i > m; i--) {
                                X[i][n] = X[i - 1][n];
                            };
                            X[m][n].t0 = t[1];
                            X[m + 1][n].t0 = t[1];
                            X2[h] += X[m][n].z1[1];
                            X3[h] += X[m][n].z2[1];
                            X4[h] += X[m][n].tr[1];
                            XL[h] += X[m][n].L[1];

                            temp = X[m][n].l[1];
                            X[m][n].l[1] = 0.7 * temp;
                            temp = X[m][n].lr[1];
                            X[m][n].lr[1] = 0.7 * temp;
                            temp = X[m][n].L[1];
                            X[m][n].L[1] = 0.7 * temp;

                            temp = X[m + 1][n].l[1];
                            X[m + 1][n].l[1] = 0.3 * temp;
                            temp = X[m + 1][n].lr[1];
                            X[m + 1][n].lr[1] = 0.3 * temp;
                            temp = X[m + 1][n].L[1];
                            X[m + 1][n].L[1] = 0.3 * temp;

                            X[m + 1][n].trihom = 2;
                            trihoms++;
                            LT[h] += X[m + 1][n].L[1];

                            NNN[h]++;
                        }
                        else if ((X[m][n].tr[1] >= trmin) && (X[m][n].z1[1] < z1min)) {
                            MM[n]++;
                            for (int i = MM[n] - 1; i > m; i--) {
                                X[i][n] = X[i - 1][n];
                            };
                            X[m][n].t0 = t[1];
                            X[m + 1][n].t0 = t[1];
                            X2[h] += X[m][n].z1[1];
                            X3[h] += X[m][n].z2[1];
                            X4[h] += X[m][n].tr[1];
                            XL[h] += X[m][n].L[1];

                            temp = X[m][n].l[1];
                            X[m][n].l[1] = 0.5 * temp;
                            temp = X[m][n].lr[1];
                            X[m][n].lr[1] = 0.5 * temp;
                            temp = X[m][n].L[1];
                            X[m][n].L[1] = 0.5 * temp;

                            temp = X[m + 1][n].l[1];
                            X[m + 1][n].l[1] = 0.5 * temp;
                            temp = X[m + 1][n].lr[1];
                            X[m + 1][n].lr[1] = 0.5 * temp;
                            temp = X[m + 1][n].L[1];
                            X[m + 1][n].L[1] = 0.5 * temp;

                            NNN[h]++;
                        }
                    }
                }
            }
        };

        X1[h] = trihoms;
        LT[h] = LT[h] / X1[h];
        X2[h] = X2[h] / NNN[h];
        X3[h] = X3[h] / NNN[h];
        X4[h] = X4[h] / NNN[h];
        XL[h] = XL[h] / NNN[h];

        /*cout << "Время: " << t[1] << "; ";
          cout << "Трихомы: " << X1[h] << "; ";
          cout << "Средняя длина трихом = " << LT[h] << "; ";
          cout << "Клеток: " << NNN[h] << "; ";
          cout << "Lmax = " << Lm1[h] << "; ";
          cout << "Lmin = " << Lm2[h] << "; ";
          cout << "Z1max = " << Z1m1[h] << "; ";
          cout << "Z1min = " << Z1m2[h] << "; ";
          cout << "Z2max = " << Z2m1[h] << "; ";
          cout << "Z2min = " << Z2m2[h] << "; ";
          cout << "Trmax = " << Trm1[h] << "; ";
          cout << "Trmin = " << Trm2[h] << "; ";
          cout << "Z1_среднее = " << X2[h] << "; ";
          cout << "Z2_среднее = " << X3[h] << "; ";
          cout << "Tr_среднее = " << X4[h] << "; ";
          cout << "L_среднее = " << XL[h] << "; ";
          cout << "Верхняя грань = " << XB[h] << endl;*/

          //переопределяем данные
        for (int n = 0; n < NN; n++) {
            for (int m = 0; m < MM[n]; m++) {
                X[m][n].l[0] = X[m][n].l[1];
                X[m][n].lr[0] = X[m][n].lr[1];
                X[m][n].L[0] = X[m][n].L[1];
                X[m][n].z1[0] = X[m][n].z1[1];
                X[m][n].z2[0] = X[m][n].z2[1];
                X[m][n].tr[0] = X[m][n].tr[1];
            }
        };
        t[0] = t[1];
    };

    for (int h = 0; h <= 200; h++) {
        int v = h * 1000;
        fout << L"Время: " << Y[v] << "; ";
        fout << L"Трихомы: " << X1[v] << "; ";
        fout << L"Средняя длина трихом = " << LT[v] << "; ";
        fout << L"Клеток: " << NNN[v] << "; ";
        fout << L"Lmax = " << Lm1[v] << "; ";
        fout << L"Lmin = " << Lm2[v] << "; ";
        fout << L"Z1max = " << Z1m1[v] << "; ";
        fout << L"Z1min = " << Z1m2[v] << "; ";
        fout << L"Z2max = " << Z2m1[v] << "; ";
        fout << L"Z2min = " << Z2m2[v] << "; ";
        fout << L"Trmax = " << Trm1[v] << "; ";
        fout << L"Trmin = " << Trm2[v] << "; ";
        fout << L"Z1_среднее = " << X2[v] << "; ";
        fout << L"Z2_среднее = " << X3[v] << "; ";
        fout << L"Tr_среднее = " << X4[v] << "; ";
        fout << L"L_среднее = " << XL[v] << "; ";
        fout << L"Верхняя грань = " << XB[v] << endl;

        f1out << X1[v] << endl;
        f2out << LT[v] << endl;
        f3out << NNN[v] << endl;
        f4out << Lm1[v] << endl;
        f5out << Lm2[v] << endl;
        f6out << Z1m1[v] << endl;
        f7out << Z1m2[v] << endl;
        f8out << Z2m1[v] << endl;
        f9out << Z2m2[v] << endl;
        f10out << Trm1[v] << endl;
        f11out << Trm2[v] << endl;
        f12out << X2[v] << endl;
        f13out << X3[v] << endl;
        f14out << X4[v] << endl;
        f15out << XL[v] << endl;
        f16out << XB[v] << endl;
    };

    fout.close(); // закрываем файл
    f1out.close();
    f2out.close();
    f3out.close();
    f4out.close();
    f5out.close();
    f6out.close();
    f7out.close();
    f8out.close();
    f9out.close();
    f10out.close();
    f11out.close();
    f12out.close();
    f13out.close();
    f14out.close();
    f15out.close();
    f16out.close();

    plot( Y, X1 );
    plot(Y, NNN);
    plot( X1 , LT);
    plot( Y , X2 );
    plot( Y , X3 );
    plot( Y , X4 );
    plot( Y , XL );
    plot( Y , XB );

    system("pause");

    //графики:
    //X1[v] от Y[v]
    //LT[v] от X1[v]
    //NNN[v] от Y[v]
    //X2[v], X3[v], X4[v] от Y[v]
    //XL[v] от Y[v]
    //XB[v] от Y[v]
}

