/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

class KalmanFilter final
{
public:

    KalmanFilter(double q, double r, double f = 1, double h = 1)
    {
        Q = q;
        R = r;
        F = f;
        H = h;
    }

    void SetState(double state, double covariance)
    {
        State = state;
        Covariance = covariance;
    }

    void Correct(double data)
    {
        //time update - prediction
        X0 = F * State;
        P0 = F * Covariance * F + Q;

        //measurement update - correction
        auto K = H * P0 / (H * P0 * H + R);
        State = X0 + K * (data - H * X0);
        Covariance = (1 - K * H) * P0;
    }

    double GetState() const
    {
        return State;
    }

private:
    double X0; // predicted state
    double P0; // predicted covariance
    double F; // factor of real value to previous real value
    double Q; // measurement noise
    double H; // factor of measured value to real value
    double R; // environment noise
    double State;
    double Covariance;
};
