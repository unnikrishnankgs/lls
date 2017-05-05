/**
 * Copyright @ San Jose State University
 * Research Work done under Prof. Kaikai Liu
 * CMPE Dept
 * @author Unnikrishnan K S <unnikrishnankgs@gmail.com>
 * Low Latency Streamer - Network Streamer module - exported header
 */

#include "glib.h"
#include "gio/gio.h"

typedef struct
{
    GSocket* pCliSo;
}t_LLS_NwStreamerCfg;

gsize lls_nw_streamer_init(t_LLS_NwStreamerCfg* apNwStreamerCfg);
void lls_nw_streamer_deinit(gsize ahNwStreamer);
