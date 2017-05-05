/**
 * Copyright @ San Jose State University
 * Research Work done under Prof. Kaikai Liu
 * CMPE Dept
 * @author Unnikrishnan K S <unnikrishnankgs@gmail.com>
 * Low Latency Streamer - Media Server
 */

#include <gst/gst.h>
#include "exp_lls_media_serv.h"
#include <stdio.h>
#define MAX_PIPELINE_STR_LEN (1024)

/**
 * @player:
 * udpsrc address="10.250.33.222" port=5050 ! 'application/x-rtp, media=video,  encoding-name=H264' 
 * ! rtph264depay ! h264parse ! avdec_h264 ! autovideosink
 */

typedef struct
{
    GstElement* pPipeline;
    char pcPipeline[MAX_PIPELINE_STR_LEN];
    GMainLoop* pGMainLoop;
}t_MediaServ;

gboolean media_serv_start(t_MediaServ* apMediaServ)
{
    gboolean res = FALSE;

    if(!apMediaServ)
        goto cleanup;

    GError* error = NULL;
    /** initialize GStreamer and configure the required pipeline */
    gst_init(NULL, NULL);
    snprintf(apMediaServ->pcPipeline, MAX_PIPELINE_STR_LEN, 
        "avfvideosrc capture-screen=true "
        "! vtenc_h264 ! h264parse config-interval=1 disable-passthrough=true "
        "! video/x-h264, stream-format=byte-stream "
        "! rtph264pay ! udpsink host=\"10.250.33.222\" port=5050");
    apMediaServ->pPipeline = gst_parse_launch(apMediaServ->pcPipeline, &error);

    /**  */
    res = gst_element_set_state((GstElement*)(apMediaServ->pPipeline), GST_STATE_PLAYING);

    apMediaServ->pGMainLoop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(apMediaServ->pGMainLoop);

    cleanup:

    return res;
}

gsize lls_media_serv_init(t_LLS_MediaServCfg* apMediaServCfg)
{
    t_MediaServ* pMediaServ = g_malloc0(sizeof(t_MediaServ));
    /** for now do this here
     * TODO move blocking call out 
     */
    media_serv_start(pMediaServ);
    return (gsize)pMediaServ; 
}

void lls_media_serv_deinit(gsize ahMediaServCfg)
{
    return;
}
