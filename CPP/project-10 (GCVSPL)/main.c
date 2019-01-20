#include <stdio.h>
#include "gcvspl.h"

int main()
{
    int choice = -1, NumDatasets = 0, time_steps;
    int HalfOrder = 2;
    double Value = -1;

    printf("Choose input dataset:\n  1. Corradini.\n  2. KITTI.\n\n> ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        // Corradini Dataset
        NumDatasets = 5;
        time_steps = 91;
        printf("\nCorradini Dataset selected.\nNumber of datasets available for Corradini is %d.\n", NumDatasets);
        printf("Time steps set as %d", time_steps);
        printf("\nPerforming GCVSPL spline filtering and derivation for half order of %d", HalfOrder);
        printf(",\nwith no relative weight knowledge.\n\n");
        break;
    case 2:
        // KITTI Dataset
        NumDatasets = 1;
        time_steps = 108;
        printf("\nKITTI Dataset selected.\nNumber of datasets available for KITTI is %d.\n", NumDatasets);
        printf("Time steps set as %d", time_steps);
        printf("\nPerforming GCVSPL spline filtering and derivation for half order of %d", HalfOrder);
        printf(",\n with no relative weight knowledge.\n\n");
        break;
    default:
        printf("Wrong Choice.\n\n");
        return  0;
    }

    char InputFile[NumDatasets][18];
    char OutputFile[NumDatasets][19];

    for (int m = 1; m <= NumDatasets; ++m) {
        sprintf(InputFile[m], "GCVSPL_Input_%d%s", m, ".txt");
        sprintf(OutputFile[m], "GCVSPL_Output_%d%s", m, ".txt");

        FILE *GCVSPL_Input, *GCVSPL_Output;
        GCVSPL_Input = fopen(InputFile[m], "r");

        double Weight[time_steps];
        double SplineCoefficients[time_steps];
        double time[time_steps], NoisyData[time_steps];
        for (int i = 0; i < time_steps; ++i) {
            fscanf(GCVSPL_Input, "%lf %lf", &time[i], &NoisyData[i]);
            Weight[i] = 1;
        }

        printf("Reading values from dataset %d\n", m);

        fclose(GCVSPL_Input);

        double WorkVector[(6*(time_steps*HalfOrder+1) + time_steps)];
        int ErrorParameter;
        double InternalWorkArray[2*HalfOrder];

        gcvspl(&time, &NoisyData, &Weight, HalfOrder, time_steps,
               &SplineCoefficients, Value, &WorkVector, &ErrorParameter);

        switch (ErrorParameter) {
        case 0:
            break;
        case 1:
            printf("Half Order < 0, or Number of observations < 2*HalfOrder\n\n");
            return 0;
        case 2:
            printf("Time series not strictly increasing\n\n");
            return 0;
        }

        double dispVals[time_steps];
        double VelVals[time_steps];
        double AccVals[time_steps];
        int curr;

        GCVSPL_Output = fopen(OutputFile[m], "w+");

        for (int i = 0; i < time_steps; ++i) {
            curr = i;
            dispVals[i] = splder(0, HalfOrder, time_steps, time[i],
                                 &time, &SplineCoefficients, &curr, &InternalWorkArray);
            VelVals[i] = splder(1, HalfOrder, time_steps, time[i],
                                &time, &SplineCoefficients, &curr, &InternalWorkArray);
            AccVals[i] = splder(2, HalfOrder, time_steps, time[i],
                                &time, &SplineCoefficients, &curr, &InternalWorkArray);
            fprintf(GCVSPL_Output, "%lf %lf %lf\n", dispVals[i], VelVals[i], AccVals[i]);
        }

        printf("...Printing values for dataset %d onto file 'GCVSPL_Output_%d.txt'.\n\n", m, m);
        fclose(GCVSPL_Output);
    }

    return 0;
}
