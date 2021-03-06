# ChillyComp

A SourceMod plugin to handle PuGs in TF2

- [ChillyComp](#chillycomp)
  - [Introduction](#introduction)
  - [Features](#features)
  - [Steps](#steps)
  - [Status and Configs](#status-and-configs)
  - [ConVars](#convars)
  - [Commands](#commands)
  - [Dependencies](#dependencies)
  - [Build](#build)
  - [Changelog](#changelog)

## Introduction

This plugin was made to be modular and easily configurable, to help it the plugin is filled with configurable cvars and commands. To keep all the commands and cvars in one place, "cc_" prefix is used instead of "sm_".

## Features

- **Match Status**: The plugin fully manages the status of the match which can be used to execute configs according to the status. Also the status can be used by other plugins.
- **Modular**: The plugin is really modular, each stage can have multiple features or a stage can be done in different ways by just changing a convar.
- **Automated**: The aim of the plugin is to make the matches completely automated without any admin involvement.
- **Easily Configurable**: The plugin is filled with cvars and commands to allow full control over the plugin to make the perfect match for you.
- **Warmup Restart**: The plugin restarts the match during warmup period to help players warmup.
- **Team Limit**: The plugin enforces team size restrictions so that other players cannot join a team for unfair match.
- **Chat Control**: The plugin filters the chat for unnecessary things like cvar change notifications and color chat exploit.
- **Per Player Ready Up**: The plugin forces each player to ready up to ensure no player is inactive.

## Steps

- Step 1: Plugin waits for enough players in each team depending on cc_match_teamsize
- Step 2: Plugin goes into rolling mode
    - Step 2.1: Sends roll message randomly to all players and counts how many players went to team spectator
    - Step 2.2: Last 2 players are made captain for each team
- Step 3: Plugin makes the 2 captains fight
    - Step 3.1 Winner of the fight gets to pick first
- Step 4: Plugin allows captains to pick players via menu or chat
- Step 5: Once enough players are picked or once all players are picked then picking is complete
- Step 6: Wait for players to ready up and start the match
- Step 7: Plugin restarts the match for warmup depending on cc_liverestart
- Step 8: Once all restarts are complete then the match is marked as LIVE
- Step 9: Waits for the match to end
- Step 10: Resets itself once match ends for next match

## Status and Configs

Plugin will automatically execute configs when the status of the match changes, so use the config however you like to control the match.<br>
The config path is configurable with cc_config_path.<br>
<br>
**Example**: If cc_config_path is conpconfig then config path is<br>
"cfg/compconfig/status_live.cfg|

| Status   | File Name       | Code | Description                                                |
| -------- | --------------- | ---- | ---------------------------------------------------------- |
| Initial  | status_initial  | 0    | Initial period of the match                                |
| Rolling  | status_rolling  | 1    | Rolling period of the match                                |
| Fighting | status_fighting | 2    | Fighting period of the match                               |
| Picking  | status_picking  | 3    | Picking period of the match                                |
| Setup    | status_setup    | 4    | After the teams are picked and teams are doing preparation |
| Warmup   | status_warmup   | 5    | Match is being restarted for player warmup                 |
| Live     | status_live     | 6    | Match is live!                                             |
| Post     | status_post     | 7    | Post match completion                                      |

## ConVars

Use this variables in config files to control your match how you want.

| Name                      | Default     | Description                                                                                                                                                                                     |
| ------------------------- | ----------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| cc_enable                 | 1           | Enables or disables the whole plugin<br>0 = Disabled<br>1 = Enabled                                                                                                                             |
| cc_rolling_autostart      | 0           | Should the plugin automatically start when enough players present<br>0 = Disabled<br>1 = Enabled                                                                                                |
| cc_rolling_mode           | 1           | Which rolling mode should the plugin use<br>1 = Spectator Roll: All the players have to roll to spectator team and the last 2 left become captains<br>**NOTE**:*More modes will come in future* |
| cc_config_path            | compconfigs | Which path should plugin use to execute per status configs                                                                                                                                      |
| cc_rolling_penalty_enable | 0           | Should a player be penalized for trying to roll early<br>0 = Disabled<br>1 = Enabled                                                                                                            |
| cc_rolling_penalty_time   | 2           | How many seconds should the penalty last for (in seconds)                                                                                                                                       |
| cc_rolling_fight_health   | 150         | How much health should the captain have during the fight                                                                                                                                        |
| cc_match_status           | 0           | The current status of the match, this is for other plugins to know the status. DO NOT CHANGE THIS IN CONFIG                                                                                   |
| cc_match_teamsize         | 6           | How many players should each team have for the match                                                                                                                                            |
| cc_match_teamlimit        | 1           | Should the teams be limited by the team size (value from cc_match_teamsize)<br>0 = Disabled<br>1 = Enabled                                                                                      |
| cc_match_postcooldown     | 30          | How many seconds should the plugin wait after the match has ended before starting new match (in seconds)                                                                                        |
| cc_warmup_liverestart     | 1           | How many times should the match restart during the warmup process                                                                                                                               |
| cc_chat_blockcolorchat    | 1           | Blocks all the cvar change notify chat<br>0 = Disabled<br>1 = Enabled                                                                                                                           |
| cc_chat_blockcolorchat    | 1           | Blocks all the color chats that can be sent by players due to SCP or CCP exploit<br>0 = Allows color chat<br>1 = Allows only for Admins<br>2 = Blocks for everyone                              |
| cc_setup_perplayerreadyup | 0           | Should each player ready up before the team can ready up<br>0 = Disabled<br>1 = Enabled                                                                                                         |

## Commands

Use these commands to have full control over the plugin.

| Name             | Alias             | Permission   | Stage              | Description                                                                                                                                 |
| ---------------- | ----------------- | ------------ | ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------- |
| pick             | p                 | Team Captain | Picking            | Allows the team captain to pick a player.<br>Usage: pick  {player name / player ID}<br>**NOTE**: *Player ID can be found with list command* |
| list             | -                 | Any Player   | Picking            | Allows the player to see the list of players that have rolled for the match                                                                 |
| ready            | -                 | Any Player   | Setup              | Allows the player to set his status as ready<br>**NOTE**: *This command is only allowed if cc_setup_perplayerreadyup is set to 1*           |
| unready          | -                 | Any Player   | Setup              | Allows the player to set his status as unready<br>**NOTE**: *This command is only allowed if cc_setup_perplayerreadyup is set to 1*         |
| startroll        | -                 | Admin (Ban)  | Initial            | Allows admin to manually start a roll<br>**NOTE**: *This command will not work if auto start feature is enabled*                            |
| mark             | -                 | Admin (Ban)  | Initial - Picking  | Allows admin to mark a player as plus one                                                                                                   |
| restartpicking   | rspicking         | Admin (Ban)  | Picking            | Allows admin to restart the picking stage                                                                                                   |
| changecaptainred | changecapred, ccr | Admin (Ban)  | Fighting           | Allows admin to switch the captain for RED team with another rolled player                                                                  |
| changecaptainblu | changecapblu, ccb | Admin (Ban)  | Fighting           | Allows admin to switch the captain for BLU team with another rolled player                                                                  |
| changeroll       | -                 | Admin (Ban)  | Fighting - Picking | Allows admin to change the roll status of a player                                                                                          |

## Dependencies

- SourceMod 1.9
- Match : https://www.teamfortress.tv/13598/?page=1#post-1
- MoreColors : https://forums.alliedmods.net/showthread.php?t=185016

## Build

```bash
spcomp chillycomp.sp -i include -o dist/chillycomp
```

## Changelog

- 1.0.7
    - Fixed an issue where different amount of server slots would cause an error
    - Added error messages for empty player list and menu commands
    - Path #1
        - Changed the method of captain swap
        - Changed the method of captain death detection
        - Fixed an issue with captains roll
        - Auto create cfg as sourcemod/chillycomp
- 1.0.6
    - Fixed an crash where the plugin tries to check client 0's name and fails
    - Fixed an crash where the plugin tries to check client's name which had special characters
    - Added proper reset methods which caused the plugin to crash after fight
    - Fixed typo in translation file
    - Added ALLOWBOT define to allow bots to take part (for debugging and testing only)
- 1.0.5
    - Fixed an issue where the plugin sets the match state as live when server starts
    - Fixed command block not being read fromm translation file
- 1.0.4
    - Fixed an issue where players were not counted as rolled due to an array issue
    - Fixed captains not being swapped with selected player
    - Added a new condition to startroll command
    - Added post match cooldown timer
- 1.0.3
    - Added per player ready up feature
    - Added new cvar to enable or disable per player ready up
- 1.0.2
    - Added cvar change chat filter
    - Added color chat filter
    - Added new cvars to control chat filters
    - Changed how colors are handled in translations file
    - Moved command block error messages to translation file
- 1.0.1
    - Fixed commands not replying with error messages when used at wrong stage
    - Fixed rolled players not being detected for swap captain menu
    - Changed how rolled players and plus one players are managed
- 1.0.0