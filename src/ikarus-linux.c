/*
  Part of: Vicare
  Contents: interface to Linux functions
  Date: Mon Nov  7, 2011

  Abstract



  Copyright (C) 2011, 2012 Marco Maggi <marco.maggi-ipsu@poste.it>

  This program is  free software: you can redistribute  it and/or modify
  it under the  terms of the GNU General Public  License as published by
  the Free Software Foundation, either  version 3 of the License, or (at
  your option) any later version.

  This program  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  General Public License for more details.

  You  should have received  a copy  of the  GNU General  Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "internals.h"
#ifdef HAVE_DIRENT_H
#  include <dirent.h>
#endif
#ifdef HAVE_FCNTL_H
#  include <fcntl.h>
#endif
#ifdef HAVE_SIGNAL_H
#  include <signal.h>
#endif
#ifdef HAVE_TIME_H
#  include <time.h>
#endif
#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif
#ifdef HAVE_SYS_EPOLL_H
#  include <sys/epoll.h>
#endif
#ifdef HAVE_SYS_MMAN_H
#  include <sys/mman.h>
#endif
#ifdef HAVE_SYS_PARAM_H
#  include <sys/param.h>
#endif
#ifdef HAVE_SYS_RESOURCE_H
#  include <sys/resource.h>
#endif
#ifdef HAVE_SYS_STAT_H
#  include <sys/stat.h>
#endif
#ifdef HAVE_SYS_TIME_H
#  include <sys/time.h>
#endif
#ifdef HAVE_SYS_TYPES_H
#  include <sys/types.h>
#endif
#ifdef HAVE_SYS_WAIT_H
#  include <sys/wait.h>
#endif

/* file descriptors */
#define IK_FD_TO_NUM(fd)		IK_FIX(fd)
#define IK_NUM_TO_FD(fd)		IK_UNFIX(fd)

static IK_UNUSED void
feature_failure_ (const char * funcname)
{
  ik_abort("called GNU+Linux specific function, %s", funcname);
}

#define feature_failure(FN)     { feature_failure_(FN); return void_object; }


/** --------------------------------------------------------------------
 ** Process exit status.
 ** ----------------------------------------------------------------- */

ikptr
ikrt_linux_WIFCONTINUED (ikptr fx_status)
{
#ifdef HAVE_WIFCONTINUED
  int   status = IK_UNFIX(fx_status);
  return (WIFCONTINUED(status))? true_object : false_object;
#else
  feature_failure(__func__);
#endif
}

ikptr
ikrt_linux_waitid (ikptr fx_idtype, ikptr fx_id, ikptr struct_info, ikptr fx_options)
{
#ifdef HAVE_WAITID
  idtype_t  idtype  = IK_UNFIX(fx_idtype);
  id_t      id      = IK_UNFIX(fx_id);
  siginfo_t info;
  int       options = IK_UNFIX(fx_options);
  int       retval;
  errno  = 0;
  retval = waitid(idtype, id, &info, options);
  if (0 <= retval) {
    IK_FIELD(struct_info, 0) = IK_FIX(info.si_pid);
    IK_FIELD(struct_info, 1) = IK_FIX(info.si_uid);
    IK_FIELD(struct_info, 2) = IK_FIX(info.si_signo);
    IK_FIELD(struct_info, 3) = IK_FIX(info.si_status);
    IK_FIELD(struct_info, 4) = IK_FIX(info.si_code);
    return struct_info;
  } else {
    return ik_errno_to_code();
  }
#else
  feature_failure(__func__);
#endif
}


/** --------------------------------------------------------------------
 ** Epoll.
 ** ----------------------------------------------------------------- */

ikptr
ikrt_linux_epoll_create (ikptr s_size)
{
#ifdef HAVE_EPOLL_CREATE
  int   size = ik_integer_to_int(s_size);
  int	rv;
  errno = 0;
  rv    = epoll_create(size);
  return (-1 != rv)? IK_FD_TO_NUM(rv) : ik_errno_to_code();
#else
  feature_failure(__func__);
#endif
}
ikptr
ikrt_linux_epoll_create1 (ikptr s_flags)
{
#ifdef HAVE_EPOLL_CREATE1
  int   flags = ik_integer_to_int(s_flags);
  int	rv;
  errno = 0;
  rv    = epoll_create1(flags);
  return (-1 != rv)? IK_FD_TO_NUM(rv) : ik_errno_to_code();
#else
  feature_failure(__func__);
#endif
}


/* end of file */
