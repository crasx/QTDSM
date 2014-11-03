// QTHLM
// Copyright (C) Matthew Ramir. aka "crasx" 2014
//
// Adapted from Source Server Query Library
// Copyright (C) 2005 Pascal Herget
//
//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef QHLPINGSTRUCTS_H
#define QHLPINGSTRUCTS_H


typedef struct
{
    char protocol;
    QString hostname;
    QString map;
    QString game_directory;
    QString game_description;
    unsigned short app_id;
    unsigned char num_players ;
    unsigned char max_players;
    unsigned char num_of_bots;
    bool is_private;
    char os;
    bool password;
    bool secure;
    QString game_version;

    //special ship stuff (id 2400)
    char ship_mode;
    unsigned char ship_whitneses;
    unsigned char ship_duration;

    char extra_data;
    //optional data
    unsigned short port;
    unsigned long long steamid;
    short sourcetv_port;
    QString sourcetv_name;

    QString keywords;
    unsigned long long game_id;
}HL_INFO_REPLY;


typedef struct{
    char index;
    QString name;
    long score;
    float time;
} HL_PLAYER_INFO;

#endif // QHLPINGSTRUCTS_H
