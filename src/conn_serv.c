/**
 * Copyright @ San Jose State University
 * Research Work done under Prof. Kaikai Liu
 * CMPE Dept
 * @author Unnikrishnan K S <unnikrishnankgs@gmail.com>
 * Low Latency Streamer - Connection Server
 */
#include "exp_lls_conn_serv.h"

#include "gio/gio.h"

typedef struct
{
    GThread* pThreadServer;
    t_LLS_ConnServCfg cfg;
    GSocket* pServSo;
}t_ConnServ;

gpointer conn_serv_serviceloop(gpointer data);

/** This serves as the initialization routine which:
 * 1) create a thread that wait on a TCP socket which would 
 * listening for incoming connections
 */
gsize lls_conn_serv_init(t_LLS_ConnServCfg* apCSCfg)
{
    t_ConnServ* pCS = NULL;

    if(!apCSCfg)
    {
        goto cleanup;
    }
    
    pCS = g_malloc0(sizeof(t_ConnServ));
    pCS->cfg = *apCSCfg;
    /** create a STREAM socket @ pCS->nServPort and listen on the same
     * to accept any new connection 
     */
    pCS->pServSo = g_socket_new(G_SOCKET_FAMILY_IPV4, G_SOCKET_TYPE_STREAM, G_SOCKET_PROTOCOL_TCP, NULL);
    if(!pCS->pServSo)
    {
        g_error("socket creation error\n");
        goto cleanup;
    }
    /** bind on port nServPort; new scope */
    {
        gboolean ret;
        GInetAddress* pIA = g_inet_address_new_any(G_SOCKET_FAMILY_IPV4);
        GSocketAddress* pSA = g_inet_socket_address_new(pIA, pCS->cfg.nServPort);
        g_object_unref(pIA);
        pIA = NULL;
        ret = g_socket_bind(pCS->pServSo, pSA, TRUE /**< SO_REUSE */, NULL);
        if(!ret)
        {
            g_error("socket bind failed\n");
            goto cleanup;
        }
        g_debug("socket bind success\n");
        g_socket_set_listen_backlog(pCS->pServSo, 0);
        ret = g_socket_listen(pCS->pServSo, NULL);
        if(!ret)
        {
            g_error("socket listen failed\n");
            goto cleanup;
        }
    }

    /** create the thread that set up our connection-listener-server 
     * Let system abort with g_thread_new rather than using g_thread_try_new() 
     */
    pCS->pThreadServer = g_thread_new("cs", conn_serv_serviceloop, pCS);

    return (gsize)pCS;

    cleanup:
    lls_conn_serv_deinit((gsize)pCS);
    return (gsize)NULL;
}

gpointer conn_serv_serviceloop(gpointer data)
{
    t_ConnServ* pCS;
    if(!pCS)
    {
        goto cleanup;
    }

    while(1)
    {
        GSocket* pCliSo = g_socket_accept(pCS->pServSo, NULL, NULL);
        if(!pCliSo)
        {
            g_error("new client socket conn accept failed\n");
            continue;
        }
    }

    cleanup:

    return NULL; 
}

void lls_conn_serv_deinit(gsize ahConnServ)
{
    t_ConnServ* pCS = (t_ConnServ*)ahConnServ;

    if(!ahConnServ)
    {
        goto cleanup;
    }

    g_thread_join(pCS->pThreadServer);
    g_socket_close(pCS->pServSo, NULL);
    g_object_unref(pCS->pServSo);
    g_free(pCS);

    cleanup:

    return;
}
