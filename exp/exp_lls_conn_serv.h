/**
 * Copyright @ San Jose State University
 * Research Work done under Prof. Kaikai Liu
 * CMPE Dept
 * @author Unnikrishnan K S <unnikrishnankgs@gmail.com>
 * Low Latency Streamer - Connection Server exported header
 */

#include "glib.h"

typedef struct
{
    guint32 nServPort;
}t_LLS_ConnServCfg;

/**
 * @brief init the LLS Connection Listener
 * @return hConnServ - the handle to the conn listener
 */
gsize lls_conn_serv_init(t_LLS_ConnServCfg* apConnServCfg);
/**
 * @brief deinit the LLS Connection Listener and all associated
 * Network Streamers 
 * This function blocks until the connection server has finished 
 * deinitializing all associated resources
 * @param ahConnServ[IN] The conn_serv handle returned at lls_conn_serv_init
 */
void lls_conn_serv_deinit(gsize ahConnServ);
