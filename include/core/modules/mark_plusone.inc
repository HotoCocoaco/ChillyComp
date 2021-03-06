Handle g_bMarkedPlusOnePlayers = INVALID_HANDLE;

int g_iServingMarkMenu = -1;

Menu g_mPlusOneMenu;

public MarkPlusOneMenu(client) {
    g_mPlusOneMenu = new Menu(MarkPlusOneHandler);

    char clientId[128];
    char name[1024];

    g_mPlusOneMenu.SetTitle("Pick Player to toggle Mark");

    for(int i = 1; i < MaxClients; i++) {
        if(IsClientProper(i)) {
            GetClientName(i, name, sizeof(name));
            IntToString(i, clientId, sizeof(clientId));

            char listName[1036];

            Format(listName, sizeof(listName), "%s (%s)", name, IsPlayerPlusOne(i) ? "o" : "x");

            g_mPlusOneMenu.AddItem(clientId, listName);
        }
    }

    g_iServingMarkMenu = client;

    g_mPlusOneMenu.ExitButton = true;
    g_mPlusOneMenu.Display(client, MENU_TIME_FOREVER);
}

public MarkPlusOneHandler(Menu:menu, MenuAction:action, param1, param2) {
    if (action == MenuAction_Select) {
        char clientId[128];

        menu.GetItem(param2, clientId, sizeof(clientId));
        int client = StringToInt(clientId, 10);

        if (IsPlayerPlusOne(client)) {
            SetPlayerPlusOne(client, false);
        } else {
            SetPlayerPlusOne(client, true);
        }

        if (g_iServingMarkMenu > -1) {
            MarkPlusOneMenu(g_iServingMarkMenu);
        }
    } else if (action == MenuAction_Cancel) {
        if (param2 == MenuCancel_Exit) {
            DebugLog("Client %d exited mark menu", param1);

            g_iServingMarkMenu = -1;

            delete g_mPlusOneMenu;
        }

        DebugLog("Client %d's mark menu was cancelled. Reason: %d", param1, param2);
    }
}

ClearPlusOne() {
    for (int i = 1; i < MaxClients; i++) {
        SetPlayerPlusOne(i, false);
    }
}

public Action:Command_MarkPlusOne(client, args) {
    if (GetStatus() > STATE_INITIAL && GetStatus() < STATE_PICKING) {
        CPrintToChat(client, "%s[%s] %t", COLOR_TAG, TAG, "Module-MarkPlusOne-CommandBlocked");

        return Plugin_Handled;
    }

    if (TotalPlayersRolled() == 0) {
        CPrintToChat(client, "%s[%s] %t", COLOR_TAG, TAG, "Module-MarkPlusOne-ListEmpty");

        return Plugin_Handled;        
    }

    MarkPlusOneMenu(client);

    return Plugin_Continue;
}