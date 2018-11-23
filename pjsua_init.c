#include <pjsua-lib/pjsua.h>

#define THIS_FILE "pjsua_init.c"

int main(int argc, char *argv[])
{

    pj_status_t status;

    /* Create pjsua first! */
    status = pjsua_create();

    if (status != PJ_SUCCESS) {
          pjsua_perror(THIS_FILE, "Error initializing pjsua", status);
          return status;
    }
    PJ_LOG(3, (THIS_FILE, "Initialization Success"));
    return 0;

}
