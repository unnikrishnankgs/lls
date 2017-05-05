/**
 * Copyright @ San Jose State University
 * Research Work done under Prof. Kaikai Liu
 * CMPE Dept
 * @author Unnikrishnan K S <unnikrishnankgs@gmail.com>
 * 
 */

/** 
 * This application shall be used to create a 
 * low-latency streaming server
 * A server which shall listen on a specific port, say 9090
 * and receive a client's request and receive the UDP port 
 * info via this (we could use RTSP, but for now can start with
 * a barebones TCP recv)
 *
 * When a client join, say client A where his port was communicated as 5050,
 * the server shall immediately start streaming the camera content
 * encoded in a predefined (for now, later communiated over RTSP) 
 * framerate, resolution, 
 * and H.264 configuration (the bitrate, I-frame interval, etc.)
 */


#include "exp_lls_conn_serv.h"
#include "exp_lls_media_serv.h"

typedef struct
{
    gsize hConnServ;
}t_AppCtx;


int main(int argc, char* argv[])
{
    int ret = 0;
    t_AppCtx* pCtx = NULL;
    /** start the connection-server @ port 9090
     * which internally will start the udp-streamer 
     * for each client
     * on disconnection of a client - connection-server shall tear down the 
     * udp-streamer
     */
    /** start the media-server which shall post H.264 data @ configured framerate
     * to all the open udp-streamers
     */
    pCtx = g_malloc0(sizeof(t_AppCtx));
    #if 0
    {
        t_LLS_ConnServCfg csCfg;
        csCfg.nServPort = 9090;
        pCtx->hConnServ = lls_conn_serv_init(&csCfg);
    }
    #endif

    lls_media_serv_init(NULL);

    lls_conn_serv_deinit(pCtx->hConnServ);
    
    return ret;
}
