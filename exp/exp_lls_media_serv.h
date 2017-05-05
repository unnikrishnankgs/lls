/**
 * Copyright @ San Jose State University
 * Research Work done under Prof. Kaikai Liu
 * CMPE Dept
 * @author Unnikrishnan K S <unnikrishnankgs@gmail.com>
 * Low Latency Streamer - Media Server
 */

#include "glib.h"

typedef struct
{
    gdouble nFR; /**< capture framerate; now the screen */
}t_LLS_MediaServCfg;

gsize lls_media_serv_init(t_LLS_MediaServCfg* apMediaServCfg);
void lls_media_serv_deinit(gsize ahMediaServCfg);
