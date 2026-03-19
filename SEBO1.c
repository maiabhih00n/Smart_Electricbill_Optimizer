#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_APPLIANCES  20
#define MAX_HOURS       24
#define MAX_NAME_LEN    40

#define PEAK_RATE       8.50
#define OFF_PEAK_RATE   4.00
#define NORMAL_RATE     6.00

typedef struct {
    char  name[MAX_NAME_LEN];
    float power_kw;
    int   duration_hours;
    int   flexible;
    int   assigned_hour;
    float cost;
} Appliance;

typedef struct {
    float rate;
    char  label[15];
} TariffSlot;

TariffSlot tariff[MAX_HOURS];
Appliance  appliances[MAX_APPLIANCES];
int        num_appliances = 0;

void init_tariff() {
    for (int h = 0; h < MAX_HOURS; h++) {
        if ((h >= 6 && h < 9) || (h >= 18 && h < 23)) {
            tariff[h].rate = PEAK_RATE;
            strcpy(tariff[h].label, "PEAK");
        } else if (h >= 23 || h < 6) {
            tariff[h].rate = OFF_PEAK_RATE;
            strcpy(tariff[h].label, "OFF-PEAK");
        } else {
            tariff[h].rate = NORMAL_RATE;
            strcpy(tariff[h].label, "NORMAL");
        }
    }
}

float compute_cost(float power_kw, int duration, int start_hour) {
    float total = 0.0f;
    for (int i = 0; i < duration; i++) {
        int h = (start_hour + i) % MAX_HOURS;
        total += power_kw * tariff[h].rate;
    }
    return total;
}