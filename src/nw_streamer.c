/**
 * Copyright @ San Jose State University
 * Research Work done under Prof. Kaikai Liu
 * CMPE Dept
 * @author Unnikrishnan K S <unnikrishnankgs@gmail.com>
 * Low Latency Streamer - Network Streamer module
 * @dev-note
 * Hand-shake:
 * At init, we receive a TCP socket connection from the client 
 * over which a hand-shake is performed 
 * - basically where the client shall give its UDP port info
 * For now this module is a UDP streamer
 */

#include "exp_lls_nw_streamer.h"

typedef struct
{
    GThread* pThread;
}t_NwStreamer;

gsize lls_nw_streamer_init(t_LLS_NwStreamerCfg* apNwStreamerCfg)
{
    t_NwStreamer* pNwS = NULL;

    if(!apNwStreamerCfg)
    {
        goto cleanup;
    }

    pNwS = (t_NwStreamer*)g_malloc0(sizeof(t_NwStreamer));

    cleanup:

    return (gsize)pNwS;
}
