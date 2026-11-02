#include <stdio.h>
#include <stdlib.h>

#define SET_VALUE 90 // Ideal engine Temp = 90 C
#define SIZE 50 // Number of elements(temp values)


int main()
{

    printf("Temperature \t Fan Duty %%\n");
    //Gains
    float GainP= 2; // proportional gain
    float GainI=0.2; // intergration gain
    float GainD=0;//  derivative gain

    //Components
    float error= 0;
    float fanDuty= 0;
    float PropControl = 0;  // proportional control
    float IntgControl= 0;  // integral control
    float DrvControl= 0;  // derivative control;
    float IntgClamp = 0;

    //Arrays
    //float arrAvgTemps[120] = {25.0, 31.5, 37.6, 43.2, 48.5, 53.4, 57.9, 62.1, 65.9, 69.4, 72.6, 75.5, 78.1, 80.5, 82.7, 84.6, 86.3, 87.8, 89.1, 90.3, 91.3, 92.1, 91.4, 92.8, 93.5, 92.1, 91.3, 90.8, 91.6, 92.4, 93.1, 92.7, 91.9, 91.2, 90.7, 91.4, 92.3, 93.0, 93.4, 92.6, 91.7, 91.1, 91.8, 92.5, 93.2, 92.8, 92.0, 91.3, 90.9, 91.7, 92.6, 93.3, 92.9, 92.1, 91.4, 91.0, 91.8, 92.7, 93.4, 93.1, 92.3, 91.5, 91.1, 91.9, 92.8, 93.5, 93.0, 92.2, 91.5, 91.0, 91.8, 92.7, 93.4, 93.2, 92.4, 91.6, 91.1, 91.9, 92.8, 93.5, 93.1, 92.3, 91.5, 91.1, 91.9, 92.8, 93.5, 93.3, 92.5, 91.7, 91.2, 92.0, 92.9, 93.6, 93.2, 92.4, 91.6, 91.2, 92.0, 92.9, 70.0, 82.0, 88.0, 92.0, 95.0, 102.0, 105.0, 110.0, 120.0, 130.0, 30.0, 60.0, 80.0, 100.0, 105.0, 120.0, 135.0, 150.0, 160.0, 200.0};
    float arrAvgTemps[SIZE] =
    {
    92.0, 92.5, 93.1, 93.8, 94.5, 95.0, 95.2, 95.5, 96.0, 96.5,
    97.0, 97.4, 98.0, 98.5, 99.0, 99.5, 100.0, 100.2, 100.5, 100.8,
    101.0, 105.2, 112.5, 122.0, 135.4,
    128.0, 118.5, 110.0, 104.5, 101.2,
    100.0, 99.8, 99.5, 99.3, 99.1, 99.0, 99.0, 99.1, 99.2, 99.3,
    99.4, 99.5, 99.6, 99.7, 99.8, 99.9, 100.0, 100.1, 100.0, 100.0
    };
    float arrErrors[SIZE];


    //Filling Arrays
    for( int i = 0;i < SIZE; i++)
    {
        error = arrAvgTemps[i] - SET_VALUE;
        arrErrors[i] = error;
    }


    //Actual PID Controller Loop
    for (int i = 0; i < (SIZE-1) ; i++) // # of temps-1
    {

     error = arrAvgTemps[i] - SET_VALUE ;

    PropControl = GainP * error;
    IntgControl = GainI*( IntgControl + error); // I need to clamp this somehow
    DrvControl = GainD * (arrErrors[i+1] - arrErrors[i]) ; //by doing  (# of temps-1) when we do
                                                        //our final run , we wont go out of bounds
    fanDuty = (PropControl + IntgControl + DrvControl);

    // Clamping the fan Duty so that is doesnt go out of bounds
    if (fanDuty > 100)
    {
        fanDuty = 100;
    }

    if (fanDuty < 0)
    {
        fanDuty = 0;
    }
    //

    //Output
    printf("%.2f \t\t %% %.2f\n", arrAvgTemps[i],fanDuty);

    } // end PID Loop



    return 0;
}
