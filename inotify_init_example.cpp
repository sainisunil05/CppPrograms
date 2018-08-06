#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/inotify.h>

using namespace std;

int event_check (int fd)
{
  fd_set rfds;
  FD_ZERO (&rfds);
  FD_SET (fd, &rfds);
  return select (FD_SETSIZE, &rfds, NULL, NULL, NULL);
}

int main( )
{
        int fd, wd;

        while(true)
        {
                fd = inotify_init();

                if ( fd < 0 )
                        cout << "inotify_init" << endl;

                wd = inotify_add_watch( fd, "file", IN_CLOSE_WRITE);

                if (event_check (fd) > 0)
                        cout << "File edited" << endl;
        }

        inotify_rm_watch( fd, wd );
        close( fd );
}
