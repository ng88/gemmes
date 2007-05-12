/***************************************************************************
 *   This file is part of the 'gemmes' project                             *
 *                                                                         *
 *                                                                         *
 *   Copyright (C) 2007 by                                                 *
 *         GARCH Soufiane                                                  *
 *         GUILLAUME Nicolas <ng@ngsoft-fr.com>                            *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License only.          *
 *   See the COPYING file.                                                 *
 ***************************************************************************/


#ifndef ASSERT_H
#define ASSERT_H

#include <stdio.h>
#include <stdlib.h>




/** check that cond is true, str is displayed if it fails */
#define c_assert2(cond, str) __assert((cond), __LINE__, __FILE__, (str), #cond)

/** check that cond is true, "assertion failed" is displayed if it failed */
#define c_assert(cond) c_assert2((cond), "assertion failed")


/** warm by showing str if cond is not true */
#define c_warning2(cond, str) __warning((cond), __LINE__, __FILE__, (str), #cond)

/** warm by showing "warning" if cond is not true */
#define c_warning(cond) c_warning2((cond), "warning")










#ifndef DISABLE_ASSERT


#define __assert(cond, line, file, str, cond_str) \
          { if(!cond) { fprintf(stderr, "assertion error on `" cond_str "' in " file  " at line %d: %s\n", line, str); abort(); } }
#define __warning(cond, line, file, str, cond_str) \
          { if(!cond) { fprintf(stderr, "warning on `" cond_str "' in " file  " at line %d: %s\n", line, str) ; } }

#else

#define __assert(cond, line, file, str, cond_str)
#define __warning(cond, line, file, str, cond_str)

#endif


#endif
