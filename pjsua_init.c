#include <pjsua-lib/pjsua.h>

#define THIS_FILE "pjsua_init.c"

#define SIP_DOMAIN	"sip.bssn.go.id"
#define SIP_USER	"test"
#define SIP_PASSWD	"test"


static void handler_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id, pjsip_rx_data *rdata)

{

  pjsua_call_info ci;

  PJ_UNUSED_ARG(acc_id);
  PJ_UNUSED_ARG(rdata);

  pjsua_call_get_info(call_id, &ci);
  PJ_LOG(3,(THIS_FILE, "Incoming call from %.*s!!",
     (int)ci.remote_info.slen,
     ci.remote_info.ptr));

  /* Automatically answer incoming calls with 200/OK */
  pjsua_call_answer(call_id, 200, NULL, NULL);

}


/* Callback called by the library when call's state has changed */
static void on_call_state(pjsua_call_id call_id, pjsip_event *e)
{
    pjsua_call_info ci;

    PJ_UNUSED_ARG(e);

    pjsua_call_get_info(call_id, &ci);
    PJ_LOG(3,(THIS_FILE, "Call %d state=%.*s", call_id,
			 (int)ci.state_text.slen,
			 ci.state_text.ptr));
}

/* Callback called by the library when call's media state has changed */
static void on_call_media_state(pjsua_call_id call_id)
{
    pjsua_call_info ci;

    pjsua_call_get_info(call_id, &ci);

    if (ci.media_status == PJSUA_CALL_MEDIA_ACTIVE) {
	// When media is active, connect call to sound device.
	  pjsua_conf_connect(ci.conf_slot, 0);
	  pjsua_conf_connect(0, ci.conf_slot);
    }
}

int main(int argc, char *argv[])
{

    pj_status_t status;

    /* Create pjsua first! */
    status = pjsua_create();

    if (status != PJ_SUCCESS) {
          pjsua_perror(THIS_FILE, "Error initializing pjsua", status);
          return status;
    }

    pjsua_config cfg;
  	pjsua_logging_config log_cfg;

    /* pjsua_config_default--->pjsua_config */

  	pjsua_config_default(&cfg); //Load PJSUA Configuration pjsua.h

    /*cfg.max_call = 10;*/

    /* Callback Configuration */
    cfg.cb.on_incoming_call = &handler_incoming_call;
  	cfg.cb.on_call_media_state = &on_call_media_state;
  	cfg.cb.on_call_state = &on_call_state;

    /* PJSUA LOGGING Initialization*/
  	pjsua_logging_config_default(&log_cfg);
  	log_cfg.console_level = 4;

    /* PJSUA Initialization */
  	status = pjsua_init(&cfg, &log_cfg, NULL);

    if (status != PJ_SUCCESS) {
          pjsua_perror(THIS_FILE, "Error in pjsua_init()", status);
          return status;
    }

    /* Transport Configuration */
    pjsua_transport_config cfg;
    pjsua_transport_config_default(&cfg);
    cfg.port = 5060;

      /* Transport Initialization */
    status = pjsua_transport_create(PJSIP_TRANSPORT_UDP, &cfg, NULL);
    if (status != PJ_SUCCESS) {
          pjsua_perror(THIS_FILE, "Error creating transport"", status);
          return status;
    }

    /* Initialization is done, now start pjsua */
    status = pjsua_start();

    if (status != PJ_SUCCESS) {
          pjsua_perror(THIS_FILE, "Error starting pjsua"", status);
          return status;
    }

    /* Account Configuration */
    pjsua_acc_config cfg;
    pjsua_acc_config_default(&cfg);

    cfg.id = pj_str("sip:" SIP_USER "@" SIP_DOMAIN);
    cfg.reg_uri = pj_str("sip:" SIP_DOMAIN);
    cfg.cred_count = 1;
    cfg.cred_info[0].realm = pj_str(SIP_DOMAIN);
    cfg.cred_info[0].scheme = pj_str("digest");
    cfg.cred_info[0].username = pj_str(SIP_USER);
    cfg.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
    cfg.cred_info[0].data = pj_str(SIP_PASSWD);

    /* Account Initialization */
    status = pjsua_acc_add(&cfg, PJ_TRUE, &acc_id);

    if (status != PJ_SUCCESS) {
          pjsua_perror(THIS_FILE, "Error adding account", status);
          return status;
    }

    PJ_LOG(3, (THIS_FILE, "Initialization Success"));
    return 0;

}
