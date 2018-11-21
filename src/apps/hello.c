 #include <pj/log.h>

int main()
{
  pj_status_t rc;

  // Error handling omited for clarity

  // Must initialize PJLIB first!
  rc = pj_init();

  PJ_LOG(3, ("main.c", "Hello world!"));

  return 0;
}
