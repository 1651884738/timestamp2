#include <stdio.h>

typedef struct times
{
    int Year;
    int Mon;
    int Day;
    int Hour;
    int Min;
    int Second;
}Times;

#define  SECONDS_IN_A_MINUTE   60
#define  SECONDS_IN_AN_HOUR    60 * SECONDS_IN_A_MINUTE
#define  SECONDS_IN_A_DAY      24 * SECONDS_IN_AN_HOUR

#define  SECONDS_IN_A_COMMON_YEAR   365 * SECONDS_IN_A_DAY
#define  SECONDS_IN_A_LEAP_YEAR     366 * SECONDS_IN_A_DAY

//从1970-01-01 08：00：00 起开始数秒
//定义一个起始时间戳 2022-01-01 00:00:00
#define  SPECIALTIMESTAMP       1640966400
typedef struct
{
    int Year;
    int Mon;
    int Day;
    int Hour;
    int Min;
    int Second;
}Date;

Date specialTime = {
        2022,
        01,
        01,
        00,
        00,
        00
};
//31 : 1  3 5 7 8 10 12 ; 30 : 4 6 9 11
const int daysofmon[] ={0,
                  31 * SECONDS_IN_A_DAY,
                  (28 + 31) * SECONDS_IN_A_DAY,
                  (31 + 28 + 31) * SECONDS_IN_A_DAY,
                  (30 + 31 + 28 + 31 ) * SECONDS_IN_A_DAY,
                  (31 + 30 + 31 + 28 + 31) * SECONDS_IN_A_DAY,
                  (30 + 31 + 30 + 31 + 28 + 31) * SECONDS_IN_A_DAY,
                  (31 + 30 + 31 + 30 + 31 + 28 + 31) * SECONDS_IN_A_DAY,
                  (31 + 31 + 30 + 31 + 30 + 31 + 28 + 31) * SECONDS_IN_A_DAY,
                  (30 + 31 + 31 + 30 + 31 + 30 + 31 + 28 + 31) * SECONDS_IN_A_DAY,
                  (31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 + 28 + 31) * SECONDS_IN_A_DAY,
                  (30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 + 28 + 31) * SECONDS_IN_A_DAY
                  };
const int _daysofmon[] ={0,
                        31 * SECONDS_IN_A_DAY,
                        (29 + 31) * SECONDS_IN_A_DAY,
                        (31 + 29 + 31) * SECONDS_IN_A_DAY,
                        (30 + 31 + 29 + 31 ) * SECONDS_IN_A_DAY,
                        (31 + 30 + 31 + 29 + 31) * SECONDS_IN_A_DAY,
                        (30 + 31 + 30 + 31 + 29 + 31) * SECONDS_IN_A_DAY,
                        (31 + 30 + 31 + 30 + 31 + 29 + 31) * SECONDS_IN_A_DAY,
                        (31 + 31 + 30 + 31 + 30 + 31 + 29 + 31) * SECONDS_IN_A_DAY,
                        (30 + 31 + 31 + 30 + 31 + 30 + 31 + 29 + 31) * SECONDS_IN_A_DAY,
                        (31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 + 29 + 31) * SECONDS_IN_A_DAY,
                        (30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 + 29 + 31) * SECONDS_IN_A_DAY
};
//日期转时间戳
size_t Date2timeStamp(Date standardTime){
    //需要计算 传进来的 standardTime 比 specialTime 大多少秒
    size_t differenceValue = 0;     //定义这个差值，单位为秒
    int leapYears = 0;

    if((standardTime.Year < specialTime.Year) || (standardTime.Year > 2099))//不允许 specialTime.Year 之前的时间传进来
    {
        printf("The year %d is not supported\r\n",standardTime.Year);
        return -1;
    }
    if((standardTime.Mon < 1) || (standardTime.Mon > 12))//不允许 无效的mon 传入
    {
        printf("The month %.2d is out of line\r\n",standardTime.Mon);
        return -1;
    }
    if((standardTime.Day < 1) || (standardTime.Day > 31))//不允许 无效的day 传入
    {
        printf("The day %.2d is out of line\r\n",standardTime.Day);
        return -1;
    }
    if((standardTime.Hour < 0) || (standardTime.Day > 24))//不允许 无效的hour 传入
    {
        printf("The hour %.2d is out of line\r\n",standardTime.Hour);
        return -1;
    }
    if((standardTime.Min < 0) || (standardTime.Min > 59))//不允许 无效的min 传入
    {
        printf("The min %.2d is out of line\r\n",standardTime.Min);
        return -1;
    }
    if((standardTime.Second < 0) || (standardTime.Second > 59))//不允许 无效的sec 传入
    {
        printf("The sec %.2d is out of line\r\n",standardTime.Second);
        return -1;
    }


    //从 specialTime 开始，到 standardTime 的前一年之间有过少个闰年
    for(int i = specialTime.Year; i < standardTime.Year; i++)
    {
        if((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
        {
            leapYears++;
        }
    }
    differenceValue += (SECONDS_IN_A_LEAP_YEAR * leapYears +
            SECONDS_IN_A_COMMON_YEAR * (standardTime.Year - specialTime.Year - leapYears));
    printf("....0......%d\r\n",leapYears);
    printf("....1......%d\r\n",differenceValue);
    //判断 是不是闰年
    if((standardTime.Year % 4 == 0 && standardTime.Year % 100 != 0) || (standardTime.Year % 400 == 0))  //判断是否闰年
    {
        differenceValue += (_daysofmon[standardTime.Mon - 1] +
                            (standardTime.Day - 1) * SECONDS_IN_A_DAY +
                            (standardTime.Hour ) *  SECONDS_IN_AN_HOUR +
                            (standardTime.Min ) * SECONDS_IN_A_MINUTE +
                            standardTime.Second
        );
        printf("....3......%d\r\n",differenceValue);
    }else
    {
        differenceValue += (daysofmon[standardTime.Mon - 1] +
                           (standardTime.Day - 1) * SECONDS_IN_A_DAY +
                           (standardTime.Hour) *  SECONDS_IN_AN_HOUR +
                           (standardTime.Min) * SECONDS_IN_A_MINUTE +
                           standardTime.Second
                           );
        printf("....2......%d\r\n",differenceValue);
    }

    return differenceValue += SPECIALTIMESTAMP;
}

int main(){
    //2022-09-16 22:47:24   1663339644
    Date Time = {
            2022,
            9,
            17,
            0,
            8,
            8
    };
    printf("%lld\r\n",Date2timeStamp(Time));
    return 0;
}