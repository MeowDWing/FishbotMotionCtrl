// #ifndef __PIDCTRLER_H__
// #define __PIDCTRLER_H__

// class pidCtrler
// {
// private:
//     // Kp * error + Ki * integral + Kd * derivative
//     float _target;
//     float _kp; // 比例系数
//     float _ki; // 积分系数
//     float _kd; // 微分系数

//     float _last_error; // 上一次误差
//     float _last_last_error; // 上上次误差
//     float _sum_error; // 误差的累积和
//     float _derror; // 当前误差的变化率
//     float _integral; // 积分值
//     float _last_time; // 上一次计算的时间

//     float _output_min; // 输出的最小值
//     float _output_max; // 输出的最大值
//     float _max_integral; // 积分的最大值

// public:
//     pidCtrler(/* args */);
//     pidCtrler(float kp, float ki, float kd);
//     ~pidCtrler();

//     float update(float current);
//     void updateTarget(float target);
//     void updatePid(float kp, float ki, float kd);
//     void outLimits(float min, float max);
//     void reset();
// };



// #endif // __PIDCTRLER_H__