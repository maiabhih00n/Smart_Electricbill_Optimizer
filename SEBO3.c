void greedy_schedule() {
    printf("\n----------------------------------------------------------\n");
    printf("  DAA MODULE 1 -- GREEDY SCHEDULING\n");
    printf("  Strategy : Assign each appliance to cheapest time slot\n");
    printf("  Time Complexity : O(A x H) = O(%d x 24)\n", num_appliances);
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < num_appliances; i++) {
        if (!appliances[i].flexible) continue;

        int   best_hour = appliances[i].assigned_hour;
        float best_cost = compute_cost(appliances[i].power_kw,
                                       appliances[i].duration_hours, best_hour);

        for (int h = 0; h < MAX_HOURS; h++) {
            float c = compute_cost(appliances[i].power_kw,
                                   appliances[i].duration_hours, h);
            if (c < best_cost) { best_cost = c; best_hour = h; }
        }

        printf("  %-16s : %02d:00 -> %02d:00 | Rs %.2f -> Rs %.2f  [%s]\n",
               appliances[i].name,
               appliances[i].assigned_hour, best_hour,
               appliances[i].cost, best_cost,
               best_hour == appliances[i].assigned_hour ? "NO CHANGE" : "RESCHEDULED");

        appliances[i].assigned_hour = best_hour;
        appliances[i].cost          = best_cost;
    }
}