#ifndef COLOR_H
#define COLOR_H

/*
**https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
*/

#define DEFAULT "\x1B[0m"

/*
** Directory
** Bold - Bright blue
*/

#define DIRECTORY_COLOR "\x1B[1;94m"

/*
** When other users have write permission on the directory
*/
#define OTHER_USERS_WRITE_PERMISSION_DIRECTORY_COLOR "\x1B[1;94;102m"

/*
** Link
** Bold - cyan
*/
#define LINK_COLOR "\x1B[1;96m"

/*
** When other users have write permission on the directory
*/
#define OTHER_USERS_EXEC_PERMISSION_FILE_COLOR "\x1B[1;92m"

/*
** Character Device
** Bold - right yellow - black background
*/
#define CHARACTER_DEVICE_COLOR "\x1B[1;93;40m"

/*
** Character Device
** Bold - purple
*/
#define SOCKET_COLOR "\x1B[1;95m"

#endif
