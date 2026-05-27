void dp_knapsack(float budget) {
    int B = (int)(budget * 100);
    int n = num_appliances;
    int weight[MAX_APPLIANCES];

    for (int i = 0; i < n; i++)
        weight[i] = (int)(appliances[i].cost * 100);

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
        dp[i] = (int *)calloc(B + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= B; w++) {
            dp[i][w] = dp[i-1][w];
            if (weight[i-1] <= w &&
                dp[i-1][w - weight[i-1]] + 1 > dp[i][w])
                dp[i][w] = dp[i-1][w - weight[i-1]] + 1;
        }
    }

    printf("\n----------------------------------------------------------\n");
    printf("  DAA MODULE 2 -- DP KNAPSACK  (Budget Optimizer)\n");
    printf("  Budget : Rs %.2f  |  Time Complexity : O(A x B)\n", budget);
    printf("----------------------------------------------------------\n");
    printf("  Appliances that fit within budget:\n\n");

    int w = B, selected = 0;
    float used = 0.0f;
    for (int i = n; i >= 1; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            printf("    [YES] %-20s  Rs %.2f\n",
                   appliances[i-1].name, appliances[i-1].cost);
            used += appliances[i-1].cost;
            w    -= weight[i-1];
            selected++;
        } else {
            printf("    [NO ] %-20s  Rs %.2f\n",
                   appliances[i-1].name, appliances[i-1].cost);
        }
    }
    printf("\n  Total selected : %d / %d\n", selected, n);
    printf("  Total cost     : Rs %.2f / Rs %.2f\n", used, budget);

    for (int i = 0; i <= n; i++) free(dp[i]);
    free(dp);
}

float calculate_optimized_bill() {
    float total = 0.0f;
    printf("\n==========================================================\n");
    printf("       OPTIMIZED BILL  (After Greedy Scheduling)\n");
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

void savings_report(float original, float optimized) {
    float saved   = original - optimized;
    float percent = (saved / original) * 100.0f;

    printf("\n==========================================================\n");
    printf("                 ENERGY SAVINGS REPORT\n");
    printf("==========================================================\n");
    printf("  Original Bill  (daily)   : Rs %8.2f\n", original);
    printf("  Optimized Bill (daily)   : Rs %8.2f\n", optimized);
    printf("  Amount Saved             : Rs %8.2f\n", saved);
    printf("  Savings Percentage       :    %6.2f %%\n", percent);
    printf("  Estimated Monthly Save   : Rs %8.2f\n", saved * 30);
    printf("  Estimated Yearly Save    : Rs %8.2f\n", saved * 365);
    printf("----------------------------------------------------------\n");
    printf("  RECOMMENDATIONS:\n");
    printf("  1. Run Washing Machine at 23:00 (off-peak rate)\n");
    printf("  2. Run EV Charger after 23:00  (cheapest rate)\n");
    printf("  3. Run Water Heater at midnight instead of morning\n");
    printf("  4. Avoid high-power devices between 18:00 - 23:00\n");
    printf("  5. Use AC during 09:00 - 17:00 instead of evenings\n");
    printf("==========================================================\n");
}

void display_tariff_table() {
    printf("\n==========================================================\n");
    printf("               TIME-OF-USE TARIFF TABLE\n");
    printf("==========================================================\n");
    printf("| Hour  | Tariff Slot  | Rate (Rs/kWh) |\n");
    printf("|-------|--------------|---------------|\n");
    for (int h = 0; h < MAX_HOURS; h++) {
        printf("| %02d:00 | %-12s |     %.2f      |\n",
               h, tariff[h].label, tariff[h].rate);
    }
    printf("==========================================================\n");
}

void time_complexity_summary() {
    printf("\n==========================================================\n");
    printf("           DAA -- TIME COMPLEXITY ANALYSIS\n");
    printf("==========================================================\n");
    printf("| %-30s | %-22s |\n", "Algorithm", "Time Complexity");
    printf("|--------------------------------|----------------------|\n");
    printf("| %-30s | %-22s |\n", "Greedy Scheduling",    "O(A x H) = O(7x24)");
    printf("| %-30s | %-22s |\n", "DP Knapsack (Budget)", "O(A x B)");
    printf("| %-30s | %-22s |\n", "Bill Calculation",     "O(A x H)");
    printf("| %-30s | %-22s |\n", "Tariff Lookup",        "O(1) per hour");
    printf("|--------------------------------|----------------------|\n");
    printf("| %-30s | %-22s |\n", "Overall System",       "O(AxH + AxB)");
    printf("==========================================================\n");
    printf("  A = appliances, H = 24 hours, B = budget (int scale)\n");
}

void add_custom_appliance() {
    if (num_appliances >= MAX_APPLIANCES) {
        printf("  [!] Maximum appliance limit reached.\n");
        return;
    }
    Appliance *a = &appliances[num_appliances];
    printf("\n  Enter appliance name        : ");
    scanf(" %[^\n]", a->name);
    printf("  Enter power consumption (kW): ");
    scanf("%f", &a->power_kw);
    printf("  Enter duration (hours)      : ");
    scanf("%d", &a->duration_hours);
    printf("  Is it flexible? (1=Yes/0=No): ");
    scanf("%d", &a->flexible);
    printf("  Default start hour (0-23)   : ");
    scanf("%d", &a->assigned_hour);
    a->cost = compute_cost(a->power_kw, a->duration_hours, a->assigned_hour);
    num_appliances++;
    printf("  [OK] Appliance '%s' added.\n", a->name);
}

int main() {
    init_tariff();
    load_sample_appliances();

    int   choice;
    float original_bill  = 0.0f;
    float optimized_bill = 0.0f;

    printf("\n");
    printf("  **********************************************************\n");
    printf("  *        SMART ELECTRICITY BILL OPTIMIZER                *\n");
    printf("  *        Team: Code Crafters  |  DAA Project             *\n");
    printf("  **********************************************************\n");

    while (1) {
        printf("\n  ==================== MAIN MENU ==========================\n");
        printf("  1. Show Tariff Table\n");
        printf("  2. Calculate Original Bill\n");
        printf("  3. Run Greedy Scheduler         (DAA - Greedy)\n");
        printf("  4. Calculate Optimized Bill\n");
        printf("  5. Budget Optimizer - DP Knapsack (DAA - DP)\n");
        printf("  6. View Savings Report\n");
        printf("  7. Add Custom Appliance\n");
        printf("  8. Time Complexity Summary\n");
        printf("  9. Run Full Optimization        (Steps 1 to 6)\n");
        printf("  0. Exit\n");
        printf("  =========================================================\n");
        printf("  Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: display_tariff_table(); break;
            case 2: original_bill = calculate_original_bill(); break;
            case 3: greedy_schedule(); break;
            case 4: optimized_bill = calculate_optimized_bill(); break;
            case 5: {
                float budget;
                printf("  Enter daily budget (Rs): ");
                scanf("%f", &budget);
                dp_knapsack(budget);
                break;
            }
            case 6:
                if (original_bill == 0 || optimized_bill == 0)
                    printf("  [!] Please run options 2, 3, and 4 first.\n");
                else
                    savings_report(original_bill, optimized_bill);
                break;
            case 7: add_custom_appliance(); break;
            case 8: time_complexity_summary(); break;
            case 9:
                printf("\n  >>> Running Full Optimization Pipeline...\n");
                display_tariff_table();
                original_bill  = calculate_original_bill();
                greedy_schedule();
                optimized_bill = calculate_optimized_bill();
                savings_report(original_bill, optimized_bill);
                dp_knapsack(original_bill * 0.80f);
                time_complexity_summary();
                break;
            case 0:
                printf("\n  Goodbye! Save energy, save money.\n\n");
                return 0;
            default:
                printf("  [!] Invalid choice. Try again.\n");
        }
    }
    return 0;
}