void load_sample_appliances() {
    strcpy(appliances[0].name, "Refrigerator");
    appliances[0].power_kw = 0.15; appliances[0].duration_hours = 24;
    appliances[0].flexible = 0;    appliances[0].assigned_hour  = 0;

    strcpy(appliances[1].name, "Lights");
    appliances[1].power_kw = 0.10; appliances[1].duration_hours = 6;
    appliances[1].flexible = 0;    appliances[1].assigned_hour  = 18;

    strcpy(appliances[2].name, "Washing Machine");
    appliances[2].power_kw = 0.50; appliances[2].duration_hours = 2;
    appliances[2].flexible = 1;    appliances[2].assigned_hour  = 8;

    strcpy(appliances[3].name, "Dishwasher");
    appliances[3].power_kw = 1.20; appliances[3].duration_hours = 2;
    appliances[3].flexible = 1;    appliances[3].assigned_hour  = 19;

    strcpy(appliances[4].name, "Water Heater");
    appliances[4].power_kw = 2.00; appliances[4].duration_hours = 1;
    appliances[4].flexible = 1;    appliances[4].assigned_hour  = 7;

    strcpy(appliances[5].name, "Air Conditioner");
    appliances[5].power_kw = 1.50; appliances[5].duration_hours = 4;
    appliances[5].flexible = 1;    appliances[5].assigned_hour  = 14;

    strcpy(appliances[6].name, "EV Charger");
    appliances[6].power_kw = 3.30; appliances[6].duration_hours = 3;
    appliances[6].flexible = 1;    appliances[6].assigned_hour  = 20;

    num_appliances = 7;
}

float calculate_original_bill() {
    float total = 0.0f;
    printf("\n==========================================================\n");
    printf("       ORIGINAL BILL  (User Default Schedule)\n");
    printf("==========================================================\n");
    printf("| %-16s | Power(kW) | Hours | Start | Cost(Rs) |\n", "Appliance");
    printf("|------------------|-----------|-------|-------|----------|\n");

    for (int i = 0; i < num_appliances; i++) {
        float c = compute_cost(appliances[i].power_kw,
                               appliances[i].duration_hours,
                               appliances[i].assigned_hour);
        appliances[i].cost = c;
        total += c;
        printf("| %-16s |   %5.2f   |  %2d   | %02d:00 |  %7.2f |\n",
               appliances[i].name, appliances[i].power_kw,
               appliances[i].duration_hours, appliances[i].assigned_hour, c);
    }
    printf("|------------------|-----------|-------|-------|----------|\n");
    printf("| %-38s |  %7.2f |\n", "TOTAL BILL (Rs)", total);
    printf("==========================================================\n");
    return total;
}
