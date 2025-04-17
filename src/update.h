
// we do this ifndef (if not defined) so make sure the file is only run once
#ifndef UPDATE_H__

// we then define it so it wont be run again
#define UPDATE_H__

void wifi_setup(void);
void wifi_loop(void);

#endif