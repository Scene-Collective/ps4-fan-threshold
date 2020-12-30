#include "ps4.h"

uint8_t THRESHOLDTEMP = 60;

int _main(struct thread *td) {
  UNUSED(td);

  initKernel();
  initLibc();

  jailbreak();

  initSysUtil();

  int fd = open("/dev/icc_fan", O_RDONLY, 0);
  if (fd <= 0) {
    printf_notification("Unable to Open Fan Settings!");
    return 0;
  }

  char data[10] = {0x00, 0x00, 0x00, 0x00, 0x00, THRESHOLDTEMP, 0x00, 0x00, 0x00, 0x00};
  ioctl(fd, 0xC01C8F07, data);
  close(fd);

  float fahrenheit = ((THRESHOLDTEMP * 9) / 5) + 32;
  printf_notification("Fan Threshold Set to %i°C/%i°F!", THRESHOLDTEMP, (int)fahrenheit);

  return 0;
}
