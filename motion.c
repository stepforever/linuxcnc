//注释风格为doxygen风格，变量命名为驼峰命名法
//函数功能：梯形加减速规划
//输入参数：起始速度，目标速度，加速度，减速度，距离
//返回值：每个时间步的位置
//其他说明：无
float *trapezoidalPlanning(float startSpeed, float targetSpeed, float acceleration, float deceleration, float distance)
{
    // 计算加速度时间
    float accelerationTime = (targetSpeed - startSpeed) / acceleration;
    // 计算减速度时间
    float decelerationTime = targetSpeed / deceleration;
    // 计算加速度距离
    float accelerationDistance = startSpeed * accelerationTime + 0.5 * acceleration * accelerationTime * accelerationTime;
    // 计算减速度距离
    float decelerationDistance = targetSpeed * decelerationTime - 0.5 * deceleration * decelerationTime * decelerationTime;
    // 计算匀速时间
    float uniformSpeedTime = (distance - accelerationDistance - decelerationDistance) / targetSpeed;
    // 计算时间步数
    int timeSteps = (int)(accelerationTime + uniformSpeedTime + decelerationTime);
    // 计算每个时间步的位置
    float *position = (float *)malloc(timeSteps * sizeof(float));
    for (int i = 0; i < accelerationTime; i++)
    {
        position[i] = startSpeed * i + 0.5 * acceleration * i * i;
    }
    for (int i = 0; i < uniformSpeedTime; i++)
    {
        position[(int)accelerationTime + i] = accelerationDistance + targetSpeed * i;
    }
    for (int i = 0; i < decelerationTime; i++)
    {
        position[(int)(accelerationTime + uniformSpeedTime) + i] = accelerationDistance + targetSpeed * uniformSpeedTime + targetSpeed * i - 0.5 * deceleration * i * i;
    }
    return position;
}
